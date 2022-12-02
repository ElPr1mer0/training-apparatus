#include "training_mode.h"
#include "db.h"
#include "chart.h"
#include "QString"
#include "QDate"
#include "QDebug"
#include <math.h>






void TRAINING::AddErrorInConteiner(QMap<QString, int> &errors_mode, QString &mistake){
    auto  it = errors_mode.find(mistake);//смотрим есть ли уже ошибка с этой буквой/слогом в списке
    if(it !=errors_mode.end()) ++it.value(); //если есть, то мы увеличиваем кол-во данных ошибок на 1
    else {
        errors_mode.insert(mistake, 1); //если нет, то создаем запись буквы/слога + 1 ошибка
        qDebug()<<"Добавилась новая ошибка! " + mistake;
    }
}

void TRAINING::GetStatisticsValue(QString &value, QString &statistics, int &i){
    while(statistics[i]!=' ' && statistics[i]!='\n'){
        value+=statistics[i];
        i++;
    }
    ++i; //после того, как нашли пробел, скипаем его
}

bool TRAINING::CheckGap(const QString &line){
    for(int i = 0; i<line.length();++i)
        if(line[i] == ' ') return true;
    return false;
}

void TRAINING::ClearStatisticsContainers(){
    letter_errors.clear();//обнуляем, чтобы можно было записывать новую статистику
    syllable_errors.clear();
    word_errors.clear();
    words_speed.clear();
    words_amount.clear();
    statistics_per_time.clear();
}

void TRAINING::UpdateStatisticsContainers(const QString &training_name){
    GetPrintErrors(training_name,letter_errors, "letter_errors");
    GetPrintErrors(training_name,syllable_errors, "syllable_errors");
    GetPrintErrors(training_name,word_errors, "word_errors");
    GetWordsSpeed(training_name);
    GetStatisticsPerTime(training_name);
}

////////////////////////////////////////////////////////////////////////
//////////////////////////ADD_TRAINING//////////////////////////////////
////////////////////////////////////////////////////////////////////////
// Эта функция добавляет words-файл для создания тренировки в каталог,//
// где хранятся остальные words-файлы и откуда они загружаются        //
bool TRAINING::AddTraining(){
    QString content = "";
    for(auto it = word_training_list.begin();it!=word_training_list.end();++it) content += *it+'\n';

    if(db->CreateCustomTraining("training", custom_training_name, content)){ //добавляем новый режим в таблицу mode
        db->SendTrainingStatistics("training", custom_training_name,"0; 0; 0; 0; 0; 0; 0;");//создаем статистику по режиму в таблицу statistics
        content = "";
        training_names.append(custom_training_name);//добавляем наше имя тренировки в список

        QString new_training_name = "";
        for(auto it : training_names) new_training_name += it +"\n"; //создаем строку наших имен для отправки в бд

        db->SendAddedTraining("training",new_training_name);//добавляем название новой тренировки в бд
        return true;
    }
    return false;   //если что-то пошло не так при обращении к бд, то возвращаем false
}

bool TRAINING::CheckWordForTrainingList(const QString &word){
    if(word == ""){
        qDebug()<<"Введите слово!";
        return false;
    }

    for(int i = 0; i<word.length();++i){
        if(word[i] == ' '){
            qDebug()<<"Слово содержит пробел! Оно не будет добавлено!";
            return false;
        }
        if(word[i] == '\n') return false; //если там есть символ перевода на новую строку, выходим
    }
    symbols_counter +=word.length() + 1 ;//если слово норм, то мы записываем кол-во символов +1 так как будет еще символ enter
    if(symbols_counter>SYMBOLS_LIMIT){//если произошло переполнение
        symbols_counter-=word.length()+1;
        return false;
    }
    return true;
}

