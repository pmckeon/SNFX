#include "sequencer.h"
#include <QDebug>
#include <QChar>
#include <unistd.h>
#include <QCoreApplication>

CSequencer::CSequencer(QObject *parent) : QObject(parent)
{
    state=0;
    m_BPM = 120;

    for(int i=0; i < 1000; ++i)
    {
        nd[i].note = QChar('A' + rand() % 7);
        nd[i].octave = (rand() % 5) + 1;
        nd[i].length = 1;
        nd[i].velocity = 127;
    }
}

void CSequencer::runSequencer()
{
    while(state != 5)
    {
        switch(state) {
        case 0:
            break;
        case 1:
            for(int i=0; i < 1000; ++i)
            {
                emit sendNote(nd[i].note, nd[i].octave, nd[i].velocity);
                //QCoreApplication::processEvents();
                if(state != 1) break;
                usleep(200000);
            }
            break;
        }
        //qDebug() << QString::number(state);
        //QCoreApplication::processEvents();
        //usleep(1);
    }
    qDebug() << "Sequencer thread, exit call recieved";
}

void CSequencer::Play()
{
    timer.start();
    mutex.lock();
    state = 1;
    mutex.unlock();
}

void CSequencer::Stop()
{
    qDebug() << "Microseconds: " + QString::number(timer.nsecsElapsed() / 1000);
    mutex.lock();
    state = 0;
    mutex.unlock();
}

void CSequencer::Pause()
{
    mutex.lock();
    state = 0;
    mutex.unlock();
}

void CSequencer::Exit()
{
    mutex.lock();
    state = 5;
    mutex.unlock();
    qDebug() << "Setting state to 5 (exit condition)";
}
