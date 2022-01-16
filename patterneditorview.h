#ifndef CPATTERNEDITORVIEW_H
#define CPATTERNEDITORVIEW_H

#include <QAbstractScrollArea>
#include "pianowidget.h"

class CPatternEditorView : public QAbstractScrollArea
{
    Q_OBJECT
public:
    explicit CPatternEditorView(QWidget *parent = nullptr);

private:
    CPianoWidget *pianoWidget;
    QWidget *tst;

protected:
    void resizeEvent(QResizeEvent *event) override;
    QSize sizeHint() const override;
    void scrollContentsBy(int dx, int dy) override;

signals:

public slots:
};

#endif // CPATTERNEDITORVIEW_H
