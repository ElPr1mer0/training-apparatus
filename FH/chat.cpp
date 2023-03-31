#include "chat.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include <QScrollArea>

CHAT::CHAT(){
    v_main_chat_l = new QVBoxLayout;
    setStyleSheet("CHAT{"
                 //   "background-color:  #6F70D9;"
                  " background-color: rgb(143, 123, 255);"
                  "}");

    setLayout(v_main_chat_l);

    //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    v_main_chat_l->setAlignment(Qt::AlignTop | Qt::AlignRight);

}


void CHAT::AddMessageToField(const QString &message, const QString &time, int server){
    message_container = new QLabel(message + time);
    message_container->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    message_container->setWordWrap(true);
    server == 0 ? v_main_chat_l->addWidget(message_container,0,Qt::AlignRight|Qt::AlignTop):
                  v_main_chat_l->addWidget(message_container,0,Qt::AlignLeft|Qt::AlignTop);


    AddMessageToHistory(message_container);
    SetMessageContanierStyle(message_container);
}

void CHAT::AddMessageToHistory(QLabel *message_container){
    history.append(message_container);
}

void CHAT::SetMessageContanierStyle(QLabel *message_container){
    //message_container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //message_container->setMaximumWidth(this->width()/1.3);
    //message_container->setStyleSheet("background-color:  #166EF2;");

}
