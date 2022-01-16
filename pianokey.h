#ifndef CPIANOKEY_H
#define CPIANOKEY_H
#include <QAbstractButton>
#include <QString>

class CPianoKey : public QAbstractButton
{
    Q_OBJECT
public:
    explicit CPianoKey(QWidget *parent = nullptr);

    int octave;
    QString note;

private:


protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // CPIANOKEY_H
