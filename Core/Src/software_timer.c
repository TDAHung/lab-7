/*
 * software_timer.c
 *
 *  Created on: Sep 24, 2023
 *      Author: HaHuyen
 */

#include "software_timer.h"

#define TIMER_CYCLE_2 1


uint16_t flag_timer2 = 0;
uint16_t timer2_counter = 0;
uint16_t timer2_MUL = 0;

uint16_t timer_flag[2] = {0,0};
uint16_t timer_counter[2] = {0,0};
uint16_t timer_MUL[2] = {0,0};

void timer_init(){
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start(&htim1);
}

void timer_EnableDelayUs(){
	HAL_TIM_Base_Start(&htim1);
}

void setTimer2(uint16_t duration){
	timer2_MUL = duration/TIMER_CYCLE_2;
	timer2_counter = timer2_MUL;
	flag_timer2 = 0;
}

void setTimer(int index, uint16_t duration){
	timer_MUL[index] = duration/TIMER_CYCLE_2;
	timer_counter[index] = timer_MUL[index];
	timer_flag[index] = 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		if(timer2_counter > 0){
			timer2_counter--;
			if(timer2_counter == 0) {
				flag_timer2 = 1;
				timer2_counter = timer2_MUL;
			}
		}
		for(int i = 0; i < 2; i++){
			if(timer_counter[i] > 0){
				timer_counter[i]--;
				if(timer_counter[i] == 0) {
					timer_flag[i] = 1;
					timer_counter[i] = timer_MUL[i];
				}
			}
		}
		led7_Scan();
	}
}

void delay_us (uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim1,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(&htim1) < us);  // wait for the counter to reach the us input in the parameter
}


