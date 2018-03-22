#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4) {
	# Qt 5
	QT += widgets
}

TARGET = Chess
TEMPLATE = app

DESTDIR = build

OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
UI_DIR = $$DESTDIR/ui
RCC_DIR = $$DESTDIR/qrc

SOURCES += main.cpp\
        mainwindow.cpp \
    tile.cpp \
    validation.cpp \
    ai_player.cpp

HEADERS  += mainwindow.h \
    tile.h \
    validation.h \
    ai_player.h

FORMS    += mainwindow.ui

RESOURCES += \
    Images.qrc
