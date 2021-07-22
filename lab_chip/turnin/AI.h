#ifndef AI_H_
#define AI_H_

#include "Ball.h"

const unsigned char AIpattern = 0x01; // AI's Paddle
const unsigned char AIrow[3] = {0xF8, 0xF1, 0xE3}; // AI's Paddle Positions
static unsigned char j = 1;

enum AIStates
{
    AIWaitState,
    AILeftState,
    AIRightState
};
int TickAI(int state)
{
    switch (state)
    {
    case AIWaitState:
        if (j == 0)
        {
            if (ballrows[k] == 0xF7 || ballrows[k] == 0xEF)
            {
                state = AILeftState;
            }
            else
            {
                state = AIWaitState;
            }
        }
        else if (j == 1)
        {
            if (ballrows[k] == 0xFE)
            {
                state = AIRightState;
            }
            else if (ballrows[k] == 0xEF)
            {
                state = AILeftState;
            }
            else
            {
                state = AIWaitState;
            }
        }
        else if (j == 2)
        {
            if (ballrows[k] == 0xFD || ballrows[k] == 0xFE)
            {
                state = AIRightState;
            }
            else
            {
                state = AIWaitState;
            }
        }
        break;

    default:
        state = AIWaitState;
        break;
    }

    switch (state)
    {
    case AIWaitState:
        break;

    case AILeftState:
        if (j > 3)
        {
            j = 2;
        }
        else
        {
            ++j;
        }
        break;

    case AIRightState:
        if (j < 1)
        {
            j = 0;
        }
        else
        {
            --j;
        }
        break;

    default:
        break;
    }

    PORTC = AIpattern;
    PORTD = AIrow[j];
    return state;
};

#endif