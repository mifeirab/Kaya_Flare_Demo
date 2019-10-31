#-------------------------------------------------
#
# Project created by QtCreator 2018-09-18T21:26:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG+=thread
TARGET = Kaya_Flare
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


RC_ICONS += logo.ico

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    kaya_flare_camera_control.cpp \
    kaya_flare_camera_control.cpp \
    camerapare.cpp \
    mylabel.cpp \
    mythread.cpp \
    qcustomplot.cpp

HEADERS += \
        mainwindow.h \
    kaya_flare_camera_control.h \
    Header/clserkyi.h \
    Header/clserkyi_defines.h \
    Header/ky_cxp_defines.h \
    Header/ky_lib_defines.h \
    Header/KYFGcppLib.h \
    Header/KYFGLib.h \
    Header/KYFGLib_defines.h \
    Header/stdafx.h \
    Header/targetver.h \
    Header/include/GetCameraValue.h \
    Header/include/GetCameraXML_File.h \
    Header/include/GetGabberConfigurationParameter.h \
    Header/image_parameters.h \
    kaya_flare_camera_control.h \
    camerapare.h \
    mylabel.h \
    mythread.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui


RESOURCES += \
    image.qrc

#---------------------------------OpenCv_Include---------------------------------#
INCLUDEPATH += F:\opencv\build\include  \

               F:\opencv\build\include\opencv \

              F:\opencv\build\include\opencv2 \


#---------------------------------OpenCv_Lib-------------------------------------#
LIBS += -LF:\opencv\build\x64\vc12\lib\ -lopencv_ts300
LIBS += -LF:\opencv\build\x64\vc12\lib\ -lopencv_ts300d
LIBS += -LF:\opencv\build\x64\vc12\lib\ -lopencv_world300
LIBS += -LF:\opencv\build\x64\vc12\lib\ -lopencv_world300d




#---------------------------------KAY_Include---------------------------------#
INCLUDEPATH += F:\Capture_Kaya_Flare\Qt_Version\Kaya_Flare\Header  \
               F:\Capture_Kaya_Flare\Qt_Version\Kaya_Flare\Header\include



#---------------------------------KAY_Lib---------------------------------#
LIBS += -LF:\Capture_Kaya_Flare\Qt_Version\Kaya_Flare\Lib_KAYA\ -lclserkyi
LIBS += -LF:\Capture_Kaya_Flare\Qt_Version\Kaya_Flare\Lib_KAYA\ -lKYFGLib



