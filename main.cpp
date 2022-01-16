#include "SNFX.h"
#include "audioengine.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SNFX w;
    w.show();

    return a.exec();
}
