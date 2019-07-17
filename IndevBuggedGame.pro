TEMPLATE = app
CONFIG += c++17 strict_c++
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS_RELEASE += -O2

LIBS += -lsfml-graphics -lsfml-window -lsfml-system

SOURCES += \
        block.cpp \
        blockManager.cpp \
        collision.cpp \
        collision1.cpp \
        editLevelState.cpp \
        event.cpp \
        eventManager.cpp \
        game.cpp \
        gamePlayed.cpp \
        gameStateStack.cpp \
        global.cpp \
        levelManager.cpp \
        main.cpp \
        mainMenuState.cpp \
        messageManager.cpp \
        messageState.cpp \
        movement1.cpp \
        movementX.cpp \
        particle.cpp \
        particleManager.cpp \
        particleMotor.cpp \
        playState.cpp \
        playerPlay.cpp \
        screenTransitionState.cpp \
        startScreenState.cpp \
        utilities.cpp \
        widgetCursor.cpp \
        widgetText.cpp

HEADERS += \
    block.hpp \
    blockManager.hpp \
    character.hpp \
    collision.hpp \
    collision1.hpp \
    editLevelState.hpp \
    event.hpp \
    eventManager.hpp \
    game.hpp \
    gamePlayed.hpp \
    gameState.hpp \
    gameStateStack.hpp \
    global.hpp \
    levelManager.hpp \
    mainMenuState.hpp \
    messageManager.hpp \
    messageState.hpp \
    movement.hpp \
    movement1.hpp \
    movementX.hpp \
    particle.hpp \
    particleManager.hpp \
    particleMotor.hpp \
    playState.hpp \
    playerPlay.hpp \
    screenTransitionState.hpp \
    startScreenState.hpp \
    utilities.hpp \
    widgetCursor.hpp \
    widgetText.hpp