bool TRAINING::CheckCustomTrainingName(const QString &name){
    if(name == ""){
        qDebug()<<"Введите имя тренировки!";
        return false;
    }

    for(int i = 0; i<name.length();++i){
        if((name[i] > 31 && name[i] < 58)  || (name[i] > 64 && name[i] < 91)
           ||(name[i] > 96 && name[i] < 123) || (name[i] > 1039 && name[i] < 1106) //добавить еще другие символы
           || (name[i] == 1025)){
            // если латицина, кириллица или цифры, то ок, иначе выходим
        }else{
            qDebug()<<"Имя может состоять только из латиницы, кириллицы и цифр!";
            return false;
        }
    }
    custom_training_name = name;
    return true;
}
////////////////////////////////////////////////////////////////////////
//////////////////////////ADD_TRAINING//////////////////////////////////
////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////
//////////////////////////LOAD_TRAINING/////////////////////////////////
////////////////////////////////////////////////////////////////////////
// Эта функция формирует уровень из слов, находящихся в words-файле.////
QString TRAINING::GetTraining(const QString &training_name){
    QString training;
    db->LoadTraining("training",training_name, training);

    QString line = "", level = "";
    int totalWordsInFile = 0;

    for(int i = 0; i<training.length();++i) if(training[i] == '\n')++totalWordsInFile; // подсчитали кол-во слов в уровне

    if (totalWordsInFile == 0){
        qDebug()<<"Нет слов в данной тренировке!";
        return "Нет слов в данной тренировке!";
    }

    for(int i = 0; i<TOTAL_WORDS_PER_LEVEL;++i){ // собираем уровень из слов; TOTAL_WORDS_PER_LEVEL - максимальное кол-во слов на уровень
        int randWord = -1;

            while(randWord>totalWordsInFile || randWord<0)  randWord = rand() % totalWordsInFile + 1; // генератор рандома для слов

            line = "";
            int j = 0;
            int k;

            while(j<randWord){

                for(k = 0; j<randWord-1;++k) if(training[k] == '\n') ++j;

                for(;k<training.length();++k){
                    if(training[k] == '\n') break;
                    line =line + training[k];
                }
                j++;
            }

            level += line+" ";
        }
    qDebug()<<"Уровень создан успешно!";
    return level;
}
////////////////////////////////////////////////////////////////////////
//////////////////////////LOAD_TRAINING/////////////////////////////////
////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////
/////////////////////////////GetTrainingNames///////////////////////////
////////////////////////////////////////////////////////////////////////
// Эта функция загружает названия тренировок в комбо бокс где их можно//
// выбрать для игры.                                                  //
void TRAINING::GetTrainingNames(){
    QString data = "";
    if(!training_names.empty())training_names.clear();
    db->LoadTrainingNames("training", data); //отправляем строку для получения имен режима

    QString training = "";
    for(int i=0; i<data.length();++i){
        if(data[i]!='\n') training += data[i];
        else{
            training_names.append(training);
            training = "";
        }
    }
}
////////////////////////////////////////////////////////////////////////
/////////////////////////////GetTrainingNames///////////////////////////
////////////////////////////////////////////////////////////////////////



void TRAINING::UpdateStatistics(const QString &training_name){
    QString statistics;
    statistics = QString::number(text_amount) +" "+ QString::number(record) +" "+QString::number(average_speed) +" "+QString::number(mistakes) +" "+QString::number(play_time_hours) +" "+
    QString::number(play_time_min) +" "+ QString::number(play_time_sec)+" "; // записываем в строку всю статистику

    db->SendTrainingStatistics("training", training_name, statistics); //добавляем ее в бд
}


void TRAINING::GetStatistics(const QString &training_name){

    QString statistics;
    db->LoadTrainingStatistics("training",training_name, statistics); //отправляем строку для получения статистики по режиму

    QString record = "";
    QString average_speed = "";
    QString mistakes = "";
    QString play_time_hours = "";
    QString play_time_min = "";
    QString play_time_sec = "";
    QString text_amount = "";


    if(statistics != ""){ //после обрабатываем эту строку, считывая данные и занося в нужные переменные
        for(int i = 0; i<statistics.length();++i){
            GetStatisticsValue(text_amount, statistics, i);
            GetStatisticsValue(record, statistics, i);
            GetStatisticsValue(average_speed, statistics, i);
            GetStatisticsValue(mistakes, statistics, i);
            GetStatisticsValue(play_time_hours, statistics, i);
            GetStatisticsValue(play_time_min, statistics, i);
            GetStatisticsValue(play_time_sec, statistics, i);
        }
    }
    else{
        qDebug()<<"Статистика не загружана!";
        return;
    }

    this->record = record.toFloat();
    this->average_speed = average_speed.toFloat();
    this->mistakes = mistakes.toFloat();
    this->play_time_hours = play_time_hours.toInt();
    this->play_time_min = play_time_min.toInt();
    this->text_amount = text_amount.toInt();
    this->play_time_sec = play_time_sec.toInt();

    qDebug()<<"Статистика сохранена в переменные успешно!";

}

