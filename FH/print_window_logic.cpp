#include "print_window_logic.h"
#include "mode.h"
#include "training_mode.h"
#include "voice_acting_mode.h"
#include "qcustomplot.h"
#include "resourse.h"
#include "chart.h"
#include <algorithm>

#include <cmath>
#include <QtWidgets>

///////////////////////////////////////////////////////////////////////
////////////////PRINT_WINDOW_LOGIC::PRINT_WINDOW_LOGIC/////////////////
///////////////////////////////////////////////////////////////////////
/// получает созданные виджеты и связывает их для последующей обработ-
/// ки взаимодействий с ними на форме, соединяет слоты со сигналами
/// этих объектов и подгружает стартовые данные по тренировке
PRINT_WINDOW_LOGIC::PRINT_WINDOW_LOGIC(QPushButton *but_lost, QPushButton *but_voice_settings,QPushButton *but_start, QPushButton *but_load_training,QComboBox *box_mode_name, QComboBox *box_training_name,
 QLineEdit *ld_game_pole, QLineEdit *ld_current_mistakes, QLineEdit *ld_current_speed, QLineEdit *ld_text_amount,
 QLineEdit *ld_record, QLineEdit *ld_average_speed, QLineEdit *ld_mistakes, QLineEdit *ld_all_time,
 QLineEdit *ld_current_min, QLineEdit *ld_current_sec,QTextBrowser *text_mistakes_browser, QTextBrowser *text_browser, QLabel* lab_current_mistakes,
 QPushButton *but_create_training, QPushButton *but_add_training,QPushButton *but_show_group_plot, QCustomPlot *plot,
 QPushButton *but_hide_group_plot, QComboBox *box_from_year, QComboBox *box_from_month, QComboBox *box_to_year,
 QComboBox *box_to_month, QGroupBox *group_plot, QLineEdit *ld_plot_value, QGroupBox *group_game_pole,
 QCheckBox *chbox_amount_text, QCheckBox *chbox_speed, QCheckBox *chbox_mistake, QCheckBox *chbox_letter_errors,
 QCheckBox *chbox_syllable_errors, QCheckBox *chbox_word_errors , QCheckBox *chbox_words_speed,
 QPushButton *but_show_word_statistic, QGroupBox *group_report, QPushButton *but_create_errors_training){
    this->but_lost = but_lost;
    this->but_voice_settings = but_voice_settings;
    this->but_start = but_start;
    this->but_load_training = but_load_training;
    this->but_create_training = but_create_training;
    this->but_add_training = but_add_training;
    this->but_show_group_plot = but_show_group_plot;
    this->but_hide_group_plot = but_hide_group_plot;
    this->but_show_word_statistic = but_show_word_statistic;
    this->but_create_errors_training = but_create_errors_training;

    this->box_mode_name = box_mode_name;
    this->box_training_name = box_training_name;
    this->box_from_year = box_from_year;
    this->box_from_month = box_from_month;
    this->box_to_year = box_to_year;
    this->box_to_month = box_to_month;

    this->ld_game_pole = ld_game_pole;
    this->ld_current_mistakes = ld_current_mistakes;
    this->ld_current_speed = ld_current_speed;
    this->ld_text_amount = ld_text_amount;
    this->ld_record = ld_record;
    this->ld_average_speed = ld_average_speed;
    this->ld_mistakes = ld_mistakes;
    this->ld_all_time = ld_all_time;
    this->ld_current_min = ld_current_min;
    this->ld_current_sec = ld_current_sec;
    this->ld_plot_value  = ld_plot_value;

    this->text_browser = text_browser;
    this->text_mistakes_browser = text_mistakes_browser;

    this->lab_current_mistakes = lab_current_mistakes;

    this->plot = plot;

    this->group_plot = group_plot;
    this->group_game_pole = group_game_pole;
    this->group_report = group_report;

    this->chbox_amount_text = chbox_amount_text;
    this->chbox_mistake = chbox_mistake;
    this->chbox_speed = chbox_speed;
    this->chbox_letter_errors = chbox_letter_errors;
    this->chbox_syllable_errors = chbox_syllable_errors;
    this->chbox_word_errors = chbox_word_errors;
    this->chbox_words_speed = chbox_words_speed;

    this->ld_game_pole->setEnabled(false);

    this->but_start->setEnabled(false);
    this->but_lost->setVisible(false);
    this->but_voice_settings->setVisible(false);

    this->box_training_name->clear();

    this->chbox_speed->setCheckState(Qt::Checked);
    this->chbox_letter_errors->setCheckState(Qt::Checked);


    sounds = new SOUNDS;
    mode = new MODE;
    training_mode = new TRAINING_MODE(mode->db);
    voice_acting_mode = new VOICE_ACTING_MODE();

    mode->GetModeNames();
    this->box_mode_name->addItems(mode->mode_names); //загрзука названий режимов

    mode->GetTrainingNames(this->box_mode_name->currentText());   // подгружаем названия наших тренировок в box_training_name_name
    this->box_training_name->addItems(mode->training_names);//загрузка названий тренировок режима


    pause_timer = new QTimer(this); //создаем таймер для паузы
    connect (pause_timer, SIGNAL(timeout()),this, SLOT(OnPauseTime()));

    connect(this->box_training_name,SIGNAL(currentIndexChanged(int)),this,SLOT(BoxTrainingCurrentIndexChanged(int)));
    connect(this->box_mode_name,SIGNAL(currentIndexChanged(int)),this,SLOT(BoxModeNamesCurrentIndexChanged(int)));

    connect(this->box_from_year,SIGNAL(currentIndexChanged(int)),this,SLOT(BoxFromYearCurrentIndexChanged(int)));
    connect(this->box_from_month,SIGNAL(currentIndexChanged(int)),this,SLOT(BoxFromMonthCurrentIndexChanged(int)));
    connect(this->box_to_year,SIGNAL(currentIndexChanged(int)),this,SLOT(BoxToYearCurrentIndexChanged(int)));
    connect(this->box_to_month,SIGNAL(currentIndexChanged(int)),this,SLOT(BoxToMonthCurrentIndexChanged(int)));


    connect(this->but_lost, SIGNAL(clicked()),this,SLOT(ButLostClicked()));
    connect(this->but_load_training, SIGNAL(clicked()),this,SLOT(ButLoadTrainingClicked()));
    connect(this->but_start, SIGNAL(clicked()),this, SLOT(ButStartClicked()));
    connect(this->but_show_group_plot, SIGNAL(clicked()),this,SLOT(ButShowGroupPlotClicked()));
    connect(this->but_hide_group_plot, SIGNAL(clicked()),this, SLOT(ButHideGroupPlotClicked()));
    connect(this->but_show_word_statistic, SIGNAL(clicked()), this, SLOT(ButShowWordStatistic()));
    connect(this->but_create_errors_training, SIGNAL(clicked()), this, SLOT(ButCreateErrorsTrainingClicked()));

    connect(this->ld_game_pole, SIGNAL(textChanged(QString)), this, SLOT(LdFieldTextChanged(QString)));

    connect(this->plot, &QCustomPlot::mousePress, this, &PRINT_WINDOW_LOGIC::PlotMousePress);
    connect(this->plot, &QCustomPlot::mouseMove, this, &PRINT_WINDOW_LOGIC::PlotMouseMove);

    connect(this->chbox_amount_text, SIGNAL(clicked()),this, SLOT(CHBoxAmountTextChecked()));
    connect(this->chbox_speed, SIGNAL(clicked()),this, SLOT(CHBoxSpeedChecked()));
    connect(this->chbox_mistake, SIGNAL(clicked()),this, SLOT(CHBoxMistakeChecked()));
    connect(this->chbox_letter_errors, SIGNAL(clicked()),this, SLOT(CHBoxLetterErrorsChecked()));
    connect(this->chbox_syllable_errors, SIGNAL(clicked()),this, SLOT(CHBoxSyllableErrorsChecked()));
    connect(this->chbox_word_errors, SIGNAL(clicked()),this, SLOT(CHBoxWordErrorsChecked()));
    connect(this->chbox_words_speed, SIGNAL(clicked()),this, SLOT(CHBoxWordsSpeedChecked()));

    mode->GetStatistics(this->box_mode_name->currentText(),this->box_training_name->currentText());//загружаем данные для режима в переменные
    OnUpdateData(); //добавляем на форму

    mode->ClearStatisticsContainers();
    mode->UpdateStatisticsContainers(this->box_mode_name->currentText(),this->box_training_name->currentText());

}
///////////////////////////////////////////////////////////////////////
////////////////PRINT_WINDOW_LOGIC::PRINT_WINDOW_LOGIC/////////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
////////////////PRINT_WINDOW_LOGIC::~PRINT_WINDOW_LOGIC////////////////
///////////////////////////////////////////////////////////////////////
PRINT_WINDOW_LOGIC::~PRINT_WINDOW_LOGIC(){
    delete training_mode;
    delete mode;
    //?delete sounds;
}


