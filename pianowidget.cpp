#include "pianowidget.h"
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QString>
#include <QWidget>
#include <QSize>

CPianoWidget::CPianoWidget(QWidget *parent) : QWidget(parent), m_lastKey{nullptr}, m_channel{0}
{
    // Create piano keys in z-order from bottom (white) to top (black) keys
    // White keys
    for(int i=0; i < NUM_OCTAVES; ++i)
    {
        int offset = (i * 7);

        keys[offset].setParent(this);
        keys[offset].octave = (NUM_OCTAVES - (i+1));
        keys[offset].note = "B";
        keys[offset].move(0, (i*216));
        keys[offset].setFixedSize(70, 27);
        keys[offset].setStyleSheet("CPianoKey { background-color: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 lightgrey, stop:1 white); border-style: solid solid none none; border-width: 1px; border-color: black; }"
                                   "CPianoKey:pressed { background-color: yellow; }");
        keys[offset].show();

        keys[offset+1].setParent(this);
        keys[offset+1].octave = (NUM_OCTAVES - (i+1));
        keys[offset+1].note = "A";
        keys[offset+1].move(0, (i*216)+27);
        keys[offset+1].setFixedSize(70, 36);
        keys[offset+1].setStyleSheet("CPianoKey { background-color: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 lightgrey, stop:1 white); border-style: none solid none none; border-width: 1px; border-color: black; }"
                                   "CPianoKey:pressed { background-color: yellow; }");
        keys[offset+1].show();

        keys[offset+2].setParent(this);
        keys[offset+2].octave = (NUM_OCTAVES - (i+1));
        keys[offset+2].note = "G";
        keys[offset+2].move(0, (i*216)+63);
        keys[offset+2].setFixedSize(70, 36);
        keys[offset+2].setStyleSheet("CPianoKey { background-color: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 lightgrey, stop:1 white); border-style: none solid none none; border-width: 1px; border-color: black; }"
                                   "CPianoKey:pressed { background-color: yellow; }");
        keys[offset+2].show();

        keys[offset+3].setParent(this);
        keys[offset+3].octave = (NUM_OCTAVES - (i+1));
        keys[offset+3].note = "F";
        keys[offset+3].move(0, (i*216)+99);
        keys[offset+3].setFixedSize(70, 27);
        keys[offset+3].setStyleSheet("CPianoKey { background-color: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 lightgrey, stop:1 white); border-style: none solid solid none; border-width: 1px; border-color: black; }"
                                   "CPianoKey:pressed { background-color: yellow; }");
        keys[offset+3].show();

        keys[offset+4].setParent(this);
        keys[offset+4].octave = (NUM_OCTAVES - (i+1));
        keys[offset+4].note = "E";
        keys[offset+4].move(0, (i*216)+126);
        keys[offset+4].setFixedSize(70, 27);
        keys[offset+4].setStyleSheet("CPianoKey { background-color: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 lightgrey, stop:1 white); border-style: none solid none none; border-width: 1px; border-color: black; }"
                                   "CPianoKey:pressed { background-color: yellow; }");
        keys[offset+4].show();

        keys[offset+5].setParent(this);
        keys[offset+5].octave = (NUM_OCTAVES - (i+1));
        keys[offset+5].note = "D";
        keys[offset+5].move(0, (i*216)+153);
        keys[offset+5].setFixedSize(70, 36);
        keys[offset+5].setStyleSheet("CPianoKey { background-color: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 lightgrey, stop:1 white); border-style: none solid none none; border-width: 1px; border-color: black; }"
                                   "CPianoKey:pressed { background-color: yellow; }");
        keys[offset+5].show();

        keys[offset+6].setParent(this);
        keys[offset+6].octave = (NUM_OCTAVES - (i+1));
        keys[offset+6].note = "C";
        keys[offset+6].move(0, (i*216)+189);
        keys[offset+6].setFixedSize(70, 27);
        keys[offset+6].setText(keys[offset+6].note + QString::number(keys[offset+6].octave));
        keys[offset+6].setStyleSheet("CPianoKey { background-color: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 lightgrey, stop:1 lightgrey); border-style: none solid none none; border-width: 1px; border-color: black; }"
                                   "CPianoKey:pressed { background-color: yellow; }");
        keys[offset+6].show();
    }

    // Black keys
    for(int i=0; i < NUM_OCTAVES; ++i)
    {
        int offset = (i * 5) + (NUM_OCTAVES * 7);

        keys[offset].setParent(this);
        keys[offset].octave = (NUM_OCTAVES - (i+1));
        keys[offset].note = "A#";
        keys[offset].move(0, (i*216)+18);
        keys[offset].setFixedSize(45, 18);
        keys[offset].setStyleSheet("CPianoKey { background-color: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 black, stop:1 grey); }"
                                   "CPianoKey:pressed { background-color: yellow; }");
        keys[offset].show();

        keys[offset+1].setParent(this);
        keys[offset+1].octave = (NUM_OCTAVES - (i+1));
        keys[offset+1].note = "G#";
        keys[offset+1].move(0, (i*216)+54);
        keys[offset+1].setFixedSize(45, 18);
        keys[offset+1].setStyleSheet("CPianoKey { background-color: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 black, stop:1 grey); }"
                                   "CPianoKey:pressed { background-color: yellow; }");
        keys[offset+1].show();


        keys[offset+2].setParent(this);
        keys[offset+2].octave = (NUM_OCTAVES - (i+1));
        keys[offset+2].note = "F#";
        keys[offset+2].move(0, (i*216)+90);
        keys[offset+2].setFixedSize(45, 18);
        keys[offset+2].setStyleSheet("CPianoKey { background-color: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 black, stop:1 grey); }"
                                   "CPianoKey:pressed { background-color: yellow; }");
        keys[offset+2].show();

        keys[offset+3].setParent(this);
        keys[offset+3].octave = (NUM_OCTAVES - (i+1));
        keys[offset+3].note = "D#";
        keys[offset+3].move(0, (i*216)+144);
        keys[offset+3].setFixedSize(45, 18);
        keys[offset+3].setStyleSheet("CPianoKey { background-color: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 black, stop:1 grey); }"
                                   "CPianoKey:pressed { background-color: yellow; }");
        keys[offset+3].show();

        keys[offset+4].setParent(this);
        keys[offset+4].octave = (NUM_OCTAVES - (i+1));
        keys[offset+4].note = "C#";
        keys[offset+4].move(0, (i*216)+180);
        keys[offset+4].setFixedSize(45, 18);
        keys[offset+4].setStyleSheet("CPianoKey { background-color: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 black, stop:1 grey); }"
                                   "CPianoKey:pressed { background-color: yellow; }");
        keys[offset+4].show();
    }
}

