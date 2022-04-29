#include<ncurses.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<sys/time.h>
#include<pthread.h>
#include<unistd.h>
#include <sched.h>
#include"elevator.h"

WINDOW *displaywin;
WINDOW *logwin;
FILE* logfile;

// when stop == 1, all threads quit voluntarily
static int stop=0;

pthread_mutex_t log_lock;
pthread_barrier_t passengers_ready;

pthread_mutex_t state_lock;

/* This is an internal struct used by the enforcement system 
	 - there is no access to this from hw6.c */
// static struct Elevator {
// 	int floor;	
// 	int open;
// 	int passengers;
// 	int trips;
// } elevators[ELEVATORS];

__thread enum { PASSENGER=1, ELEVATOR=2 } type;
__thread int id;

// state_lock must be held when calling
void elevator_check(int elevator) {
	if(type != ELEVATOR || id != elevator) {
		log(0,"VIOLATION: elevator %d operation attempted on wrong thread!",elevator);
		exit(1);
	}	
	if(elevators[elevator].passengers > MAX_CAPACITY || elevators[elevator].passengers < 0) {
		log(0,"VIOLATION: elevator %d over capacity, or negative passenger count %d!\n",elevator,elevators[elevator].passengers);
		exit(1);
	}
}

void log_msg(int level, char* message) {
	log(level,"%s",message);
}

static void elevator_move_direction_check(int elevator, int direction) {
	pthread_mutex_lock(&state_lock);

	elevator_check(elevator);
	log(8,"Moving elevator %d %s from %d\n",elevator,(direction==-1?"down":"up"),elevators[elevator].floor);
	if(elevators[elevator].open) {
		log(0,"VIOLATION: attempted to move elevator %d with door open.\n", elevator);
		exit(1);
	}	
	if(elevators[elevator].floor >= FLOORS || elevators[elevator].floor < 0) {
		log(0,"VIOLATION: attempted to move elevator %d outside of building!\n", elevator);
		exit(1);
	}	
	pthread_mutex_unlock(&state_lock);
}

void elevator_move_direction(int elevator, int direction) {
	elevator_move_direction_check(elevator,direction);

	sched_yield();
	usleep(DELAY);
	
	elevator_move_direction_check(elevator,direction);
	
	pthread_mutex_lock(&state_lock);
	elevators[elevator].floor+=direction;
	pthread_mutex_unlock(&state_lock);
}

static void elevator_open_door_check(int elevator) {
	pthread_mutex_lock(&state_lock);

	elevator_check(elevator);
	log(9,"Opening elevator %d at floor %d\n",elevator,elevators[elevator].floor);
	if(elevators[elevator].open) {
		log(0,"VIOLATION: attempted to open elevator %d door when already open.\n", elevator);
		exit(1);
	}	
	pthread_mutex_unlock(&state_lock);
}
void elevator_open_door(int elevator) {	
	elevator_open_door_check(elevator);
	usleep(10*DELAY);
	elevator_open_door_check(elevator);

	pthread_mutex_lock(&state_lock);
	elevators[elevator].open=1;
	pthread_mutex_unlock(&state_lock);

}
void elevator_close_door(int elevator) {
	pthread_mutex_lock(&state_lock);

	elevator_check(elevator);
	log(9,"Closing elevator %d at floor %d\n",elevator,elevators[elevator].floor);
	if(!elevators[elevator].open) {
		log(0,"VIOLATION: attempted to close elevator %d door when already closed.\n", elevator);
		exit(1);
	}	
	pthread_mutex_unlock(&state_lock);

	pthread_mutex_lock(&state_lock);
	elevators[elevator].open=0;
	pthread_mutex_unlock(&state_lock);

	sched_yield();
	usleep(10*DELAY);
}

void* start_elevator(void *arg) {
	size_t elevator = (size_t)arg;
	id=elevator;
	type=ELEVATOR;
	struct Elevator *e = &elevators[elevator];
	e->passengers = 0;
	e->trips = 0;
	log(6,"Starting elevator %lu\n", elevator);

	e->floor = 0;//elevator % (FLOORS-1);
	while(!stop) {
		elevator_ready(elevator,e->floor,elevator_move_direction,elevator_open_door,elevator_close_door);
		sched_yield();
	}
}

/* This is an internal struct used by the enforcement system 
	 - there is no access to this from hw6.c. */

// static Passenger passengers[PASSENGERS];

