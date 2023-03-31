#ifndef TRAINING_MODE_H
#define TRAINING_MODE_H
#include <QList>
#include <QMap>

class  QString;
class DB;
class QDate;
class CHART;
class QCPGraphData;


#define TOTAL_WORDS_PER_LEVEL 60
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

    int from_year = 2019; // для выборки данных за время для графика
    int from_month = 1;
    int to_year = 2020;
    int to_month = 2;

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
    template <typename T>
    QString GetErrorsTraining(const QMap<QString, T> &);
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
    template <typename T>
    void SortBufPrintStatistics(const QMap<QString, T>&, std::vector<QString>&, std::vector<float> &);

    void UpdateStatisticsPerTime(const QString&, const float&, const int&);
    void GetStatisticsPerTime(const QString&);

    void DetermineDayCoffForPlot(double &, QVector<QCPGraphData>&, const QString &);

    TRAINING();
    ~TRAINING();
};

template<typename T>
QString TRAINING::GetErrorsTraining(const QMap<QString, T> &map){
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

template<typename T>
void TRAINING::SortBufPrintStatistics(const QMap<QString, T> &map, std::vector<QString> &keys, std::vector<float> &values){
    for(auto it = map.begin(); it!=map.end(); ++it){ //без сортировки
        keys.push_back(it.key()); // записываю переменные в буферные вектора
        values.push_back(it.value());
     }

    for(unsigned long i = 0; i<values.size(); ++i) //сортировка буф векторов
        for(unsigned long i = 0; i<values.size()-1; ++i){
            if(values[i]<values[i+1]){
                std::swap(values[i],values[i+1]); // сортирую по кол-во ошибок
                std::swap(keys[i],keys[i+1]);
            }
        }
}

#endif // TRAINING_MODE_H
