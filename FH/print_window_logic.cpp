#include "print_window_logic.h"
#include "training_mode.h"
#include "sounds.h"

#include <cmath>
#include <QtWidgets>

///////////////////////////////////////////////////////////////////////
////////////////////////////MAIN_WINDOW/////////////////////////////////
////////////////////////////////////////////////////////////////////////
// Эта функция используется для задания значений переменных при старте//
// приложения.                                                        //
PRINT_WINDOW_LOGIC::PRINT_WINDOW_LOGIC(QPushButton *but_start, QPushButton *but_load_training, QComboBox *box_training,
 QLineEdit *ld_game_pole, QLineEdit *ld_current_mistakes, QLineEdit *ld_current_speed, QLineEdit *ld_text_amount,
 QLineEdit *ld_record, QLineEdit *ld_average_speed, QLineEdit *ld_mistakes, QLineEdit *ld_all_time,
 QLineEdit *ld_current_min, QLineEdit *ld_current_sec, QTextBrowser *text_browser, QLabel* lab_current_mistakes,
 QPushButton *but_create_training, QPushButton *but_add_training){

    this->but_start = but_start;
    this->but_load_training = but_load_training;
    this->but_create_training = but_create_training;
    this->but_add_training = but_add_training;
    this->box_training = box_training;
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
    this->text_browser = text_browser;
    this->lab_current_mistakes = lab_current_mistakes;
    this->ld_game_pole->setEnabled(false);
    this->but_start->setEnabled(false);
    this->box_training->clear();

    sounds = new SOUNDS;

    training = new TRAINING;
    training->GetTrainingNames();   // подгружаем названия наших тренировок в box_training
    this->box_training->addItems(training->training_names);

    pause_timer = new QTimer(this); //создаем таймер для паузы
    connect (pause_timer, SIGNAL(timeout()),this, SLOT(OnPauseTime()));

    connect(this->box_training,SIGNAL(currentIndexChanged(int)),this,SLOT(BoxTrainingCurrentIndexChanged(int)));
    connect(this->but_load_training, SIGNAL(clicked()),this,SLOT(ButLoadTrainingClicked()));
    connect(this->but_start, SIGNAL(clicked()),this, SLOT(ButStartClicked()));
    connect(this->ld_game_pole, SIGNAL(textChanged(QString)), this, SLOT(LdFieldTextChanged(QString)));

    training->GetStatistics(this->box_training->currentText());//загружаем данные для режима в переменные
    OnUpdateData(); //добавляем на форму

    training->ClearStatisticsContainers();
    training->UpdateStatisticsContainers(box_training->currentText());

}

PRINT_WINDOW_LOGIC::~PRINT_WINDOW_LOGIC(){
    delete training;
    //?delete sounds;
}

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
        if(training->symbols_counter + content.length() >SYMBOLS_LIMIT){
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
                training->symbols_counter +=word.length(); //увеличиваем кол-во символов до удаления последнего символа chop(1), так как потом прибавил \n
                word.chop(1);//удаляем символ enter для того, чтобы в browser не записался лишний enter
                training->word_training_list.push_back(word);
                word ="";
            }else{
                if(i == content.length()-1 && word.length()>1){//случай, если после последнего слова в файле не поставили enter
                    training->word_training_list.push_back(word);
                    training->symbols_counter +=word.length()+1; //увеличиваем кол-во символов
                    word ="";
                }
                if(content[i] =='\n' && word.length() <= 1){
                    lab_status->setText("Файл сделан некорректно!");
                    return;
                }
            }
        }
        ld_current_symbols->setText(QString::number(training->symbols_counter)); // записываем текущее кол-во символов
        lab_status->setText("Файл считан успешно!");

        for(auto it : training->word_training_list) browser_training_word->append(it); //добавляем наши слова на браузер
    }
    else{
        lab_status->setText("Ошибка открытия файла!");
    }

}

void PRINT_WINDOW_LOGIC::ButAddWordClicked(){
    if(training->CheckWordForTrainingList(ld_add_word->text())){ //если слово написано правильно
        training->word_training_list.push_back(ld_add_word->text());
        lab_status->setText("Слово добавлено!");
        ld_current_symbols->setText(QString::number(training->symbols_counter));
        browser_training_word->append(ld_add_word->text());
        ld_add_word->clear();
    }else{
        lab_status->setText("Ошибка в слове!");
    }
}

