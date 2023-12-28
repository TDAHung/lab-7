/*
 * fsm_snake.h
 *
 *  Created on: Dec 28, 2023
 *      Author: Mr.HUNG
 */

#ifndef INC_FSM_SNAKE_H_
#define INC_FSM_SNAKE_H_

#include "main.h"
#include "software_timer.h"
#include "touch.h"
#include "lcd.h"

enum STATE_SNAKE {
	INIT,
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

enum STATE_SNAKE_GAME{
	INIT_GAME,
	START,
	STOP,
};

void fsm_snake();

#endif /* INC_FSM_SNAKE_H_ */
