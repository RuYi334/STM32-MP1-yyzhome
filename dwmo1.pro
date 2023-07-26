QT       += core gui multimedia network mqtt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
#文件夹路径
include($$PWD/led/led.pri)
include($$PWD/fanction/fanction.pri)
include($$PWD/keyboard/keyboard.pri)
include($$PWD/widget/widget.pri)
include($$PWD/modify/modify.pri)
include($$PWD/register/register.pri)
include($$PWD/air/air.pri)
include($$PWD/environment/environment.pri)
include($$PWD/camera/camera.pri)
include($$PWD/setting/setting.pri)
# 在QMAKE_CXXFLAGS中添加 -Wno-deprecated-copy 选项来禁用警告
QMAKE_CXXFLAGS += -Wno-deprecated-copy
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += $$PWD/register/
INCLUDEPATH += $$PWD/modify/
INCLUDEPATH += $$PWD/keyboard/
INCLUDEPATH += $$PWD/air/
INCLUDEPATH += $$PWD/environment/
INCLUDEPATH += $$PWD/camera/
INCLUDEPATH += $$PWD/fanction/
INCLUDEPATH += $$PWD/led/
INCLUDEPATH += $$PWD/widget/
INCLUDEPATH += $$PWD/setting/

SOURCES += \
    main.cpp

HEADERS += \
    buzzer.h \
    fsmpCamera.h \
    fsmpEvents.h \
    fsmpLight.h \
    fsmpTempHum.h


FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    1.qrc

DISTFILES += \
    source/夜灯.png \
    source/按钮-关.png \
    source/按钮-开.png \
    source/返回.png