QSize CPianoWidget::sizeHint() const
{
    return QSize(70, NUM_OCTAVES*216);
}

void CPianoWidget::mousePressEvent(QMouseEvent *event)
{
    CPianoKey *key = dynamic_cast<CPianoKey*>(childAt(event->pos()));
    if(key != nullptr)
    {
        key->setDown(true);
        //qDebug() << "Pressed: " + key->note;
        emit noteOn(key->note, key->octave, m_channel);
        m_lastKey = key;
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void CPianoWidget::mouseReleaseEvent(QMouseEvent *event)
{
    CPianoKey *key = dynamic_cast<CPianoKey*>(childAt(event->pos()));
    if(key != nullptr)
    {
        key->setDown(false);
        //qDebug() << "Released: " + key->note;
        emit noteOff();
        event->accept();
    }
    else
    {
        event->ignore();
    }
    m_lastKey = nullptr;
}

void CPianoWidget::mouseMoveEvent(QMouseEvent *event)
{
    CPianoKey *key = dynamic_cast<CPianoKey*>(childAt(event->pos()));
    if(key != nullptr)
    {
        if(key != m_lastKey && m_lastKey != nullptr)
        {
            m_lastKey->setDown(false);
            key->setDown(true);
            //qDebug() << "Released: " + m_lastKey->note;
            //qDebug() << "Pressed: " + key->note;
            emit noteOff();
            emit noteOn(key->note, key->octave, m_channel);
            m_lastKey = key;
        }
        else if(m_lastKey == nullptr)
        {
            key->setDown(true);
            //qDebug() << "Pressed: " + key->note;
            emit noteOn(key->note, key->octave, m_channel);
            m_lastKey = key;
        }
    }
    else if(m_lastKey != nullptr)
    {
        m_lastKey->setDown(false);
        //qDebug() << "Released: " + m_lastKey->note;
        emit noteOff();
        m_lastKey = nullptr;
    }

    event->accept();
}

void CPianoWidget::setChannel(int channel)
{
    m_channel = channel;
}