///////////////////////////////////////////////////////////////////////
////////////////PRINT_WINDOW_LOGIC::~PRINT_WINDOW_LOGIC////////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
/////////////PRINT_WINDOW_LOGIC::ChangeStyleEnteredLetters/////////////
///////////////////////////////////////////////////////////////////////
/// функция принимает index - позиция, до которой были правильно введе-
/// ны символы (и до этой позиции мы их окрашиваем), а остальнаые сим-
/// волы, которые идут после мы оставляем без изменения
void PRINT_WINDOW_LOGIC::ChangeStyleEnteredLetters(const int &index){
    QString text_editing = "<font color = SlateBlue face = Arial><strong>"+ edit_text.mid(0,index+1) + "</strong></font>"; // из исходного текста мы берем самое начало + index,
    text_editing += edit_text.midRef(index+1,edit_text.length()-1); //потом мы добавляем оставшийся текст, который еще не был введен пользователем

    text_browser->clear(); //обнуляем браузер
    text_browser->append(text_editing);
}
///////////////////////////////////////////////////////////////////////
/////////////PRINT_WINDOW_LOGIC::ChangeStyleEnteredLetters/////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
/////////////PRINT_WINDOW_LOGIC::~ChangeStyleEnteredWords//////////////
///////////////////////////////////////////////////////////////////////
/// меняет стиль напечатанного текста на другой, для отличия от того,
/// что нужно еще печатать
//void PRINT_WINDOW_LOGIC::ChangeStyleEnteredWords(const int &index){
//    QString text_editing = "<font color = SlateBlue face=Arial> <strong>"+ edit_text.mid(0,index) + "</strong></font> "; // из исходного текста мы берем самое начало + index,
//    //который обозначает конец последнего введенного слова, и для этого всего мы меняем стиль оторажения в браузере
//    text_editing += edit_text.mid(index+1,edit_text.length()-1); //потом мы добавляем оставшийся текст, который еще не был введен пользователем

