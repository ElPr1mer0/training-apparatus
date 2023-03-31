#ifndef WINDOW_FORMS_H
#define WINDOW_FORMS_H

#include "client.h"
#include "db.h"
#include "widget_style.h"

#include <QVBoxLayout>

class PRINT_WINDOW_LOGIC;
class REACTION_SPEED_LOGIC;
class QCustomPlot;
class QCPGraph;
class QCPRange;
class CLIENT;

class WINDOWS : public QWidget{
    Q_OBJECT

public:

private:
    QWidget *sign_in_form = nullptr; // страница войти
    QWidget *register_form = nullptr; //страница регистрации
    QWidget *home_form = nullptr;
    QWidget *print_form = nullptr;
    QWidget *reaction_speed_form = nullptr;
    QWidget *create_training_form = nullptr;

    QCustomPlot *plot = nullptr;    // Объявляем графическое полотно
    QCPGraph *graphic = nullptr;          // Объявляем график


    DB *db = new DB; // указатель на класс работы с базой данных
    WIDGET_STYLE *my_style = new WIDGET_STYLE;

    QString login; //для отправки в бд
    QString password;

    PRINT_WINDOW_LOGIC *print_window_logic = nullptr;
    REACTION_SPEED_LOGIC *reaction_speed_logic = nullptr;

    CLIENT *client = nullptr;

    QPushButton *but_send_message= nullptr;
    QLineEdit *ld_message = nullptr;

private slots:
    // REGISTRATION WINDOW SLOTS
    void SetRegisterWindow();//создает окно регистрации
    void SetLoginValue(QString login){this->login = login;};
    void SetPasswordValue(QString password){this->password = password;};
    void SendRegistrationDataToDB(); //отправляет данные в бд для проверки регистрации


    // SIGN IN WINDOW SLOTS
    void SetSignInWindow(); //создает окно входа
    void SendSignInDataToDB(); //и входа, если все ок, то переходим в форму home
    void SignInButBackClicked();

    // PRINT WINDOW SLOTS
    void SetPrintWindow();
    void PrintWindowButBackClicked(); //обертка обработки события нажатия на кнопку назад в print_window

    // HOME WINDOW SLOTS
    void SetHomeWindow();
    void HomeButPrintSpeedClicked();
    void HomeButReactionSpeedClicked();
    void HomeButSendMessagePressed();
    void HomeLdEnterPressed();

    // CREATE TRAINING WINDOW
    void SetCreateTrainingWindow();

    // REACTION SPEED TEST
    void SetReactionSpeedWindow();
    void ReactionSpeedWindowClosed();

private slots:
    void CreateTrainingWindowClosed();

public:
    WINDOWS(QWidget *parent = nullptr);
    ~WINDOWS(){delete client;};
};
#endif // WINDOW_FORMS_H
