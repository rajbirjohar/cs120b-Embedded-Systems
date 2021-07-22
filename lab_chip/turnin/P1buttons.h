#ifndef P1BUTTONS_H_
#define P1BUTTONS_H_

unsigned char p1Left = 0x00;
unsigned char p1Right = 0x00;

enum P1ButtonsStates
{
    P1ButtonsWaitState
};
int TickP1Buttons(int state)
{
    switch (state)
    {
    case P1ButtonsWaitState:
        break;

    default:
        state = P1ButtonsWaitState;
        break;
    }

    switch (state)
    {
    case P1ButtonsWaitState:
        p1Left = ~PINB & 0x01;
        p1Right = ~PINB & 0x02;
        break;

    default:
        break;
    }

    return state;
}

#endif /* P1BUTTONS_H_ */