void TRAINING::MistakeReader(QString current_word, int current_pos){
    QString letter = QString(current_word[current_pos]);
    AddErrorInConteiner(letter_errors, letter);

    QString syllable;

    if(current_pos < current_word.length()-2){ // проверка, что можно брать 2 буквы после нашей ошибки
        syllable = current_word.mid(current_pos, 3); //копируем слог
        if(!CheckGap(syllable) || syllable.length()<3) AddErrorInConteiner(syllable_errors,syllable); //если есть пробел, то записывать не будем
    }                                                                                           //+ слог из 3 букв

    if(current_pos < current_word.length()-1 && current_pos > -1){// проверка на то, что после нашей ошибки и до можно брать буквы (когда она в середине слога)
        syllable = current_word.mid(current_pos-1, 3);
        if(!CheckGap(syllable) || syllable.length()<3) AddErrorInConteiner(syllable_errors,syllable);
    }

    if(current_pos > 1){
        syllable = current_word.mid(current_pos-2,3); // 2 буквы до нашей ошибки
        if(!CheckGap(syllable) ||syllable.length()<3) AddErrorInConteiner(syllable_errors,syllable);
    }

    QString word = "";
    if(current_word[current_pos] == ' ') return; //если ошибка в пробеле, то мы ее не записываем
    else{
        int i = current_pos; // иначе выписываем буквы слова до ошибки, пока не встретим пробел или начало текста
        while(i>=0 && current_word[i]!=' '){
            word =current_word[i] + word;
            --i;
        }
        i = current_pos+1;
        while(i<current_word.length() && current_word[i]!=' '){//потом выписываем буквы после ошибки пока не встреим пробел или конец текста
            word +=current_word[i];
            ++i;
        }
        AddErrorInConteiner(word_errors, word);
        qDebug()<<"Word: " + word;
    }

}

void TRAINING::GetPrintErrors(const QString& training_name, QMap<QString, int> &container,const QString &errors_mode){// имя режима, сам контейнер, его название
    QString statistics;

    db->LoadAdditionalStatistics("training",training_name, statistics, errors_mode); //получаем данные из бд

    QString key;
    QString value = "";

    if(!statistics.isEmpty()){
        for(int i=0; i<statistics.length();){
            key = statistics[i]; //сразу делаем так, если первый символ это пробел
            i++;
            GetStatisticsValue(key,statistics,i);
            GetStatisticsValue(value,statistics,i);
            container.insert(key,value.toInt());
            key = "";
            value = "";
        }
        qDebug()<<"Статистика ошибок по тексту загружена из базы данных!";
    }
    else qDebug()<<"Статистика ошибок по тексту не заполнена!";
}

void TRAINING::GetWordsSpeed(const QString &training_name){
    QString statistics;
    db->LoadAdditionalStatistics("training",training_name,statistics,"words_speed");

    QString key;
    QString value1 ="", value2 = "";

    if(!statistics.isEmpty()){
        for(int i=0; i<statistics.length();){
            GetStatisticsValue(key, statistics,i);
            GetStatisticsValue(value1, statistics,i);
            GetStatisticsValue(value2, statistics,i);
            words_speed.insert(key,value1.toInt());
            words_amount.insert(key,value2.toInt());
            key = "";
            value1 = "";
            value2 = "";
        }
        qDebug()<<"Статистика скорости слов загружена из базы данных!";
    }else qDebug()<<"Статистика скорости слов не заполнена!";
}