void PRINT_WINDOW_LOGIC::ButCreateTrainingClicked(){
    if(training->CheckCustomTrainingName(ld_training_name->text())){ //если имя правильное
        if(!training->word_training_list.empty()){//если не пустой
            if(training->symbols_counter <= SYMBOLS_LIMIT){ //если не превышен лимит символов
                if(training->AddTraining()){                    
                    ld_current_symbols->setText("0"); //очищаем поля в доп форме и переменные для создания тренировки
                    ld_training_name->clear();
                    ld_add_word->clear();
                    training->symbols_counter = 0;
                    training->word_training_list.clear(); //удаляем, так как нам уже не нужно его запоминать после создания тренировки
                    browser_training_word->clear();
                    lab_status->setText("Тренировка добавлена!");

                    box_training->addItem(training->training_names.last());//обновляем данные на освновной форме (выбираем новую тренировку)
                    training->GetStatistics(training->training_names.last());
                    OnUpdateData();

                    training->ClearStatisticsContainers();
                    training->UpdateStatisticsContainers(box_training->currentText());
                }else{
                    lab_status->setText("Ошибка сохранения тренировки!");
                }

            }else{
                lab_status->setText("Превышен лимит символов в " + QString::number(SYMBOLS_LIMIT) + "!\n"
                                    "Последнее слово удалено!");
                training->word_training_list.pop_back();
            }

        }else{
            lab_status->setText("Тренировка пуста!");
        }
    }else{
        lab_status->setText("Ошибка ввода имени!");
    }
}

void PRINT_WINDOW_LOGIC::ButDeleteLastWordClicked(){
    if(!training->word_training_list.empty()){//если не пусто, то удаляем последнее слово в тренировке
        lab_status->setText("Удалено: "+training->word_training_list.last());
        training->symbols_counter -= training->word_training_list.last().length()+1;//-1 так как есть ещё символ enter
        ld_current_symbols->setText(QString::number(training->symbols_counter));
        training->word_training_list.pop_back();
        browser_training_word->clear();

        for(auto it = training->word_training_list.begin();it<training->word_training_list.end();++it) browser_training_word->append(*it);

    }else{
        lab_status->setText("Тренировка пуста!");
    }
}

void PRINT_WINDOW_LOGIC::ButDeleteWordClicked(){
    bool found = false;
    if(!training->word_training_list.empty()){ //если не пусто
        for(auto it = training->word_training_list.begin();it<training->word_training_list.end();++it){ //тогда ищем слово для удаления в тренировке

            if(*it == ld_delete_word->text()){ //если находим, то удаляем его
                training->symbols_counter -= it->length()+1;//уменьшаем кол-во символов в тренировке, -1 так как есть ещё символ enter
                ld_current_symbols->setText(QString::number(training->symbols_counter));
                lab_status->setText("Удалено: "+ *it);
                training->word_training_list.erase(it);
                browser_training_word->clear();
                found = true;
            }
        }
        if(!found){
            lab_status->setText("Такого слова нет!"); //если не нашли
            return;
        }

        for(auto it = training->word_training_list.begin();it<training->word_training_list.end();++it) browser_training_word->append(*it);

    }else{
        lab_status->setText("Тренировка пуста!");
    }
}

