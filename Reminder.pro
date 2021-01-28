QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS_DEBUG += "-fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls"
QMAKE_LFLAGS += "-fsanitize=address"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    event.cpp \
    main.cpp \
    main_window.cpp \
    reminder.cpp \
    reminder_manager.cpp

HEADERS += \
    event.h \
    main_window.h \
    reminder.h \
    reminder_manager.h \
    test.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
