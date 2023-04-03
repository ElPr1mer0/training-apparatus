#include "reaction_speed_logic.h"
#include "widget_style.h"

#include <QtWidgets>
#include <ctime>

////////////////////////////////////////////////////////////////////////
/////////////REACTION_SPEED_LOGIC::REACTION_SPEED_LOGIC/////////////////
////////////////////////////////////////////////////////////////////////
/// получает виджеты для обработки их действий на форме, соединяет
/// слоты со сигналами
REACTION_SPEED_LOGIC::REACTION_SPEED_LOGIC(QPushButton *but_reaction_speed, QLabel *lab_info, QLabel *lab_result){
    this->but_reaction_speed = but_reaction_speed;
    this->lab_info = lab_info;
    this->lab_result = lab_result;


    my_style = new WIDGET_STYLE; //создаем свой стиль
    timer = new QTimer();
    timer->setTimerType(Qt::PreciseTimer);
    connect (timer, SIGNAL(timeout()),this, SLOT(OnTime()));

    connect(this->but_reaction_speed,SIGNAL(pressed()), this, SLOT(ButReactionSpeedPressed()));
    std::srand(time(NULL));
}
////////////////////////////////////////////////////////////////////////
/////////////REACTION_SPEED_LOGIC::REACTION_SPEED_LOGIC/////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////REACTION_SPEED_LOGIC::~REACTION_SPEED_LOGIC////////////////
////////////////////////////////////////////////////////////////////////
REACTION_SPEED_LOGIC::~REACTION_SPEED_LOGIC(){
    delete but_reaction_speed;
    delete lab_info;
    delete lab_result;
    delete my_style;
    delete timer;
}
////////////////////////////////////////////////////////////////////////
/////////////REACTION_SPEED_LOGIC::~REACTION_SPEED_LOGIC////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
////////////////REACTION_SPEED_LOGIC::OnTime////////////////////////////
////////////////////////////////////////////////////////////////////////
/// таймер, меняет стиль кнопки, когда надо нажимать
void REACTION_SPEED_LOGIC::OnTime(){
    ++ms;
    if(ms >= random_time){
        can_click = true;
        my_style->SetButReactionSpeedCanClickStyle(but_reaction_speed);
        ms = 0;
    }
}
////////////////////////////////////////////////////////////////////////
////////////////REACTION_SPEED_LOGIC::OnTime////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////REACTION_SPEED_LOGIC::ButReactionSpeedPressed//////////////
////////////////////////////////////////////////////////////////////////
/// обработка нажатий на кнопку при тесте скорости реакции
void REACTION_SPEED_LOGIC::ButReactionSpeedPressed(){
    ++counter;
    if(counter == 1){ //первое нажатие
        random_time = (rand() %(1+5-1)+1)*1000; // получаем время ожидания перед нажатием *1000 = мc
        can_click = false;
        but_reaction_speed->setText("Ждите зелёный!");
        timer->start(1);

    }
    else if (counter < MAX_CLICK+1){// после первого нажатия тест запущен, надо обрабатывать след нажатия на кнопку
        if(can_click){ //если уже можно нажимать (когда кнопка загорелась)
            reaction_time += ms;
            lab_result->setText(QString::number(ms));
            can_click = false;
            my_style->SetButReactionSpeedStyle(but_reaction_speed);
            but_reaction_speed->setText("Ждите зелёный!");
            ms = 0;
        }else{
            --counter;
            qDebug()<<"РАНО!!!";
            ms = 0;
            can_click = false;
        }
    }
    else if(counter == MAX_CLICK+1){
        if(can_click){
            reaction_time += ms;
            lab_result->setText(QString::number(ms));
            my_style->SetButReactionSpeedStyle(but_reaction_speed);
            but_reaction_speed->setText("Начать тест");
            counter = 0;
            timer->stop();
            ms = 0;
            lab_result->setText("Средняя скорость нажатия :"+QString::number(reaction_time/MAX_CLICK));
            reaction_time = 0;
            can_click = false;
        }
        else{
            --counter;
            qDebug()<<"РАНО!!!";
            ms = 0;
            can_click = false;
        }
    }
}
////////////////////////////////////////////////////////////////////////
/////////////REACTION_SPEED_LOGIC::ButReactionSpeedPressed//////////////
////////////////////////////////////////////////////////////////////////
