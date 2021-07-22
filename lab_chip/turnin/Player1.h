#ifndef PLAYER1_H_
#define PLAYER1_H_

#include "Player1Buttons.h"
// Player's possible positions
const unsigned char Player1paddle = 0x80, Player1row[3] = {0xF8, 0xF1, 0xE3};
static unsigned char i = 1;

enum Player1States
{
    Player1WaitState,
    Player1LeftState,
    Player1RightState,
    Player1WaitStateRelease
};
int TickPlayer1(int state)
{
    switch (state)
    {
    case Player1WaitState:
        if (player1Left && !player1Right)
        {
            state = Player1LeftState;
        }
        else if (!player1Left && player1Right)
        {
            state = Player1RightState;
        }
        else
        {
            state = Player1WaitState;
        }
        break;

    case Player1LeftState:
        if (!player1Left && !player1Right)
        {
            state = Player1WaitState;
        }
        else if (player1Left && !player1Right)
        {
            state = Player1WaitStateRelease;
        }
        break;

    case Player1RightState:
        if (!player1Left && !player1Right)
        {
            state = Player1WaitState;
        }
        else if (!player1Left && player1Right)
        {
            state = Player1WaitStateRelease;
        }
        break;

    case Player1WaitStateRelease:
        if (!player1Left && !player1Right)
        {
            state = Player1WaitState;
        }
        else
        {
            state = Player1WaitStateRelease;
        }
        break;

    default:
        state = Player1WaitState;
        break;
    }

    switch (state)
    {
    case Player1WaitState:
        break;

    case Player1LeftState:
        if (i <= 0)
        {
            i = 0;
        }
        else
        {
            --i;
        }
        break;

    case Player1RightState:
        if (i >= 2)
        {
            i = 2;
        }
        else
        {
            ++i;
        }
        break;

    case Player1WaitStateRelease:
        break;

    default:
        break;
    }

    PORTC = Player1paddle;
    PORTD = Player1row[i];
    return state;
}

#endif /* PLAYER1_H_ */