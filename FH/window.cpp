#include "window.h"
#include "print_window_logic.h"
#include "reaction_speed_logic.h"
#include <QtWidgets>




WINDOW::WINDOW(QWidget *parent) : QWidget(parent){
    //SetRegisterWindow();
   // SetHomeWindow(register_page);
   // SetPrintWindow();
  // SetReactionSpeedWindow();
    //SetCreateTrainingWindow();

}

void WINDOW::DeletePageFromLay(QWidget *page){
    page_l->removeWidget(page);
    delete page;
}


void WINDOW::SetCurrentPageOnLay(QWidget *page){
    page_l->addWidget(page);
    WINDOW::setLayout(page_l);
}

void WINDOW::CreateTrainingWindowClosed(){
    setEnabled(true);
}


void WINDOW::SetRegisterWindow(){
    register_page = new QWidget;
    login = "";
    password = "";
    my_style->SetRegistryWindowStyle(register_page);

    if(sign_in_page != nullptr ) WINDOW::DeletePageFromLay(sign_in_page); // если форма войти была уже создана

    QPushButton *but_registration = new QPushButton("Зарегистрироваться"); // заполняем ее объектами
    QPushButton *but_sign_in = new QPushButton("Уже зарегистрированы?");
    QLineEdit *ld_login = new QLineEdit("Введите логин");
    QLineEdit *ld_password = new QLineEdit("Введите пароль");
    QLabel *lab_welcome = new QLabel("Добро пожаловать");

    connect(but_sign_in,SIGNAL(clicked()),this,SLOT(SetSignInWindow())); // соединяем кнопку войти с созданием формы войти   
    connect(ld_login,SIGNAL(textChanged(QString)),this,SLOT(SetLoginValue(QString))); //получение введенного логина
    connect(ld_password,SIGNAL(textChanged(QString)),this,SLOT(SetPasswordValue(QString))); //получение введенного пароля
    connect(but_registration,SIGNAL(clicked()),this,SLOT(SendRegistrationDataToDB())); // отправка данных в класс бд при нажатии на кнопку зарегистрироваться

    QVBoxLayout *v_register_l = new QVBoxLayout(register_page);
    QVBoxLayout *v_sec_l = new QVBoxLayout;

    my_style->SetLoginLineEditStyle(ld_login);
    my_style->SetPasswordLineEditStyle(ld_password);
    my_style->SetLabWelcomeStyle(lab_welcome);
    my_style->SetButRegistrationStyle(but_registration);
    my_style->SetButSignInStyle(but_sign_in);

    v_sec_l->addWidget(ld_login);
    v_sec_l->addWidget(ld_password);
    v_sec_l->setSpacing(10);

    v_register_l->addWidget(lab_welcome);
    v_register_l->addLayout(v_sec_l);
    v_register_l->addWidget(but_registration);
    v_register_l->addWidget(but_sign_in);

    SetCurrentPageOnLay(register_page);
}


void WINDOW::SetHomeWindow(QWidget *page){
    home_page = new QWidget;
    my_style->SetHomeWindowStyle(home_page);
    WINDOW::DeletePageFromLay(page);

    QVBoxLayout *v_home_l = new QVBoxLayout;
    QHBoxLayout* h_home_l = new QHBoxLayout;
    QToolBox *tb_home_panel = new QToolBox;
    tb_home_panel->setMinimumSize(200,800);
    tb_home_panel->setMaximumSize(200,800);

    QWidget *page_profile = new QWidget(tb_home_panel);
    QWidget *page_settings = new QWidget(tb_home_panel); // нужен для помещения в закладку компоновки с виджетами
    QWidget *page_choice = new QWidget(tb_home_panel);

    QVBoxLayout* v_page_profile_l = new QVBoxLayout(page_profile);
 //   QVBoxLayout* v_page_settings_l = new QVBoxLayout(page_settings);//компоновка для виджетов
    QVBoxLayout* v_page_choice_l = new QVBoxLayout(page_choice);

    QLabel *lab_user = new QLabel(login,page_settings);
    QPushButton *but_print_speed = new QPushButton("Скорость печати",page_choice);
    QPushButton *but_reaction_speed_test = new QPushButton("Тест скорости реакции",page_choice);

    connect(but_print_speed,SIGNAL(clicked()),this,SLOT(SetPrintWindow()));
    connect(but_reaction_speed_test, SIGNAL(clicked()),this, SLOT(SetReactionSpeedWindow()));


    v_page_profile_l->addWidget(lab_user);

    v_page_choice_l->addWidget(but_print_speed,0,Qt::AlignTop);
    v_page_choice_l->addWidget(but_reaction_speed_test,0,Qt::AlignTop);

    tb_home_panel->addItem(page_profile,"Профиль");
    tb_home_panel->addItem(page_settings,"Настройки");
    tb_home_panel->addItem(page_choice,"Выбрать режим");

    h_home_l->addWidget(tb_home_panel,0,Qt::AlignRight);
    v_home_l->addLayout(h_home_l);

    SetCurrentPageOnLay(home_page);
}

