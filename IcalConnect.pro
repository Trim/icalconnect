#-------------------------------------------------
#
# Project created by QtCreator 2015-11-11T18:22:08
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = icalconnect
TEMPLATE = app

#Qtopia app
CONFIG+=qtopia

# Specify the languages that make lupdate should produce .ts files for
STRING_LANGUAGE=en_US
LANGUAGES=en_US

APP_NAME = IcalConnect
DEFINES += APP_NAME="$$APP_NAME"

APP_UNIX_NAME = IcalConnect
DEFINES += APP_UNIX_NAME="$$APP_UNIX_NAME"

SOURCES += main.cpp\
	icalconnect.cpp \
    filepicker.cpp

HEADERS  += icalconnect.h \
    filepicker.h

FORMS    += icalconnect.ui

## Package information (used for qbuild packages)
#pkg [
#    name=icalconnect
#    desc="Connect to your online calendars"
#    license=GPLv3
#    version=1.0
#    maintainer="Adrien Dorsaz <adrien@adorsaz.ch>"
#]

## SXE information
#target [
#    hint=sxe
#    domain=untrusted
#]

## Install the launcher item. The metadata comes from the .desktop file
## and the path here.
#desktop [
#    hint=desktop
#    files=resources/icalconnect.desktop
#    path=/apps/Applications
#]

## Install some pictures.
#pics [
#    hint=pics
#    files=pics/*
#    path=/pics/getcal
#]

## Install help files
#help [
#    hint=help
#    source=help
#    files=getcal.html
#]