static void passenger_enter_check(int passenger, int elevator) {
		pthread_mutex_lock(&state_lock);

	if(type != PASSENGER || id != passenger) {
		log(0,"VIOLATION: passenger enter for %d attempted on wrong thread!",passenger);
		exit(1);
	}	

	if(passengers[passenger].from_floor != elevators[elevator].floor) {
		log(0,"VIOLATION: let passenger %d on on wrong floor %d!=%d.\n", passengers[passenger].id, passengers[passenger].from_floor, elevators[elevator].floor);
		exit(1);
	}	
	if(!elevators[elevator].open) {
		log(0,"VIOLATION: passenger %d walked into a closed door entering elevator %d.\n", passengers[passenger].id, elevator);
		exit(1);
	}	
	if(elevators[elevator].passengers == MAX_CAPACITY) {
		log(0,"VIOLATION: passenger %d attempted to board full elevator %d.\n", passengers[passenger].id, elevator);
		exit(1);
	}	
	if(passengers[passenger].state!=WAITING) {
		log(0,"VIOLATION: passenger %d told to board elevator %d, was not waiting.\n", passengers[passenger].id, elevator);
		exit(1);
	}
	pthread_mutex_unlock(&state_lock);
}
void passenger_enter(int passenger, int elevator) {
	passenger_enter_check(passenger,elevator);
	sched_yield();
	usleep(DELAY);
	passenger_enter_check(passenger,elevator);

	pthread_mutex_lock(&state_lock);
	log(6,"Passenger %d got on elevator %d at %d, requested %d\n", passengers[passenger].id, elevator, passengers[passenger].from_floor, elevators[elevator].floor);

	elevators[elevator].passengers++;
	passengers[passenger].in_elevator = elevator;
	passengers[passenger].state = ENTERED;
	pthread_mutex_unlock(&state_lock);
}

static void passenger_exit_check(int passenger, int elevator) {
	pthread_mutex_lock(&state_lock);

	if(type != PASSENGER || id != passenger) {
		log(0,"VIOLATION: passenger exit for %d attempted on wrong thread!",passenger);
		exit(1);
	}	
	if(passengers[passenger].in_elevator != elevator) {
		log(0,"VIOLATION: passenger %d told to get off elevator %d, was in elevator %d.\n", passengers[passenger].id, elevator, passengers[passenger].in_elevator);
		exit(1);
	}	
	
	if(passengers[passenger].to_floor != elevators[elevator].floor) {
		log(0,"VIOLATION: let passenger %d off on wrong floor %d!=%d.\n", passengers[passenger].id, passengers[passenger].to_floor, elevators[elevator].floor);
		exit(1);
	}	
	if(!elevators[elevator].open) {
		log(0,"VIOLATION: passenger %d walked into a closed door leaving elevator %d.\n", passengers[passenger].id, elevator);
		exit(1);
	}
	if(passengers[passenger].state!=ENTERED) {
		log(0,"VIOLATION: passenger %d told to board elevator %d, was not waiting.\n", passengers[passenger].id, elevator);
		exit(1);
	}
	
	pthread_mutex_unlock(&state_lock);
}
void passenger_exit(int passenger, int elevator) {
	passenger_exit_check(passenger,elevator);
	sched_yield();
	usleep(DELAY);
	passenger_exit_check(passenger,elevator);

	pthread_mutex_lock(&state_lock);
	log(6,"Passenger %d got off elevator %d at %d, requested %d\n", passengers[passenger].id, elevator, passengers[passenger].to_floor, elevators[elevator].floor);

	elevators[elevator].passengers--;
	elevators[elevator].trips++;
	passengers[passenger].in_elevator = -1;
	passengers[passenger].at_floor = elevators[elevator].floor;
	passengers[passenger].state = EXITED;
	pthread_mutex_unlock(&state_lock);
}