void WINDOW::SetPrintWindow(){

   // delete db;

    print_page = new QWidget;
    WINDOW::DeletePageFromLay(home_page);
    my_style->SetPrintSpeedWindowStyle(print_page);
    QHBoxLayout *h_home_l = new QHBoxLayout(print_page);


    QVBoxLayout *v_left_l = new QVBoxLayout;
    h_home_l->addLayout(v_left_l);
    h_home_l->setSpacing(10);

    QPushButton *but_load_training = new QPushButton("Загрузить тренировку");
    QPushButton *but_start = new QPushButton("Начать");
    QPushButton *but_add_training = new QPushButton("Добавить тренировку");
    QPushButton *but_create_training = new QPushButton("Создать тренировку");
    QPushButton *but_back = new QPushButton("Назад");
    QVBoxLayout *v_buts_l = new QVBoxLayout;

    connect(but_back, SIGNAL(clicked()), this, SLOT(PrintWindowButBackClicked()));
    connect(but_create_training, SIGNAL(clicked()),this, SLOT(SetCreateTrainingWindow()));

    v_left_l->addLayout(v_buts_l);
    v_left_l->setContentsMargins(0,100,0,0);
    v_buts_l->addWidget(but_back,0,Qt::AlignTop);
    v_buts_l->addWidget(but_create_training,0,Qt::AlignTop);
    v_buts_l->addWidget(but_add_training,0,Qt::AlignTop);
    v_buts_l->addWidget(but_load_training,0,Qt::AlignTop);
    v_buts_l->addWidget(but_start,1,Qt::AlignTop);


    QVBoxLayout *v_center_l = new QVBoxLayout;
    h_home_l->addLayout(v_center_l);
    QTextBrowser *text_browser = new QTextBrowser;
    text_browser->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    v_center_l->addWidget(text_browser);

    QVBoxLayout *v_game_pole_l = new QVBoxLayout;
    v_center_l->addLayout(v_game_pole_l);
    QLineEdit *ld_game_pole = new QLineEdit;
    v_game_pole_l->addWidget(ld_game_pole);

    QHBoxLayout *h_current_info_l = new QHBoxLayout;
    v_game_pole_l->addLayout(h_current_info_l);

    QHBoxLayout *v_current_mistakes_l = new QHBoxLayout;
    h_current_info_l->addLayout(v_current_mistakes_l);
    QLineEdit *ld_current_mistakes = new QLineEdit;
    QLabel *lab_current_mistakes = new QLabel("Ошибки: ");
    v_current_mistakes_l->addWidget(lab_current_mistakes,1,Qt::AlignTop);
    v_current_mistakes_l->addWidget(ld_current_mistakes,1,Qt::AlignTop);

    QHBoxLayout *v_current_speed_l = new QHBoxLayout;
    h_current_info_l->addLayout(v_current_speed_l);
    QLineEdit *ld_current_speed = new QLineEdit;
    QLabel *lab_current_speed = new QLabel("Скорость");
    v_current_speed_l->addWidget(lab_current_speed,1,Qt::AlignTop);
    v_current_speed_l->addWidget(ld_current_speed,1,Qt::AlignTop);

    QHBoxLayout *v_play_time_l = new QHBoxLayout;
    h_current_info_l->addLayout(v_play_time_l);
    QLineEdit *ld_current_min = new QLineEdit;
    QLineEdit *ld_current_sec = new QLineEdit;
    QLabel *lab_play_time = new QLabel("Время набора");
    QLabel *lab_current_min = new QLabel("мин");
    QLabel *lab_current_sec = new QLabel("сек");
    v_play_time_l->addWidget(lab_play_time,1,Qt::AlignTop);
    v_play_time_l->addWidget(lab_current_min,1,Qt::AlignTop);
    v_play_time_l->addWidget(ld_current_min,1,Qt::AlignTop);
    v_play_time_l->addWidget(lab_current_sec,1,Qt::AlignTop);
    v_play_time_l->addWidget(ld_current_sec,1,Qt::AlignTop);



    QVBoxLayout *v_right_l = new QVBoxLayout;
    h_home_l->addLayout(v_right_l);
    QComboBox *box_training = new QComboBox;
    v_right_l->addWidget(box_training);
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

    my_style->SetTextBrowserStyle(text_browser);

    print_window_logic = new PRINT_WINDOW_LOGIC(but_start, but_load_training,box_training, ld_game_pole, ld_current_mistakes,
    ld_current_speed, ld_text_amount, ld_record, ld_average_speed,  ld_mistakes, ld_all_time, ld_current_min, ld_current_sec,
    text_browser, lab_current_mistakes, but_create_training, but_add_training); //здесь мы передаем объекты в класс осуществляющий взаимодействие с пользователем

    SetCurrentPageOnLay(print_page);
}

