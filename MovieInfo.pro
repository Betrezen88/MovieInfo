TEMPLATE = app

QT += qml quick widgets network xml sql

HEADERS += \
    Database.h\
    Parser.h \
    Movie.h \
    MovieModel.h \
    MovieManager.h \
    ResourceImageProvider.h \
    Task.h \
    TaskList.h \
    TaskDetails.h \
    TaskImageDownloader.h \
    TaskTorrentDetails.h \
    TorrentInfo.h \
    TorrentInfoModel.h \

SOURCES += main.cpp \
    Parser.cpp \
    MovieManager.cpp \
    TaskList.cpp \
    TaskImageDownloader.cpp \
    TaskDetails.cpp \
    TaskTorrentDetails.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)
