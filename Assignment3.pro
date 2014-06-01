#-------------------------------------------------
#
# Project created by QtCreator 2014-03-23T23:22:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Assignment3
TEMPLATE = app

SOURCES +=	main.cpp\
	        dialog.cpp\
	        config.cpp \
		    ball.cpp \
		    itemfactory.cpp \
    block.cpp \
    ballconfigitem.cpp \
    blockconfigitem.cpp \
    paddleconfigitem.cpp \
    paddle.cpp \
    AbstractResponsibility.cpp \
    score.cpp \
    chainofresponsibility.cpp \
    helpdialogmanager.cpp \
    scoreboardmanager.cpp \
    levelconfigitem.cpp \
    level.cpp

HEADERS  += dialog.h\
            config.h \
		    ball.h \
		    itemfactory.h \
    item.h \
    defaults.h \
    block.h \
    configitem.h \
    ballconfigitem.h \
    blockconfigitem.h \
    paddleconfigitem.h \
    paddle.h \
    AbstractResponsibility.h \
    score.h \
    chainofresponsibility.h \
    Events.h \
    helpdialogmanager.h \
    scoreboardmanager.h \
    levelconfigitem.h \
    level.h

FORMS    += dialog.ui \
    scoreboard.ui \
    helpdialog.ui

OTHER_FILES += config.config \
    README.md \
    breakoutscore



