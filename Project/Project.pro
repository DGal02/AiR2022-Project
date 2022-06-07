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
        double_shot_potion.cpp \
        enemy.cpp \
        fire.cpp \
        fly.cpp \
        ghost.cpp \
        health_potion.cpp \
        main.cpp \
        potion.cpp

HEADERS += \
    boss.h \
    bullet.h \
    character.h \
    double_shot_potion.h \
    enemy.h \
    fire.h \
    fly.h \
    ghost.h \
    health_potion.h \
    potion.h
