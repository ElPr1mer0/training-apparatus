#include "training_mode.h"
#include "db.h"

////////////////////////////////////////////////////////////////////////
/////////////////////////TRAINING::TRAINING/////////////////////////////
////////////////////////////////////////////////////////////////////////
TRAINING_MODE::TRAINING_MODE(DB *db):db(db){}
////////////////////////////////////////////////////////////////////////
/////////////////////////TRAINING::TRAINING/////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
////////////////////////TRAINING::AddTraining///////////////////////////
////////////////////////////////////////////////////////////////////////
/// отправляет в бд созданную пользователем тренировку и данные по ней
bool TRAINING_MODE::AddTraining(){
    QString content = "";
    for(auto it = word_training_list.begin();it!=word_training_list.end();++it) content += *it+'\n';

    if(db->CreateCustomTraining("training", custom_training_name, content)){ //добавляем новый режим в таблицу mode
        db->SendTrainingStatistics("training", custom_training_name,"0 0 0 0 0 0 0 ");//создаем статистику по режиму в таблицу statistics
        content = "";
        training_names.append(custom_training_name);//добавляем наше имя тренировки в список

        QString new_training_name = "";
        for(auto it : training_names) new_training_name += it +"\n"; //создаем строку наших имен для отправки в бд

        db->SendAddedTraining("training",new_training_name);//добавляем название новой тренировки в бд
        return true;
    }
    return false;   //если что-то пошло не так при обращении к бд, то возвращаем false
}
////////////////////////////////////////////////////////////////////////
////////////////////////TRAINING::AddTraining///////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////////TRAINING::GetTraining/////////////////////////////
////////////////////////////////////////////////////////////////////////
/// создает тренировку по режиму
QString TRAINING_MODE::GetTraining(const QString &mode_name, const QString &training_name){
    QString training;
    db->LoadTraining(mode_name,training_name, training);

    QString line = "", level = "";
    int total_words_in_file = 0;

    for(int i = 0; i<training.length();++i) if(training[i] == '\n')++total_words_in_file; // подсчитали кол-во слов в уровне

    if (total_words_in_file == 0){
        qDebug()<<"Нет слов в данной тренировке!";
        return "Нет слов в данной тренировке!";
    }

    for(int i = 0; i<TOTAL_WORDS_PER_LEVEL;++i){ // собираем уровень из слов; TOTAL_WORDS_PER_LEVEL - максимальное кол-во слов на уровень
        int rand_word = -1;

            while(rand_word>total_words_in_file || rand_word<0)  rand_word = rand() % total_words_in_file + 1; // генератор рандома для слов

            line = "";
            int j = 0;
            int k;

            while(j<rand_word){

                for(k = 0; j<rand_word-1;++k) if(training[k] == '\n') ++j;

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
//////////////////////TRAINING::GetTraining/////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////TRAINING::CheckWordForTrainingList////////////////////
////////////////////////////////////////////////////////////////////////
/// проверяет корректность слова при создании тренировки пользователем
bool TRAINING_MODE::CheckWordForTrainingList(const QString &word){
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
////////////////////////////////////////////////////////////////////////
//////////////////TRAINING::CheckWordForTrainingList////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
///////////////////TRAINING::CheckCustomTrainingName////////////////////
////////////////////////////////////////////////////////////////////////
/// проверяет правильность введенного названии тренировки, когда ее
/// создает пользователь
bool TRAINING_MODE::CheckCustomTrainingName(const QString &training_name){
    if(training_name == ""){
        qDebug()<<"Введите имя тренировки!";
        return false;
    }

    for(int i = 0; i<training_name.length();++i){
        if((training_name[i] > 31 && training_name[i] < 58)  || (training_name[i] > 64 && training_name[i] < 91)
           ||(training_name[i] > 96 && training_name[i] < 123) || (training_name[i] > 1039 && training_name[i] < 1106) //добавить еще другие символы
           || (training_name[i] == 1025)){
            // если латицина, кириллица или цифры, то ок, иначе выходим
        }else{
            qDebug()<<"Имя может состоять только из латиницы, кириллицы и цифр!";
            return false;
        }
    }
    custom_training_name = training_name;
    return true;
}
////////////////////////////////////////////////////////////////////////
///////////////////TRAINING::CheckCustomTrainingName////////////////////
////////////////////////////////////////////////////////////////////////
