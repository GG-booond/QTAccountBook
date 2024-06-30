QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addbyhand.cpp \
    addone.cpp \
    categoryManager.cpp \
    changefast.cpp \
    fenzhangjiemian.cpp \
    fzjilu.cpp \
    history.cpp \
    main.cpp \
    mainData.cpp \
    mainwindow.cpp \
    oneBill.cpp \
    planning.cpp \
    planshow.cpp \
    quanju.cpp \
    readweixin.cpp \
    reportWindow.cpp \
    saybills.cpp \
    settings.cpp \
    splitManager.cpp

HEADERS += \
    addbyhand.h \
    addone.h \
    background.h \
    categoryManager.h \
    changefast.h \
    fenzhangjiemian.h \
    fzjilu.h \
    history.h \
    mainData.h \
    mainwindow.h \
    oneBill.h \
    planning.h \
    planshow.h \
    quanju.h \
    readweixin.h \
    reportWindow.h \
    saybills.h \
    settings.h \
    splitManager.h

FORMS += \
    addbyhand.ui \
    addone.ui \
    changefast.ui \
    fenzhangjiemian.ui \
    fzjilu.ui \
    history.ui \
    mainwindow.ui \
    planning.ui \
    planshow.ui \
    readweixin.ui \
    saybills.ui \
    settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    CMakeLists.txt \
    CMakeLists.txt.user \
    DestinationPath \
    Image/OIP-C.png \
    Pictures/21.png \
    Pictures/OIP-C.jpg \
    Pictures/OIP-C.png \
    QTproject.pro.user \
    QTproject.pro.user.be567f4 \
    QTproject.pro.user.ff88db1 \
    data.txt

RESOURCES += \
    Image/background.qrc \
    background.qrc \
    background.qrc \
    background.qrc \
    background.qrc \
    background.qrc \
    background.qrc
