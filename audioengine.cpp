#include "audioengine.h"
#include <QString>
#include <math.h>

#define SAMPLE_RATE (44100)
#define PAL_CLOCK (3546893)
static SN76489_Context *PSG;

static int paPSGCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
        SN76489_Context *data = reinterpret_cast<SN76489_Context*>(userData);
        INT16 **out = reinterpret_cast<INT16**>(outputBuffer);
        (void) inputBuffer; /* Prevent unused variable warning. */

        SN76489_Update(data, out, 1);

        return 0;
}

CAudioEngine::CAudioEngine()
{
    PaError err;

    err = Pa_Initialize();
    if( err != paNoError )
    {
        qDebug() << "Error: Initialize PortAudio";
        qDebug() <<  Pa_GetErrorText(err);
    }

    PSG = SN76489_Init(PAL_CLOCK,SAMPLE_RATE);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CAudioEngine::timerCallback);
    timer->start(0);

    err = Pa_OpenDefaultStream( &stream,
                                   0,          /* no input channels */
                                   2,          /* stereo output */
                                   paInt16|paNonInterleaved,  /* 16 bit Integer output */
                                   SAMPLE_RATE,
                                   1,        /* frames per buffer, i.e. the number 256
                                                      of sample frames that PortAudio will
                                                      request from the callback. Many apps
                                                      may want to use
                                                      paFramesPerBufferUnspecified, which
                                                      tells PortAudio to pick the best,
                                                      possibly changing, buffer size.*/
                                   paPSGCallback, /* this is your callback function */
                                   PSG ); /*This is a pointer that will be passed to
                                                      your callback*/
    if( err != paNoError )
    {
        qDebug() << "Error: Open Stream";
        qDebug() <<  Pa_GetErrorText(err);
    }

    err = Pa_StartStream( stream );
    if( err != paNoError )
    {
        qDebug() << "Error: Play";
        qDebug() <<  Pa_GetErrorText(err);
    }

    toneEnvelope[0].attack = 50;
    toneEnvelope[0].decay = 0;
    toneEnvelope[0].sustain = 5;
    toneEnvelope[0].release = 6000;
    toneEnvelope[0].volume = 0;

    toneEnvelope[1].attack = 50;
    toneEnvelope[1].decay = 0;
    toneEnvelope[1].sustain = 5;
    toneEnvelope[1].release = 6000;
    toneEnvelope[1].volume = 0;

    toneEnvelope[2].attack = 50;
    toneEnvelope[2].decay = 0;
    toneEnvelope[2].sustain = 5;
    toneEnvelope[2].release = 6000;
    toneEnvelope[2].volume = 0;

    toneEnvelope[3].attack = 50;
    toneEnvelope[3].decay = 0;
    toneEnvelope[3].sustain = 5;
    toneEnvelope[3].release = 6000;
    toneEnvelope[3].volume = 0;

    // Create our worker object for pattern playback/recording and attach to a new thread.
    sequencer = new CSequencer;
    sequencer->moveToThread(&sequencerThread);
    connect(&sequencerThread, &QThread::started, sequencer, &CSequencer::runSequencer);
    connect(sequencer, &CSequencer::sendNote, this, &CAudioEngine::recieveNote);
    sequencerThread.start();

    SN76489_Write(PSG, 0xe5); // White medium
    setChannelVolume(3, 15);
}

CAudioEngine::~CAudioEngine()
{
    PaError err;

    err = Pa_StopStream( stream );

    if( err != paNoError )
    {
        qDebug() << "Error: Stop";
        qDebug() <<  Pa_GetErrorText(err);
    }

    err = Pa_CloseStream( stream );
    if( err != paNoError )
    {
        qDebug() << "Error: Close Stream";
        qDebug() <<  Pa_GetErrorText(err);
    }

    SN76489_Shutdown(PSG);

    err = Pa_Terminate();
    if( err != paNoError )
    {
        qDebug() << "Error: Terminate PortAudio";
        qDebug() <<  Pa_GetErrorText(err);
    }

    qDebug() << "Quitting thread";
    sequencer->Exit();
    sequencerThread.quit();
    sequencerThread.wait(10000);
    qDebug() << "Exited Sucessfully";
}

