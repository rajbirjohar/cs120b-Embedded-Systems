#ifndef Player1BUTTONS_H_
#define Player1BUTTONS_H_

unsigned char player1Left = 0x00;
unsigned char player1Right = 0x00;

enum Player1ButtonsStates
{
    Player1ButtonsWaitState
};
int TickPlayer1Buttons(int state)
{
    switch (state)
    {
    case Player1ButtonsWaitState:
        break;

    default:
        state = Player1ButtonsWaitState;
        break;
    }

    switch (state)
    {
    case Player1ButtonsWaitState:
        player1Left = ~PINB & 0x01;
        player1Right = ~PINB & 0x02;
        break;

    default:
        break;
    }

    return state;
}

#endif /* Player1BUTTONS_H_ */