#include "envelope.h"
#include "ui_envelope.h"

Envelope::Envelope(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Envelope)
{
    ui->setupUi(this);

    mainWnd = reinterpret_cast<SNFX*>(parent);

    ui->ch1AttackDial->setValue(mainWnd->AEngine->toneEnvelope[0].attack);
    ui->ch1AttackEdit->setText(QString::number(mainWnd->AEngine->toneEnvelope[0].attack));
    ui->ch1DecayDial->setValue(mainWnd->AEngine->toneEnvelope[0].decay);
    ui->ch1DecayEdit->setText(QString::number(mainWnd->AEngine->toneEnvelope[0].decay));
    ui->ch1SustainDial->setValue(mainWnd->AEngine->toneEnvelope[0].sustain);
    ui->ch1SustainEdit->setText(QString::number(mainWnd->AEngine->toneEnvelope[0].sustain));
    ui->ch1ReleaseDial->setValue(mainWnd->AEngine->toneEnvelope[0].release);
    ui->ch1ReleaseEdit->setText(QString::number(mainWnd->AEngine->toneEnvelope[0].release));

    ui->ch2AttackDial->setValue(mainWnd->AEngine->toneEnvelope[1].attack);
    ui->ch2AttackEdit->setText(QString::number(mainWnd->AEngine->toneEnvelope[1].attack));
    ui->ch2DecayDial->setValue(mainWnd->AEngine->toneEnvelope[1].decay);
    ui->ch2DecayEdit->setText(QString::number(mainWnd->AEngine->toneEnvelope[1].decay));
    ui->ch2SustainDial->setValue(mainWnd->AEngine->toneEnvelope[1].sustain);
    ui->ch2SustainEdit->setText(QString::number(mainWnd->AEngine->toneEnvelope[1].sustain));
    ui->ch2ReleaseDial->setValue(mainWnd->AEngine->toneEnvelope[1].release);
    ui->ch2ReleaseEdit->setText(QString::number(mainWnd->AEngine->toneEnvelope[1].release));

    ui->ch3AttackDial->setValue(mainWnd->AEngine->toneEnvelope[2].attack);
    ui->ch3AttackEdit->setText(QString::number(mainWnd->AEngine->toneEnvelope[2].attack));
    ui->ch3DecayDial->setValue(mainWnd->AEngine->toneEnvelope[2].decay);
    ui->ch3DecayEdit->setText(QString::number(mainWnd->AEngine->toneEnvelope[2].decay));
    ui->ch3SustainDial->setValue(mainWnd->AEngine->toneEnvelope[2].sustain);
    ui->ch3SustainEdit->setText(QString::number(mainWnd->AEngine->toneEnvelope[2].sustain));
    ui->ch3ReleaseDial->setValue(mainWnd->AEngine->toneEnvelope[2].release);
    ui->ch3ReleaseEdit->setText(QString::number(mainWnd->AEngine->toneEnvelope[2].release));

    ui->ch4AttackDial->setValue(mainWnd->AEngine->toneEnvelope[3].attack);
    ui->ch4AttackEdit->setText(QString::number(mainWnd->AEngine->toneEnvelope[3].attack));
    ui->ch4DecayDial->setValue(mainWnd->AEngine->toneEnvelope[3].decay);
    ui->ch4DecayEdit->setText(QString::number(mainWnd->AEngine->toneEnvelope[3].decay));
    ui->ch4SustainDial->setValue(mainWnd->AEngine->toneEnvelope[3].sustain);
    ui->ch4SustainEdit->setText(QString::number(mainWnd->AEngine->toneEnvelope[3].sustain));
    ui->ch4ReleaseDial->setValue(mainWnd->AEngine->toneEnvelope[3].release);
    ui->ch4ReleaseEdit->setText(QString::number(mainWnd->AEngine->toneEnvelope[3].release));
}

Envelope::~Envelope()
{
    delete ui;
}

void Envelope::on_ch1AttackDial_valueChanged(int value)
{
    ui->ch1AttackEdit->setText(QString::number(value));
    mainWnd->AEngine->toneEnvelope[0].attack = value;
}

void Envelope::on_ch1DecayDial_valueChanged(int value)
{
    ui->ch1DecayEdit->setText(QString::number(value));
    mainWnd->AEngine->toneEnvelope[0].decay = value;
}

void Envelope::on_ch1SustainDial_valueChanged(int value)
{
    ui->ch1SustainEdit->setText(QString::number(value));
    mainWnd->AEngine->toneEnvelope[0].sustain = value;
}

void Envelope::on_ch1ReleaseDial_valueChanged(int value)
{
    ui->ch1ReleaseEdit->setText(QString::number(value));
    mainWnd->AEngine->toneEnvelope[0].release = value;
}