void WINDOW::SetCreateTrainingWindow(){

    create_training_page = new QWidget();
    create_training_page->setWindowModality(Qt::ApplicationModal);
    //SetCurrentPageOnLay(create_training_page);
    my_style->SetCreateTrainingWindowStyle(create_training_page);

    setEnabled(false);
    connect(create_training_page, SIGNAL(destroyed()),this, SLOT(CreateTrainingWindowClosed()));
    QVBoxLayout *v_create_training_l = new QVBoxLayout(create_training_page);

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

void WINDOW::SetReactionSpeedWindow(){
    reaction_speed_page = new QWidget;
    WINDOW::DeletePageFromLay(home_page);
    my_style->SetReactionSpeedWindowStyle(reaction_speed_page);

    QVBoxLayout *v_reaction_speed_l = new QVBoxLayout(reaction_speed_page);

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

    v_reaction_speed_l->addWidget(lab_info,0,Qt::AlignCenter);
    v_reaction_speed_l->addWidget(lab_result,0,Qt::AlignCenter);
    v_reaction_speed_l->addWidget(but_reaction_speed);

    my_style->SetButReactionSpeedStyle(but_reaction_speed);
    my_style->SetLabResultStyle(lab_result);
    my_style->SetLabInfoStyle(lab_info);

    reaction_speed_logic = new REACTION_SPEED_LOGIC(but_reaction_speed,lab_info, lab_result);


    SetCurrentPageOnLay(reaction_speed_page);
}


void WINDOW::SetSignInWindow(){
    sign_in_page = new QWidget;
    login = "";
    password = "";

    WINDOW::DeletePageFromLay(register_page); //удаляем страницу регистрации
    my_style->SetSignInWindowStyle(sign_in_page);

    QLineEdit *ld_login = new QLineEdit("Введите логин");
    QLineEdit *ld_password = new QLineEdit("Введите пароль");
    QPushButton *but_sign_in = new QPushButton("Войти");
    QPushButton *but_back = new QPushButton("Назад");

    connect(but_back,SIGNAL(clicked()),this,SLOT(SetRegisterWindow()));
    connect(ld_login,SIGNAL(textChanged(QString)),this,SLOT(SetLoginValue(QString))); //получение введенного логина
    connect(ld_password,SIGNAL(textChanged(QString)),this,SLOT(SetPasswordValue(QString))); //получение введенного пароля
    connect(but_sign_in,SIGNAL(clicked()),this,SLOT(SendSignInDataToDB())); // отправка данных в класс бд при нажатии на кнопку войти

    QVBoxLayout *v_sign_in_l = new QVBoxLayout(sign_in_page);

    my_style->SetLoginLineEditStyle(ld_login);
    my_style->SetPasswordLineEditStyle(ld_password);
    my_style->SetButBackStyle(but_back);
    my_style->SetButSignInStyle2(but_sign_in);

    v_sign_in_l->addWidget(but_back);
    v_sign_in_l->addWidget(ld_login);
    v_sign_in_l->addWidget(ld_password);
    v_sign_in_l->addWidget(but_sign_in,0,Qt::AlignRight);

    SetCurrentPageOnLay(sign_in_page);
}
