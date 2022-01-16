#include "patterneditorview.h"
#include "SNFX.h"
#include <QScrollBar>
#include <QDebug>
#include <QString>
#include <QSizePolicy>

CPatternEditorView::CPatternEditorView(QWidget *parent) : QAbstractScrollArea(parent)
{
    tst = new QWidget(this);
    tst->setStyleSheet("background: lightslategray;");
    tst->move(50,0);
    tst->show();

    pianoWidget = new CPianoWidget(this);
    pianoWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    pianoWidget->setChannel(0);
    pianoWidget->show();

    connect(pianoWidget, &CPianoWidget::noteOn, dynamic_cast<SNFX*>(parent), &SNFX::playNote);
    connect(pianoWidget, &CPianoWidget::noteOff, dynamic_cast<SNFX*>(parent), &SNFX::stopNote);
}

void CPatternEditorView::resizeEvent(QResizeEvent *event)
{
    QSize areaSize = viewport()->size();
    QSize  widgetSize(2000,pianoWidget->height());

    verticalScrollBar()->setPageStep(areaSize.height());
    horizontalScrollBar()->setPageStep(areaSize.width());
    verticalScrollBar()->setRange(0, widgetSize.height() - areaSize.height());
    horizontalScrollBar()->setRange(0, widgetSize.width() - areaSize.width());

//    verticalScrollBar()->setValue(pianoWidget->height()/2);
}

QSize CPatternEditorView::sizeHint() const
{
    return QSize(200, pianoWidget->height());
}

void CPatternEditorView::scrollContentsBy(int dx, int dy)
{
    int xvalue = tst->pos().x() + dx;
    int yvalue = pianoWidget->pos().y() + dy;

    tst->move(xvalue, yvalue);
    pianoWidget->move(0, yvalue);

    viewport()->update();
}
