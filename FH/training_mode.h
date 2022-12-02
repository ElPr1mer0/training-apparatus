#ifndef TRAINING_MODE_H
#define TRAINING_MODE_H
#include <QList>
#include <QMap>

class  QString;
class DB;
class QDate;
class CHART;


#define TOTAL_WORDS_PER_LEVEL 5
#define SYMBOLS_LIMIT 10000

class TRAINING{

public:
    float record = 0; //базовая статистика по тексту
    float average_speed = 0;
    float mistakes = 0;
    int play_time_min = 0;
    int play_time_sec = 0;
    int play_time_hours = 0;
    int text_amount = 0;

    QList <QString> training_names;
    QMap<QString, int> letter_errors; //для подсчета кол-ва ошибок при наборе определенной буквы
    QMap <QString, int> syllable_errors; //для подсчета кол-во ошибок в слоге
    QMap <QString, int> word_errors; // для подсчета кол-во ошибочных слов

    QList <QString>word_training_list; // для создания своего режима
    int symbols_counter;
    QString custom_training_name;

    QMap<QString, int> words_amount; // слово, скорость, кол-во
    QMap<QString, float> words_speed;

    QList<CHART> statistics_per_time;


private:
    QDate *date = nullptr;
    DB *db = nullptr;

private:
    void AddErrorInConteiner(QMap<QString, int>&, QString &letter); // используется в MistakeReader
    void GetStatisticsValue(QString &,QString &, int &);
    bool CheckGap(const QString &);

public:
    bool AddTraining();
    QString GetTraining(const QString &);
    void GetTrainingNames();

    void ClearStatisticsContainers();
    void UpdateStatisticsContainers(const QString &);

    bool CheckWordForTrainingList(const QString &);//проверка правильности написания слова перед добавлением в training_list для создания своей тренировки
    bool CheckCustomTrainingName(const QString &);
    bool CheckCustomTrainingFile(const QString &);

    void UpdateStatistics(const QString &);
    void GetStatistics(const QString &);

    void MistakeReader(QString, int);
    void WordSpeedReader(QString, const int &, const int &);
    void GetPrintErrors(const QString &,QMap<QString, int> &,const QString &);
    void GetWordsSpeed(const QString&);
    void UpdateAdditionalStatistics(const QString &);

    void UpdateStatisticsPerTime(const QString&, const float&, const int&);
    void GetStatisticsPerTime(const QString&);

    TRAINING();
    ~TRAINING();
};

#endif // TRAINING_MODE_H
