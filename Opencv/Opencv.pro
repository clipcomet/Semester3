
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    opencv.cpp


INCLUDEPATH += C:\opencv\opencv\build\include



LIBS += C:\opencv\opencv\build\bin\libopencv_core343.dll
LIBS += C:\opencv\opencv\build\bin\libopencv_highgui343.dll
LIBS += C:\opencv\opencv\build\bin\libopencv_imgcodecs343.dll
LIBS += C:\opencv\opencv\build\bin\libopencv_imgproc343.dll
LIBS += C:\opencv\opencv\build\bin\libopencv_features2d343.dll
LIBS += C:\opencv\opencv\build\bin\libopencv_calib3d343.dll
LIBS += C:\opencv\opencv\build\bin\libopencv_videoio343.dll

HEADERS += \
    opencv.h
