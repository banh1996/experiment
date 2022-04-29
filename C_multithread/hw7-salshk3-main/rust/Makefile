FLOORS?=28
ELEVATORS?=4
CAPACITY?=3
PASSENGERS?=50
LOG_LEVEL?=5
CFLAGS=-lpthread -lncurses -ldl
FILES=elevators

elevators: elevator/src/lib.rs ../C/main.c
	LOG_LEVEL=$(LOG_LEVEL) FLOORS=$(FLOORS) ELEVATORS=$(ELEVATORS) PASSENGERS=$(PASSENGERS) CAPACITY=$(CAPACITY) envsubst < elevator/src/constants.tmpl > elevator/src/constants.rs
	cd elevator; cargo build; cd ..
	gcc -DFLOORS=$(FLOORS) -DELEVATORS=$(ELEVATORS) -DLOG_LEVEL=$(LOG_LEVEL) -DCAPACITY=$(CAPACITY) -DPASSENGERS=$(PASSENGERS) -I../C -Lelevator/target/debug ../C/main.c -o $@ -lelevator $(CFLAGS)

clean:
	rm -f $(FILES) *.o 
	cd elevator ; cargo clean ; rm src/constants.rs; cd ..
