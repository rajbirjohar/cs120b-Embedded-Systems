#include <avr/io.h>
#include "scheduler.h"
#include "timer.h"

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

task tasks[1];

const unsigned char tasksNum = 1;
const unsigned long tasksPeriodGCD = 100;
const unsigned long periodMatrixDemo = 100;

//--------------------------------------
// LED Matrix Demo SynchSM
// Period: 100 ms
//--------------------------------------
enum Demo_States
{
    shift
};
int Demo_Tick(int state)
{

    // Local Variables
    static unsigned char pattern = 0x80; // LED pattern - 0: LED off; 1: LED on
    static unsigned char row = 0xFE;     // Row(s) displaying pattern.
                                         // 0: display pattern on row
                                         // 1: do NOT display pattern on row
    // Transitions
    switch (state)
    {
    case shift:
        break;

    default:
        state = shift;
        break;
    }

    // Actions
    switch (state)
    {
    case shift:
        if (row == 0xEF && pattern == 0x01)
        { // Reset demo
            pattern = 0x80;
            row = 0xFE;
        }
        else if (pattern == 0x01)
        { // Move LED to start of next row
            pattern = 0x80;
            row = (row << 1) | 0x01;
        }
        else
        { // Shift LED one spot to the right on current row
            pattern >>= 1;
        }
        break;

    default:
        break;
    }

    PORTC = pattern; // Pattern to display
    PORTD = row;     // Row(s) displaying pattern
    return state;
}

int main(void)
{
    DDRC = 0xFF;
    PORTC = 0x00;
    DDRD = 0xFF;
    PORTD = 0x00;

    tasks[0].state = shift;
    tasks[0].period = periodMatrixDemo;
    tasks[0].elapsedTime = tasks[0].period;
    tasks[0].TickFct = &Demo_Tick;

    PORTC = 0x00;
    PORTD = 0x00;

    TimerSet(tasksPeriodGCD);
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
            tasks[i].elapsedTime += tasksPeriodGCD;
        }

        while (!TimerFlag)
            ;
        TimerFlag = 0;
    }

    return 1;
}
