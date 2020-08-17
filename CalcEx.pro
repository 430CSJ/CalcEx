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
    dialog0.cpp \
    ex1dialog.cpp \
    ex1lineedit.cpp \
    ex2dialog.cpp \
    ex2lineedit.cpp \
    ex3buylineedit.cpp \
    ex3dialog.cpp \
    ex3selllineedit.cpp \
    exdata.cpp \
    main.cpp \
    mainwindow.cpp \
    preparedialog.cpp \
    resultdialog.cpp

HEADERS += \
    dialog0.h \
    ex1dialog.h \
    ex1lineedit.h \
    ex2dialog.h \
    ex2lineedit.h \
    ex3buylineedit.h \
    ex3dialog.h \
    ex3selllineedit.h \
    exdata.h \
    mainwindow.h \
    preparedialog.h \
    resultdialog.h

FORMS += \
    dialog0.ui \
    ex1dialog.ui \
    ex2dialog.ui \
    ex3dialog.ui \
    mainwindow.ui \
    preparedialog.ui \
    resultdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