void CAudioEngine::noteOn()
{
    //SN76489_Write(PSG, 0x8e); // Latch ch1 tone
    //SN76489_Write(PSG, 0xf); // ch1 tone data
    //SN76489_Write(PSG, 0x2f); // ch1 tone data

    //PlayNote(0, "G", 3);
    //PlayNote(1, "G#", 3);
    //PlayNote(2, "D", 4);

    /*SN76489_Write(PSG, 0xae); // Latch ch2 tone
    SN76489_Write(PSG, 0xd); // ch2 tone data

    SN76489_Write(PSG, 0xce); // Latch ch3 tone
    SN76489_Write(PSG, 0xf); // ch3 tone data*/
    //SN76489_Write(PSG, 0xa); // ch3 tone data

    //SN76489_Write(PSG, 0xe0); // Periodic low
    //SN76489_Write(PSG, 0xe1); // Periodic medium
    //SN76489_Write(PSG, 0xe2); // Periodic high
    SN76489_Write(PSG, 0xe3); // Periodic ch3 (Bass)
    //SN76489_Write(PSG, 0xe4); // White low
    //SN76489_Write(PSG, 0xe5); // White medium
    //SN76489_Write(PSG, 0xe6); // White high
    //SN76489_Write(PSG, 0xe7); // white ch3 (Noise/Drum)

    for(int i=0; i < 4; ++i)
    {
        if(toneEnvelope[i].enabled)
        {
            toneEnvelope[i].state = STATE_ATTACK;
            toneEnvelope[i].time.start();
        }
    }
}

void CAudioEngine::noteOff()
{
    for(int i=0; i < 4; ++i)
    {
        if(toneEnvelope[i].state != STATE_IDLE)
        {
            toneEnvelope[i].state = STATE_RELEASE;
            toneEnvelope[i].time.start();
        }
    }
}

void CAudioEngine::playSong()
{
    sequencer->Play();
}

void CAudioEngine::stopSong()
{
    sequencer->Stop();
}

void CAudioEngine::pauseSong()
{
    sequencer->Pause();
}

void CAudioEngine::timerCallback()
{
    for(int i=0; i < 4; ++i)
    {
        switch(toneEnvelope[i].state)
        {
        case STATE_IDLE:
            setChannelVolume(i, 15);
            break;
        case STATE_ATTACK:
            if(toneEnvelope[i].attack == 0)
            {
                toneEnvelope[i].volume = 0;
                setChannelVolume(i, 0);
                toneEnvelope[i].state = STATE_DECAY;
                toneEnvelope[i].time.start();
            }
            else if(toneEnvelope[i].time.elapsed() <= toneEnvelope[i].attack) {
                float step = 15.0f / toneEnvelope[i].attack;
                int vol = static_cast<int>(round(15.0f - (step * toneEnvelope[i].time.elapsed())));
                toneEnvelope[i].volume = vol;
                setChannelVolume(i, vol);
            }
            else {
                toneEnvelope[i].state = STATE_DECAY;
                toneEnvelope[i].time.start();
            }
            break;
        case STATE_DECAY:
            if(toneEnvelope[i].decay == 0)
            {
                toneEnvelope[i].volume = toneEnvelope[i].sustain;
                setChannelVolume(i, toneEnvelope[i].volume);
                toneEnvelope[i].state = STATE_SUSTAIN;
            }
            else if(toneEnvelope[i].time.elapsed() <= toneEnvelope[i].decay)
            {
                float step = static_cast<float>(toneEnvelope[i].sustain / static_cast<float>(toneEnvelope[i].decay));
                int vol = static_cast<int>(round(step * toneEnvelope[i].time.elapsed()));
                toneEnvelope[i].volume = vol;
                setChannelVolume(i, vol);
                //qDebug() << QString::number(vol);
            }
            else
            {
                toneEnvelope[i].state = STATE_SUSTAIN;
                qDebug() << "SUSTAIN";
            }
            break;
        case STATE_SUSTAIN:
            break;
        case STATE_RELEASE:
            if(toneEnvelope[i].release == 0)
            {
                setChannelVolume(i, 15);
                toneEnvelope[i].state = STATE_IDLE;
            }
            else if(toneEnvelope[i].time.elapsed() <= toneEnvelope[i].release) {
                float step = (15.0f - toneEnvelope[i].volume) / toneEnvelope[i].release;
                int vol = static_cast<int>(round((step * toneEnvelope[i].time.elapsed()) + toneEnvelope[i].volume));
                setChannelVolume(i, vol);
            }
            else {
                toneEnvelope[i].state = STATE_IDLE;
                qDebug() << "IDLE";
            }
            break;
        }
    }
}

