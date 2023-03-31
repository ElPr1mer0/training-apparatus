#include "widget_style.h"
#include "qcustomplot.h"
#include <QtWidgets>



void WIDGET_STYLE::SetPasswordLineEditStyle(QLineEdit *ld_password){
    QFont text;
    text.setPixelSize(14);
    text.setBold(false);
    text.setFamily("Candara Light");
    ld_password->setFont(text);
    ld_password->setMinimumSize(60,30);
    ld_password->setFrame(false);
    ld_password->setEchoMode(QLineEdit::Password);
    ld_password->setStyleSheet("background-color: #d9d9d9;");

}


void WIDGET_STYLE::SetLoginLineEditStyle(QLineEdit *ld_login){
    QFont text;
    ld_login->setMinimumSize(60,30);
    text.setPixelSize(14);
    text.setBold(false);
    text.setFamily("Candara Light");
    ld_login->setFont(text);
    ld_login->setFrame(false);
    ld_login->setStyleSheet("background-color: #d9d9d9;");

}


void WIDGET_STYLE::SetLabWelcomeStyle(QLabel *lab_welcome){
    QFont text;
    text.setPixelSize(20);
    text.setBold(true);
    text.setFamily("Candara");
    lab_welcome->setFont(text);
    lab_welcome->setAlignment(Qt::AlignHCenter);

}


void WIDGET_STYLE::SetButSignInStyle(QPushButton *but_sign_in){
    QFont text;
    text.setPixelSize(12);
    text.setBold(false);
    text.setFamily("Candara Light");
    but_sign_in->setFont(text);
    but_sign_in->setStyleSheet("QPushButton{"
                               "    background-color:  white;"
                               "    border-radius: 10 px;"
                               "    border-color: black;"
                               "    color: black"
                                "}"
                               "QPushButton::hover{"
                               "    background-color:  #d9d9d9;"
                               "}"
                                    );
    but_sign_in->setMinimumSize(100,30);

}


void WIDGET_STYLE::SetButRegistrationStyle(QPushButton *but_registration){
    QFont text;
    text.setPixelSize(14);
    text.setBold(true);
    text.setFamily("Candara Light");
    but_registration->setFont(text);
    but_registration->setStyleSheet("QPushButton{"
                                        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(79, 13, 171, 202), stop:1 rgba(169, 41, 102, 204));"
                                        "border-radius: 0 px;"
                                        "border-color: black;"
                                        "color: white;"
                                    "}"
                                    "QPushButton::hover{"
                                    "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(79, 13, 171, 228), stop:1 rgba(169, 41, 102, 240));"
                                    "}"
                                    );

    but_registration->setMinimumSize(100,30);

}


void WIDGET_STYLE::SetRegistryWindowStyle(QWidget *registration_window){
    registration_window->setWindowTitle("Регистрация");
    registration_window->setMinimumSize(240,260);
    registration_window->setMaximumSize(240,260);
    registration_window->setStyleSheet("background-color: white;");
}


void WIDGET_STYLE::SetSignInWindowStyle(QWidget *login_window){
    login_window->setWindowTitle("Вход");
    login_window->setMinimumSize(240,260);
    login_window->setMaximumSize(240,260);
    login_window->setStyleSheet("background-color: white;");
}


void WIDGET_STYLE::SetButSignInStyle2(QPushButton *but_sign_in){
    QFont text;
    text.setPixelSize(14);
    text.setBold(true);
    text.setFamily("Candara Light");
    but_sign_in->setFont(text);
    but_sign_in->setStyleSheet("QPushButton{"
                                        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(79, 13, 171, 202), stop:1 rgba(169, 41, 102, 204));"
                                        "border-radius: 0 px;"
                                        "border-color: black;"
                                        "color: white;"
                                    "}"
                                    "QPushButton::hover{"
                                    "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(79, 13, 171, 228), stop:1 rgba(169, 41, 102, 240));"
                                    "}"
                               );
    but_sign_in->setMinimumSize(100,30);
    but_sign_in->setMaximumSize(100,30);

}