void* start_passenger(void *arg) {
	size_t passenger=(size_t)arg;
	id = passenger;
	type = PASSENGER;

	struct Passenger *p = &passengers[passenger];
	log(6,"Starting passenger %lu\n", passenger);
	p->from_floor = random()%FLOORS;
	p->at_floor = p->from_floor;
	p->in_elevator = -1;
	p->id = passenger;
	int trips = TRIPS_PER_PASSENGER;

	pthread_barrier_wait(&passengers_ready);

	while(!stop && trips-- > 0) {
		pthread_mutex_lock(&state_lock);

		p->to_floor = random() % FLOORS;
		log(6,"Passenger %lu requesting %d->%d\n",
						passenger,p->from_floor,p->to_floor);

		struct timeval before;
		gettimeofday(&before,0);
		passengers[passenger].state=WAITING;
		pthread_mutex_unlock(&state_lock);

		passenger_request(passenger, p->from_floor, p->to_floor, passenger_enter, passenger_exit);
		if (p->at_floor != p->to_floor){
			log(0,"VIOLATION: Passenger %d wanted to get to floor %d but ended up on floor %d\n",p->id,p->to_floor,p->at_floor);
			exit(1);
		}
		struct timeval after;
		gettimeofday(&after,0);
		int ms = (after.tv_sec - before.tv_sec)*1000 + (after.tv_usec - before.tv_usec)/1000;
		log(1,"Passenger %lu trip duration %d ms, %d slots\n",passenger,ms,ms*1000/DELAY);

		pthread_mutex_lock(&state_lock);
		p->from_floor = p->to_floor;
		pthread_mutex_unlock(&state_lock);

		usleep(DELAY); // sleep for some time
	}
}

void* draw_state(void *ptr) {

	while(1) {
		pthread_mutex_lock(&state_lock);
		pthread_mutex_lock(&log_lock);

		//printf("\033[2J\033[1;1H");
		//wclear(displaywin);
		wmove(displaywin,0,0);

		for(int floor=FLOORS-1;floor>=0;floor--) {
      		wprintw(displaywin,"%d\t",floor);
			for(int el=0;el<ELEVATORS;el++) {

				if(elevators[el].floor==floor) 	wprintw(displaywin," %c ",(elevators[el].open?'O':'_'));
				else
					wprintw(displaywin," %c ",elevators[el].floor>floor?'|':' ');
			}
 			wprintw(displaywin,"    ");
			int align = 15*ELEVATORS;
			for(int p=0;p<PASSENGERS;p++)
				if((passengers[p].state==ENTERED && elevators[passengers[p].in_elevator].floor==floor)) {
					align-=5;
					wprintw(displaywin,"->%02d ",passengers[p].to_floor);
				}
			while(align-->0) wprintw(displaywin," ");
			wprintw(displaywin,"X ");
			for(int p=0;p<PASSENGERS;p++)
				if((passengers[p].from_floor==floor && passengers[p].state==WAITING)) {
					wprintw(displaywin,"->%d ",passengers[p].to_floor);
				}
			wprintw(displaywin,"\n");
		}
		wrefresh(displaywin);
		pthread_mutex_unlock(&state_lock);
		pthread_mutex_unlock(&log_lock);

		usleep(DELAY);
	}
}

int main(int argc, char** argv) {
	logfile = fopen("elevator.log","w");

	WINDOW *mainwin = initscr();
	cbreak(); noecho();
    displaywin = subwin(mainwin, FLOORS+2,0,0,0);
    logwin = subwin(mainwin, LINES-FLOORS-2, 0, FLOORS+2, 0);
    scrollok(logwin,true);
	refresh();
	
	struct timeval before;
	gettimeofday(&before,0);
	pthread_mutex_init(&log_lock,0);
	pthread_mutex_init(&state_lock,0);

	pthread_barrier_init(&passengers_ready, 0, PASSENGERS+1);

	scheduler_init();

	pthread_t passenger_t[PASSENGERS];
	for(size_t i=0;i<PASSENGERS;i++)  {
		pthread_create(&passenger_t[i],NULL,start_passenger,(void*)i);	
	}

	// this is not necessary for a correct solution, it is just here to keep things orderly.
	pthread_barrier_wait(&passengers_ready);

	pthread_t elevator_t[ELEVATORS];
	for(size_t i=0;i<ELEVATORS;i++) {
		pthread_create(&elevator_t[i],NULL,start_elevator,(void*)i);
	}
	

#ifndef NODISPLAY
	pthread_t draw_t;
	if(pthread_create(&draw_t,NULL,draw_state,NULL)) {
		perror("creating display thread");
		exit(1);
	}
#endif 

	/* wait for all trips to complete */
	for(int i=0;i<PASSENGERS;i++) 
		pthread_join(passenger_t[i],NULL);
	stop=1;
	for(int i=0;i<ELEVATORS;i++) 
		pthread_join(elevator_t[i],NULL);

	struct timeval after;
	gettimeofday(&after,0);

	log(0,"All %d passengers finished their %d trips each.\n",PASSENGERS,TRIPS_PER_PASSENGER);
	int ms = (after.tv_sec-before.tv_sec)*1000+(after.tv_usec-before.tv_usec)/1000;
	log(0,"Total time elapsed: %d ms, %d slots\n",ms,ms*1000/DELAY);

	endwin();
}

