#ifndef CSTREAMWORKER_H
#define CSTREAMWORKER_H

#include <QObject>
#include <QElapsedTimer>
#include <QString>
#include <QMutex>

struct NoteData {
    QString note;
    int octave;
    int velocity;
    int length;
};

class CSequencer : public QObject
{
    Q_OBJECT
public:
    explicit CSequencer(QObject *parent = nullptr);
    NoteData nd[1000];
    void Play();
    void Stop();
    void Pause();
    void Exit();

private:
    int state;
    int m_BPM;
    QElapsedTimer timer;
    QMutex mutex;

signals:
    void sendNote(QString note, int octave, int velocity);

public slots:
    void runSequencer();
};

#endif // CSTREAMWORKER_H