void WIDGET_STYLE::SetButBackStyle(QPushButton *but_back){
    QFont text;
    text.setPixelSize(13);
    text.setBold(true);
    text.setFamily("Candara");
    but_back->setFont(text);
    but_back->setStyleSheet("QPushButton{"
                               "    background-color:  white;"
                               "    border-radius: 10 px;"
                               "    border-color: black;"
                               "    color: black"
                                "}"
                               "QPushButton::hover{"
                               "    background-color:  #d9d9d9;"
                               "}"
                            );
    but_back->setMinimumSize(40,20);
    but_back->setMaximumSize(40,20);

}




void WIDGET_STYLE::SetHomeWindowStyle(QWidget *home_window){
    home_window->setWindowTitle("Хаб аристократов :)");
    home_window->setMinimumSize(1200,640);
    //home_window->setMaximumSize(10000,10000);
  //  home_window->setWindowFlags(Qt::WindowMinMaxButtonsHint|Qt::WindowFullscreenButtonHint|
    //                            Qt::WindowCloseButtonHint);


    //home_window->setStyleSheet("background-color: gray;");
//    home_window->setStyleSheet(
//                               "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(79, 13, 171, 202), stop:1 rgba(169, 41, 102, 204));"

    //                );
}

void WIDGET_STYLE::SetTBHomePanelStyle(QToolBox *tb_home_panel){
     tb_home_panel->setMinimumSize(400,200);
     tb_home_panel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
}





void WIDGET_STYLE::SetPrintSpeedWindowStyle(QWidget *print_window){
    print_window->setWindowTitle("Тренировка скорости печати");
    print_window->setMinimumSize(1200,640);
    print_window->setMaximumSize(1920,1080);


    print_window->setStyleSheet(
                               "background-color: #d9d9d9;"

                );
}

void WIDGET_STYLE::SetTextBrowserStyle(QTextBrowser *text_browser){
    QFont text;
    text.setPixelSize(20);
    text.setBold(true);
    text.setFamily("Candara Light");
    text_browser->setFont(text);


}

void WIDGET_STYLE::SetPlotMistakeStyle(QCustomPlot *plot){
    plot->setInteraction(QCP::iRangeZoom,true);   // Включаем взаимодействие удаления/приближения
    plot->axisRect()->setRangeDrag(Qt::Horizontal);   // Включаем перетаскивание только по горизонтальной оси
    plot->axisRect()->setRangeZoom(Qt::Horizontal);   // Включаем удаление/приближение только по горизонтальной оси
    plot->setInteraction(QCP::iRangeDrag, true);  // Включаем взаимодействие перетаскивания графика

    QSharedPointer<QCPAxisTickerDateTime> x_ticker(new QCPAxisTickerDateTime);
    x_ticker->setDateTimeFormat("d. MMMM\nyyyy");
    plot->xAxis->setTicker(x_ticker);

    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime); //подпись данных по X
    dateTicker->setDateTimeFormat("d. MMMM\nyyyy");
    plot->xAxis->setTicker(dateTicker);

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText); //подпись данных по Y
    for(int i = 0; i<=100; i+=5) textTicker->addTick(i, QString::number(i) + "%");
    plot->yAxis->setTicker(textTicker);

    plot->xAxis->setTickLabelFont(QFont(QFont().family(), 10)); //шрифты
    plot->yAxis->setTickLabelFont(QFont(QFont().family(), 10));

    plot->xAxis->setLabel("Дата");
    plot->yAxis->setLabel("Ошибки %");

    plot->xAxis2->setVisible(true);//настраиваю отображение данных
    plot->yAxis2->setVisible(true);
    plot->xAxis2->setTicks(false);
    plot->yAxis2->setTicks(false);
    plot->xAxis2->setTickLabels(true);
    plot->yAxis2->setTickLabels(true);

   // plot->legend->setVisible(true);  // легенда
    plot->legend->setBrush(QColor(255, 255, 255, 150));

    plot->setMinimumSize(400,400);
}

