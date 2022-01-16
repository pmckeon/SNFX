#ifndef CPIANOWIDGET_H
#define CPIANOWIDGET_H

#include <QWidget>
#include <QString>
#include "pianokey.h"

#define NUM_OCTAVES 11 // Number of octaves for the piano
#define NUM_KEYS (NUM_OCTAVES * 12) // Number of piano keys

class CPianoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CPianoWidget(QWidget *parent = nullptr);
    void setChannel(int channel);

private:
    CPianoKey keys[NUM_KEYS];
    CPianoKey *m_lastKey;
    int m_channel;

protected:
    QSize sizeHint() const override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

signals:
    void noteOn(QString note, int octave, int channel);
    void noteOff();

public slots:
};

#endif // CPIANOWIDGET_H