void Envelope::on_ch1AttackEdit_textChanged(const QString &arg1)
{
    ui->ch1AttackDial->setValue(arg1.toInt());
    mainWnd->AEngine->toneEnvelope[0].attack = arg1.toInt();
}

void Envelope::on_ch1DecayEdit_textChanged(const QString &arg1)
{
    ui->ch1DecayDial->setValue(arg1.toInt());
    mainWnd->AEngine->toneEnvelope[0].decay = arg1.toInt();
}

void Envelope::on_ch1SustainEdit_textChanged(const QString &arg1)
{
    ui->ch1SustainDial->setValue(arg1.toInt());
    mainWnd->AEngine->toneEnvelope[0].sustain = arg1.toInt();
}

void Envelope::on_ch1ReleaseEdit_textChanged(const QString &arg1)
{
    ui->ch1ReleaseDial->setValue(arg1.toInt());
    mainWnd->AEngine->toneEnvelope[0].release = arg1.toInt();
}


void Envelope::on_ch2AttackDial_valueChanged(int value)
{
    ui->ch2AttackEdit->setText(QString::number(value));
    mainWnd->AEngine->toneEnvelope[1].attack = value;
}

void Envelope::on_ch2DecayDial_valueChanged(int value)
{
    ui->ch2DecayEdit->setText(QString::number(value));
    mainWnd->AEngine->toneEnvelope[1].decay = value;
}

void Envelope::on_ch2SustainDial_valueChanged(int value)
{
    ui->ch2SustainEdit->setText(QString::number(value));
    mainWnd->AEngine->toneEnvelope[1].sustain = value;
}

void Envelope::on_ch2ReleaseDial_valueChanged(int value)
{
    ui->ch2ReleaseEdit->setText(QString::number(value));
    mainWnd->AEngine->toneEnvelope[1].release = value;
}

void Envelope::on_ch3AttackDial_valueChanged(int value)
{
    ui->ch3AttackEdit->setText(QString::number(value));
    mainWnd->AEngine->toneEnvelope[2].attack = value;
}

void Envelope::on_ch3DecayDial_valueChanged(int value)
{
    ui->ch3DecayEdit->setText(QString::number(value));
    mainWnd->AEngine->toneEnvelope[2].decay = value;
}

void Envelope::on_ch3SustainDial_valueChanged(int value)
{
    ui->ch3SustainEdit->setText(QString::number(value));
    mainWnd->AEngine->toneEnvelope[2].sustain = value;
}

void Envelope::on_ch3ReleaseDial_valueChanged(int value)
{
    ui->ch3ReleaseEdit->setText(QString::number(value));
    mainWnd->AEngine->toneEnvelope[2].release = value;
}

void Envelope::on_ch4AttackDial_valueChanged(int value)
{
    ui->ch4AttackEdit->setText(QString::number(value));
    mainWnd->AEngine->toneEnvelope[3].attack = value;
}

void Envelope::on_ch4DecayDial_valueChanged(int value)
{
    ui->ch4DecayEdit->setText(QString::number(value));
    mainWnd->AEngine->toneEnvelope[3].decay = value;
}

void Envelope::on_ch4SustainDial_valueChanged(int value)
{
    ui->ch4SustainEdit->setText(QString::number(value));
    mainWnd->AEngine->toneEnvelope[3].sustain = value;
}

void Envelope::on_ch4ReleaseDial_valueChanged(int value)
{
    ui->ch4ReleaseEdit->setText(QString::number(value));
    mainWnd->AEngine->toneEnvelope[3].release = value;
}

void Envelope::on_ch1Enable_toggled(bool checked)
{
    mainWnd->AEngine->toneEnvelope[0].enabled = checked;
    if(!checked)
        mainWnd->AEngine->toneEnvelope[0].state = STATE_IDLE;
}

void Envelope::on_ch2Enable_toggled(bool checked)
{
    mainWnd->AEngine->toneEnvelope[1].enabled = checked;
    if(!checked)
        mainWnd->AEngine->toneEnvelope[1].state = STATE_IDLE;
}

void Envelope::on_ch3Enable_toggled(bool checked)
{
    mainWnd->AEngine->toneEnvelope[2].enabled = checked;
    if(!checked)
        mainWnd->AEngine->toneEnvelope[2].state = STATE_IDLE;
}

void Envelope::on_ch4Enable_toggled(bool checked)
{
    mainWnd->AEngine->toneEnvelope[3].enabled = checked;
    if(!checked)
        mainWnd->AEngine->toneEnvelope[3].state = STATE_IDLE;
}
