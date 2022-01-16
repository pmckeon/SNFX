#include "pianokey.h"
#include <QPainter>
#include <QStylePainter>
#include <QStyleOptionButton>
#include <QEvent>
#include <QDebug>
#include <QString>
#include <QMouseEvent>
#include <QCoreApplication>

CPianoKey::CPianoKey(QWidget *parent) : QAbstractButton(parent)
{

}

void CPianoKey::paintEvent(QPaintEvent * /*event*/)
{
    QStylePainter p(this);
    QStyleOptionButton option;

    option.initFrom(this);
    option.features = QStyleOptionButton::None;
    if(isDown())
        option.state |= QStyle::State_Sunken;
    option.text = text();

    p.drawControl(QStyle::CE_PushButton, option);
}

void CPianoKey::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
}

void CPianoKey::mouseReleaseEvent(QMouseEvent *event)
{
    event->ignore();
}

void CPianoKey::mouseMoveEvent(QMouseEvent *event)
{
    event->ignore();
}
