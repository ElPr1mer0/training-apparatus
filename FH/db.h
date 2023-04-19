#ifndef DB_H
#define DB_H

#include <QObject>
#include <QSqlDatabase>
#include <QList>

class QtSql;
class QSqlQuery;
class HASH;
class CHART;

class DB: public QObject{
    Q_OBJECT

public:
    bool record_exist; //при отправке запроса, если находим не пустую запись

private:
    QSqlDatabase *db = nullptr; //база данных
    QSqlQuery *query = nullptr; // работа с запросами
    HASH *hash = nullptr; // чтобы сокрыть пользовательские данные

    int user_id = 105; // для поиска пользователя в бд
    QString user_name = "EL PRIMERO";
public:
    DB();
    ~DB(){delete db;}

    /////////////////////////////////////////////////////////////////////////////
    ////////////////REGISTRATION AND LOGIN WINDOW////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////
    bool CheckRegistrationData(QString, QString); // правильность при регистрации
    bool LoginAlreadyExist(QString); // проверка существования логина



    /////////////////////////////////////////////////////////////////////////////
    ////////////////REGISTRATION AND LOGIN WINDOW////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////


    /////////////////////////////////////////////////////////////////////////////
    ////////////////PRINT_WINDOW(training_mode)//////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////
    void LoadModeNames(QList<QString> &mode_names);
    void LoadTrainingNames(const QString &mode_name, QList<QString> &training_names);
    void LoadTrainingStatistics(const QString &mode_name, const QString &training_name,QString &statistics);
    void LoadTraining(const QString &mode_name,const QString &training_name, QString &training);
    void LoadAdditionalStatistics(const QString &mode_name,const QString &training_name, QString &statistics, const QString &statistics_type);
    void LoadStatisticsPerTime(const QString &mode_name, const QString &training_name, QList<CHART> &statistics_per_time,
                               const int &year = 2019, const int &month = 0, const int &day = 0);

    void SendTrainingStatistics(const QString &mode_name, const QString &training_name, const QString &statistics);
    void SendAdditionalStatistics(const QString &mode_name, const QString &training_name, QString &statistics, const QString &statistics_type);
    void SendAddedTraining(const QString &mode_name, const QString &training_name);
    void SendStatisticsPerTime(const QString &mode_name, const QString &training_name, const int &year, const int &month,
                               const int &day, const int &speed, const int &amount, const float &mistakes);

    bool CreateCustomTraining(const QString &mode_name,const QString &training_name, const QString &content);
    bool CreateCustomBook(const QString &mode_name,const QString &training_name, const QList<QString> &content);

    void LoadBookTraining(const QString &mode_name,const QString &training_name, QList<QString> &content);
    /////////////////////////////////////////////////////////////////////////////
    ////////////////PRINT_WINDOW(training_mode)//////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////

private:
    bool Query(QString); // проверка правильности запроса, ставит record_exist в true, если находится запись по поиску при входе или регистрации
    void GetUserId(const QString &);

public slots:
    bool Registration(QString, QString); // возвращают true, если регистрация прошла успешно, и можно переходить в форму home
    bool SignIn(QString,QString);// тоже самое, что сверху, только при входе
};

#endif // DB_H
