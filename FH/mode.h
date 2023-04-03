#ifndef MODE_H
#define MODE_H
#include "qcustomplot.h"
#include <QList>
#include <QMap>

class QString;
class DB;
class CHART;

class QDate;

#define TOTAL_WORDS_PER_LEVEL 60

class MODE{
    //Q_OBJECT
public:
    DB *db = nullptr; //база данных
    QDate *date = nullptr;// время для графиков

    QList<QString> mode_names;
    QList <QString> training_names;//названия тренировок в режиме
    QList<CHART> statistics_per_time;

    QMap<QString, int> letter_errors; //для подсчета кол-ва ошибок при наборе определенной буквы
    QMap<QString, int> syllable_errors; //для подсчета кол-во ошибок в слоге
    QMap<QString, int> word_errors; // для подсчета кол-во ошибочных слов
    QMap<QString, int> words_amount; // слово, скорость, кол-во
    QMap<QString, float> words_speed;

    float record = 0; //базовая статистика по тренировке режима
    float average_speed = 0;
    float mistakes = 0;
    int play_time_min = 0;
    int play_time_sec = 0;
    int play_time_hours = 0;
    int text_amount = 0;

    int from_year = 2019; // для выборки данных за время для графика
    int from_month = 1;
    int to_year = 2020;
    int to_month = 2;

public:
    MODE();
    ~MODE();
    void GetModeNames();
    void GetTrainingNames(const QString &mode_name);

    void ClearStatisticsContainers();
    void UpdateStatisticsContainers(const QString &mode_name, const QString &training_name);

    void GetPrintErrors(const QString &mode_name, const QString &training_name, QMap<QString, int> &map, const QString &errors_mode);
    void GetWordsSpeed(const QString &mode_name, const QString &training_name);
    void GetStatisticsPerTime(const QString &mode_name, const QString&training_name);
    void GetStatisticsValue(QString &value, QString &statistics, int &i);

    void UpdateStatistics(const QString &mode_name, const QString &training_name);
    void GetStatistics(const QString &mode_name, const QString &training_name);

    void MistakeReader(const QString &current_word, const int &current_pos);
    void WordSpeedReader(QString word, const int &length, const int &time_ms);

    void UpdateAdditionalStatistics(const QString &mode_name,const QString &training_name);
    void UpdateStatisticsPerTime(const QString &mode_name, const QString &training_name, const float &current_mistakes, const int &current_speed);

    void DetermineDayCoffForPlot(double &now, QVector<QCPGraphData>&graph_data, const QString &type);
    void AddErrorInConteiner(QMap<QString, int>&errors_map, const QString &letter); // используется в MistakeReader
    bool CheckGap(const QString &line); // поиск пробелов при обработке ошибок в слогах

    template <typename T>
    QString GetErrorsTraining(const QMap<QString, T> &map); //создание тренировки по частым ошибкам
    template <typename T>
    void SortBufPrintStatistics(const QMap<QString, T>&map, std::vector<QString>&keys, std::vector<float> &values); // сортировка по кол-ву ошибок


};

////////////////////////////////////////////////////////////////////////
/////////////////////MODE::GetErrorsTraining////////////////////////////
////////////////////////////////////////////////////////////////////////
/// создает тренировку по наиболее часто встречаемым ошибкам
template<typename T>
QString MODE::GetErrorsTraining(const QMap<QString, T> &map){
    QString  level = "";
    int total_words_in_map = map.size(); //узнаем сколько есть слов в контейнере

    if (total_words_in_map == 0){
        return "Список пуст!";
    }

    int all_mistakes = 0;
    for(auto it = map.begin(); it!=map.end(); ++it) all_mistakes += it.value(); //считаем сколько всего ошибок по каждому слову (или ср. скорость)

    int count_total_words = 0;
    int average_mistakes;
    for(int i = 2;; ++i){
        average_mistakes = all_mistakes / i; // обнуляем значение перед счетом
        for(auto it = map.begin(); it!=map.end(); ++it)
            if(it.value() >= average_mistakes) ++count_total_words;

        if(map.size() < TOTAL_WORDS_PER_LEVEL/2){   // берем случай, когда слов меньше в два раза чем нужно для составления в игре
            if((count_total_words <= map.size()) && (count_total_words >= map.size() - map.size()*0.80)){
                break;
            }
        }else if(((count_total_words <= TOTAL_WORDS_PER_LEVEL *0.80) && (count_total_words >= TOTAL_WORDS_PER_LEVEL *0.80)) || count_total_words == map.size()) break;
        count_total_words = 0;
    }

    bool is_find;
    for(int i = 0; i<TOTAL_WORDS_PER_LEVEL;){ // собираем уровень из слов; TOTAL_WORDS_PER_LEVEL - максимальное кол-во слов на уровень
        int rand_word = -1;
        int j = 0;
        is_find = false;
        while(rand_word>total_words_in_map || rand_word<0)  rand_word = rand() % total_words_in_map + 1; // генератор рандома для слов

        for(auto it = map.begin(); j <= rand_word;++it, ++j){
            if(j == rand_word && it.value()>= average_mistakes ){
                level +=it.key() + " ";
                is_find  = true;
            }
        }
        if(is_find)++i; //если слово добавили, то увеличиваем для выхода из цикла
    }
    return level;
};
////////////////////////////////////////////////////////////////////////
/////////////////////MODE::GetErrorsTraining////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////////////MODE::SortBufPrintStatistics///////////////////////
////////////////////////////////////////////////////////////////////////
/// сортирует контейнеры со статистикой по возрастанию
template<typename T>
void MODE::SortBufPrintStatistics(const QMap<QString, T> &map, std::vector<QString> &keys, std::vector<float> &values){
    for(auto it = map.begin(); it!=map.end(); ++it){ //без сортировки
        keys.push_back(it.key()); // записываю переменные в буферные вектора
        values.push_back(it.value());
     }

    for(unsigned long i = 0; i<values.size(); ++i) //сортировка буф векторов
        for(unsigned long i = 0; i<values.size()-1; ++i){
            if(values[i]<values[i+1]){
                std::swap(values[i],values[i+1]); // сортирую по кол-ву ошибок
                std::swap(keys[i],keys[i+1]);
            }
        }
}
////////////////////////////////////////////////////////////////////////
/////////////////////MODE::SortBufPrintStatistics///////////////////////
////////////////////////////////////////////////////////////////////////


#endif // MODE_H
