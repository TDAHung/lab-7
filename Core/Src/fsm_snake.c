/*
 * fsm_snake.c
 *
 *  Created on: Dec 28, 2023
 *      Author: Mr.HUNG
 */


#include "fsm_snake.h"

#define RECTANGLE_X1 0
#define RECTANGLE_X2 160
#define RECTANGLE_Y1 0
#define RECTANGLE_Y2 160


enum STATE_SNAKE state = INIT;
enum STATE_SNAKE_GAME state_game = INIT;
int x;
int y;

int check_touch_point(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2){
	if(touch_GetX() >= x1 && touch_GetX() <= x2 && touch_GetY() >= y1 && touch_GetY() <= y2) return 1;
	return 0;
}

void fsm_snake(){
	switch(state){
	case INIT:
		lcd_Clear(BLACK);
		lcd_DrawRectangle(RECTANGLE_X1,RECTANGLE_X2,RECTANGLE_Y1,RECTANGLE_Y2, RED);
		lcd_DrawPoint(x,y,RED);
		x = 80;
		y = 80;
		lcd_ShowStr(20, 30, "UP", RED, BLUE, 2, 0);
		lcd_ShowStr(20, 0, "DOWN", RED, BLUE, 4, 0);
		lcd_ShowStr(30, 15, "LEFT", RED, BLUE, 4, 0);
		lcd_ShowStr(10, 15, "RIGHT", RED, BLUE, 5, 0);
		state = LEFT;
		break;
	case LEFT:
		lcd_DrawPoint(x,y,BLACK);
		x--;
		lcd_DrawPoint(x,y,RED);
		if(touch_IsTouched()){
			if(check_touch_point(20,22,30,40)) state = UP;
		}
		if(touch_IsTouched()){
			if(check_touch_point(20,22,30,40)) state = DOWN;
		}
		if(touch_IsTouched()){
			if(check_touch_point(20,22,30,40)) state = LEFT;
		}
		if(touch_IsTouched()){
			if(check_touch_point(20,22,30,40)) state = RIGHT;
		}
		break;
	case RIGHT:
		lcd_DrawPoint(x,y,BLACK);
		x++;
		lcd_DrawPoint(x,y,RED);
		if(touch_IsTouched()){
			if(check_touch_point(20,22,30,40)) state = UP;
		}
		if(touch_IsTouched()){
			if(check_touch_point(20,22,30,40)) state = DOWN;
		}
		if(touch_IsTouched()){
			if(check_touch_point(20,22,30,40)) state = LEFT;
		}
		if(touch_IsTouched()){
			if(check_touch_point(20,22,30,40)) state = RIGHT;
		}
		break;
	case UP:
		lcd_DrawPoint(x,y,BLACK);
		y++;
		lcd_DrawPoint(x,y,RED);
		if(touch_IsTouched()){
			if(check_touch_point(20,22,30,40)) state = UP;
		}
		if(touch_IsTouched()){
			if(check_touch_point(20,22,30,40)) state = DOWN;
		}
		if(touch_IsTouched()){
			if(check_touch_point(20,22,30,40)) state = LEFT;
		}
		if(touch_IsTouched()){
			if(check_touch_point(20,22,30,40)) state = RIGHT;
		}
		break;

	case DOWN:
		lcd_DrawPoint(x,y,BLACK);
		y--;
		lcd_DrawPoint(x,y,RED);
		if(touch_IsTouched()){
			if(check_touch_point(20,22,30,40)) state = UP;
		}
		if(touch_IsTouched()){
			if(check_touch_point(20,22,30,40)) state = DOWN;
		}
		if(touch_IsTouched()){
			if(check_touch_point(20,22,30,40)) state = LEFT;
		}
		if(touch_IsTouched()){
			if(check_touch_point(20,22,30,40)) state = RIGHT;
		}
		break;
	default:
		break;
	}
}

void fsm_start_snake(){
	switch(state_game){
	case INIT_GAME:
		lcd_Clear(BLACK);
		lcd_ShowStr(20, 30, "START SNAKE GAME", RED, BLUE, 16, 0);
		lcd_DrawRectangle(20,30,36,40, RED);
		if(touch_IsTouched()){
			if(check_touch_point(20,36,30,40)){
				state_game = START;
				state = INIT;
			}
		}
		break;
	case START:
		if(timer_flag[0]){
			fsm_snake();
			setTimer(0,100);
		}
		if(x == 0 || x == 160 || y == 0 || y == 160){
			state_game == STOP;
		}
		break;
	case STOP:
		lcd_Clear(BLACK);
		lcd_ShowStr(20, 30, "YOU LOSE!", RED, BLUE, 9, 0);
		if(timer_flag[1]) {
			state_game = INIT_GAME;
			state = INIT;
			setTimer(1,10000);
		}
		break;
	default:
		break;
	}
}
