INCLUDEPATH += $$PWD

DEFINES += ZEBRA_MODULE
include(zebra_libs/zebra_libs.pri)

SOURCES += \
    $$PWD/zebra_peer.cpp
   

HEADERS  += \
    $$PWD/zebra_peer.h
    
