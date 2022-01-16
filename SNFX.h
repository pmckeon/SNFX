#ifndef SNFX_H
#define SNFX_H

#include <QMainWindow>
#include "audioengine.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SNFX; }
QT_END_NAMESPACE

class SNFX : public QMainWindow
{
    Q_OBJECT

public:
    SNFX(QWidget *parent = nullptr);
    ~SNFX();

    CAudioEngine *AEngine;

public slots:
    void playNote(QString note, int octave, int channel=0);
    void stopNote();

private slots:
    void on_actionPlay_triggered();

    void on_actionStop_triggered();

private:
    Ui::SNFX *ui;
};
#endif // SNFX_H