void CAudioEngine::setChannelVolume(int channel, int volume)
{
    unsigned char b = 0;
    b |= 1 << 7; // LATCH/DATA byte
    b |= channel << 5; // Channel number
    b |= 1 << 4; // Volume
    b |= volume;
    SN76489_Write(PSG, b);
}

void CAudioEngine::setNote(int channel, QString note, int octave)
{
    // Return if octave out of range
    if(octave < 2 || octave > 8)
        return;

    // Note range B8 - A2
    int NTSCTable[] = {1017, 956, 909, 854, 805, 761, 717, 678, 639, 605, 571, 538, 508, 480, 453, 427, 404, 380, 360, 339, 321, 302, 285, 270, 254, 240, 226, 214, 202, 191, 180, 170, 160, 151, 143, 135, 127, 120, 113, 107, 101, 95, 90, 85, 80, 76, 71, 67, 64, 60, 57, 53, 50, 48, 45, 42, 40, 38, 36, 34, 32, 30, 28, 27, 25, 24, 22, 21, 20, 19, 18, 17, 16, 15, 14};
    int PALTable[] = {1008, 947, 901, 846, 797, 754, 711, 672, 633, 599, 566, 533, 504, 476, 449, 423, 400, 377, 356, 336, 318, 300, 283, 267, 252, 238, 224, 212, 200, 189, 178, 168, 159, 150, 141, 133, 126, 119, 112, 106, 100, 94, 89, 84, 79, 75, 71, 67, 63, 59, 56, 53, 50, 47, 45, 42, 40, 37, 35, 33, 31, 30, 28, 26, 25, 24, 22, 21, 20, 19, 18, 17, 16, 15, 14};

    QHash<QString, int> noteTable{ {"C", 0}, {"C#", 1}, {"D-", 1}, {"D", 2}, {"D#", 3}, {"E-", 3}, {"E", 4}, {"F", 5}, {"F#", 6}, {"G-", 6}, {"G", 7}, {"G#", 8}, {"A-", 8}, {"A", 9}, {"A#", 10}, {"B-", 10}, {"B", 11} };

    int offset = (((octave - 2) * 12) + noteTable.value(note)) - 9;

    // Avoid out of range errors
    if(offset < 0) return;

    if(channel < 3)
    {
        int data = NTSCTable[offset];

        unsigned char b = 0;
        b |= 1 << 7; // LATCH byte
        b |= channel << 5; // Channel number
        b |= data & ~0x3f0; // Tone data lower bytes
        SN76489_Write(PSG, b);

        b = 0;
        b |= data >> 4; // Tone data upper bytes
        SN76489_Write(PSG, b);
    }
    else
    {
        unsigned char b = 0;
        b |= 1 << 7; // LATCH byte
        b |= 3 << 5; // Noise channel
        b |= 1 << 2; // Set white (1) or periodic (0)
        b |= 0; // Noise patern
        SN76489_Write(PSG, b);
    }
}

void CAudioEngine::recieveNote(QString note, int octave, int velocity)
{
    qDebug() << "Received note " + note + QString::number(octave);
    setNote(rand()%3, note, octave);
    noteOn();
}
