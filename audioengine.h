#ifndef CAUDIOENGINE_H
#define CAUDIOENGINE_H
#include "sn76489/sn76489.h"
#include "portaudio.h"
#include <QThread>
#include <QDebug>
#include <QTimer>
#include "adsrenvelope.h"
#include "sequencer.h"

class CAudioEngine : public QObject
{
    Q_OBJECT

public:
    CAudioEngine();
    ~CAudioEngine();
    void noteOn();
    void noteOff();
    void playSong();
    void stopSong();
    void pauseSong();
    void timerCallback();
    CADSREnvelope toneEnvelope[4];
    QThread sequencerThread;
    CSequencer *sequencer;
    void setNote(int channel, QString note, int octave);
    void setChannelVolume(int channel, int volume);

private:
    PaStream *stream;
    QTimer *timer;
    void GenerateNTSCScale();
    void GeneratePALScale();

public slots:
    void recieveNote(QString note, int octave, int velocity);
};

#endif // CAUDIOENGINE_H
