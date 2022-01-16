#ifndef ENVELOPE_H
#define ENVELOPE_H

#include <QWidget>
#include "SNFX.h"

namespace Ui {
class Envelope;
}

class Envelope : public QWidget
{
    Q_OBJECT

public:
    explicit Envelope(QWidget *parent = nullptr);
    ~Envelope();

private slots:
    void on_ch1AttackDial_valueChanged(int value);

    void on_ch1DecayDial_valueChanged(int value);

    void on_ch1SustainDial_valueChanged(int value);

    void on_ch1ReleaseDial_valueChanged(int value);

    void on_ch1AttackEdit_textChanged(const QString &arg1);

    void on_ch1DecayEdit_textChanged(const QString &arg1);

    void on_ch1SustainEdit_textChanged(const QString &arg1);

    void on_ch1ReleaseEdit_textChanged(const QString &arg1);

    void on_ch1Enable_toggled(bool checked);

    void on_ch2Enable_toggled(bool checked);

    void on_ch2AttackDial_valueChanged(int value);

    void on_ch2DecayDial_valueChanged(int value);

    void on_ch2SustainDial_valueChanged(int value);

    void on_ch2ReleaseDial_valueChanged(int value);

    void on_ch3Enable_toggled(bool checked);

    void on_ch4Enable_toggled(bool checked);

    void on_ch4AttackDial_valueChanged(int value);

    void on_ch4DecayDial_valueChanged(int value);

    void on_ch4SustainDial_valueChanged(int value);

    void on_ch4ReleaseDial_valueChanged(int value);

    void on_ch3AttackDial_valueChanged(int value);

    void on_ch3DecayDial_valueChanged(int value);

    void on_ch3SustainDial_valueChanged(int value);

    void on_ch3ReleaseDial_valueChanged(int value);

private:
    Ui::Envelope *ui;

    SNFX *mainWnd;
};

#endif // ENVELOPE_H
