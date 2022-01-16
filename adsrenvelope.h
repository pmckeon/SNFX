#ifndef CADSRENVELOPE_H
#define CADSRENVELOPE_H
#include <QTime>

enum filterstate {
    STATE_IDLE,
    STATE_ATTACK,
    STATE_DECAY,
    STATE_SUSTAIN,
    STATE_RELEASE
};

class CADSREnvelope
{
public:
    filterstate state = STATE_IDLE;
    QTime time;

    bool enabled = false;
    int attack;
    int decay;
    int sustain;
    int release;
    int volume;
};

#endif // CADSRENVELOPE_H