void WIDGET_STYLE::SetPlotAmountTextStyle(QCustomPlot *plot){
    plot->setInteraction(QCP::iRangeZoom,true);   // Включаем взаимодействие удаления/приближения
    plot->axisRect()->setRangeDrag(Qt::Horizontal);   // Включаем перетаскивание только по горизонтальной оси
    plot->axisRect()->setRangeZoom(Qt::Horizontal);   // Включаем удаление/приближение только по горизонтальной оси
    plot->setInteraction(QCP::iRangeDrag, true);  // Включаем взаимодействие перетаскивания графика

    QSharedPointer<QCPAxisTickerDateTime> x_ticker(new QCPAxisTickerDateTime);
    x_ticker->setDateTimeFormat("d. MMMM\nyyyy");
    plot->xAxis->setTicker(x_ticker);

    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime); //подпись данных по X
    dateTicker->setDateTimeFormat("d. MMMM\nyyyy");
    plot->xAxis->setTicker(dateTicker);

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText); //подпись данных по Y
    for(int i = 0; i<=400; i+=20) textTicker->addTick(i, QString::number(i));
    plot->yAxis->setTicker(textTicker);

    plot->xAxis->setTickLabelFont(QFont(QFont().family(), 10)); //шрифты
    plot->yAxis->setTickLabelFont(QFont(QFont().family(), 10));

    plot->xAxis->setLabel("Дата");
    plot->yAxis->setLabel("Кол-во текстов");

    plot->xAxis2->setVisible(true);//настраиваю отображение данных
    plot->yAxis2->setVisible(true);
    plot->xAxis2->setTicks(false);
    plot->yAxis2->setTicks(false);
    plot->xAxis2->setTickLabels(true);
    plot->yAxis2->setTickLabels(true);

   // plot->legend->setVisible(true);  // легенда
    plot->legend->setBrush(QColor(255, 255, 255, 150));

    plot->setMinimumSize(400,400);
}

void WIDGET_STYLE::SetPlotSpeedStyle(QCustomPlot *plot){
    plot->setInteraction(QCP::iRangeZoom,true);   // Включаем взаимодействие удаления/приближения
    plot->axisRect()->setRangeDrag(Qt::Horizontal);   // Включаем перетаскивание только по горизонтальной оси
    plot->axisRect()->setRangeZoom(Qt::Horizontal);   // Включаем удаление/приближение только по горизонтальной оси
    plot->setInteraction(QCP::iRangeDrag, true);  // Включаем взаимодействие перетаскивания графика

    QSharedPointer<QCPAxisTickerDateTime> x_ticker(new QCPAxisTickerDateTime);
    x_ticker->setDateTimeFormat("d. MMMM\nyyyy");
    plot->xAxis->setTicker(x_ticker);

    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime); //подпись данных по X
    dateTicker->setDateTimeFormat("d. MMMM\nyyyy");
    plot->xAxis->setTicker(dateTicker);

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText); //подпись данных по Y
    for(int i = 0; i<=1000; i+=50) textTicker->addTick(i, QString::number(i));
    plot->yAxis->setTicker(textTicker);

    plot->xAxis->setTickLabelFont(QFont(QFont().family(), 10)); //шрифты
    plot->yAxis->setTickLabelFont(QFont(QFont().family(), 10));

    plot->xAxis->setLabel("Дата");
    plot->yAxis->setLabel("Скорость");

    plot->xAxis2->setVisible(true);//настраиваю отображение данных
    plot->yAxis2->setVisible(true);
    plot->xAxis2->setTicks(false);
    plot->yAxis2->setTicks(false);
    plot->xAxis2->setTickLabels(true);
    plot->yAxis2->setTickLabels(true);

   // plot->legend->setVisible(true);  // легенда
    plot->legend->setBrush(QColor(255, 255, 255, 150));

    plot->setMinimumSize(400,400);
}

