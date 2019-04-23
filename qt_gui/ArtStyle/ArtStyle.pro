QT += core xml widgets multimedia multimediawidgets

TARGET = ArtStyle
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++14

#### Deployment rules ####
CONFIG(debug, debug|release){
    DESTDIR = $$PWD/../ArtStyle-build-x64-Debug
} else {
    DESTDIR = $$PWD/../ArtStyle-build-x64-Relase
}
########

#### Include rules ####
INCLUDE_D = include
SRC_D = src
UI_D = ui

INCLUDEPATH += $$INCLUDE_D $$UI_D
########

#### Project files ####
SOURCES += $$SRC_D/main.cpp

HEADERS += $$INCLUDE_D/QStyleTransformator.h
SOURCES += $$SRC_D/QStyleTransformator.cpp

HEADERS += $$INCLUDE_D/SContext.h

HEADERS += $$INCLUDE_D/SConfig.h
SOURCES += $$SRC_D/SConfig.cpp

HEADERS += $$INCLUDE_D/QMainWnd.h
SOURCES += $$SRC_D/QMainWnd.cpp
FORMS += $$UI_D/QMainWnd.ui

HEADERS += $$INCLUDE_D/QVideoPlayerWdgt.h
SOURCES += $$SRC_D/QVideoPlayerWdgt.cpp

HEADERS += $$INCLUDE_D/QImageViewWdgt.h
SOURCES += $$SRC_D/QImageViewWdgt.cpp

HEADERS += $$INCLUDE_D/QTransformApiHandler.h
SOURCES += $$SRC_D/QTransformApiHandler.cpp
########

#### Resources ####
RESOURCES = resources.qrc
########
