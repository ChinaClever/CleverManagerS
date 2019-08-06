INCLUDEPATH += $$PWD

DEFINES += ZEBRA_MODULE
include(zebra_libs/zebra_libs.pri)

SOURCES += \
    $$PWD/zebra_peer.cpp \
    $$PWD/zebra_client.cpp \
    $$PWD/zebra_sql.cpp \
    $$PWD/zebra_im.cpp \
    $$PWD/zebra_datapacket.cpp
   

HEADERS  += \
    $$PWD/zebra_peer.h \
    $$PWD/zebra_client.h \
    $$PWD/zebra_sql.h \
    $$PWD/zebra_im.h \
    $$PWD/zebra_datapacket.h
    
