#include "SNFX.h"
#include "ui_SNFX.h"
#include "envelope.h"
#include <QMdiSubWindow>
#include "patterneditorview.h"
#include <QSpinBox>
#include <QSizePolicy>
#include <QHBoxLayout>

SNFX::SNFX(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SNFX)
{
    ui->setupUi(this);

    AEngine = new CAudioEngine();
    Envelope *e = new Envelope(this);

    ui->mdiArea->addSubWindow(e);

    CPatternEditorView *peView = new CPatternEditorView(this);
    peView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QMdiSubWindow *mywnd = ui->mdiArea->addSubWindow(peView);

    QSpinBox *spinBPM = new QSpinBox(this);
    spinBPM->setRange(1, 500);
    spinBPM->setValue(120);
    ui->toolBar->addWidget(spinBPM);
}

SNFX::~SNFX()
{
    delete AEngine;
    delete ui;
}

void SNFX::playNote(QString note, int octave, int channel)
{
    channel = 2; // remove
    AEngine->setNote(channel, note, octave);
    AEngine->noteOn();
}

void SNFX::stopNote()
{
    AEngine->noteOff();
}

void SNFX::on_actionPlay_triggered()
{
    AEngine->playSong();
}

void SNFX::on_actionStop_triggered()
{
    AEngine->stopSong();
}