void WIDGET_STYLE::SetBoxsYearsStyle(QComboBox* box_year){
    for(int i = 0; i<5; ++i){
        box_year->addItem(QString::number(2019+i));
    }

}

void WIDGET_STYLE::SetBoxsMonthsStyle(QComboBox* box_month){
    box_month->addItem("Январь");
    box_month->addItem("Февраль");
    box_month->addItem("Март");
    box_month->addItem("Апрель");
    box_month->addItem("Май");
    box_month->addItem("Июнь");
    box_month->addItem("Июль");
    box_month->addItem("Август");
    box_month->addItem("Сентябрь");
    box_month->addItem("Октябрь");
    box_month->addItem("Ноябрь");
    box_month->addItem("Декабрь");
}

void WIDGET_STYLE::SetGroupPlotStyle(QGroupBox *group_plot){
    group_plot->setVisible(false);
}

void WIDGET_STYLE::SetCreateTrainingWindowStyle(QWidget *create_training_window){
    create_training_window->setWindowTitle("Мастер создания тренировок");
    create_training_window->setAttribute(Qt::WA_DeleteOnClose, true); //удаление объекта по "закрыть окно"
    create_training_window->showNormal();
    create_training_window->setFixedSize(740,800);
}

void WIDGET_STYLE::SetLdGeneralTrainingWindowStyle(QLineEdit *ld_training_name){
    QFont text;
    text.setPixelSize(20);
    text.setFamily("Candara Light");
    ld_training_name->setFont(text);
    ld_training_name->setStyleSheet("background-color: #d9d9d9;");
    ld_training_name->setFrame(false);
    ld_training_name->setFixedSize(200,25);
}

void WIDGET_STYLE::SetLdCurrentSymbolsStyle(QLineEdit *ld_current_symbol){
    QFont text;
    text.setPixelSize(20);
    text.setFamily("Candara Light");
    ld_current_symbol->setFont(text);
    ld_current_symbol->setStyleSheet("background-color: #d9d9d9;");
    ld_current_symbol->setFrame(false);
    ld_current_symbol->setFixedSize(200,25);
    ld_current_symbol->setReadOnly(true);
    ld_current_symbol->setAlignment(Qt::AlignRight);
    ld_current_symbol->setText("0");
}


void WIDGET_STYLE::SetLabAddRulesStyle(QLabel *lab_add_rules){
    QFont text;
    text.setPixelSize(14);
    text.setBold(true);
    text.setFamily("Candara Light");
    lab_add_rules->setFont(text);

    lab_add_rules->setText("ПРАВИЛА СОЗДАНИЯ ТРЕНИРОВКИ:\n"
                           "РУЧНОЕ СОЗДАНИЕ:\n"
                           "  1) Введите имя тренировки в поле \"Название тренировки\".\n"
                           "  2) Имя тренировки может содержать в себе только буквы латинского алфавита и кириллицы, а так-\n"
                           "же цифры и символы (!\"#$%&'*()-+,.).\n"
                           "  3) Количество символов в тренировке не должно превышать лимита (10.000 символов).\n"
                           "  4) Для добавления слова в тренировку нужно записать ОДНО слово в поле записи и нажать кнопку\n"
                           "\"Добавить слово\". Использование пробелов запрещено!\n"
                           "  5) Добавлять можно пока не будет превышен лимит.\n"
                           "ДОБАВЛЕНИЕ ФАЙЛА: \n"
                           "  1) Нажмите кнопку \"Добавить файл\" и выберите файл формата (*.txt, *.text) со словами, кото-\n"
                           "рые должны быть записаны следующим образом:\n                                        "
                           "                                        слово1\n                                        "
                           "                                        слово2\n                                        "
                           "                                          ... \n                                        "
                           "                                        словоN\n"
                           "ОДНО слово в строке (пробелы использовать ЗАПРЕЩАЕТСЯ). При некорректной записи слов в файле\n"
                           "или превышении лимита слова не будут добавлены! Добавлять слова из файла-ов можно несколько\n"
                           "раз, при этом ещё можно добавлять отдельные слова в ручную.\n"
                           "ДОПОЛНИТЕЛЬНО:\n"
                           "При необходимости удаления слова из тренировки введити в поле под кнопкой \"Удалить слово\"\n"
                           "слово, и нажмите кнопку. Слово будет удалено. Также можно удалить последнее вставленное слово\n"
                           "нажав кнопку \"Удалить последнее слово\".\n"
                           "ПУБЛИКАЦИЯ:\n"
                           "     После редактирования тренировки нажмите кнопку \"Опубликовать\" тренировка будет сохранена.\n"
                           );
}

