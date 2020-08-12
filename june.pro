QT       += core gui sql widgets multimedia multimediawidgets
requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport



CONFIG += c++11
TARGET = June
TEMPLATE = app
QMAKE_LFLAGS += -no-pie
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
    en_game.cpp \
    en_gameitem.cpp \
    j_word.cpp \
    jdockwidget.cpp \
    jmdi.cpp \
    jrtclass.cpp \
    jtab.cpp \
    juneobject.cpp \
    main.cpp \
    june_main.cpp \
    qsqlite3_database.cpp \
    qsqlite3_datastruct.cpp \
    sqlitedata.cpp

HEADERS += \
    en_game.h \
    en_gameitem.h \
    j_word.h \
    jdockwidget.h \
    jmdi.h \
    jrtclass.h \
    jtab.h \
    june_main.h \
    juneobject.h \
    qsqlite3_database.h \
    qsqlite3_datastruct.h \
    sqlitedata.h

FORMS += \
    en_game.ui \
    j_twodata.ui \
    j_word.ui \
    jdockwidget.ui \
    jmdi.ui \
    jtab.ui \
    june_main.ui \
    sqlitedata.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    june.qrc
RC_ICONS = june_icon.ico
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/release/ -lqscintilla2_qt5
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/debug/ -lqscintilla2_qt5
else:unix: LIBS += -L$$PWD/../../../usr/lib/ -lqscintilla2_qt5

INCLUDEPATH += $$PWD/''
DEPENDPATH += $$PWD/''


