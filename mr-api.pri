

INCLUDEPATH += $$PWD/Include

LIBS += -L$$PWD/Lib -lmrapi
#LIBS += -L$$PWD/LibOut -lmrapi

INCLUDEPATH += $$PWD/PCANBasic/Include

LIBS += -L$$PWD/PCANBasic/x64 -lPCANBasic

LIBS += -L$$PWD/PCANBasic/x64/VC_LIB -lPCANBasic
