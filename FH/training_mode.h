#ifndef TRAINING_MODE_H
#define TRAINING_MODE_H
#include "mode.h"



#define SYMBOLS_LIMIT 10000
#define TRAINING "training"

class TRAINING_MODE: public MODE{

public:
    QList <QString>word_training_list; // для создания своей тренировки в training_mode
    int symbols_counter; //подсчет символов при создании тренировки
    QString custom_training_name; //имя новой, созданной пользователем тренировки

private:
    DB *db = nullptr;
public:
    TRAINING_MODE(DB *db);
    bool AddTraining(); //оставить, добавляет данные, по новой, только что созданной тренировке
    QString GetTraining(const QString &mode_name, const QString &training_name); // оставить

    bool CheckWordForTrainingList(const QString &word);//проверка правильности написания слова перед добавлением в training_list для создания своей тренировки
    bool CheckCustomTrainingName(const QString &training_name); //оставить эти три функции тут
};

#endif // TRAINING_MODE_H
