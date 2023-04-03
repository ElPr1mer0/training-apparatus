QT       += core gui sql multimedia printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chat.cpp \
    db.cpp \
    main.cpp \
    mode.cpp \
    print_window_logic.cpp \
    qcustomplot.cpp \
    reaction_speed_logic.cpp \
    resourse.cpp \
    training_mode.cpp \
    widget_style.cpp \
    hash.cpp \
    window_forms.cpp\
    client.cpp

HEADERS += \
    chart.h \
    chat.h \
    db.h \
    mode.h \
    print_window_logic.h \
    qcustomplot.h \
    reaction_speed_logic.h \
    resourse.h \
    training_mode.h \
    widget_style.h \
    hash.h \
    window_forms.h\
    client.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourse.qrc
