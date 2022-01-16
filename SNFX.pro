QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    envelope.cpp \
    main.cpp \
    SNFX.cpp \
    audioengine.cpp \
    panning.cpp \
    patterneditorview.cpp \
    pianokey.cpp \
    pianowidget.cpp \
    sequencer.cpp \
    sn76489/sn76489.cpp

HEADERS += \
    SNFX.h \
    adsrenvelope.h \
    audioengine.h \
    envelope.h \
    panning.h \
    patterneditorview.h \
    pianokey.h \
    pianowidget.h \
    sequencer.h \
    sn76489/sn76489.h

FORMS += \
    SNFX.ui \
    envelope.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -L$$PWD/../../Programming/API/portaudio/build/msvc/Win32/Release/ -lportaudio_x86

INCLUDEPATH += $$PWD/../../Programming/API/portaudio/include
DEPENDPATH += $$PWD/../../Programming/API/portaudio/include