//    text_browser->clear(); //обнуляем браузер
//    text_browser->append(text_editing);
//}
///////////////////////////////////////////////////////////////////////
/////////////PRINT_WINDOW_LOGIC::~ChangeStyleEnteredWords//////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
////////////////PRINT_WINDOW_LOGIC::~AlterMistakesText/////////////////
///////////////////////////////////////////////////////////////////////
/// окрашивает правильно введеные буквы в один цвет, неправильные - в
/// другой и добавляет их в mistakes_text
void PRINT_WINDOW_LOGIC::AlterMistakesText(QChar right_letter, QChar error_letter){
    right_letter == error_letter? mistakes_text =mistakes_text + "<font color = SlateBlue face=Arial><strong>"+ right_letter +"</strong></font>":
    mistakes_text = mistakes_text + "<s><font color=Maroon face=Arial><strong>" + error_letter + "</strong></font></s>";
    //right_letter если right_letter = error_letter, тогда это не ошибка и менять цвет буквы не надо, иначе меняем
}
///////////////////////////////////////////////////////////////////////
////////////////PRINT_WINDOW_LOGIC::~AlterMistakesText/////////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
////////////////PRINT_WINDOW_LOGIC::ButAddFileClicked//////////////////
///////////////////////////////////////////////////////////////////////
/// используется при создании тренировки пользователем, проверяет есть
/// ли файл, проверяет соответствует ли текст правилу создания пользо-
/// вательской тренировки
void PRINT_WINDOW_LOGIC::ButAddFileClicked(){

    QFile file(QFileDialog::getOpenFileName(0,"Выбор файла","","*.text *.txt"));
    QFileInfo name(file);

    if(!file.exists()){
        lab_status->setText("Файл не существует или поврежден!");
    }
    else if(file.open(QIODevice::ReadOnly| QIODevice::Text)){
        ld_training_name->setText(name.baseName());//получаем имя тренировки

        QTextStream stream(&file);//считываем данные из файла и закрываем его
        stream.setCodec( "UTF-8" );
        QString content = stream.readAll();
        file.close();

        if(content.length()<=1){
            lab_status->setText("Файл пустой!");
            return;
        }
        if(content.length()>SYMBOLS_LIMIT){
            lab_status->setText("Кол-во символов больше ограничения!");
            return;
        }
        if(training_mode->symbols_counter + content.length() >SYMBOLS_LIMIT){
            lab_status->setText("Лимит будет превышен, слова не добавлены!");
            return;
        }

        QString word = "";
        for(int i=0; i<content.length();++i){
            word +=content[i];

            if(content[i] == ' '){
                lab_status->setText("В файле есть пробелы!");
                return;
            }
            if(content[i] == '\n' && word.length()>1){//если встретили enter и слово не пустое, то добавляем слово в тренировку
                training_mode->symbols_counter +=word.length(); //увеличиваем кол-во символов до удаления последнего символа chop(1), так как потом прибавил \n
                word.chop(1);//удаляем символ enter для того, чтобы в browser не записался лишний enter
                training_mode->word_training_list.push_back(word);
                word ="";
            }else{
                if(i == content.length()-1 && word.length()>1){//случай, если после последнего слова в файле не поставили enter
                    training_mode->word_training_list.push_back(word);
                    training_mode->symbols_counter +=word.length()+1; //увеличиваем кол-во символов
                    word ="";
                }
                if(content[i] =='\n' && word.length() <= 1){
                    lab_status->setText("Файл сделан некорректно!");
                    return;
                }
            }
        }
        ld_current_symbols->setText(QString::number(training_mode->symbols_counter)); // записываем текущее кол-во символов
        lab_status->setText("Файл считан успешно!");

        for(auto it : training_mode->word_training_list) browser_training_word->append(it); //добавляем наши слова на браузер
    }
    else{
        lab_status->setText("Ошибка открытия файла!");
    }

}
///////////////////////////////////////////////////////////////////////
////////////////PRINT_WINDOW_LOGIC::ButAddFileClicked//////////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
////////////////PRINT_WINDOW_LOGIC::ButAddWordClicked//////////////////
///////////////////////////////////////////////////////////////////////
/// добавляет введенное пользователем слово в текст будущей тренировки
void PRINT_WINDOW_LOGIC::ButAddWordClicked(){
    if(training_mode->CheckWordForTrainingList(ld_add_word->text())){ //если слово написано правильно
        training_mode->word_training_list.push_back(ld_add_word->text());
        lab_status->setText("Слово добавлено!");
        ld_current_symbols->setText(QString::number(training_mode->symbols_counter));
        browser_training_word->append(ld_add_word->text());
        ld_add_word->clear();
    }else{
        lab_status->setText("Ошибка в слове!");
    }
}
///////////////////////////////////////////////////////////////////////
////////////////PRINT_WINDOW_LOGIC::ButAddWordClicked//////////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
//////////////PRINT_WINDOW_LOGIC::ButCreateTrainingClicked/////////////
///////////////////////////////////////////////////////////////////////
/// создает трнировку и отправляет данные по ней в бд, если она прохо-
/// дит проверку на соответствие всем правилами создания
void PRINT_WINDOW_LOGIC::ButCreateTrainingClicked(){
    if(training_mode->CheckCustomTrainingName(ld_training_name->text())){ //если имя правильное
        if(!training_mode->word_training_list.empty()){//если не пустой
            if(training_mode->symbols_counter <= SYMBOLS_LIMIT){ //если не превышен лимит символов
                if(training_mode->AddTraining()){
                    ld_current_symbols->setText("0"); //очищаем поля в доп форме и переменные для создания тренировки
                    ld_training_name->clear();
                    ld_add_word->clear();
                    training_mode->symbols_counter = 0;
                    training_mode->word_training_list.clear(); //удаляем, так как нам уже не нужно его запоминать после создания тренировки
                    browser_training_word->clear();
                    lab_status->setText("Тренировка добавлена!");

                    box_training_name->addItem(mode->training_names.last());//обновляем данные на освновной форме (выбираем новую тренировку)
                    mode->GetStatistics(box_mode_name->currentText(),mode->training_names.last());
                    OnUpdateData();

                    mode->ClearStatisticsContainers();
                    mode->UpdateStatisticsContainers(box_mode_name->currentText(),box_training_name->currentText());
                }else{
                    lab_status->setText("Ошибка сохранения тренировки!");
                }

            }else{
                lab_status->setText("Превышен лимит символов в " + QString::number(SYMBOLS_LIMIT) + "!\n"
                                    "Последнее слово удалено!");
                training_mode->word_training_list.pop_back();
            }

        }else{
            lab_status->setText("Тренировка пуста!");
        }
    }else{
        lab_status->setText("Ошибка ввода имени!");
    }
}
///////////////////////////////////////////////////////////////////////
//////////////PRINT_WINDOW_LOGIC::ButCreateTrainingClicked/////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
/////////////PRINT_WINDOW_LOGIC::ButDeleteLastWordClicked//////////////
///////////////////////////////////////////////////////////////////////
/// удаляет последнее слово на поле
void PRINT_WINDOW_LOGIC::ButDeleteLastWordClicked(){
    if(!training_mode->word_training_list.empty()){//если не пусто, то удаляем последнее слово в тренировке
        lab_status->setText("Удалено: "+training_mode->word_training_list.last());
        training_mode->symbols_counter -= training_mode->word_training_list.last().length()+1;//-1 так как есть ещё символ enter
        ld_current_symbols->setText(QString::number(training_mode->symbols_counter));
        training_mode->word_training_list.pop_back();
        browser_training_word->clear();

        for(auto it = training_mode->word_training_list.begin();it<training_mode->word_training_list.end();++it) browser_training_word->append(*it);

    }else{
        lab_status->setText("Тренировка пуста!");
    }
}
///////////////////////////////////////////////////////////////////////
/////////////PRINT_WINDOW_LOGIC::ButDeleteLastWordClicked//////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
///////////////PRINT_WINDOW_LOGIC::ButDeleteWordClicked////////////////
///////////////////////////////////////////////////////////////////////
/// удаляет слово по поиску
void PRINT_WINDOW_LOGIC::ButDeleteWordClicked(){
    bool found = false;
    if(!training_mode->word_training_list.empty()){ //если не пусто
        for(auto it = training_mode->word_training_list.begin();it<training_mode->word_training_list.end();++it){ //тогда ищем слово для удаления в тренировке

            if(*it == ld_delete_word->text()){ //если находим, то удаляем его
                training_mode->symbols_counter -= it->length()+1;//уменьшаем кол-во символов в тренировке, -1 так как есть ещё символ enter
                ld_current_symbols->setText(QString::number(training_mode->symbols_counter));
                lab_status->setText("Удалено: "+ *it);
                training_mode->word_training_list.erase(it);
                browser_training_word->clear();
                found = true;
            }
        }
        if(!found){
            lab_status->setText("Такого слова нет!"); //если не нашли
            return;
        }

        for(auto it = training_mode->word_training_list.begin();it<training_mode->word_training_list.end();++it) browser_training_word->append(*it);

    }else{
        lab_status->setText("Тренировка пуста!");
    }
}
///////////////////////////////////////////////////////////////////////
///////////////PRINT_WINDOW_LOGIC::ButDeleteWordClicked////////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
//////////////PRINT_WINDOW_LOGIC::GetCreateTrainingComponents//////////
///////////////////////////////////////////////////////////////////////
/// получает созданные виджеты для CreateTrainingWindow и связывает
/// их для последующей обработки взаимодействий с ними на форме,
/// соединяет слоты со сигналами этих объектов
void PRINT_WINDOW_LOGIC::GetCreateTrainingComponents(QPushButton * but_delete_word, QPushButton *but_delete_last_word, QPushButton *but_add_file,
QPushButton *but_add_word, QPushButton *but_publish_training, QLineEdit *ld_delete_word, QLineEdit *ld_training_name, QLineEdit *ld_add_word,
QLineEdit *ld_current_symbols, QLabel *lab_status, QTextBrowser *browser_training_word){
    training_mode->symbols_counter = 0;
    training_mode->word_training_list.clear();

    this->ld_current_symbols = ld_current_symbols;
    this->ld_training_name = ld_training_name;
    this->ld_add_word = ld_add_word;
    this->ld_delete_word = ld_delete_word;
    this->but_delete_last_word = but_delete_last_word;
    this->but_add_word = but_add_word;
    this->but_publish_training = but_publish_training;
    this->but_add_file = but_add_file;
    this->but_delete_word = but_delete_word;
    this->lab_status = lab_status;
    this->browser_training_word = browser_training_word;

    connect(this->but_add_file, SIGNAL(clicked()),this, SLOT(ButAddFileClicked()));
    connect(this->but_add_word, SIGNAL(clicked()),this, SLOT(ButAddWordClicked()));
    connect(this->but_publish_training, SIGNAL(clicked()),this, SLOT(ButCreateTrainingClicked()));
    connect(this->but_delete_last_word, SIGNAL(clicked()),this, SLOT(ButDeleteLastWordClicked()));
    connect(this->but_delete_word, SIGNAL(clicked()),this, SLOT(ButDeleteWordClicked()));
}
///////////////////////////////////////////////////////////////////////
//////////////PRINT_WINDOW_LOGIC::GetCreateTrainingComponents//////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
/////////////////PRINT_WINDOW_LOGIC::LdFieldTextChanged////////////////
///////////////////////////////////////////////////////////////////////
/// обрабатывает события изменения вводимого текста в поле при наборе
/// тренировки, фиксирует ошибки, проверяет на победу.
void PRINT_WINDOW_LOGIC::LdFieldTextChanged(QString current_word){
    if(!errors_mode){ //!errors_mode если равен true, то это режим исправления ошибок, статистику нам тут ловить не надо
        if(start_writing){
            start_ms = ms + sec*1000 + min*60*1000; //считаем кол-во мс, которые прошли с начала набора слова
            start_writing = false;
        }
    }

    if(current_word.length()- 1 + line_size  == letter) { // + lineSize, так как мы обнуляем нашу строку после пробела
                                                // а кол-во символов, которые были помнить надо для правильно проверки на ввод
        if(((edit_text[letter].unicode()==8211 || edit_text[letter].unicode()==8212) && current_word[letter - line_size] == '-')||// это условие нужно, чтобы большое и маленькое тире считалось как обычное
          (edit_text[letter].unicode()==1105 && current_word[letter - line_size].unicode() == 1077 ) || // е=ё
          (edit_text[letter].unicode()==1025 && current_word[letter - line_size].unicode() == 1045 )||//Е=Ё
          (edit_text[letter].unicode()==171 && current_word[letter - line_size].unicode() == 34 )|| // ковычки
          (edit_text[letter].unicode()==187 && current_word[letter - line_size].unicode() == 34 ))  // ковычки
                was_minus = true;

        if(current_word[letter - line_size] != edit_text[letter] && !was_minus){   // - lineSize, чтобы не выйти за пределы массива(причина как сверху)

                if(!is_mistake && first_time){    // когда мы стираем текст после ошибки, нам нужно, чтобы оно не посчитало лишний раз ошибку
                    mistakes++;                 // firstTime здесь нужно, потому что если поставить после ошибки ещё символы, то при стирании
                    ld_current_mistakes->setText(QString::number(mistakes)); // мы вернемся опять сюда, и будет лишняя ошибка засчитана
                    sounds->Play(sounds->print_error); //звук ошибки
                    is_mistake = true;
                    first_time = false;
                    if(!errors_mode) mode->MistakeReader(edit_text, letter); // для анализа ошибок
                    AlterMistakesText(edit_text[letter],current_word[letter - line_size]); //выделение ошибки в mistakes_text после тренировки
                }


        }else{    // если правильно ввели букву
            ChangeStyleEnteredLetters(letter);// меняем цвет правильно введенной буквы
            AlterMistakesText(current_word[letter - line_size ],current_word[letter - line_size ]); //если правильно ввели букву, то запишем только правильлный ответ
            was_minus = false;                            // для статистики скорости набора слова
            is_mistake = false;
            letter++;

            if(current_word[letter - 1 - line_size] == ' '){ //когда ввели все слово правильно -1, так как до этого выше увеличил на 1, а это значени след буквы
                line_size = letter;

                if(!errors_mode){
                    if(box_mode_name->currentText() == TEXT_ACTING) end_ms -= voice_acting_mode->pause_time_between_words;
                    mode->WordSpeedReader(ld_game_pole->text(),ld_game_pole->text().length()-1,abs(end_ms-start_ms)); //передаем длину слова и время написания его в мс
                    start_writing = true;                                               // length()-1, чтобы пробел не учитывать
                }

                ld_game_pole->clear();
            }else if(edit_text.length() - 1 == letter){
                if(!errors_mode){
                    if(box_mode_name->currentText() == TEXT_ACTING) end_ms -= voice_acting_mode->pause_time_between_words;
                    mode->WordSpeedReader(ld_game_pole->text()+" ",ld_game_pole->text().length(),abs(end_ms-start_ms)); // добавляю здесь " ", так как в другой функции
                }                                                                                           //всегда удаляю пробел, а в конце строки его нет
            }

            if(edit_text.length() -1  == letter){ //проверка на конец текста, -2 так как в конце каждой строки есть символ перехода на новую
                                     //n, его нам считать не надо, и ещё -1 так как с нуля идет счет
                AlterMistakesText(edit_text[edit_text.length()-1],edit_text[edit_text.length()-1]);//нужно вызывать, чтобы последний символ тренировки попал под редактирование
                IsWin(); //победа
            }
        }
    }
    else{
            if(letter>current_word.length() +line_size && letter>0){ //сюда попадаем, когда стираем символы, которые были правильными                                
                ChangeStyleEnteredLetters(current_word.length() +line_size-1);
                //current_word.length() + line_size - 1 - это текущая позиция index для окрашивания текста в обычный

                letter = current_word.length() +line_size; // может произойти такое, что пользователь нажмет back и сотрет сразу много символов

                first_time = true;
            }
            else{
                is_mistake = false;
                if(current_word.length()- 1 + line_size  == letter-1) first_time = true;  // когда стираем уже неправильный символ
            }
    }
}
///////////////////////////////////////////////////////////////////////
/////////////////PRINT_WINDOW_LOGIC::LdFieldTextChanged////////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
////////PRINT_WINDOW_LOGIC::BoxModeNamesCurrentIndexChanged////////////
///////////////////////////////////////////////////////////////////////
/// при смене режима вызывает функции обновления данных на форме и тп
void PRINT_WINDOW_LOGIC::BoxModeNamesCurrentIndexChanged(int){
    box_training_name->clear();//очищаем box
    but_start->setEnabled(true); // это если кнопка была заблочена, когда книга пройдена

    if(box_mode_name->currentText() == TEXT_ACTING){
        but_voice_settings->setVisible(true);
        but_lost->setVisible(true);
        mode->GetTrainingNames(TRAINING);
    }else{
        but_voice_settings->setVisible(false);
        but_lost->setVisible(false);

        mode->GetTrainingNames(this->box_mode_name->currentText()); //получаем имена тренировок по режиму
    }

    box_training_name->addItems(mode->training_names); //добавляем имена в box
    mode->GetStatistics(box_mode_name->currentText(),box_training_name->currentText());//получаем статистику по тренировке
    mode->UpdateStatisticsContainers(box_mode_name->currentText(),box_training_name->currentText());

    mode->ClearStatisticsContainers(); //очистках контейнеров с ошибками для добавления ошибок по загружаемой тренировке

    OnUpdateData();//обновление данных на поле
}
///////////////////////////////////////////////////////////////////////
////////PRINT_WINDOW_LOGIC::BoxModeNamesCurrentIndexChanged////////////
///////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
////////////////PRINT_WINDOW_LOGIC::ButStartClicked/////////////////////
////////////////////////////////////////////////////////////////////////
/// начинает тренировку, проверяет есть ли текст в поле, обнуляет неко-
/// торые данные и запускает таймер
void PRINT_WINDOW_LOGIC::ButStartClicked(){
    if(text_browser->toPlainText() == ""){ //если браузер пуст, значит тренировка не загрузилась
        text_browser->insertPlainText("Ошибка, тренировка не загрузилась или она не содержит текста!");
        ld_game_pole->setEnabled(false);
        but_start->setEnabled(false);
    }
    else{
        ld_game_pole->setEnabled(true); //обнуляем данные на форме временной статы
        ld_current_mistakes->setText("0");
        ld_current_speed->setText("0");
        lab_current_mistakes->setText("Ошибки: ");
        pause_timer->start(1000);
        but_load_training->setEnabled(false);
        but_start->setEnabled(false);
        box_training_name->setEnabled(false);


        letter = 0; // надо каждый раз сбрасывать для корректной работы считывания строки + отображения статистики
        line_size = 0;
        mistakes = 0;
        is_mistake = false;
        sec = 0;
        min = 0;
        timer = new QTimer(this); //создаем таймер
        connect (timer, SIGNAL(timeout()),this, SLOT(OnTime()));

        group_report->setEnabled(false);
    }
}
////////////////////////////////////////////////////////////////////////
////////////////PRINT_WINDOW_LOGIC::ButStartClicked/////////////////////
////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
//////////////PRINT_WINDOW_LOGIC::ButLoadTrainingClicked///////////////
///////////////////////////////////////////////////////////////////////
/// загружает текст выбранной тренировки в поле для старта
void PRINT_WINDOW_LOGIC::ButLoadTrainingClicked(){
    errors_mode = false;
    text_browser->clear();
    mistakes_text = ""; //нужно обнулить, чтобы старые ошибки не отображались
    text_mistakes_browser->clear();
   // text_mistakes_browser->setVisible(false);
    QString training_text;

    if(box_mode_name->currentText() == TRAINING || box_mode_name->currentText() == TEXT_ACTING){
        training_text = training_mode->GetTraining(TRAINING,box_training_name->currentText());
        if(training_text == "Нет слов в данной тренировке!")
            but_start->setEnabled(false); //если тренировка не создастся, но ее нельзя запускать

        if(box_mode_name->currentText() == TEXT_ACTING){
            voice_acting_mode->acting_words = training_text.split(" ");//полученную тренировку разделяем по словам
            voice_acting_mode->acting_words.pop_back(); //удаляем последний элемент, так как там будет пусто из-за лишниго пробела
            voice_acting_mode->SetPlayingText(voice_acting_mode->acting_words.front());
            text_browser->setVisible(false);
            text_mistakes_browser->setVisible(true);
        }else{
            text_browser->setVisible(true);
            text_mistakes_browser->setVisible(false);
        }
    }

    text_browser->insertPlainText(training_text);
    edit_text = training_text;
    but_start->setEnabled(true);
}
///////////////////////////////////////////////////////////////////////
//////////////PRINT_WINDOW_LOGIC::ButLoadTrainingClicked///////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
////////////PRINT_WINDOW_LOGIC::ButShowGroupPlotClicked////////////////
///////////////////////////////////////////////////////////////////////
/// отображает график по выбранным данным
void PRINT_WINDOW_LOGIC::ButShowGroupPlotClicked(){
    group_game_pole->setVisible(false);
    group_report->setVisible(false);
    group_plot->setVisible(true);
    but_show_group_plot->setEnabled(false);

    double now = QDateTime::currentDateTimeUtc().toTime_t();
    QDate *date = new QDate;

    plot->addGraph();
    QVector<QCPGraphData> graph_data(mode->statistics_per_time.length());// помещаем наши данные для отображения:
    QString type;
    if(chbox_amount_text->isChecked()) type = "Кол-во текстов";
    else if(chbox_speed->isChecked()) type = "Скорость";
    else if(chbox_mistake->isChecked()) type = "Ошибки %";

    mode->DetermineDayCoffForPlot(now,graph_data, type); // обрабатываем дни для графика

    plot->graph(0)->data()->set(graph_data);

    QColor color(149,137,250);
    plot->graph()->setLineStyle(QCPGraph::lsStepCenter); //настраиваем кисть
    plot->graph()->setPen(QPen(color.lighter(200)));
    plot->graph()->setBrush(QBrush(color));
    plot->graph()->setName("Тренировка скорости за время");

    tracer = new QCPItemTracer(plot);
    tracer->setGraph(plot->graph(0));   // Трассировщик будет работать с графиком   

    plot->xAxis->setRange(now -24*3600*10, now+24*3600*10);//диапазон отображения данных по X и Y

    if(type == "Скорость"){
        QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText); //подпись данных по Y
        for(int i = 0; i<=700; i+=35) textTicker->addTick(i, QString::number(i));
        plot->yAxis->setTicker(textTicker);
        plot->yAxis->setLabel("Скорость");
        plot->yAxis->setRange(0, 700);
    }else if(type =="Ошибки %"){
        QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText); //подпись данных по Y
        for(int i = 0; i<=40; i+=2) textTicker->addTick(i, QString::number(i) + "%");
        plot->yAxis->setTicker(textTicker);
        plot->yAxis->setLabel("Ошибки %");
        plot->yAxis->setRange(0, 40);
    }else{
        QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText); //подпись данных по Y
        for(int i = 0; i<=200; i+=10) textTicker->addTick(i, QString::number(i));
        plot->yAxis->setTicker(textTicker);
        plot->yAxis->setRange(0, 200);
        plot->yAxis->setLabel("Кол-во текстов");
    }
    plot->replot();
    delete date;
}
///////////////////////////////////////////////////////////////////////
////////////PRINT_WINDOW_LOGIC::ButShowGroupPlotClicked////////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
/////////////PRINT_WINDOW_LOGIC::ButHideGroupPlotClicked///////////////
///////////////////////////////////////////////////////////////////////
/// убирает график с формы
void PRINT_WINDOW_LOGIC::ButHideGroupPlotClicked(){
    group_plot->setVisible(false);
    group_report->setVisible(true);
    group_game_pole->setVisible(true);
    but_show_group_plot->setEnabled(true);
    delete tracer;
}
///////////////////////////////////////////////////////////////////////
/////////////PRINT_WINDOW_LOGIC::ButHideGroupPlotClicked///////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
//////////////PRINT_WINDOW_LOGIC::ButShowWordStatistic/////////////////
///////////////////////////////////////////////////////////////////////
/// выводит статистическую информацию по тренировкам
void PRINT_WINDOW_LOGIC::ButShowWordStatistic(){
    text_browser->clear();
    QString type;
    if(chbox_letter_errors->isChecked()) type = "Ошибки в буквах:";
    else if(chbox_syllable_errors->isChecked()) type = "Ошибки в слогах:";
    else if (chbox_word_errors->isChecked()) type = "Ошибки в словах:";
    else type = "Средняя скорость набора слова:";
    text_browser->insertPlainText("                     " + type+ "\n" );

    std::vector<QString> keys;
    std::vector<float> values;

    if(chbox_letter_errors->isChecked()){
        mode->SortBufPrintStatistics(mode->letter_errors, keys, values);

        for(unsigned long it = 0; it<values.size(); ++it) //вывод отсортированных данных в браузер
                text_browser->insertPlainText("Буква: "+keys[it] +"; Кол-во ошибок при написании: "+QString::number(values[it])+"\n");
    }
    else if(chbox_syllable_errors->isChecked()){
        mode->SortBufPrintStatistics(mode->syllable_errors, keys, values);

        for(unsigned long it = 0; it<values.size(); ++it) //вывод отсортированных данных в браузер
                text_browser->insertPlainText("Слог: "+keys[it] +"; Кол-во ошибок при написании: "+QString::number(values[it])+"\n");

    }
    else if (chbox_word_errors->isChecked()){
        mode->SortBufPrintStatistics(mode->word_errors, keys, values);

        for(unsigned long it = 0; it<values.size(); ++it) //вывод отсортированных данных в браузер
            text_browser->insertPlainText("Слово: "+keys[it] +"; Кол-во ошибок при написании: "+QString::number(values[it])+"\n");
    }
    else {
        std::vector<int> values2;
        for(auto it = mode->words_speed.begin(); it!=mode->words_speed.end(); ++it){ //без сортировки
            keys.push_back(it.key()); // записываю переменные в буферные вектора (слово)
            values.push_back(it.value());//скорость слова
         }
        for(auto it = mode->words_amount.begin(); it!=mode->words_amount.end();++it) values2.push_back(it.value()); //сколько раз набирал

        for(unsigned long i = 0; i<values.size(); ++i) //сортировка буф векторов
            for(unsigned long i = 0; i<values.size()-1; ++i){
                if(values[i]<values[i+1]){
                    std::swap(values[i],values[i+1]); // сортирую по кол-во ошибок
                    std::swap(keys[i],keys[i+1]);
                    std::swap(values2[i], values2[i+1]);
                }
            }


        for(unsigned long i = 0; i<values.size(); ++i) //вывод отсортированных данных в браузер
            text_browser->insertPlainText("Слово: "+keys[i]+"; Написано: "+ QString::number(values2[i]) +
            "; Средняя скорость при написании: "+QString::number(values[i])+"\n");
    }
}
///////////////////////////////////////////////////////////////////////
//////////////PRINT_WINDOW_LOGIC::ButShowWordStatistic/////////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
//////////PRINT_WINDOW_LOGIC::ButCreateErrorsTrainingClicked///////////
///////////////////////////////////////////////////////////////////////
/// создает тренировку по ошибкам
void PRINT_WINDOW_LOGIC::ButCreateErrorsTrainingClicked(){
    if(chbox_words_speed->isChecked()){
        qDebug()<<"Выберите режим с ошибками!";
        return;
    }
    errors_mode = true;
    text_browser->clear();
    if(chbox_letter_errors->isChecked()) text_browser->insertPlainText(mode->GetErrorsTraining(mode->letter_errors));
    else if (chbox_syllable_errors->isChecked()) text_browser->insertPlainText(mode->GetErrorsTraining(mode->syllable_errors));
    else if (chbox_word_errors->isChecked()) text_browser->insertPlainText(mode->GetErrorsTraining(mode->word_errors));
    edit_text = text_browser->toPlainText();
    but_start->setEnabled(true);
}
///////////////////////////////////////////////////////////////////////
//////////PRINT_WINDOW_LOGIC::ButCreateErrorsTrainingClicked///////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
/////////////////PRINT_WINDOW_LOGIC::ButLostClicked////////////////////
///////////////////////////////////////////////////////////////////////
/// когда человек сбился при наборе текста на слух, отображаем основной
/// обзорщик текста, чтобы можно было донабрать то, что упустил
void PRINT_WINDOW_LOGIC::ButLostClicked(){
    text_browser->setVisible(true);
}
///////////////////////////////////////////////////////////////////////
/////////////////PRINT_WINDOW_LOGIC::ButLostClicked////////////////////
///////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
///////////PRINT_WINDOW_LOGIC::BoxTrainingCurrentIndexChanged///////////
////////////////////////////////////////////////////////////////////////
/// обрабатывает событие выбора другой тренировки в комбо боксе и
/// подгружает информацию об ошибках и статистике
void PRINT_WINDOW_LOGIC::BoxTrainingCurrentIndexChanged(int){
    mode->GetStatistics(box_mode_name->currentText(),box_training_name->currentText());
    but_start->setEnabled(true); // это если кнопка была заблочена, когда книга пройдена
    OnUpdateData();

    mode->ClearStatisticsContainers();
    mode->UpdateStatisticsContainers(box_mode_name->currentText(),box_training_name->currentText());

    if(but_hide_group_plot->isVisible()){
        ld_plot_value->clear();
        delete tracer;
        ButShowGroupPlotClicked();
    }
}
////////////////////////////////////////////////////////////////////////
///////////PRINT_WINDOW_LOGIC::BoxTrainingCurrentIndexChanged///////////
////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
//////////PRINT_WINDOW_LOGIC::BoxFromYearCurrentIndexChanged///////////
///////////////////////////////////////////////////////////////////////
/// проверяет корректность выбранного промежутка времени
void PRINT_WINDOW_LOGIC::BoxFromYearCurrentIndexChanged(int index){
    if(index > box_to_year->currentIndex()){
        qDebug()<<"Значение начала промежутка не может быть больше конца!";
        box_from_year->setCurrentIndex(mode->from_year - 2019); // возвращаем значение до изменения
        return;
    }

    if(box_to_month->currentIndex() < box_from_month->currentIndex()){
        box_to_month->setCurrentIndex(box_from_month->currentIndex());
        mode->to_month = mode->from_month;

    }
    mode->from_year = index + 2019; // + 2019, чтобы вести отчет с 2019 года
}
///////////////////////////////////////////////////////////////////////
//////////PRINT_WINDOW_LOGIC::BoxFromYearCurrentIndexChanged///////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
/////////PRINT_WINDOW_LOGIC::BoxFromMonthCurrentIndexChanged///////////
///////////////////////////////////////////////////////////////////////
/// проверяет корректность выбранного промежутка времени
void PRINT_WINDOW_LOGIC::BoxFromMonthCurrentIndexChanged(int index){
    if(index > box_to_month->currentIndex() && box_from_year->currentIndex() == box_to_year->currentIndex()){
        qDebug()<<"Значение начала промежутка не может быть больше конца!";
        box_from_month->setCurrentIndex(mode->from_month - 1);
        return;
    }
    mode->from_month = index + 1; // +1, чтобы вести с января
}
///////////////////////////////////////////////////////////////////////
/////////PRINT_WINDOW_LOGIC::BoxFromMonthCurrentIndexChanged///////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
///////////PRINT_WINDOW_LOGIC::BoxToYearCurrentIndexChan///////////////
///////////////////////////////////////////////////////////////////////
/// проверяет корректность выбранного промежутка времени
void PRINT_WINDOW_LOGIC::BoxToYearCurrentIndexChanged(int index){
    if(index < box_from_year->currentIndex()){
        qDebug()<<"Значение конца промежутка не может быть меньше начала!";
        box_to_year->setCurrentIndex(mode->to_year - 2019);
        return;
    }

    if(box_to_month->currentIndex() < box_from_month->currentIndex()){
        box_to_month->setCurrentIndex(box_from_month->currentIndex());
        mode->to_month = mode->from_month;

    }

    mode->to_year = index + 2019;
}
///////////////////////////////////////////////////////////////////////
///////////PRINT_WINDOW_LOGIC::BoxToYearCurrentIndexChan///////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
/////////PRINT_WINDOW_LOGIC::BoxToMonthCurrentIndexChanged/////////////
///////////////////////////////////////////////////////////////////////
/// проверяет корректность выбранного промежутка времени
void PRINT_WINDOW_LOGIC::BoxToMonthCurrentIndexChanged(int index){
    if(index < box_from_month->currentIndex() && box_from_year->currentIndex() == box_to_year->currentIndex()){
        qDebug()<<"Значение конца промежутка не может быть меньше начала!";
        box_to_month->setCurrentIndex(mode->to_month - 1);
        return;
    }
    mode->to_month = index + 1;
}
///////////////////////////////////////////////////////////////////////
/////////PRINT_WINDOW_LOGIC::BoxToMonthCurrentIndexChanged/////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
//////////////////PRINT_WINDOW_LOGIC::PlotMousePress///////////////////
///////////////////////////////////////////////////////////////////////
/// обрабатывает нажатие мышки на графике
void PRINT_WINDOW_LOGIC::PlotMousePress(QMouseEvent *event){
    double coordX = plot->xAxis->pixelToCoord(event->pos().x()); // Определяем координату X на графике, где был произведён клик мышью

    QString type;
    if(chbox_amount_text->isChecked()) type = "Кол-во текстов";
    else if(chbox_speed->isChecked()) type = "Скорость";
    else if(chbox_mistake->isChecked()) type = "Ошибки %";

    tracer->setGraphKey(coordX); // По координате X клика мыши определим ближайшие координаты для трассировщика
    plot->replot(); // Перерисовываем содержимое полотна графика

    double now = tracer->position->key(); //получаем дату
    QDateTime *date = new QDateTime;
    date->setTime_t(now); // Выводим координаты точки графика, где установился трассировщик, в ld_plot_value
    QString res_message;
    if(type == "Кол-во текстов") res_message = "Текстов набранно";
    else if(type == "Скорость") res_message = "Скорость по пройденным текстам в симв/м";
    else res_message = "Ошибок по пройденным текстам в %";

    ld_plot_value->setText("Дата: " + date->date().toString()+"; "+ res_message+ ": " + QString::number(tracer->position->value()));

    delete date;
}
///////////////////////////////////////////////////////////////////////
//////////////////PRINT_WINDOW_LOGIC::PlotMousePress///////////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
//////////////////PRINT_WINDOW_LOGIC::PlotMouseMove////////////////////
///////////////////////////////////////////////////////////////////////
/// обрабатывает движение мышки на графике
void PRINT_WINDOW_LOGIC::PlotMouseMove(QMouseEvent *event){
    if(QApplication::mouseButtons()) PlotMousePress(event);
}
///////////////////////////////////////////////////////////////////////
//////////////////PRINT_WINDOW_LOGIC::PlotMouseMove////////////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
////////////////PRINT_WINDOW_LOGIC::CHBoxSpeedChecked//////////////////
///////////////////////////////////////////////////////////////////////
void PRINT_WINDOW_LOGIC::CHBoxSpeedChecked(){
    chbox_speed->setCheckState(Qt::Checked);
    chbox_mistake->setCheckState(Qt::Unchecked);
    chbox_amount_text->setCheckState(Qt::Unchecked);
    ld_plot_value->clear();
    delete tracer;
    ButShowGroupPlotClicked();
}
///////////////////////////////////////////////////////////////////////
////////////////PRINT_WINDOW_LOGIC::CHBoxSpeedChecked//////////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
///////////////PRINT_WINDOW_LOGIC::CHBoxMistakeChecked/////////////////
///////////////////////////////////////////////////////////////////////
void PRINT_WINDOW_LOGIC::CHBoxMistakeChecked(){
    chbox_speed->setCheckState(Qt::Unchecked);
    chbox_mistake->setCheckState(Qt::Checked);
    chbox_amount_text->setCheckState(Qt::Unchecked);
    ld_plot_value->clear();
    delete tracer;
    ButShowGroupPlotClicked();
}
///////////////////////////////////////////////////////////////////////
///////////////PRINT_WINDOW_LOGIC::CHBoxMistakeChecked/////////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
//////////////PRINT_WINDOW_LOGIC::CHBoxAmountTextChecked///////////////
///////////////////////////////////////////////////////////////////////
void PRINT_WINDOW_LOGIC::CHBoxAmountTextChecked(){
    chbox_speed->setCheckState(Qt::Unchecked);
    chbox_mistake->setCheckState(Qt::Unchecked);
    chbox_amount_text->setCheckState(Qt::Checked);
    ld_plot_value->clear();
    delete tracer;
    ButShowGroupPlotClicked();
}
///////////////////////////////////////////////////////////////////////
//////////////PRINT_WINDOW_LOGIC::CHBoxAmountTextChecked///////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
//////////////PRINT_WINDOW_LOGIC::CHBoxLetterErrorsChecked/////////////
///////////////////////////////////////////////////////////////////////
void PRINT_WINDOW_LOGIC::CHBoxLetterErrorsChecked(){
    chbox_letter_errors->setCheckState(Qt::Checked);
    chbox_syllable_errors->setCheckState(Qt::Unchecked);
    chbox_word_errors->setCheckState(Qt::Unchecked);
    chbox_words_speed->setCheckState(Qt::Unchecked);
}
///////////////////////////////////////////////////////////////////////
//////////////PRINT_WINDOW_LOGIC::CHBoxLetterErrorsChecked/////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
/////////////PRINT_WINDOW_LOGIC::CHBoxSyllableErrorsChecked////////////
///////////////////////////////////////////////////////////////////////
void PRINT_WINDOW_LOGIC::CHBoxSyllableErrorsChecked(){
    chbox_letter_errors->setCheckState(Qt::Unchecked);
    chbox_syllable_errors->setCheckState(Qt::Checked);
    chbox_word_errors->setCheckState(Qt::Unchecked);
    chbox_words_speed->setCheckState(Qt::Unchecked);
}
///////////////////////////////////////////////////////////////////////
/////////////PRINT_WINDOW_LOGIC::CHBoxSyllableErrorsChecked////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
/////////////PRINT_WINDOW_LOGIC::CHBoxWordErrorsChecked////////////////
///////////////////////////////////////////////////////////////////////
void PRINT_WINDOW_LOGIC::CHBoxWordErrorsChecked(){
    chbox_letter_errors->setCheckState(Qt::Unchecked);
    chbox_syllable_errors->setCheckState(Qt::Unchecked);
    chbox_word_errors->setCheckState(Qt::Checked);
    chbox_words_speed->setCheckState(Qt::Unchecked);
}
///////////////////////////////////////////////////////////////////////
/////////////PRINT_WINDOW_LOGIC::CHBoxWordErrorsChecked////////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
//////////////PRINT_WINDOW_LOGIC::CHBoxWordsSpeedChecked///////////////
///////////////////////////////////////////////////////////////////////
void PRINT_WINDOW_LOGIC::CHBoxWordsSpeedChecked(){
    chbox_letter_errors->setCheckState(Qt::Unchecked);
    chbox_syllable_errors->setCheckState(Qt::Unchecked);
    chbox_word_errors->setCheckState(Qt::Unchecked);
    chbox_words_speed->setCheckState(Qt::Checked);
}
///////////////////////////////////////////////////////////////////////
//////////////PRINT_WINDOW_LOGIC::CHBoxWordsSpeedChecked///////////////
///////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
////////////////////PRINT_WINDOW_LOGIC::OnTime//////////////////////////
////////////////////////////////////////////////////////////////////////
/// функция создана для подсчета времени нахождения в игре, при наборе
/// текста, для сохранения в статистике, а также для подсчета
/// времени написания каждого слова
void PRINT_WINDOW_LOGIC::OnTime(){
    ms+=10;
    if(ms >= 1000){
        ms = 0;
        sec++;
        ld_current_sec->setText(QString::number(sec));
        if(sec >= 60){
            sec = 0;
            min++;
            ld_current_min->setText(QString::number(min));
        }             
    }
    end_ms = ms + sec*1000 + min*60*1000;
}
////////////////////////////////////////////////////////////////////////
////////////////////PRINT_WINDOW_LOGIC::OnTime//////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////PRINT_WINDOW_LOGIC::OnPauseTime///////////////////////
////////////////////////////////////////////////////////////////////////
/// функция создана для удерживания паузы перед игрой
void PRINT_WINDOW_LOGIC::OnPauseTime(){
      if(pause_time<=0){
        pause_timer->stop();
        if(box_mode_name->currentText() == TEXT_ACTING) voice_acting_mode->Speak(); //если выбран режим озвучки, то когда пауза заканчивается начинается озвучка
        timer->start(10);//обновляется каждые 100мс
        ld_game_pole->setReadOnly(false);
        ld_game_pole->setFocus();

      }
      else{
        --pause_time;
        ld_current_sec->setText(QString::number(pause_time));
        ld_game_pole->setReadOnly(true);
      }
}
////////////////////////////////////////////////////////////////////////
//////////////////PRINT_WINDOW_LOGIC::OnPauseTime///////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////////PRINT_WINDOW_LOGIC::OnUpdateData///////////////////////
////////////////////////////////////////////////////////////////////////
/// функция обновляет данные после набора текста, или при загрузке
/// приложения в информационных полях.
void PRINT_WINDOW_LOGIC::OnUpdateData(){
    ld_text_amount->setText(QString::number(mode->text_amount)); //здесь заполняем данные для отображения на поле
    ld_record->setText(QString::number(floor(mode->record)));
    ld_average_speed->setText(QString::number(floor(mode->average_speed))+" симв/м");
    ld_mistakes->setText(QString::number(mode->mistakes)+"%");
    ld_all_time->setText(QString::number(floor(mode->play_time_hours)) + " ч; " +
                         QString::number(floor(mode->play_time_min)) + " м; "); // floor убирает остаток от числа
}
////////////////////////////////////////////////////////////////////////
/////////////////PRINT_WINDOW_LOGIC::OnUpdateData///////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////////////PRINT_WINDOW_LOGIC::IsWin//////////////////////////
////////////////////////////////////////////////////////////////////////
/// функция вызывается при "победе" (окончании тренировки), для подсчета
/// данных, их обработки и сохранения.
void PRINT_WINDOW_LOGIC::IsWin(){
    timer->stop();
    delete timer;
    //pause_time = PAUSE;


    //обрабатываем полученные данные
    float average_current_speed = edit_text.length() - 1;
    average_current_speed = round(round((average_current_speed /(ld_current_min->text().toFloat()*60 + ld_current_sec->text().toFloat())*60)*100)/100);
    ld_current_speed->setText(QString::number(average_current_speed)); //считаем среднюю скорость за текст

    float current_mistakes =  round(100*ld_current_mistakes->text().toFloat()*100/(edit_text.length()-1))/100;
    lab_current_mistakes->setText("Ошибки: ("+ QString::number(current_mistakes) +"%)");
    //считаем кол-во ошибок в процентах  // round*100/100 это нужно, чтобы было 2 знака после запятой


    if(!errors_mode){ // если не запущен режим по работе над ошибками, то данные надо сохранить и обновить

        if(average_current_speed>mode->record){ // если новый рекорд
            sounds->Play(sounds->print_record);
            mode->record = average_current_speed;
            text_browser->insertPlainText("         New record!!!           ");
        }

        mode->average_speed = (average_current_speed + mode->text_amount*mode->average_speed) / (mode->text_amount+1); // средняя скорость за все время
        mode->mistakes = round(100*((round(100*ld_current_mistakes->text().toFloat()*100/(edit_text.length()-1))/100) +
                              mode->text_amount*mode->mistakes)/(mode->text_amount+1))/100;//среднее кол-во ошибок за все время

        ++mode->text_amount; //кол-во пройденных текстов стало больше на 1

        mode->play_time_min += min; //сохраняем время
        mode->play_time_sec += sec;
        if(mode->play_time_sec >= 60){
            mode->play_time_min++;
            mode->play_time_sec-=60;
         }
        if( mode->play_time_min >= 60){
            mode->play_time_min -=60;
            mode->play_time_hours++;
        }

        OnUpdateData();
        mode->UpdateStatistics(box_mode_name->currentText(),box_training_name->currentText()); // загружаем инфу в бд
        mode->UpdateAdditionalStatistics(box_mode_name->currentText(),box_training_name->currentText());//мы отправляем статистику ошибочных букв в бд
        mode->UpdateStatisticsPerTime(box_mode_name->currentText(),box_training_name->currentText(),current_mistakes,average_current_speed);
    }

    errors_mode = false;

    but_load_training->setEnabled(true); // делаем доступными на форме

    ld_game_pole->setEnabled(false);
    ld_game_pole->clear();

    group_report->setEnabled(true);

    box_training_name->setEnabled(true);
    but_load_training->setEnabled(true);

    text_browser->clear();//очистка основного экрана

    text_mistakes_browser->setVisible(true); //показываем экран с ошибками
    text_mistakes_browser->append(mistakes_text);
}
////////////////////////////////////////////////////////////////////////
/////////////////////PRINT_WINDOW_LOGIC::IsWin//////////////////////////
////////////////////////////////////////////////////////////////////////