void TRAINING::UpdateAdditionalStatistics(const QString &training_name){ //название тренировки, имя контейнера
    if (letter_errors.empty()){
        qDebug()<<"Ошибок не было, не обновляем!";
        return;
    }
    else{
        QString statistics = "";
        for(auto it = letter_errors.begin();it!=letter_errors.end();++it) statistics += it.key()+" "+QString::number(it.value())+'\n';    //записываем статистику в строку для отправки в бд

        db->SendAdditionalStatistics("training",training_name, statistics, "letter_errors");

        statistics = "";
        for(auto it = syllable_errors.begin();it!=syllable_errors.end();++it) statistics += it.key()+" "+QString::number(it.value())+'\n';
        db->SendAdditionalStatistics("training",training_name, statistics, "syllable_errors");

        statistics = "";
        for(auto it = word_errors.begin();it!=word_errors.end();++it) statistics += it.key()+" "+QString::number(it.value())+'\n';
        db->SendAdditionalStatistics("training",training_name, statistics, "word_errors");


        statistics = "";
        auto it2 = words_amount.begin(); //так как words_speed и words_amount полностью равны, то проверяю на выход только один it
        for(auto it = words_speed.begin(); it!=words_speed.end();++it,++it2) statistics += it.key()+" "+QString::number(it.value())+" " + QString::number(it2.value()) + '\n';
        db->SendAdditionalStatistics("training", training_name, statistics, "words_speed");
    }
}

void TRAINING::UpdateStatisticsPerTime(const QString &training_name, const float &current_mistakes,const int &current_speed){
    bool is_update = false;
    for(auto it = statistics_per_time.begin(); it<statistics_per_time.end();++it)
        if(it->year == date->currentDate().year())
            if(it->month == date->currentDate().month())
                if(it->day == date->currentDate().day()){
                    it->mistakes = (it->mistakes*it->amount+current_mistakes)/(it->amount+1);
                    it->speed = (it->speed*it->amount+current_speed)/(it->amount+1);
                    ++it->amount; //если обновили элемент, то его нужно перезаписать в бд после этого
                    db->SendStatisticsPerTime("training", training_name,it->year, it->month, it->day, it->speed, it->amount, it->mistakes);
                    is_update = true;
                    qDebug()<<"Статистика за этот день уже есть, обновляем! ";
                    break;
                }

    if(!is_update){
        db->SendStatisticsPerTime("training", training_name,date->currentDate().year(), date->currentDate().month(), date->currentDate().day(),
                                  current_speed, 1, current_mistakes);
        CHART chart; //если до этого не было таких данных в бд, их нужно создать и добавить в лист и в саму бд
        chart.amount = 1;
        chart.speed = current_speed;
        chart.mistakes = current_mistakes;
        chart.year = date->currentDate().year();
        chart.month = date->currentDate().month();
        chart.day = date->currentDate().day();

        statistics_per_time.append(chart);
        qDebug()<<"Статистика за день была создана! ";
    }

}

void TRAINING::GetStatisticsPerTime(const QString &training_name){
    db->LoadStatisticsPerTime("training", training_name,statistics_per_time,date->currentDate().year(),
                              date->currentDate().month(),date->currentDate().day());

}

TRAINING::TRAINING(){
    db = new DB;
    date = new QDate;
}

TRAINING::~TRAINING(){
    delete db;
    delete date;
}


void TRAINING::WordSpeedReader(QString word, const int &length,const int &time_ms){
    float current_word_speed;
    word.chop(1);//так как сюда попадает ещё и пробел, мы его убираем
    current_word_speed = round(float(length)/float(time_ms)*1000*60);//round *1000/1000 - чтобы не было больше 2 знаков после запятой,*1000 для перевода в сек; *60 для перевода из в минуты

    auto  it = words_speed.find(word);//смотрим писали ли это слово
    if(it != words_speed.end()){ //если есть
        auto it2 = words_amount.find(word); //и сколько раз уже набирали; it.value() - средняя скорость набора слова ; it2.value() - сколько раз набирали уже это слово
        it.value() = round((it.value()*it2.value() + current_word_speed)/(it2.value()+1));//тут записываем новую скорость
        ++it2.value(); //увеличиваем кол-во написанных слов на 1;
        qDebug()<<"Word: "+it.key()+"; speed: "+QString::number(it.value())+"; amount: " + QString::number(it2.value());
    }
    else {//если нет
        words_speed.insert(word, current_word_speed);
        words_amount.insert(word, 1); //если нет, то создаем запись буквы/слога + 1 ошибка
    }
}


