#ifndef WINDOW_H
#define WINDOW_H

#include "db.h"
#include "widget_style.h"
#include <QVBoxLayout>
#include <QDebug>

class PRINT_WINDOW_LOGIC;
class REACTION_SPEED_LOGIC;


class WINDOW : public QWidget{
    Q_OBJECT

public:

private:
    QWidget *sign_in_page = nullptr; // страница войти
    QWidget *register_page = nullptr; //страница регистрации
    QWidget *home_page = nullptr;
    QWidget *print_page = nullptr;
    QWidget *reaction_speed_page = nullptr;
    QWidget *create_training_page = nullptr;

    QVBoxLayout *page_l = new QVBoxLayout; // компоновщик

    DB *db = new DB; // указатель на класс работы с базой данных
    WIDGET_STYLE *my_style = new WIDGET_STYLE;

    QString login; //для отправки в бд
    QString password;

    PRINT_WINDOW_LOGIC *print_window_logic = nullptr;
    REACTION_SPEED_LOGIC *reaction_speed_logic = nullptr;  


public slots:
    void SetSignInWindow(); //создает окно входа
    void SetRegisterWindow();//создает окно регистрации
    void SetHomeWindow(QWidget*); // основное переходное окно
    void SetPrintWindow();
    void SetCreateTrainingWindow();
    void SetReactionSpeedWindow();

    void SetLoginValue(QString login){this->login = login;};
    void SetPasswordValue(QString password){this->password = password;};

    void SendRegistrationDataToDB(){if(db->Registration(login, password)) SetHomeWindow(register_page); delete db;}; //отправляет данные в бд для проверки регистрации
    void SendSignInDataToDB(){if(db->SignIn(login, password)) SetHomeWindow(sign_in_page); delete db;}; //и входа, если все ок, то переходим в форму home

    void PrintWindowButBackClicked(){SetHomeWindow(print_page);}; //обертка обработки события нажатия на кнопку назад в print_window

private slots:
    void CreateTrainingWindowClosed();

public:
    WINDOW(QWidget *parent = nullptr);
    ~WINDOW(){};

private:
    void DeletePageFromLay(QWidget*);// удаляет страницу
    void SetCurrentPageOnLay(QWidget*); //устанавливает на основной слой текущую страницу

};
#endif // WINDOW_H
