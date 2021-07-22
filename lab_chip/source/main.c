/*	Author: sjoha005
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *  LINK: https://youtu.be/p7K-HIWsxNI
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "Player1.h"
#include "AI.h"
#include "Ball.h"
#include "scheduler.h"
#include "timer.h"

task tasks[4];

const unsigned char tasksNum = 4;
const unsigned long taskGCDPeriod = 1, p1Period = 5, p1PeriodButtons = 10, AIPeriod = 10, ballPeriod = 500;

int main(void)
{
    DDRB = 0x00;
    PORTB = 0xFF;
    DDRC = 0xFF;
    PORTC = 0x00;
    DDRD = 0xFF;
    PORTD = 0x00;

    tasks[0].state = P1WaitState;
    tasks[0].period = p1Period;
    tasks[0].elapsedTime = tasks[0].period;
    tasks[0].TickFct = &TickPlayer1;

    tasks[1].state = P1ButtonsWaitState;
    tasks[1].period = p1PeriodButtons;
    tasks[1].elapsedTime = tasks[1].period;
    tasks[1].TickFct = &TickP1Buttons;

    tasks[2].state = AIWaitState;
    tasks[2].period = AIPeriod;
    tasks[2].elapsedTime = tasks[2].period;
    tasks[2].TickFct = &TickAI;

    tasks[3].state = P1Start;
    tasks[3].period = ballPeriod;
    tasks[3].elapsedTime = tasks[3].period;
    tasks[3].TickFct = &TickBall;

    PORTC = 0x00;
    PORTD = 0x00;

    TimerSet(taskGCDPeriod);
    TimerOn();

    unsigned char i;
    while (1)
    {
        for (i = 0; i < tasksNum; ++i)
        {
            if (tasks[i].elapsedTime >= tasks[i].period)
            {
                tasks[i].state = tasks[i].TickFct(tasks[i].state);
                tasks[i].elapsedTime = 0;
            }
            tasks[i].elapsedTime += taskGCDPeriod;
        }
        while (!TimerFlag)
            ;
        TimerFlag = 0;
    }
}