void WIDGET_STYLE::SetLabGeneralTrainingWindowStyle(QLabel *label){
    QFont text;
    text.setPixelSize(18);
    text.setBold(true);
    text.setFamily("Candara Light");
    label->setFont(text);
    label->setAlignment(Qt::AlignLeft);
    label->setFixedSize(200,25);
}

void WIDGET_STYLE::SetLabStatusStyle(QLabel *lab_status){
    QFont text;
    text.setPixelSize(18);
    text.setBold(true);
    text.setFamily("Candara Light");
    lab_status->setFont(text);
    lab_status->setAlignment(Qt::AlignLeft);
    lab_status->setMinimumWidth(200);
    lab_status->setMaximumWidth(200);
    lab_status->setMinimumHeight(25);
    lab_status->setMaximumHeight(100);
    lab_status->setWordWrap(true);
}


void WIDGET_STYLE::SetButGeneralTrainingWindwowStyle(QPushButton *but_add_word){
    but_add_word->setMinimumHeight(25);
}

void WIDGET_STYLE::SetBrowserTrainingWordStyle(QTextBrowser *browser_training_word){
    QFont text;
    text.setPixelSize(18);
    text.setBold(true);
    text.setFamily("Candara Light");
    browser_training_word->setFont(text);
    browser_training_word->setReadOnly(true);
}





void WIDGET_STYLE::SetReactionSpeedWindowStyle(QWidget *reaction_speed_window){
    reaction_speed_window->setWindowTitle("Тест на скорость реакции");
    reaction_speed_window->setMinimumSize(800,720);
    reaction_speed_window->setMaximumSize(1920,1080);


    reaction_speed_window->setStyleSheet(
                               "background-color: white;"

                );
}

void WIDGET_STYLE::SetButReactionSpeedStyle(QPushButton *but_reaction_speed){
    QFont text;
    text.setPixelSize(20);
    text.setBold(false);
    text.setFamily("Candara Light");
    but_reaction_speed->setFont(text);
    but_reaction_speed->setStyleSheet("QPushButton{"
                                      "    background-color:  white;"
                                      "}"
                                      "QPushButton::hover{"
                                      "    background-color:  #d9d9d9;"
                                      "}"
                                    );
    but_reaction_speed->setMinimumSize(200,250);

}

void WIDGET_STYLE::SetButReactionSpeedCanClickStyle(QPushButton *but_reaction_speed){
    but_reaction_speed->setStyleSheet("QPushButton{"
                                      "    background-color:  #238c11;"
                                      "}"
                                     );
    but_reaction_speed->setText("Жми!");
}

void WIDGET_STYLE::SetLabResultStyle(QLabel *lab_result){
    QFont text;
    text.setPixelSize(30);
    text.setFamily("Candara Light");
    lab_result->setFont(text);


    lab_result->setStyleSheet("QLabel{"
                              "    background-color:  #238c11;"
                              "}"
                              );
}

void WIDGET_STYLE::SetLabInfoStyle(QLabel *lab_info){
    QFont text;
    text.setPixelSize(25);
    text.setFamily("Candara Light");
    lab_info->setFont(text);

}



