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
    void LoadTrainingNames(const QString &, QString &);
    void LoadTrainingStatistics(const QString &, const QString &,QString &);
    void LoadTraining(const QString &,const QString &, QString &);
    void LoadAdditionalStatistics(const QString &,const QString &, QString &, const QString &);
    void LoadStatisticsPerTime(const QString &, const QString & , QList<CHART> &, const int &, const int & = 0, const int & = 0);

    void SendTrainingStatistics(const QString &, const QString &, const QString &);
    void SendAdditionalStatistics(const QString &, const QString &, QString &, const QString &);
    void SendAddedTraining(const QString &, const QString &);
    void SendStatisticsPerTime(const QString &, const QString &, const int &, const int &,
                               const int &, const int &, const int &, const float &);

    bool CreateCustomTraining(const QString &,const QString &, const QString &);

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
