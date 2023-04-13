#include "window_forms.h"
#include "print_window_logic.h"
#include "reaction_speed_logic.h"
#include "qcustomplot.h"
#include "client.h"
#include "chat.h"

#include <QtWidgets>



////////////////////////////////////////////////////////////////////////
//////////////////////////WINDOWS::WINDOWS//////////////////////////////
////////////////////////////////////////////////////////////////////////
/// прога запускается здесь, можно запустить любое окно сразу, но в
/// обычном случае это должно быть окно регистрации или входа
WINDOWS::WINDOWS(QWidget *parent) : QWidget(parent){
    //SetRegisterWindow();
    //SetHomeWindow();
    SetPrintWindow();
  // SetReactionSpeedWindow();
    //SetCreateTrainingWindow();

}
////////////////////////////////////////////////////////////////////////
//////////////////////////WINDOWS::WINDOWS//////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////////////WINDOWS::SetRegisterWindow/////////////////////////
////////////////////////////////////////////////////////////////////////
/// создает окно регистрации, компоненты, которые используются на нем,
/// соединяет сигналы со слотами, настраивает стиль
void WINDOWS::SetRegisterWindow(){
    register_form = new QWidget;
    login = "";
    password = "";
    my_style->SetRegistryWindowStyle(register_form);

    QPushButton *but_registration = new QPushButton("Зарегистрироваться"); // заполняем ее объектами
    QPushButton *but_sign_in = new QPushButton("Уже зарегистрированы?");
    QLineEdit *ld_login = new QLineEdit("Введите логин");
    QLineEdit *ld_password = new QLineEdit("Введите пароль");
    QLabel *lab_welcome = new QLabel("Добро пожаловать");

    connect(but_sign_in,SIGNAL(clicked()),this,SLOT(SetSignInWindow())); // соединяем кнопку войти с созданием формы войти
    connect(ld_login,SIGNAL(textChanged(QString)),this,SLOT(SetLoginValue(QString))); //получение введенного логина
    connect(ld_password,SIGNAL(textChanged(QString)),this,SLOT(SetPasswordValue(QString))); //получение введенного пароля
    connect(but_registration,SIGNAL(clicked()),this,SLOT(SendRegistrationDataToDB())); // отправка данных в класс бд при нажатии на кнопку зарегистрироваться

    QVBoxLayout *v_main_register_l  = new QVBoxLayout(register_form);
    QVBoxLayout *v_sec_l = new QVBoxLayout;

    my_style->SetLoginLineEditStyle(ld_login);
    my_style->SetPasswordLineEditStyle(ld_password);
    my_style->SetLabWelcomeStyle(lab_welcome);
    my_style->SetButRegistrationStyle(but_registration);
    my_style->SetButSignInStyle(but_sign_in);

    v_sec_l->addWidget(ld_login);
    v_sec_l->addWidget(ld_password);
    v_sec_l->setSpacing(10);

    v_main_register_l->addWidget(lab_welcome);
    v_main_register_l->addLayout(v_sec_l);
    v_main_register_l->addWidget(but_registration);
    v_main_register_l->addWidget(but_sign_in);

    register_form->setLayout(v_main_register_l);
    register_form->show();
}
////////////////////////////////////////////////////////////////////////
/////////////////////WINDOWS::SetRegisterWindow/////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////WINDOWS::SendRegistrationDataToDB/////////////////////
////////////////////////////////////////////////////////////////////////
/// отправляет логин и пароль на проверку в бд, если все хорошо, то
/// создает форму профиля
void WINDOWS::SendRegistrationDataToDB(){
    if(db->Registration(login, password)){
        delete register_form;
        SetHomeWindow();
    }
}
////////////////////////////////////////////////////////////////////////
//////////////////WINDOWS::SendRegistrationDataToDB/////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////////////WINDOWS::SetSignInWindow///////////////////////////
////////////////////////////////////////////////////////////////////////
/// создает окно входа, компоненты, которые используются на нем,
/// соединяет сигналы со слотами, настраивает стиль
void WINDOWS::SetSignInWindow(){
    sign_in_form = new QWidget;
    delete register_form;

    login = "";
    password = "";

    my_style->SetSignInWindowStyle(sign_in_form);

    QLineEdit *ld_login = new QLineEdit("Введите логин");
    QLineEdit *ld_password = new QLineEdit("Введите пароль");
    QPushButton *but_sign_in = new QPushButton("Войти");
    QPushButton *but_back = new QPushButton("Назад");

    connect(but_back,SIGNAL(clicked()),this,SLOT(SignInButBackClicked()));
    connect(ld_login,SIGNAL(textChanged(QString)),this,SLOT(SetLoginValue(QString))); //получение введенного логина
    connect(ld_password,SIGNAL(textChanged(QString)),this,SLOT(SetPasswordValue(QString))); //получение введенного пароля
    connect(but_sign_in,SIGNAL(clicked()),this,SLOT(SendSignInDataToDB())); // отправка данных в класс бд при нажатии на кнопку войти

    QVBoxLayout *v_main_sign_in_l = new QVBoxLayout(sign_in_form);

    my_style->SetLoginLineEditStyle(ld_login);
    my_style->SetPasswordLineEditStyle(ld_password);
    my_style->SetButBackStyle(but_back);
    my_style->SetButSignInStyle2(but_sign_in);

    v_main_sign_in_l->addWidget(but_back);
    v_main_sign_in_l->addWidget(ld_login);
    v_main_sign_in_l->addWidget(ld_password);
    v_main_sign_in_l->addWidget(but_sign_in,0,Qt::AlignRight);

    sign_in_form->show();
}
////////////////////////////////////////////////////////////////////////
/////////////////////WINDOWS::SetSignInWindow///////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////////////WINDOWS::SendSignInDataToDB////////////////////////
////////////////////////////////////////////////////////////////////////
/// отправляет пароль и логин в бд для проверки на вход, в удачном
/// случае создает форму профиля
void WINDOWS::SendSignInDataToDB(){
    if(db->SignIn(login, password)){
        delete sign_in_form;
        SetHomeWindow();
    }
}
////////////////////////////////////////////////////////////////////////
/////////////////////WINDOWS::SendSignInDataToDB////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
////////////////////WINDOWS::SignInButBackClicked///////////////////////
////////////////////////////////////////////////////////////////////////
/// возвращает пользователя на окно регистрации с окна входа
void WINDOWS::SignInButBackClicked(){
    delete  sign_in_form;
    SetRegisterWindow();
}
////////////////////////////////////////////////////////////////////////
////////////////////WINDOWS::SignInButBackClicked///////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
///////////////////////WINDOWS::SetPrintWindow//////////////////////////
////////////////////////////////////////////////////////////////////////
/// создает окно набора текста, компоненты, которые используются на нем,
/// соединяет сигналы со слотами, настраивает стиль
void WINDOWS::SetPrintWindow(){
    print_form = new QWidget;

    my_style->SetPrintSpeedWindowStyle(print_form);
    QHBoxLayout *h_main_print_l = new QHBoxLayout;

    ///////////////////////////LEFT_LAYOUT/////////////////////
    QVBoxLayout *v_left_l = new QVBoxLayout;
    h_main_print_l->addLayout(v_left_l);
    h_main_print_l->setSpacing(10);

    QPushButton *but_load_training = new QPushButton("Загрузить тренировку");
    QPushButton *but_start = new QPushButton("Начать");
    QPushButton *but_add_training = new QPushButton("Добавить тренировку");
    QPushButton *but_create_training = new QPushButton("Создать тренировку");
    QPushButton *but_show_plot = new QPushButton("Отобразить график");
    QPushButton *but_back = new QPushButton("Назад");
    but_back->setVisible(true);//пока они не используются
    but_add_training->setVisible(false);

    QVBoxLayout *v_buts_l = new QVBoxLayout;

    connect(but_back, SIGNAL(clicked()), this, SLOT(PrintWindowButBackClicked()));
    connect(but_create_training, SIGNAL(clicked()),this, SLOT(SetCreateTrainingWindow()));

    v_left_l->addLayout(v_buts_l);
    v_left_l->setContentsMargins(0,100,0,0);
    v_buts_l->addWidget(but_back,0,Qt::AlignTop);
    v_buts_l->addWidget(but_create_training,0,Qt::AlignTop);
    v_buts_l->addWidget(but_add_training,0,Qt::AlignTop);
    v_buts_l->addWidget(but_show_plot,0,Qt::AlignTop);
    v_buts_l->addWidget(but_load_training,0,Qt::AlignTop);
    v_buts_l->addWidget(but_start,1,Qt::AlignTop);

    QGroupBox *group_report = new QGroupBox;
    QVBoxLayout *v_group_report_l = new QVBoxLayout(group_report);
    QLabel *lab_group_report_info = new QLabel("Общая статистика по словам:");
    QCheckBox *chbox_letter_errors = new QCheckBox("Ошибки в буквах");
    QCheckBox *chbox_syllable_errors = new QCheckBox("Ошибки в слогах");
    QCheckBox *chbox_word_errors = new QCheckBox("Ошибки в словах");
    QCheckBox *chbox_words_speed = new QCheckBox("Средняя скорость слова");
    QPushButton *but_show_word_statistic = new QPushButton("Показать статистику");
    QPushButton *but_create_errors_training = new QPushButton("Создать тренировку по ошибкам");
    v_group_report_l->addWidget(lab_group_report_info);
    v_group_report_l->addWidget(chbox_letter_errors);
    v_group_report_l->addWidget(chbox_syllable_errors);
    v_group_report_l->addWidget(chbox_word_errors);
    v_group_report_l->addWidget(chbox_words_speed);
    v_group_report_l->addWidget(but_show_word_statistic);
    v_group_report_l->addWidget(but_create_errors_training);

    v_left_l->addWidget(group_report);

    ///////////////////////////CENTER_LAYOUT/////////////////////
    QVBoxLayout *v_center_l = new QVBoxLayout;
    h_main_print_l->addLayout(v_center_l);
    QGroupBox *group_game_pole = new QGroupBox;
    group_game_pole->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    v_center_l->addWidget(group_game_pole);
    QVBoxLayout *v_group_game_pole_l = new QVBoxLayout(group_game_pole);
    QTextBrowser *text_browser = new QTextBrowser;
    v_group_game_pole_l->addWidget(text_browser);
    text_browser->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::MinimumExpanding);

    QVBoxLayout *v_game_pole_l = new QVBoxLayout;
    v_group_game_pole_l->addLayout(v_game_pole_l);

    QLineEdit *ld_game_pole = new QLineEdit;
    v_game_pole_l->addWidget(ld_game_pole);

    QHBoxLayout *h_current_info_l = new QHBoxLayout;
    v_game_pole_l->addLayout(h_current_info_l);

    QHBoxLayout *v_current_mistakes_l = new QHBoxLayout;
    h_current_info_l->addLayout(v_current_mistakes_l);
    QLineEdit *ld_current_mistakes = new QLineEdit;
    QLabel *lab_current_mistakes = new QLabel("Ошибки: ");
    v_current_mistakes_l->addWidget(lab_current_mistakes,1,Qt::AlignTop|Qt::AlignLeft);
    v_current_mistakes_l->addWidget(ld_current_mistakes,1,Qt::AlignTop|Qt::AlignLeft);

    QHBoxLayout *v_current_speed_l = new QHBoxLayout;
    h_current_info_l->addLayout(v_current_speed_l);
    QLineEdit *ld_current_speed = new QLineEdit;
    QLabel *lab_current_speed = new QLabel("Скорость:");
    v_current_speed_l->addWidget(lab_current_speed,1,Qt::AlignTop|Qt::AlignLeft);
    v_current_speed_l->addWidget(ld_current_speed,1,Qt::AlignTop|Qt::AlignLeft);

    QHBoxLayout *v_play_time_l = new QHBoxLayout;
    h_current_info_l->addLayout(v_play_time_l);
    QLineEdit *ld_current_min = new QLineEdit;
    QLineEdit *ld_current_sec = new QLineEdit;
    QLabel *lab_play_time = new QLabel("Время набора мин:");
   // QLabel *lab_current_min = new QLabel("мин:");
    QLabel *lab_current_sec = new QLabel("сек:");
    v_play_time_l->addWidget(lab_play_time,1,Qt::AlignTop|Qt::AlignRight);
    //v_play_time_l->addWidget(lab_current_min,1,Qt::AlignTop|Qt::AlignRight);
    v_play_time_l->addWidget(ld_current_min,1,Qt::AlignTop);
    v_play_time_l->addWidget(lab_current_sec,1,Qt::AlignTop|Qt::AlignRight);
    v_play_time_l->addWidget(ld_current_sec,1,Qt::AlignTop);

    my_style->SetLdCurrentInfoStyle(ld_current_min);
    my_style->SetLdCurrentInfoStyle(ld_current_mistakes);
    my_style->SetLdCurrentInfoStyle(ld_current_sec);
    my_style->SetLdCurrentInfoStyle(ld_current_speed);

    QTextBrowser *text_mistakes_browser = new QTextBrowser;
    v_group_game_pole_l->addWidget(text_mistakes_browser);
    text_mistakes_browser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    text_mistakes_browser->setVisible(false);



    QGroupBox *group_plot = new QGroupBox; // группа отображения графика на форме
    v_center_l->addWidget(group_plot);
    group_plot->setTitle("Результаты работы за промежуток");
    QVBoxLayout *v_group_l = new QVBoxLayout(group_plot);
    QHBoxLayout *h_group_l = new QHBoxLayout();
    v_group_l->addLayout(h_group_l);
    QLabel *lab_interval = new QLabel("Выберите интервал отображения данных");
    QPushButton *but_hide_group_plot = new QPushButton("Убрать график");
    QComboBox *box_from_year = new QComboBox;
    QComboBox *box_from_month = new QComboBox;
    QComboBox *box_to_year = new QComboBox;
    QComboBox *box_to_month = new QComboBox;
    h_group_l->addWidget(lab_interval);
    h_group_l->addWidget(box_from_year);
    h_group_l->addWidget(box_from_month);
    h_group_l->addWidget(box_to_year);
    h_group_l->addWidget(box_to_month);
    h_group_l->addWidget(but_hide_group_plot);
    plot = new QCustomPlot;
    v_group_l->addWidget(plot);
    QHBoxLayout *h_plot_l = new QHBoxLayout;
    v_group_l->addLayout(h_plot_l);
    QLineEdit *ld_plot_value = new QLineEdit;
    h_plot_l->addWidget(ld_plot_value);

    QCheckBox *chbox_speed = new QCheckBox("Скорость");
    QCheckBox *chbox_mistake = new QCheckBox("Ошибки");
    QCheckBox *chbox_amount_text = new QCheckBox("Кол-во текстов");
    h_plot_l->addWidget(chbox_speed);
    h_plot_l->addWidget(chbox_mistake);
    h_plot_l->addWidget(chbox_amount_text);

    my_style->SetTextBrowserStyle(text_browser);
    my_style->SetTextBrowserStyle(text_mistakes_browser);
    my_style->SetBoxsMonthsStyle(box_from_month);
    my_style->SetBoxsMonthsStyle(box_to_month);
    my_style->SetBoxsYearsStyle(box_from_year);
    my_style->SetBoxsYearsStyle(box_to_year);
    my_style->SetPlotSpeedStyle(plot);
    my_style->SetGroupPlotStyle(group_plot);


    ///////////////////////////RIGHT_LAYOUT/////////////////////
    QVBoxLayout *v_right_l = new QVBoxLayout;
    h_main_print_l->addLayout(v_right_l);

    QPushButton *but_lost = new QPushButton("Сбился");
    v_right_l->addWidget(but_lost);
    QPushButton *but_voice_settings = new QPushButton("Настройка озвучки");
    v_right_l->addWidget(but_voice_settings);
    QComboBox *box_mode_name = new QComboBox;
    v_right_l->addWidget(box_mode_name);
    QComboBox *box_training_name = new QComboBox;
    v_right_l->addWidget(box_training_name);
    QVBoxLayout *v_info_l = new QVBoxLayout;
    v_right_l->addLayout(v_info_l);
    v_right_l->setContentsMargins(0,100,0,0);
    v_info_l->setSpacing(10);


    QHBoxLayout *h_text_amount_l = new QHBoxLayout();
    v_info_l->addLayout(h_text_amount_l);
    QLabel *lab_text_amount = new QLabel("Пройдено");
    QLineEdit *ld_text_amount = new QLineEdit;
    lab_text_amount->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    ld_text_amount->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    h_text_amount_l->addWidget(lab_text_amount,0,Qt::AlignLeft);
    h_text_amount_l->addWidget(ld_text_amount,0,Qt::AlignRight);

    QHBoxLayout *h_record_l = new QHBoxLayout();
    v_info_l->addLayout(h_record_l);
    QLabel *lab_record = new QLabel("Рекорд");
    QLineEdit *ld_record = new QLineEdit;
    lab_record->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    ld_record->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    h_record_l->addWidget(lab_record,0,Qt::AlignLeft);
    h_record_l->addWidget(ld_record,0,Qt::AlignRight);

    QHBoxLayout *h_average_speed_l = new QHBoxLayout();
    v_info_l->addLayout(h_average_speed_l);
    QLabel *lab_average_speed = new QLabel("Средняя скорость");
    QLineEdit *ld_average_speed = new QLineEdit;
    lab_average_speed->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    ld_average_speed->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    h_average_speed_l->addWidget(lab_average_speed,0,Qt::AlignLeft);
    h_average_speed_l->addWidget(ld_average_speed,0,Qt::AlignRight);

    QHBoxLayout *h_mistakes_l = new QHBoxLayout();
    v_info_l->addLayout(h_mistakes_l);
    QLabel *lab_mistakes = new QLabel("Ошибки");
    QLineEdit *ld_mistakes = new QLineEdit;
    lab_mistakes->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    ld_mistakes->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    h_mistakes_l->addWidget(lab_mistakes,0,Qt::AlignLeft);
    h_mistakes_l->addWidget(ld_mistakes,0,Qt::AlignRight);

    QHBoxLayout *h_all_time_l = new QHBoxLayout();
    v_info_l->addLayout(h_all_time_l);
    QLabel *lab_all_time = new QLabel("Потрачено времени");
    QLineEdit *ld_all_time = new QLineEdit;
    lab_all_time->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    ld_all_time->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    h_all_time_l->addWidget(lab_all_time,0,Qt::AlignLeft);
    h_all_time_l->addWidget(ld_all_time,0,Qt::AlignRight);

    QSpacerItem *info_l_spacer = new QSpacerItem(0,100,QSizePolicy::Fixed,QSizePolicy::Expanding);
    v_right_l->addSpacerItem(info_l_spacer);

    my_style->SetLdInfoStyle(ld_text_amount);
    my_style->SetLdInfoStyle(ld_record);
    my_style->SetLdInfoStyle(ld_average_speed);
    my_style->SetLdInfoStyle(ld_mistakes);
    my_style->SetLdInfoStyle(ld_all_time);

    print_window_logic = new PRINT_WINDOW_LOGIC(but_lost,but_voice_settings,but_start, but_load_training,box_mode_name,box_training_name, ld_game_pole, ld_current_mistakes,
    ld_current_speed, ld_text_amount, ld_record, ld_average_speed,  ld_mistakes, ld_all_time, ld_current_min, ld_current_sec, text_mistakes_browser,
    text_browser, lab_current_mistakes, but_create_training, but_add_training, but_show_plot, plot, but_hide_group_plot, box_from_year,
    box_from_month, box_to_year, box_to_month, group_plot, ld_plot_value, group_game_pole,chbox_amount_text,
    chbox_speed, chbox_mistake, chbox_letter_errors, chbox_syllable_errors, chbox_word_errors, chbox_words_speed, but_show_word_statistic,
    group_report, but_create_errors_training); //здесь мы передаем объекты в класс осуществляющий взаимодействие с пользователем

    print_form->setLayout(h_main_print_l);
    print_form->show();
}
////////////////////////////////////////////////////////////////////////
///////////////////////WINDOWS::SetPrintWindow//////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////////WINDOWS::PrintWindowButBackClicked/////////////////////
////////////////////////////////////////////////////////////////////////
/// возвращает пользователя на форму профиля с окна тренировки
void WINDOWS::PrintWindowButBackClicked(){
    delete print_form;
    SetHomeWindow();
}
////////////////////////////////////////////////////////////////////////
/////////////////WINDOWS::PrintWindowButBackClicked/////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////////WINDOWS::SetHomeWindow////////////////////////////
////////////////////////////////////////////////////////////////////////
/// создает окно профиля, компоненты, которые используются на нем,
/// соединяет сигналы со слотами, настраивает стиль
void WINDOWS::SetHomeWindow(){    
    home_form = new QWidget;
    my_style->SetHomeWindowStyle(home_form);


    QVBoxLayout *v_main_home_l = new QVBoxLayout;
    home_form->setLayout(v_main_home_l);

    QHBoxLayout* h_home_l = new QHBoxLayout;
    v_main_home_l->addLayout(h_home_l);

    // ПРОФИЛЬ
    QLabel *lab_back_ground_image = new QLabel();
    lab_back_ground_image->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::MinimumExpanding);
    QPixmap image;
    image.load(":/images/girl.jpg");
    lab_back_ground_image->setMaximumHeight(500);
    //lab_back_ground_image->resize(image.size());
    lab_back_ground_image->setScaledContents(true);
    lab_back_ground_image->setPixmap(image);

    QWidget *w_back_ground_info = new QWidget;
    QLabel *t = new QLabel(w_back_ground_info);
    t->setGeometry(50,50,300,300);
    t->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    QPixmap ti;
    ti.load(":/images/girl2.jpg");
    t->setScaledContents(true);
    t->setPixmap(ti);

    QVBoxLayout *v_back_ground_l = new QVBoxLayout;
    h_home_l->addLayout(v_back_ground_l);

    v_back_ground_l->addWidget(lab_back_ground_image);
    v_back_ground_l->addWidget(w_back_ground_info);


    //lab_back_ground_image->setStyleSheet("background-color: rgb(10, 230, 255);");
    //v_back_ground_l->addWidget(lab_back_ground_image);







    QToolBox *tb_home_panel = new QToolBox;
    my_style->SetTBHomePanelStyle(tb_home_panel);
    //ПРОФИЛЬ
    QWidget *page_profile = new QWidget;
    QVBoxLayout *v_page_profile_l = new QVBoxLayout(page_profile);
    QLabel *lab_user = new QLabel("login");
    v_page_profile_l->addWidget(lab_user);

    //ЧАТ
    CHAT *chat = new CHAT;
    chat->setGeometry(0,0,300,600);

    QWidget *page_chat = new QWidget;
    QVBoxLayout *v_page_chat_l = new QVBoxLayout(page_chat);



   // QTextBrowser *text_browser = new QTextBrowser;
    v_page_chat_l->addWidget(chat);
    chat->setAutoFillBackground(true);

    QHBoxLayout *h_send_message_l = new QHBoxLayout;
    v_page_chat_l->addLayout(h_send_message_l);

    ld_message = new QLineEdit;
    h_send_message_l->addWidget(ld_message);

    but_send_message = new QPushButton;
    h_send_message_l->addWidget(but_send_message);

    client = new CLIENT(chat,ld_message);
    client->connectToHost("localhost", 2282);

    connect(but_send_message, SIGNAL(clicked()),this, SLOT(HomeButSendMessagePressed()));
    connect(ld_message, SIGNAL(returnPressed()),this, SLOT(HomeLdEnterPressed()));

    //ВЫБОР РЕЖИМА
    QWidget *page_choice_mode = new QWidget;
    QVBoxLayout *v_page_choice_l = new QVBoxLayout(page_choice_mode);

    QPushButton *but_print_speed = new QPushButton("Скорость печати");
    QPushButton *but_reaction_speed_test = new QPushButton("Тест скорости реакции");

    connect(but_print_speed,SIGNAL(clicked()),this,SLOT(HomeButPrintSpeedClicked()));
    connect(but_reaction_speed_test, SIGNAL(clicked()),this, SLOT(HomeButReactionSpeedClicked()));

    v_page_choice_l->addWidget(but_print_speed,0,Qt::AlignTop);
    v_page_choice_l->addWidget(but_reaction_speed_test,10,Qt::AlignTop);
    page_choice_mode->setLayout(v_page_choice_l);


    //ДРУЗЬЯ
    QWidget *page_friends = new QWidget;
    //НОВОСТИ
    QWidget *page_news = new QWidget;
    //НАСТРОЙКИ
    QWidget *page_settings = new QWidget; // нужен для помещения в закладку компоновки с виджетами
    //QVBoxLayout* v_page_settings_l = new QVBoxLayout(page_settings);//компоновка для виджетов

    tb_home_panel->addItem(page_profile,"Профиль");
    tb_home_panel->addItem(page_chat,"Общение");
    tb_home_panel->addItem(page_choice_mode,"Выбрать режим");
    tb_home_panel->addItem(page_friends,"Друзья");
    tb_home_panel->addItem(page_news,"Новости");
    tb_home_panel->addItem(page_settings,"Настройки");


    h_home_l->addWidget(tb_home_panel,0,Qt::AlignRight);

    home_form->show();
}
////////////////////////////////////////////////////////////////////////
//////////////////////WINDOWS::SetHomeWindow////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////////WINDOWS::HomeButPrintSpeedClicked//////////////////////
////////////////////////////////////////////////////////////////////////
/// переводит пользователя на окно тренировки скорости печати
void WINDOWS::HomeButPrintSpeedClicked(){
    delete home_form;
    SetPrintWindow();
}
////////////////////////////////////////////////////////////////////////
/////////////////WINDOWS::HomeButPrintSpeedClicked//////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
////////////////WINDOWS::HomeButReactionSpeedClicked////////////////////
////////////////////////////////////////////////////////////////////////
/// переводит пользователя на окно теста реакции
void WINDOWS::HomeButReactionSpeedClicked(){
    delete home_form;
    SetReactionSpeedWindow();
}
////////////////////////////////////////////////////////////////////////
////////////////WINDOWS::HomeButReactionSpeedClicked////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
////////////////WINDOWS::HomeButSendMessagePressed//////////////////////
////////////////////////////////////////////////////////////////////////
/// отправка сообщения другим пользователям
void WINDOWS::HomeButSendMessagePressed(){
    client->SendToServer(ld_message->text());
}
////////////////////////////////////////////////////////////////////////
////////////////WINDOWS::HomeButSendMessagePressed//////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////////////WINDOWS::HomeLdEnterPressed////////////////////////
////////////////////////////////////////////////////////////////////////
/// отправка сообщения другим пользователям
void WINDOWS::HomeLdEnterPressed(){
    client->SendToServer(ld_message->text());
}
////////////////////////////////////////////////////////////////////////
/////////////////////WINDOWS::HomeLdEnterPressed////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////////WINDOWS::SetCreateTrainingWindow///////////////////////
////////////////////////////////////////////////////////////////////////
/// создает окно создания пользовательской тренировки, компоненты,
/// которые используются на нем,соединяет сигналы со слотами, настраивает
/// стиль
void WINDOWS::SetCreateTrainingWindow(){

    create_training_form = new QWidget();
    create_training_form->setWindowModality(Qt::ApplicationModal);
    //SetCurrentPageOnLay(create_training_page);
    my_style->SetCreateTrainingWindowStyle(create_training_form);

    setEnabled(false);
    connect(create_training_form, SIGNAL(destroyed()),this, SLOT(CreateTrainingWindowClosed()));
    QVBoxLayout *v_create_training_l = new QVBoxLayout(create_training_form);

    QLineEdit *ld_add_word = new QLineEdit;
    QLineEdit *ld_training_name = new QLineEdit;
    QLineEdit *ld_current_symbols = new QLineEdit;
    QLineEdit *ld_delete_word = new QLineEdit;
    QLabel *lab_add_rules = new QLabel("Правила создания тренировки:");
    QLabel *lab_training_name = new QLabel("Название тренировки:");
    QLabel *lab_current_symbols = new QLabel("Введено символов:");
    QLabel *lab_word = new QLabel ("Слово:");
    QLabel *lab_status = new QLabel("Статус:");
    QPushButton *but_add_word = new QPushButton("Добавить слово");
    QPushButton *but_publish_training = new QPushButton("Опубликовать");
    QPushButton *but_add_file = new QPushButton("Добавить файл");
    QPushButton *but_delete_last_word = new QPushButton("Удалить последнее слово");
    QPushButton *but_delete_word = new QPushButton("Удалить слово");
    QTextBrowser *browser_training_word = new QTextBrowser;

    QHBoxLayout *h_first_l = new QHBoxLayout();
    v_create_training_l->addLayout(h_first_l);


    QVBoxLayout *v_labels_l = new QVBoxLayout();
    h_first_l->addLayout(v_labels_l);
    v_labels_l->addWidget(lab_training_name);
    v_labels_l->addWidget(lab_word);
    v_labels_l->addWidget(lab_current_symbols);


    QVBoxLayout *v_line_edits_l = new QVBoxLayout();
    h_first_l->addLayout(v_line_edits_l);
    v_line_edits_l->addWidget(ld_training_name);
    v_line_edits_l->addWidget(ld_add_word);
    v_line_edits_l->addWidget(ld_current_symbols);


    QVBoxLayout *v_buttons_l = new QVBoxLayout;
    h_first_l->addLayout(v_buttons_l);
    v_buttons_l->addWidget(but_add_file);
    v_buttons_l->addWidget(but_add_word);
    v_buttons_l->addWidget(but_publish_training);


    QHBoxLayout *h_second_l = new QHBoxLayout;
    v_create_training_l->addLayout(h_second_l);
    QVBoxLayout *v_status_l = new QVBoxLayout;
    h_second_l->addLayout(v_status_l);
    v_status_l->addWidget(lab_status,0,Qt::AlignTop);
    v_status_l->addWidget(but_delete_word,100,Qt::AlignBottom);
    v_status_l->addWidget(ld_delete_word,1,Qt::AlignBottom);
    v_status_l->addWidget(but_delete_last_word,0,Qt::AlignBottom);
    h_second_l->addWidget(browser_training_word);

    v_create_training_l->addWidget(lab_add_rules);

    my_style->SetLdGeneralTrainingWindowStyle(ld_training_name);
    my_style->SetLdGeneralTrainingWindowStyle(ld_add_word);
    my_style->SetLdCurrentSymbolsStyle(ld_current_symbols);
    my_style->SetLdGeneralTrainingWindowStyle(ld_delete_word);
    my_style->SetLabAddRulesStyle(lab_add_rules);
    my_style->SetLabGeneralTrainingWindowStyle(lab_training_name);
    my_style->SetLabGeneralTrainingWindowStyle(lab_current_symbols);
    my_style->SetLabGeneralTrainingWindowStyle(lab_word);
    my_style->SetLabStatusStyle(lab_status);
    my_style->SetButGeneralTrainingWindwowStyle(but_add_word);
    my_style->SetButGeneralTrainingWindwowStyle(but_publish_training);
    my_style->SetButGeneralTrainingWindwowStyle(but_add_file);
    my_style->SetButGeneralTrainingWindwowStyle(but_delete_last_word);
    my_style->SetButGeneralTrainingWindwowStyle(but_delete_word);
    my_style->SetBrowserTrainingWordStyle(browser_training_word);

    print_window_logic->GetCreateTrainingComponents(but_delete_word, but_delete_last_word, but_add_file, but_add_word, but_publish_training,
    ld_delete_word, ld_training_name, ld_add_word, ld_current_symbols, lab_status, browser_training_word);// указатели на компоненты в доп окне create_training в print_window
}
////////////////////////////////////////////////////////////////////////
/////////////////WINDOWS::SetCreateTrainingWindow///////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////////WINDOWS::SetReactionSpeedWindow////////////////////////
////////////////////////////////////////////////////////////////////////
/// создает окно теста реакции, компоненты, которые используются на нем,
/// соединяет сигналы со слотами, настраивает стиль
void WINDOWS::SetReactionSpeedWindow(){
    reaction_speed_form = new QWidget;

    my_style->SetReactionSpeedWindowStyle(reaction_speed_form);

    //connect(reaction_speed_page, &QObject::deleteLater, this, &WINDOW::ReactionSpeedWindowClosed);
    //reaction_speed_page->deleteLater()
    QVBoxLayout *v_main_reaction_speed_l = new QVBoxLayout;

    QLabel *lab_info = new QLabel("Тест-тренажер на скорость реакции \n"
                                  "Трактовка результатов\n"
                                  "\n"
                                  "до 150мс Превосходно! Можно садиться за штурвал истребителя или болида формулы 1.\n"
                                  "от 150 - 170мс Это пять с плюсом! Чемпионы мира по пинг-понгу и боксу смотрят на Вас как на конкурента.\n"
                                  "от 170 - 190мс Великолепно! Мастера спорта международного класса одобряют.\n"
                                  "от 190 - 200мс Хорошо! Мастер спорта у Вас в кармане.\n"
                                  "от 200 - 210мс Неплохо. КМС зачтен.\n"
                                  "от 210 - 230мс Нормально. Вы активны, можете лучше.\n"
                                  "от 230 - 270мс Средненько. Скорость реакции, как и у большинства людей.\n"
                                  "от 270 - 350мс Неуд.\n"
                                  "от 350 - 500мс Незачет.\n"
                                  "от 500 и выше Вы вообще живы там? Лучше отдохните, попробуйте завтра.) \n");

    QPushButton *but_reaction_speed = new QPushButton("Начать тест");
    QLabel *lab_result = new QLabel("Результат");

    v_main_reaction_speed_l->addWidget(lab_info,0,Qt::AlignCenter);
    v_main_reaction_speed_l->addWidget(lab_result,0,Qt::AlignCenter);
    v_main_reaction_speed_l->addWidget(but_reaction_speed);

    my_style->SetButReactionSpeedStyle(but_reaction_speed);
    my_style->SetLabResultStyle(lab_result);
    my_style->SetLabInfoStyle(lab_info);

    reaction_speed_logic = new REACTION_SPEED_LOGIC(but_reaction_speed,lab_info, lab_result);
    reaction_speed_form->setLayout(v_main_reaction_speed_l);
    reaction_speed_form->show();
}
////////////////////////////////////////////////////////////////////////
/////////////////WINDOWS::SetReactionSpeedWindow////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
////////////////WINDOWS::ReactionSpeedWindowClosed//////////////////////
////////////////////////////////////////////////////////////////////////
/// закрывает окно теста на реакцию и перводит в окно профиля
void WINDOWS::ReactionSpeedWindowClosed(){
    delete reaction_speed_form;
    SetHomeWindow();
}
////////////////////////////////////////////////////////////////////////
////////////////WINDOWS::ReactionSpeedWindowClosed//////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////////WINDOWS::CreateTrainingWindowClosed////////////////////
////////////////////////////////////////////////////////////////////////
/// закрывает окно создания пользовательской тренировки
void WINDOWS::CreateTrainingWindowClosed(){
    setEnabled(true);
}
////////////////////////////////////////////////////////////////////////
/////////////////WINDOWS::CreateTrainingWindowClosed////////////////////
////////////////////////////////////////////////////////////////////////

