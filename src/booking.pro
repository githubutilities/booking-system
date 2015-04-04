#-------------------------------------------------
#
# Project created by QtCreator 2014-05-18T10:44:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = booking
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    MyCustomer.cpp \
    MyFlight.cpp \
    MyFlightBookingSystem.cpp \
    querywindows.cpp \
    buy_ticket.cpp \
    buy_dialog.cpp \
    return_ticket_dialog.cpp

HEADERS  += mainwindow.h \
    MyCustomer.h \
    MyFlight.h \
    MyFlightBookingSystem.h \
    MyQueue.h \
    MySet.h \
    MyVector.h \
    querywindows.h \
    buy_ticket.h \
    buy_dialog.h \
    return_ticket_dialog.h

FORMS    += mainwindow.ui \
    querywindows.ui \
    buy_ticket.ui \
    buy_dialog.ui \
    return_ticket_dialog.ui

OTHER_FILES += \
    in.txt