void PRINT_WINDOW_LOGIC::GetCreateTrainingComponents(QPushButton * but_delete_word, QPushButton *but_delete_last_word, QPushButton *but_add_file,
QPushButton *but_add_word, QPushButton *but_publish_training, QLineEdit *ld_delete_word, QLineEdit *ld_training_name, QLineEdit *ld_add_word,
QLineEdit *ld_current_symbols, QLabel *lab_status, QTextBrowser *browser_training_word){
    training->symbols_counter = 0;
    training->word_training_list.clear();

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


////////////////////////////////////////////////////////////////////////
////////////////////////////MAIN_WINDOW/////////////////////////////////
////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////
//////////////////ON_LINE_EDIT_FIELD_TEXT_CHANGED///////////////////////
////////////////////////////////////////////////////////////////////////
// Эта функция обрабатывает события изменения вводимого текста в      //
// игровое поле в ходе игры. Проверяет на победу.                     //
void PRINT_WINDOW_LOGIC::LdFieldTextChanged(QString current_word){
    if(start_writing){
        start_ms = ms + sec*1000 + min*60*1000; //считаем кол-во мс, которые прошли с начала набора слова
        start_writing = false;
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
                    training->MistakeReader(edit_text, letter); // для анализа ошибок
                }

        }else{    // если правильно ввели букву

            //if(current_word[letter - line_size] != ' ')  end_ms = ms + sec*1000 + min*60*1000;//это для запоминания конечного значения ввода слова
            was_minus = false;                            // для статистики скорости набора слова
            is_mistake = false;
            letter++;

            if(current_word[letter - 1 - line_size] == ' '){ //когда ввели все слово правильно -1, так как до этого выше увеличил на 1, а это значени след буквы
                line_size = letter;

                training->WordSpeedReader(ld_game_pole->text(),ld_game_pole->text().length()-1,abs(end_ms-start_ms)); //передаем длину слова и время написания его в мс
                start_writing = true;                                               // length()-1, чтобы пробел не учитывать

                ld_game_pole->clear();
            }else if(edit_text.length() - 1 == letter){
                training->WordSpeedReader(ld_game_pole->text()+" ",ld_game_pole->text().length(),abs(end_ms-start_ms)); // добавляю здесь " ", так как в другой функции
            }                                                                                       //всегда удаляю пробел, а в конце строки его нет

            if(edit_text.length() -1  == letter){ //проверка на конец текста, -2 так как в конце каждой строки есть символ перехода на новую
                                     //n, его нам считать не надо, и ещё -1 так как с нуля идет счет
                IsWin(); //победа
            }
        }
    }
    else{
            if(letter>current_word.length() +line_size && letter>0){ //сюда попадаем, когда стираем символы, которые были правильными
                --letter;
                first_time = true;
            }
            else{
                is_mistake = false;
                if(current_word.length()- 1 + line_size  == letter-1) first_time = true;  // когда стираем уже неправильный символ
            }
    }
}
////////////////////////////////////////////////////////////////////////
//////////////////ON_LINE_EDIT_FIELD_TEXT_CHANGED///////////////////////
////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////
//////////////////////////ON_BUT_START_CLICKED//////////////////////////
////////////////////////////////////////////////////////////////////////
// Эта функция обрабатывает нажатие на кнопку старта игры             //
void PRINT_WINDOW_LOGIC::ButStartClicked(){
    if(text_browser->toPlainText() == ""){
        text_browser->insertPlainText("Text not Loaded");
        ld_game_pole->setEnabled(false);
    }
    else{
        ld_game_pole->setEnabled(true); //обнуляем данные на форме временной статы
        ld_current_mistakes->setText("0");
        ld_current_speed->setText("0");
        lab_current_mistakes->setText("Ошибки: ");
        pause_timer->start(1000);
        but_load_training->setEnabled(false);
        but_start->setEnabled(false);
        box_training->setEnabled(false);

        letter = 0; // надо каждый раз сбрасывать для корректной работы считывания строки + отображения статистики
        line_size = 0;
        mistakes = 0;
        is_mistake = false;
        sec = 0;
        min = 0;
        timer = new QTimer(this); //создаем таймер
        connect (timer, SIGNAL(timeout()),this, SLOT(OnTime()));
    }
}
////////////////////////////////////////////////////////////////////////
//////////////////////////ON_BUT_START_CLICKED//////////////////////////
////////////////////////////////////////////////////////////////////////





void PRINT_WINDOW_LOGIC::ButLoadTrainingClicked(){
    text_browser->clear();
    text_browser->insertPlainText(training->GetTraining(box_training->currentText()));
    edit_text = text_browser->toPlainText();
    but_start->setEnabled(true);
}



