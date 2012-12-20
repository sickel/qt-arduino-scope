################################################################
# Qwt Widget Library
# Copyright (C) 1997   Josef Wilgen
# Copyright (C) 2002   Uwe Rathmann
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Qwt License, Version 1.0
###################################################################

# QWT_ROOT = $${PWD}/..
#include( qwtconfig.pri )
#include( qwtbuild.pri )
include( qwtfunctions.pri )

MOC_DIR      = moc
OBJECTS_DIR  = obj

TEMPLATE     = app

INCLUDEPATH += src
INCLUDEPATH += /usr/include/qwt
DEPENDPATH  += src
DESTDIR      = bin

QMAKE_RPATHDIR *= $${QWT_ROOT}/lib

contains(QWT_CONFIG, QwtFramework) {

    LIBS      += -Flib
}
else {

    LIBS      += -Llib
}

qwtAddLibrary(qwt)

greaterThan(QT_MAJOR_VERSION, 4) {

    QT += printsupport
}

contains(QWT_CONFIG, QwtSvg) {

    QT += svg
}
else {

    DEFINES += QWT_NO_SVG
}


win32 {
    contains(QWT_CONFIG, QwtDll) {
        DEFINES    += QT_DLL QWT_DLL
    }
}
