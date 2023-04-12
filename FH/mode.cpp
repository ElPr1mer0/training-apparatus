#include "mode.h"
#include "db.h"
#include "chart.h"
#include "qcustomplot.h"

#include <QDebug>
#include <QDate>
#include <math.h>



////////////////////////////////////////////////////////////////////////
////////////////////////////MODE::MODE//////////////////////////////////
////////////////////////////////////////////////////////////////////////
MODE::MODE(){
    db = new DB;
    date = new QDate;// время для графиков
}
////////////////////////////////////////////////////////////////////////
////////////////////////////MODE::MODE//////////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
////////////////////////////MODE::~MODE/////////////////////////////////
////////////////////////////////////////////////////////////////////////
MODE::~MODE(){
    delete db;
    delete date;
}
////////////////////////////////////////////////////////////////////////
////////////////////////////MODE::~MODE/////////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
///////////////////////MODE::GetModeNames///////////////////////////////
////////////////////////////////////////////////////////////////////////
/// Получает доступных режимов из бд
void MODE::GetModeNames(){
    if(!mode_names.empty())mode_names.clear();
    db->LoadModeNames(mode_names); //отправляем строку для получения имен режимов
}
////////////////////////////////////////////////////////////////////////
///////////////////////MODE::GetModeNames///////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////////MODE::GetTrainingNames////////////////////////////
////////////////////////////////////////////////////////////////////////
/// получает имена тренировок режима
void MODE::GetTrainingNames(const QString &mode_name){
    if(!training_names.empty())training_names.clear();
    db->LoadTrainingNames(mode_name,training_names); //отправляем строку для получения имен режима
}
////////////////////////////////////////////////////////////////////////
//////////////////////MODE::GetTrainingNames////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
///////////////////MODE::ClearStatisticsContainers//////////////////////
////////////////////////////////////////////////////////////////////////
/// обнуляет статистику по все контейнерам (ошибки в буквах, слогах,
/// буквах и скорости набора слов, и их кол-во + статистика за время)
void MODE::ClearStatisticsContainers(){
    letter_errors.clear();//обнуляем, чтобы можно было записывать новую статистику
    syllable_errors.clear();
    word_errors.clear();
    words_speed.clear();
    words_amount.clear();
    statistics_per_time.clear();
}
////////////////////////////////////////////////////////////////////////
///////////////////MODE::ClearStatisticsContainers//////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
///////////////////MODE::UpdateStatisticsContainers/////////////////////
////////////////////////////////////////////////////////////////////////
/// обновляет данные в контейнерах
void MODE::UpdateStatisticsContainers(const QString &mode_name, const QString &training_name){
    GetPrintErrors(mode_name,training_name,letter_errors, "letter_errors");
    GetPrintErrors(mode_name,training_name,syllable_errors, "syllable_errors");
    GetPrintErrors(mode_name,training_name,word_errors, "word_errors");
    GetWordsSpeed(mode_name,training_name);
    GetStatisticsPerTime(mode_name,training_name);
}
////////////////////////////////////////////////////////////////////////
///////////////////MODE::UpdateStatisticsContainers/////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
////////////////////////MODE::GetPrintErrors////////////////////////////
////////////////////////////////////////////////////////////////////////
/// получает ошибки набора по полученному режиму и тренировке из бд
void MODE::GetPrintErrors(const QString &mode_name, const QString &training_name, QMap<QString, int> &map, const QString &errors_type){
    QString statistics;

    db->LoadAdditionalStatistics(mode_name,training_name, statistics, errors_type); //получаем данные из бд

    QString key;
    QString value = "";

    if(!statistics.isEmpty()){
        for(int i=0; i<statistics.length();){
            key = statistics[i]; //сразу делаем так, если первый символ это пробел
            i++;
            GetStatisticsValue(key,statistics,i);
            GetStatisticsValue(value,statistics,i);
            map.insert(key,value.toInt());
            key = "";
            value = "";
        }
        qDebug()<<"Статистика ошибок по тексту загружена из базы данных!";
    }
    else qDebug()<<"Статистика ошибок по тексту не заполнена!";
}
////////////////////////////////////////////////////////////////////////
////////////////////////MODE::GetPrintErrors////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
////////////////////////MODE::GetWordsSpeed/////////////////////////////
////////////////////////////////////////////////////////////////////////
/// получает данные по скорости набора слова из бд
void MODE::GetWordsSpeed(const QString &mode_name,const QString &training_name){
    QString statistics;
    db->LoadAdditionalStatistics(mode_name,training_name,statistics,"words_speed");

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
////////////////////////////////////////////////////////////////////////
////////////////////////MODE::GetWordsSpeed/////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
////////////////////MODE::GetStatisticsPerTime//////////////////////////
////////////////////////////////////////////////////////////////////////
/// получает данные статистики за время (для графиков)
void MODE::GetStatisticsPerTime(const QString &mode_name, const QString &training_name){
    db->LoadStatisticsPerTime(mode_name, training_name,statistics_per_time);//date->currentDate().year() НУЖНО ИСПРАВИТЬ, ЧТОБЫ ВЫБИРАЛАСЬ ДАТА
}
////////////////////////////////////////////////////////////////////////
////////////////////MODE::GetStatisticsPerTime//////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////////////MODE::GetStatisticsValue///////////////////////////
////////////////////////////////////////////////////////////////////////
/// считывает данные разделенные пробелами
void MODE::GetStatisticsValue(QString &value, QString &statistics, int &i){
    while(statistics[i]!=' ' && statistics[i]!='\n'){
        value+=statistics[i];
        i++;
    }
    ++i; //после того, как нашли пробел, скипаем его
}
////////////////////////////////////////////////////////////////////////
/////////////////////MODE::GetStatisticsValue///////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////////////MODE::UpdateStatistics/////////////////////////////
////////////////////////////////////////////////////////////////////////
/// обновляет данные по краткой статистике набора и отправляет в бд
void MODE::UpdateStatistics(const QString &mode_name, const QString &training_name){
    QString statistics;
    statistics = QString::number(text_amount) +" "+ QString::number(record) +" "+QString::number(average_speed) +" "+QString::number(mistakes) +" "+QString::number(play_time_hours) +" "+
    QString::number(play_time_min) +" "+ QString::number(play_time_sec)+" "; // записываем в строку всю статистику

    db->SendTrainingStatistics(mode_name, training_name, statistics); //добавляем ее в бд
}
////////////////////////////////////////////////////////////////////////
/////////////////////MODE::UpdateStatistics/////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////////////////MODE::GetStatistics////////////////////////////
////////////////////////////////////////////////////////////////////////
/// получает краткую статистику по набору из бд если она существует,
/// если произошла ошибка при загрузке статистики или если ее не сущест-
/// вует, то перемененные обнуляется, так как они отображаются на форме
void MODE::GetStatistics(const QString &mode_name, const QString &training_name){

    QString statistics;
    db->LoadTrainingStatistics(mode_name,training_name, statistics); //отправляем строку для получения статистики по режиму

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
        qDebug()<<"Статистика не загружана!"; // при ошибке загрузки статистики или если ее еще не существует, то обнуляем все поля
        this->record = 0;
        this->average_speed = 0;
        this->mistakes = 0;
        this->play_time_hours = 0;
        this->play_time_min = 0;
        this->text_amount = 0;
        this->play_time_sec = 0;
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
////////////////////////////////////////////////////////////////////////
/////////////////////////MODE::GetStatistics////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
///////////////////////MODE::MistakeReader//////////////////////////////
////////////////////////////////////////////////////////////////////////
/// считывает ошибки при наборе слова и сохраняет эти данные (по словам,
/// буквам и слогам)
void MODE::MistakeReader(const QString &current_word,const int &current_pos){
    QString letter = QString(current_word[current_pos]);
    AddErrorInConteiner(letter_errors, letter);

    QString syllable;

    if(current_pos < current_word.length()-2){ // проверка, что можно брать 2 буквы после нашей ошибки
        syllable = current_word.mid(current_pos, 3); //копируем слог
        if(!CheckGap(syllable) || syllable.length()<3) AddErrorInConteiner(syllable_errors,syllable); //если есть пробел, то записывать не будем
    }                                                                                           //+ слог из 3 букв

    if(current_pos < current_word.length()-1 && current_pos > 0){// проверка на то, что после нашей ошибки и до можно брать буквы (когда она в середине слога)
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
////////////////////////////////////////////////////////////////////////
///////////////////////MODE::MistakeReader//////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////////MODE::WordSpeedReader/////////////////////////////
////////////////////////////////////////////////////////////////////////
/// считывает скорость и кол-во написаний слова
void MODE::WordSpeedReader(QString word, const int &length, const int &time_ms){
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
////////////////////////////////////////////////////////////////////////
//////////////////////MODE::WordSpeedReader/////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
////////////////MODE::UpdateAdditionalStatistics////////////////////////
////////////////////////////////////////////////////////////////////////
/// отправляет статистику по ошибкам и скорости набора в бд
void MODE::UpdateAdditionalStatistics(const QString &mode_name, const QString &training_name){
    if (letter_errors.empty()){
        qDebug()<<"Ошибок не было, не обновляем!";
        return;
    }
    else{
        QString statistics = "";
        for(auto it = letter_errors.begin();it!=letter_errors.end();++it) statistics += it.key()+" "+QString::number(it.value())+'\n';    //записываем статистику в строку для отправки в бд

        db->SendAdditionalStatistics(mode_name,training_name, statistics, "letter_errors");

        statistics = "";
        for(auto it = syllable_errors.begin();it!=syllable_errors.end();++it) statistics += it.key()+" "+QString::number(it.value())+'\n';
        db->SendAdditionalStatistics(mode_name,training_name, statistics, "syllable_errors");

        statistics = "";
        for(auto it = word_errors.begin();it!=word_errors.end();++it) statistics += it.key()+" "+QString::number(it.value())+'\n';
        db->SendAdditionalStatistics(mode_name,training_name, statistics, "word_errors");

        statistics = "";
        auto it2 = words_amount.begin(); //так как words_speed и words_amount полностью равны, то проверяю на выход только один it
        for(auto it = words_speed.begin(); it!=words_speed.end();++it,++it2) statistics += it.key()+" "+QString::number(it.value())+" " + QString::number(it2.value()) + '\n';
        db->SendAdditionalStatistics(mode_name, training_name, statistics, "words_speed");
        }
        }
////////////////////////////////////////////////////////////////////////
////////////////MODE::UpdateAdditionalStatistics////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////MODE::UpdateStatisticsPerTime/////////////////////////
////////////////////////////////////////////////////////////////////////
/// отправляет статистику набора за промежуток в бд
void MODE::UpdateStatisticsPerTime(const QString &mode_name, const QString &training_name, const float &current_mistakes, const int &current_speed){
    bool is_update = false;
    for(auto it = statistics_per_time.begin(); it<statistics_per_time.end();++it)
        if(it->year == date->currentDate().year())
            if(it->month == date->currentDate().month())
                if(it->day == date->currentDate().day()){
                    it->mistakes = round(100*(it->mistakes*it->amount+current_mistakes)/(it->amount+1))/100;
                    it->speed = (it->speed*it->amount+current_speed)/(it->amount+1);
                    it->amount += 1; //если обновили элемент, то его нужно перезаписать в бд после этого
                    db->SendStatisticsPerTime(mode_name, training_name,it->year, it->month, it->day, it->speed, it->amount, it->mistakes);
                    is_update = true;
                    qDebug()<<"Статистика за этот день уже есть, обновляем! ";
                    break;
                }

    if(!is_update){
        db->SendStatisticsPerTime(mode_name, training_name,date->currentDate().year(), date->currentDate().month(), date->currentDate().day(),
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
////////////////////////////////////////////////////////////////////////
//////////////////MODE::UpdateStatisticsPerTime/////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////MODE::DetermineDayCoffForPlot/////////////////////////
////////////////////////////////////////////////////////////////////////
/// рассчитывает нужный коэффициент для корректного отображения данных
/// на графике в правильные дни
void MODE::DetermineDayCoffForPlot(double &now, QVector<QCPGraphData> &graph_data, const QString &type){
    int year = date->currentDate().year();
    int month = date->currentDate().month();
    int day = date->currentDate().day();
    int day_coff; // для отображения дня на графике

    for(int i = 0;i<statistics_per_time.length();++i){
        day_coff = 0;

        if((year - statistics_per_time[i].year) == 0){//одинаковый год

            if (day - statistics_per_time[i].day >= 0){
                    day_coff = (month - statistics_per_time[i].month) * 31 + (day - statistics_per_time[i].day);//получаем кол-во месяцев разницы и переводим это в дни
            }else{ //если текущее число меньше числа из листа
                day_coff = (month - statistics_per_time[i].month - 1) * 31 + (day + 31 - statistics_per_time[i].day);
            }

        }else{ //если разные года

            if((day - statistics_per_time[i].day) >= 0){ //текущий день больше числа из списка
                if((month - statistics_per_time[i].month) >= 0){ // текущий месяц больше месяца из списка
                    day_coff = (year - statistics_per_time[i].year) * 365 + (month - statistics_per_time[i].month) * 31 + (day - statistics_per_time[i].day);
                }else{ //месяц меньше
                    day_coff = (year - statistics_per_time[i].year - 1) * 365 + (month + 12 - statistics_per_time[i].month) * 31 + (day - statistics_per_time[i].day);
                }
            }else{//день меньше
                if((month - statistics_per_time[i].month) >= 0){ // текущий месяц больше месяца из списка
                    day_coff = (year - statistics_per_time[i].year) * 365 + (month - statistics_per_time[i].month - 1) * 31 + (day + 31 - statistics_per_time[i].day);
                }else{ //месяц меньше
                    day_coff = (year - statistics_per_time[i].year - 1) * 365 + (month + 12 - statistics_per_time[i].month - 1) * 31 + (day + 31 - statistics_per_time[i].day);
                }
            }
        }

        graph_data[i].key = now - 24*3600*day_coff;
        if(type == "Скорость") graph_data[i].value = statistics_per_time[i].speed;
        else if (type == "Кол-во текстов") graph_data[i].value = statistics_per_time[i].amount;
        else graph_data[i].value = statistics_per_time[i].mistakes;
    }
}
////////////////////////////////////////////////////////////////////////
//////////////////MODE::DetermineDayCoffForPlot/////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
///////////////////MODE::AddErrorInConteiner////////////////////////////
////////////////////////////////////////////////////////////////////////
/// смотрит была ли уже такая ошибка при наборе, если да, то увеличивает
/// счетчик на 1, иначе записывает новую ошибку
void MODE::AddErrorInConteiner(QMap<QString, int> &errors_map,const QString &mistake){
    auto  it = errors_map.find(mistake);//смотрим есть ли уже ошибка с этой буквой/слогом в списке
    if(it !=errors_map.end()) ++it.value(); //если есть, то мы увеличиваем кол-во данных ошибок на 1
    else {
        errors_map.insert(mistake, 1); //если нет, то создаем запись буквы/слога + 1 ошибка
        qDebug()<<"Добавилась новая ошибка! " + mistake;
    }
}
////////////////////////////////////////////////////////////////////////
///////////////////MODE::AddErrorInConteiner////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
///////////////////////////MODE::CheckGap///////////////////////////////
////////////////////////////////////////////////////////////////////////
/// ищет пробел в линии из трех букв (если он есть, то нам эта линия не
/// подходит)
bool MODE::CheckGap(const QString &line){
    for(int i = 0; i<line.length();++i)
        if(line[i] == ' ') return true;
    return false;
}
////////////////////////////////////////////////////////////////////////
///////////////////////////MODE::CheckGap///////////////////////////////
////////////////////////////////////////////////////////////////////////
