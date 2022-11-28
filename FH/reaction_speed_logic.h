#ifndef REACTION_SPEED_LOGIC_H
#define REACTION_SPEED_LOGIC_H

#include <QWidget>

class QTimer;
class QPushButton;
class QLabel;
class WIDGET_STYLE;
class QElapsedTimer;

class REACTION_SPEED_LOGIC:public QWidget{
    Q_OBJECT
private:
    QTimer *timer = nullptr;
    int ms = 0; //милисекунды

    QPushButton *but_reaction_speed = nullptr;
    QLabel *lab_info = nullptr;
    QLabel *lab_result = nullptr;

    const int MAX_CLICK = 5;//столько раз мы будем кликать для получения среднего результата
    int counter = 0; //счетчик нажатий на кнопку скорости реакции

    float random_time = 0; // рандомное время, которое будет ждать пользователем перед нажатием кнопки
    float reaction_time = 0;

    bool can_click = false; // если уже можно нажимать на кнопку, иначе будет нажатие раньше времени

    WIDGET_STYLE *my_style = nullptr;

public:
    REACTION_SPEED_LOGIC(QPushButton*, QLabel*, QLabel*);
    ~REACTION_SPEED_LOGIC();

private slots:
    void OnTime();
    void ButReactionSpeedPressed();
};

#endif // REACTION_SPEED_LOGIC_H
