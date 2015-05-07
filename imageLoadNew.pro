#-------------------------------------------------
#
# Project created by QtCreator 2015-05-01T19:46:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = imageLoadNew
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    prep_options.cpp \
    callFisher.cpp

HEADERS  += mainwindow.h \
    feature_option.h \
    feat_desc.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include/opencv
INCLUDEPATH +=/home/sgnosh/vlfeat-0.9.20

LIBS += -L/usr/local/lib/ -lopencv_core -lopencv_imgcodecs -lopencv_highgui
LIBS += -L//home/sgnosh/vlfeat-0.9.20/bin/glnxa64
