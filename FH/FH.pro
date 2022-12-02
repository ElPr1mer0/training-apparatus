QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    db.cpp \
    main.cpp \
    object_memory_test.cpp \
    print_window_logic.cpp \
    reaction_speed_logic.cpp \
    sounds.cpp \
    training_mode.cpp \
    widget_style.cpp \
    window.cpp\
    hash.cpp

HEADERS += \
    chart.h \
    db.h \
    object_memory_test.h \
    print_window_logic.h \
    reaction_speed_logic.h \
    sounds.h \
    training_mode.h \
    widget_style.h \
    window.h\
    hash.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sounds.qrc
