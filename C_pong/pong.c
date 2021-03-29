#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <curses.h>
#include <termios.h>

#define LIFE_NUM			3
#define MAX_NUM_BALL_DIR 	4
#define OFFSET_X 			3
#define OFFSET_Y 			6
#define PADDEL_LEN 			4
#define BALL_SYM			"O"
#define PADDLE_SYM			"#"
#define MIN_SPEED			1000

typedef enum eDir
{
	STOP = 0,
	UPLEFT = 1,
	DOWNLEFT = 2,
	UPRIGHT = 3,
	DOWNRIGHT = 4,
	LEFT = 5,
	RIGHT = 6,
	DOWN = 7,
	UP = 8
} eDir;

typedef struct ball_t
{
	eDir dir;
	int x, y;
} ball_t;

typedef struct paddle_t
{
	eDir dir;
	int x, y;
} paddle_t;

typedef struct wall_t
{
	int offset_x, offset_y, len_x, len_y;
	uint64_t clk;
} wall_t;

static ball_t g_ball;
static paddle_t g_paddle;
static wall_t g_wall;

static uint64_t get_time_stamp()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec*(uint64_t)1000000+tv.tv_usec;
}

static eDir random_direction(void)
{
	return (eDir)((rand()%MAX_NUM_BALL_DIR) + 1);
}

static void move_paddle(paddle_t *p_paddle)
{
	switch (p_paddle->dir)
	{
		case DOWN:
			if (p_paddle->x+PADDEL_LEN < g_wall.offset_x + g_wall.len_x)
			{
				mvprintw(p_paddle->x, p_paddle->y, " ");
				p_paddle->x++;
				mvprintw(p_paddle->x+PADDEL_LEN-1, p_paddle->y, PADDLE_SYM);
			}
			break;
		case UP:
			if (p_paddle->x > g_wall.offset_x+1)
			{
				mvprintw(p_paddle->x+PADDEL_LEN-1, p_paddle->y, " ");
				p_paddle->x--;
				mvprintw(p_paddle->x, p_paddle->y, PADDLE_SYM);
			}
			break;
		default:
			break;
	}
	p_paddle->dir = STOP;
	refresh();
}

static void move_ball(ball_t *p_ball)
{
	mvprintw(p_ball->x, p_ball->y, " ");
	/* hide the input key */
	if (p_ball->y+2 == g_wall.offset_y + g_wall.len_y)
		mvprintw(p_ball->x, p_ball->y+1, PADDLE_SYM);
	else
		mvprintw(p_ball->x, p_ball->y+1, " ");
	switch (p_ball->dir)
	{
		case STOP:
			break;
		case UPLEFT:
			p_ball->y--; p_ball->x--;
			break;
		case DOWNLEFT:
			p_ball->y--; p_ball->x++;
			break;
		case UPRIGHT:
			p_ball->y++; p_ball->x--;
			break;
		case DOWNRIGHT:
			p_ball->y++; p_ball->x++;
			break;
		default:
			break;
	}
	mvprintw(p_ball->x, p_ball->y, BALL_SYM);
	refresh();
}

static void draw_map(int x, int y, int ball_left)
{
	/* draw status */
	char temp_str[50];
	move(OFFSET_X, OFFSET_Y);
	memset(temp_str, 0 ,sizeof(temp_str));
	sprintf(temp_str, "BALLS LEFT: %d", ball_left);
	addstr(temp_str);
	move(OFFSET_X, OFFSET_Y + 15);
	memset(temp_str, 0 ,sizeof(temp_str));
	sprintf(temp_str, "TOTAL TIME: %ld", (get_time_stamp()-g_wall.clk)/1000000);
	addstr(temp_str);

	/* draw map */
	g_wall.offset_x = OFFSET_X+1;
	g_wall.offset_y = OFFSET_Y;
	g_wall.len_x = x;
	g_wall.len_y = y;
	move(OFFSET_X+1, OFFSET_Y);
	for (int i = 0; i < y; i++)
		addstr("-");
	for (int i = 1; i <= x; i++)
	{
		move(OFFSET_X+1+i, OFFSET_Y);
		addstr("|");
	}
	move(OFFSET_X+1+x, OFFSET_Y);
	for (int i = 0; i < y; i++)
		addstr("-");
	//mvprintw(g_wall.offset_x + g_wall.len_x, g_wall.offset_y + g_wall.len_y, "&");

	/* draw paddle */
	g_paddle.x = OFFSET_X+x/2;
	g_paddle.y = OFFSET_Y+y-1;
	g_paddle.dir = STOP;
	for (int i = 0; i < PADDEL_LEN; i++)
	{
		move(g_paddle.x+i, g_paddle.y);
		addstr(PADDLE_SYM);
	}

	/* draw ball */
	g_ball.x = OFFSET_X+1+x/2;
	g_ball.y = OFFSET_Y+y/2;
	g_ball.dir = random_direction();
	mvprintw(g_ball.x, g_ball.y, BALL_SYM);
	//refresh();
}

