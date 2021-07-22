#ifndef PLAYER1_H_
#define PLAYER1_H_

#include "P1Buttons.h"

const unsigned char P1pattern = 0x80;              // Player 1's Paddle
const unsigned char P1row[3] = {0xF8, 0xF1, 0xE3}; // Player 1's Paddle Positions
static unsigned char i = 1;

enum P1States
{
    P1WaitState,
    P1LeftState,
    P1RightState,
    P1WaitStateRelease
};
int TickPlayer1(int state)
{
    switch (state)
    {
    case P1WaitState:
        if (p1Left && !p1Right)
        {
            state = P1LeftState;
        }
        else if (!p1Left && p1Right)
        {
            state = P1RightState;
        }
        else
        {
            state = P1WaitState;
        }
        break;

    case P1LeftState:
        if (!p1Left && !p1Right)
        {
            state = P1WaitState;
        }
        else if (p1Left && !p1Right)
        {
            state = P1WaitStateRelease;
        }
        break;

    case P1RightState:
        if (!p1Left && !p1Right)
        {
            state = P1WaitState;
        }
        else if (!p1Left && p1Right)
        {
            state = P1WaitStateRelease;
        }
        break;

    case P1WaitStateRelease:
        if (!p1Left && !p1Right)
        {
            state = P1WaitState;
        }
        else
        {
            state = P1WaitStateRelease;
        }
        break;

    default:
        state = P1WaitState;
        break;
    }

    switch (state)
    {
    case P1WaitState:
        break;

    case P1LeftState:
        if (i <= 0)
        {
            i = 0;
        }
        else
        {
            --i;
        }
        break;

    case P1RightState:
        if (i >= 2)
        {
            i = 2;
        }
        else
        {
            ++i;
        }
        break;

    case P1WaitStateRelease:
        break;

    default:
        break;
    }

    PORTC = P1pattern;
    PORTD = P1row[i];
    return state;
}

#endif /* PLAYER1_H_ */