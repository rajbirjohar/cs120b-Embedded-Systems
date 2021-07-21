#ifndef BALL_H_
#define BALL_H_

#include "AI.h"
const unsigned char AIpattern = 0x01; // AI's Paddle
static unsigned char j = 1;

static unsigned char l = 4; // Index for Ballpatterns array
unsigned char ballPattern[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

static unsigned char k = 2; // Index for Ballrows array
unsigned char ballRow[5] = {0xFE, 0xFD, 0xFB, 0xF7, 0xEF};

enum BallState
{
    P1StartState,
    P1BallMiddle,
    P1BallLeft,
    P1BallRight,
    AITurnState,
    AIBallMiddle,
    AIBallLeft,
    AIBallRight,
    P1TurnState,
    GameOverState
};
int TickBall(int state)
{
    // This is in charge of the where the ball hits the paddle
    unsigned char computation;

    switch (state)
    {
    // Game starts with ball moving towards Player 1
    case P1StartState:
        if (ballPattern[l] == P1pattern)
        {
            if (i == 1)
            { // Paddle in the middle
                computation = (ballRow[k] >> i) & 0x07;
                if (computation == 5)
                {
                    state = P1BallMiddle;
                }
            }
            else if (i == 2)
            { // Paddle in the right
                computation = (ballRow[k] >> i) & 0x07;
                if (computation == 6)
                {
                    state = P1BallLeft;
                }
            }
            else if (i == 0)
            { // Paddle in the left
                computation = (ballRow[k] >> i) & 0x07;
                if (computation == 3)
                {
                    state = P1BallRight;
                }
            }
        }
        else
        {
            state = P1StartState;
        }
        break;
    // Cases where it becomes the AI turns after the ball hits the paddle
    case P1BallMiddle:
        if (ballPattern[l] == AIpattern)
        {
            state = AITurnState;
        }
        else
        {
            state = P1BallMiddle;
        }
        break;

    case P1BallLeft:
        if (ballPattern[l] == AIpattern)
        {
            state = AITurnState;
            break;
        }

        if (ballRow[k] == 0xFE)
        {
            state = P1BallRight;
        }
        else
        {
            state = P1BallLeft;
        }
        break;

    case P1BallRight:
        if (ballPattern[l] == AIpattern)
        {
            state = AITurnState;
            break;
        }

        if (ballRow[k] == 0xEF)
        {
            state = P1BallLeft;
        }
        else
        {
            state = P1BallRight;
        }
        break;
    // It is now the AI's turn
    case AITurnState:
        if (j == 1)
        {
            if (ballRow[k] == 0xFE || ballRow[k] == 0xEF)
            {
                state = GameOverState;
            }
            else
            {
                computation = (ballRow[k] >> j) & 0x07;
                if (computation == 3)
                {
                    state = AIBallRight;
                }
                else if (computation == 5)
                {
                    state = AIBallMiddle;
                }
                else if (computation == 6)
                {
                    state = AIBallLeft;
                }
            }
        }
        else if (j == 0)
        {
            if (ballRow[k] == 0xF7 || ballRow[k] == 0xEF)
            {
                state = GameOverState;
            }
            else
            {
                computation = ballRow[k] & 0x07;
                if (computation == 3)
                {
                    state = AIBallRight;
                }
                else if (computation == 5)
                {
                    state = AIBallMiddle;
                }
                else if (computation == 6)
                {
                    state = AIBallLeft;
                }
            }
        }
        else if (j == 2)
        {
            if (ballRow[k] == 0xFE || ballRow[k] == 0xFD)
            {
                state = GameOverState;
            }
            else
            {
                computation = (ballRow[k] >> j) & 0x07;
                if (computation == 3)
                {
                    state = AIBallRight;
                }
                else if (computation == 5)
                {
                    state = AIBallMiddle;
                }
                else if (computation == 6)
                {
                    state = AIBallLeft;
                }
            }
        }
        break;
    // Cases where the ball will hit AI's paddle
    case AIBallMiddle:
        if (ballPattern[l] == P1pattern)
        {
            state = P1TurnState;
        }
        else
        {
            state = AIBallMiddle;
        }
        break;

    case AIBallRight:
        if (ballPattern[l] == P1pattern)
        {
            state = P1TurnState;
            break;
        }

        if (ballRow[k] == 0xEF)
        {
            state = AIBallLeft;
        }
        else
        {
            state = AIBallRight;
        }
        break;

    case AIBallLeft:
        if (ballPattern[l] == P1pattern)
        {
            state = P1TurnState;
            break;
        }

        if (ballRow[k] == 0xFE)
        {
            state = AIBallRight;
        }
        else
        {
            state = AIBallLeft;
        }
        break;
    // Cases where it is now the players turn
    case P1TurnState:
        if (i == 1)
        {
            if (ballRow[k] == 0xFE || ballRow[k] == 0xEF)
            {
                state = GameOverState;
            }
            else
            {
                computation = (ballRow[k] >> i) & 0x07;
                if (computation == 3)
                {
                    state = P1BallRight;
                }
                else if (computation == 5)
                {
                    state = P1BallMiddle;
                }
                else if (computation == 6)
                {
                    state = P1BallLeft;
                }
            }
        }
        else if (i == 0)
        {
            if (ballRow[k] == 0xF7 || ballRow[k] == 0xEF)
            {
                state = GameOverState;
            }
            else
            {
                computation = ballRow[k] & 0x07;
                if (computation == 3)
                {
                    state = P1BallRight;
                }
                else if (computation == 5)
                {
                    state = P1BallMiddle;
                }
                else if (computation == 6)
                {
                    state = P1BallLeft;
                }
            }
        }
        else if (i == 2)
        {
            if (ballRow[k] == 0xFE || ballRow[k] == 0xFD)
            {
                state = GameOverState;
            }
            else
            {
                computation = (ballRow[k] >> i) & 0x07;
                if (computation == 3)
                {
                    state = P1BallRight;
                }
                else if (computation == 5)
                {
                    state = P1BallMiddle;
                }
                else if (computation == 6)
                {
                    state = P1BallLeft;
                }
            }
        }
        break;
    // Case where the game ends
    case GameOverState:
        if ((~PINB & 0x04) == 0x04)
        {
            l = 4;
            k = 2;
            state = P1StartState;
        }
        else
        {
            state = GameOverState;
        }
        break;

    default:
        state = P1StartState;
        break;
    }

    switch (state)
    {
    case P1StartState:
        --l;
        break;
    // Shift ball to the right once
    case P1BallMiddle:
        ++l;
        break;
    // Shift ball to the right once.
    // Shift ball row upward
    case P1BallLeft:
        ++l;
        --k;
        break;

    case P1BallRight:
        ++l;
        ++k;
        break;

    case AITurnState:
        break;
    // Shift ball to the right once
    case AIBallMiddle:
        --l;
        break;
    // Shift ball to the right once.
    // Shift ball row upward
    case AIBallLeft:
        --l;
        --k;
        break;
    // Shift ball to the right once.
    // Shift ball row upward
    case AIBallRight:
        --l;
        ++k;
        break;
    case P1TurnState:
        break;

    case GameOverState:
        break;

    default:
        break;
    }

    PORTC = ballPattern[l];
    PORTD = ballRow[k];
    return state;
};

#endif /* BALL_H_ */