////////////////////////////////////////////////////////////////////////
////////////ON_COMBO_BOX_SELECT_BOOK_CURRENT_INDEX_CHANGED//////////////
////////////////////////////////////////////////////////////////////////
// Эта функция обрабатывает событие выбора другой книги в комбо боксе //
// и подгружает информацию о игровой книге.                           //
void PRINT_WINDOW_LOGIC::BoxTrainingCurrentIndexChanged(int){
    training->GetStatistics(box_training->currentText());
    but_start->setEnabled(true); // это если кнопка была заблочена, когда книга пройдена
    OnUpdateData();

    training->ClearStatisticsContainers();
    training->UpdateStatisticsContainers(box_training->currentText());
}
////////////////////////////////////////////////////////////////////////
////////////ON_COMBO_BOX_SELECT_BOOK_CURRENT_INDEX_CHANGED//////////////
////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////
///////////////////////////////ON_TIME//////////////////////////////////
////////////////////////////////////////////////////////////////////////
// Эта функция создана для подсчета времени нахождения в игре, при    //
// при наборе текста, для сохранения этого в статистике.              //
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
///////////////////////////////ON_TIME//////////////////////////////////
////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////
///////////////////////////ON_PAUSE_TIME////////////////////////////////
////////////////////////////////////////////////////////////////////////
// Эта функция создана для удерживания паузы длиной PAUSE перед игрой.//
void PRINT_WINDOW_LOGIC::OnPauseTime(){
      if(pause_time<=0){
        pause_timer->stop();
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
///////////////////////////ON_PAUSE_TIME////////////////////////////////
////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////
////////////////////////////ON_UPDATE_DATE//////////////////////////////
////////////////////////////////////////////////////////////////////////
// Функция обновляет данные после набора текста, или при загрузке     //
// приложения.                                                        //
void PRINT_WINDOW_LOGIC::OnUpdateData(){
    ld_text_amount->setText(QString::number(training->text_amount)); //здесь заполняем данные для отображения на поле
    ld_record->setText(QString::number(floor(training->record)));
    ld_average_speed->setText(QString::number(floor(training->average_speed))+" симв/м");
    ld_mistakes->setText(QString::number(training->mistakes)+"%");
    ld_all_time->setText(QString::number(floor(training->play_time_hours)) + " ч; " +
                         QString::number(floor(training->play_time_min)) + " м; "); // floor убирает остаток от числа
}

////////////////////////////////////////////////////////////////////////
////////////////////////////ON_UPDATE_DATE//////////////////////////////
////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////
////////////////////////////////////ON_WIN//////////////////////////////
////////////////////////////////////////////////////////////////////////
// Функция вызывается при "победе" (окончании игрового текста), для   //
// подсчета игровых данных, их обработки и сохранения.                //
void PRINT_WINDOW_LOGIC::IsWin(){
    timer->stop();
    delete timer;
    //pause_time = PAUSE;
    ld_game_pole->setEnabled(false);
    ld_game_pole->clear();

    //обрабатываем полученные данные
    float average_current_speed = edit_text.length() - 1;
    average_current_speed = round(round((average_current_speed /(ld_current_min->text().toFloat()*60 + ld_current_sec->text().toFloat())*60)*100)/100);
    ld_current_speed->setText(QString::number(average_current_speed)); //считаем среднюю скорость за текст

    if(average_current_speed>training->record){ // если новый рекорд
        sounds->Play(sounds->print_record);
        training->record = average_current_speed;
        text_browser->insertPlainText("         New record!!!           ");
    }

    float current_mistakes =  round(100*ld_current_mistakes->text().toFloat()*100/(edit_text.length()-1))/100;
    lab_current_mistakes->setText("Ошибки: ("+ QString::number(current_mistakes) +"%)");
    //считаем кол-во ошибок в процентах  // round*100/100 это нужно, чтобы было 2 знака после запятой

    training->average_speed = (average_current_speed + training->text_amount*training->average_speed) / (training->text_amount+1); // средняя скорость за все время
    training->mistakes = round(100*((round(100*ld_current_mistakes->text().toFloat()*100/(edit_text.length()-1))/100) +
                          training->text_amount*training->mistakes)/(training->text_amount+1))/100;//среднее кол-во ошибок за все время

    ++training->text_amount; //кол-во пройденных текстов стало больше на 1

    training->play_time_min += min; //сохраняем время
    training->play_time_sec += sec;
    if(training->play_time_sec >= 60){
        training->play_time_min++;
        training->play_time_sec-=60;
     }
    if( training->play_time_min >= 60){
        training->play_time_min -=60;
        training->play_time_hours++;
    }


    OnUpdateData();
    training->UpdateStatistics(box_training->currentText()); // загружаем инфу в бд
    training->UpdateAdditionalStatistics(box_training->currentText());//мы отправляем статистику ошибочных букв в бд
    training->UpdateStatisticsPerTime(box_training->currentText(),current_mistakes,average_current_speed);

    but_load_training->setEnabled(true); // делаем доступными на форме
    box_training->setEnabled(true);
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////ON_WIN//////////////////////////////
////////////////////////////////////////////////////////////////////////

