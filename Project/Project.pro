TEMPLATE = app
CONFIG += console c++19
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += "C:/SFML-2.5.1/include"
LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}
SOURCES += \
        boss.cpp \
        bullet.cpp \
        character.cpp \
        enemy.cpp \
        fire.cpp \
        fly.cpp \
        main.cpp

HEADERS += \
    boss.h \
    bullet.h \
    character.h \
    enemy.h \
    fire.h \
    fly.h