static int game_rules(ball_t *p_ball,
					  paddle_t *p_paddle,
					  wall_t *p_wall,
					  int is_reached_paddle)
{
	/* ball reaches to bottom wall */
	if (p_ball->x+1 >= p_wall->offset_x + p_wall->len_x)
	{
		if (p_ball->dir == DOWNLEFT)
			p_ball->dir = UPLEFT;
		if (p_ball->dir == DOWNRIGHT)
			p_ball->dir = UPRIGHT;
	}

	/* ball reaches to top wall */
	if (p_ball->x-1 <= p_wall->offset_x)
	{
		if (p_ball->dir == UPLEFT)
			p_ball->dir = DOWNLEFT;
		if (p_ball->dir == UPRIGHT)
			p_ball->dir = DOWNRIGHT;
	}

	/* ball reaches to left wall */
	if (p_ball->y-1 <= p_wall->offset_y)
	{
		if (p_ball->dir == UPLEFT)
			p_ball->dir = UPRIGHT;
		if (p_ball->dir == DOWNLEFT)
			p_ball->dir = DOWNRIGHT;
	}

	/* ball reaches to paddle */
	if (p_ball->y+2 >= p_wall->offset_y + p_wall->len_y &&
		is_reached_paddle == 0)
	{
		if (p_ball->x >= p_paddle->x && p_ball->x < p_paddle->x + PADDEL_LEN)
		{
			if (p_ball->dir == DOWNRIGHT)
				p_ball->dir = DOWNLEFT;
			if (p_ball->dir == UPRIGHT)
				p_ball->dir = UPLEFT;
		}
		return 2;
		//p_ball->dir = STOP;
	}

	/* ball out of court */
	if (p_ball->y >= p_wall->offset_y + p_wall->len_y)
		return 0;
	return 1;
}

int main(void)
{
	int ball_left = LIFE_NUM, ret = 0, is_reached_paddle = 0;
	uint32_t speed, count = 0;
	char temp_str[10], c;

	srand(getpid());
	speed = rand()%100 + MIN_SPEED;
	initscr();
	timeout(0);
	clear();
	g_wall.clk = get_time_stamp();
	draw_map(20, 60, ball_left);
	while (1)
	{
		ret = game_rules(&g_ball, &g_paddle, &g_wall, is_reached_paddle);
		if (ret == 0)
		{
			ball_left--;
			if (ball_left == 0)
				break;
			clear();
			draw_map(20, 60, ball_left);
			speed = rand()%100 + MIN_SPEED;
		}
		else if (ret == 2)
		{
			if (speed > 25)
				speed -= (rand()%15 + 10);
			is_reached_paddle = 1;
		}

		if (count >= speed)
		{
			move_ball(&g_ball);
			count = 0;
			is_reached_paddle = 0;
		}
		c = getch();
		if (c == 'k')
		{
			g_paddle.dir = UP;
			move_paddle(&g_paddle);
		}
		else if (c == 'm')
		{
			g_paddle.dir = DOWN;
			move_paddle(&g_paddle);
		}
		else if (c == 'Q')
			break;

		/* show time status */
		move(OFFSET_X, OFFSET_Y + 27);
		addstr("        ");
		move(OFFSET_X, OFFSET_Y + 27);
		memset(temp_str, 0, sizeof(temp_str));
		uint64_t temp_time = (get_time_stamp()-g_wall.clk)/1000000;
		sprintf(temp_str, "%ld:%ld", temp_time/60, temp_time%60);
		addstr(temp_str);

		count++;
		usleep(10);
	}
	mvprintw(g_wall.offset_x + g_wall.len_x/2, g_wall.offset_y + g_wall.len_y/2, "YOU LOSE");
 	endwin();
	return 0;
}