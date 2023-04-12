#include "db.h"
#include "hash.h"
#include "chart.h"

#include <QtSql>
#include <QSqlError>
#include <QSqlQuery>



////////////////////////////////////////////////////////////////////////
////////////////////////////DB::DB//////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/// создает подключение к базе данным на локальном хосте
DB::DB(){
    db = new QSqlDatabase;
    *db = QSqlDatabase::addDatabase("QMYSQL"); // подключаемся к бд
    db->setHostName("127.0.0.1");
    db->setDatabaseName("testbd");
    db->setUserName("root");
    db->setPassword("1111");

    if(db->open()){ //проверяем на октрытие
        qDebug()<<"open";
    }
    else{
        qDebug()<<db->lastError().text();
    }
}
////////////////////////////////////////////////////////////////////////
////////////////////////////DB::DB//////////////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////////DB::CheckRegistrationData/////////////////////////
////////////////////////////////////////////////////////////////////////
/// проверяет подходит ли введенным пользователем пароль и логин для
/// регистрации
bool DB::CheckRegistrationData(QString login, QString password){
    if(login.length() > 20 || login.length() < 6){ // проверяем корректность логина для регистрации
        qDebug()<<"Длина логина должна быть от 6 до 20 символов!";
        return false;
    }

    if(login[0] > 47 && login[0] < 58){
        qDebug()<<"Логин не может начинаться с цифр!";
        return false;
    }

    for(int i = 0; i<login.length();++i){

        if((login[i] < 48 || login[i] > 255) || (login[i] > 57 && login[i] < 65)
          || (login[i] > 90 && login[i] < 97) || (login[i] > 122 && login[i] < 192)){
            qDebug()<<"Нельзя использовать спец-символы!";
            return false;
        }
    }


    if(password.length() > 20 || password.length() < 6){ // проверяем корректность пароля для регистрации
        qDebug()<<"Длина пароля должна быть от 6 до 20 символов!";
        return false;
    }

    for(int i = 0; i<password.length();++i){
        if((password[i] < 48 || password[i] > 255) || (password[i] > 57 && password[i] < 65)
          || (password[i] > 90 && password[i] < 97) || (password[i] > 122 && password[i] < 192)){
            qDebug()<<"Нельзя использовать спец-символы!";
            return false;
        }
    }

    return true;
}
////////////////////////////////////////////////////////////////////////
//////////////////////DB::CheckRegistrationData/////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////////DB::LoginAlreadyExist/////////////////////////////
////////////////////////////////////////////////////////////////////////
/// проверяет существует ли данный логин
bool DB::LoginAlreadyExist(QString login){
    hash = new HASH;
    login = hash->GetHash(login);
    delete hash;

    Query("SELECT login FROM users WHERE login = '" +login+"'");
    if(!record_exist) return false; // проверяем, что пользователя с таким именем еще не было зарегистрировано
    qDebug()<<"Логин занят!";
    return true;
}
////////////////////////////////////////////////////////////////////////
//////////////////////DB::LoginAlreadyExist/////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
////////////////////////DB::LoadModeNames///////////////////////////////
////////////////////////////////////////////////////////////////////////
/// выдает существующие режимы
void DB::LoadModeNames(QList<QString> &mode_names){
    query = new QSqlQuery(*db);
    if(query->exec("SELECT DISTINCT mode_name FROM mode ")){
        while(query->next()){
            mode_names.append(query->value(0).toString());
        }
        qDebug()<<"Названия режимов загружены из базы данных!";
    }else qDebug()<<"Ошибка загрузки названий тренировок из базы данных!";
    delete query;
}
////////////////////////////////////////////////////////////////////////
////////////////////////DB::LoadModeNames///////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////////////DB::GetUserId/////////////////////////////////
////////////////////////////////////////////////////////////////////////
/// получает id пользователя из бд по логину
void DB::GetUserId(const QString &login){
    query = new QSqlQuery(*db);
    if(query->exec("SELECT id FROM users WHERE login = '" +login+"'")){
        while(query->next()) {
            user_id = query->value(0).toInt();
        }
        qDebug()<<"id найден! " + QString::number(user_id);
    }else qDebug()<<"id не найден!";

    delete query;
}
////////////////////////////////////////////////////////////////////////
//////////////////////////DB::GetUserId/////////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
///////////////////////DB::LoadTrainingNames////////////////////////////
////////////////////////////////////////////////////////////////////////
/// выдает имена тренировок по режиму
void DB::LoadTrainingNames(const QString &mode_name, QList<QString> &training_names){
    query = new QSqlQuery(*db);
    if(query->exec("SELECT training_names FROM added_mods "
                   "WHERE id = " + QString::number(user_id)+" AND "
                   "mode_name = '"+mode_name+"'")){

        while(query->next()){
            training_names.append(query->value(0).toString());
        }
        qDebug()<<"Названия тренировок загружены из базы данных!";
    }else qDebug()<<"Ошибка загрузки названий тренировок из базы данных!";
    delete query;
}
////////////////////////////////////////////////////////////////////////
///////////////////////DB::LoadTrainingNames////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////////////DB::LoadTrainingStatistics/////////////////////////
////////////////////////////////////////////////////////////////////////
/// выдает краткую статистику по тренировке режима
void DB::LoadTrainingStatistics(const QString &mode_name, const QString &training_name,QString &statistics){
    query = new QSqlQuery(*db);
    if(query->exec("SELECT data FROM statistics WHERE id = "+QString::number(user_id)+
                   " AND mode_name = '"+ mode_name+"' AND training_name = '"+training_name+"'")){
        while(query->next()) {
            statistics = query->value(0).toString();
        }
        qDebug()<<statistics;
        qDebug()<<"Статистика загружена из базы данных!";
    }else qDebug()<<"Ошибка загрузки статистики из базы данных!";
    delete query;
}
////////////////////////////////////////////////////////////////////////
/////////////////////DB::LoadTrainingStatistics/////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////////////DB::LoadTraining//////////////////////////////
////////////////////////////////////////////////////////////////////////
/// выдает текст тренировки режима, для составления по нему тренировки
void DB::LoadTraining(const QString &mode_name,const QString &training_name, QString &training){
    query = new QSqlQuery(*db);

    if(query->exec("SELECT content FROM mode "
                   "WHERE training_name = '"+training_name+"' "
                   "AND mode_name = '"+mode_name+"'")){
        while(query->next()) {
            training = query->value(0).toString();
        }

        qDebug()<<"Тренировка загружена из базы данных!";
    }
    else qDebug()<<"Ошибка загрузки тренировки из базы данных!";
    delete query;
}
////////////////////////////////////////////////////////////////////////
//////////////////////////DB::LoadTraining//////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
////////////////////DB::LoadAdditionalStatistics////////////////////////
////////////////////////////////////////////////////////////////////////
/// выдает статистику по ошибкам по тренировке режима
void DB::LoadAdditionalStatistics(const QString &mode_name,const QString &training_name, QString &statistics, const QString &statistics_type){

    if(Query("SELECT "+ statistics_type+ " FROM statistics WHERE id = "+ QString::number(user_id)+
             " AND training_name = '"+training_name+ "' AND mode_name = '"+mode_name+"'")){     
            query = new QSqlQuery(*db);
            query->exec("SELECT "+ statistics_type+ " FROM statistics WHERE id = "+ QString::number(user_id)+
                        " AND training_name = '"+training_name+ "' AND mode_name = '"+mode_name+"'");
            while(query->next()){
                statistics = query->value(0).toString();
            }
            qDebug()<<"Статитиска "+ statistics_type+ " загружена из базы данных!";
            delete query;

        return;
    }else{
        if(!record_exist) qDebug()<<"Статистика "+ statistics_type+ " еще не была создана!";//если запись такая уже есть

    }
}
////////////////////////////////////////////////////////////////////////
////////////////////DB::LoadAdditionalStatistics////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////////DB::LoadStatisticsPerTime/////////////////////////
////////////////////////////////////////////////////////////////////////
/// выдает статистику за период (для графиков)
void DB::LoadStatisticsPerTime(const QString &mode_name, const QString &training_name, QList<CHART> &statistics_per_time,
                          const int &year, const int &month, const int &day){

    if(Query("SELECT * FROM statistics_per_time "
            "WHERE id = "+ QString::number(user_id)+" AND training_name = '"+ training_name +"' AND "
            "mode_name = '"+mode_name+"' AND year >= "+ QString::number(year))){

        if(!record_exist) qDebug()<<"За этот период ничего нет!";
        else{
            query = new QSqlQuery(*db);
            query->exec("SELECT * FROM statistics_per_time "
                        "WHERE id = "+ QString::number(user_id)+" AND training_name = '"+ training_name +"' AND "
                        "mode_name = '"+mode_name+"' AND year >= "+ QString::number(year));
            while(query->next()){
                CHART chart;
                chart.speed = query->value("speed").toInt();
                chart.amount = query->value("amount").toInt();
                chart.mistakes = query->value("mistakes").toFloat();
                chart.year = query->value("year").toInt();
                chart.month = query->value("month").toInt();
                chart.day = query->value("day").toInt();
                statistics_per_time.append(chart);
            }
            qDebug()<<" Статистика за время загружена из базы данных!";
            delete query;
        }
    }
    else qDebug()<<"Статистика еще не создана за сегодня!";
}
////////////////////////////////////////////////////////////////////////
//////////////////////DB::LoadStatisticsPerTime/////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////////////DB::SendTrainingStatistics/////////////////////////
////////////////////////////////////////////////////////////////////////
/// проверяет есть ли в базе краткая статистика по тренировке режима и
/// если есть, то обновляет ее, иначе создает новую
void DB::SendTrainingStatistics(const QString &mode_name, const QString &training_name, const QString &statistics){

    if(Query("UPDATE statistics set data = '" + statistics+"'" //проверяем была ли уже запись, чтобы ее можно было обновить
                   " WHERE id = " +QString::number(user_id)+
                   " AND mode_name = '"+mode_name+"' AND training_name ='"+training_name+"'")){

        qDebug()<<"Статистика обновлена в базе данных!";
    }else if(!record_exist){ //если статистика ещё не была создана
        query = new QSqlQuery;
        query->exec("INSERT INTO statistics (id,mode_name,training_name,data)" //проверяем была ли уже запись, чтобы ее можно было обновить
                    " VALUES (" +QString::number(user_id)+", '"+mode_name+"','"+training_name+"','"+statistics+"')");
        qDebug()<<"Статистика была создана в базе данных!";
        delete query;
    }
    else{//если записи не было, то делаем другой запрос
        qDebug()<<"Ошибка обновления статистики в базе данных!";
    }    
}
////////////////////////////////////////////////////////////////////////
/////////////////////DB::SendTrainingStatistics/////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////////////DB::SendAdditionalStatistics///////////////////////
////////////////////////////////////////////////////////////////////////
/// проверяет есть ли в базе статистика ошибок по тренировке режима и
/// если есть, то обновляет ее, иначе создает новую
void DB::SendAdditionalStatistics(const QString &mode_name,const QString &training_name, QString &statistics, const QString &statistics_type){
    query = new QSqlQuery(*db);

    if( query->exec("UPDATE statistics set "+ statistics_type+ " = '" + statistics+"' " //проверяем была ли уже запись, чтобы ее можно было обновить
                    "WHERE id = " +QString::number(user_id)+" AND training_name ='"+training_name+"' "
                    "AND mode_name = '"+mode_name+"'")){
        qDebug()<<"Статистика "+ statistics_type+ " обновлена в базе данных!";
    }else{
        qDebug()<<"Ошибка обновления статистики "+ statistics_type+ " в базе данных!"; //если не один запрос не работате, то возвращаем ошибку
    }

    delete query;
}
////////////////////////////////////////////////////////////////////////
/////////////////////DB::SendAdditionalStatistics///////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////////DB::SendAddedTraining/////////////////////////////
////////////////////////////////////////////////////////////////////////
/// добавляет созданную пользователем тренировку в бд
void DB::SendAddedTraining(const QString &mode_name, const QString &training_names){
    query = new QSqlQuery(*db);
    if(query->exec("UPDATE added_mods set training_names = '"+training_names+"' "
                   "WHERE id = " +QString::number(user_id)+" AND mode_name = '"+mode_name+"'")){
        qDebug()<<"Таблица имен обновлена!";
    }else qDebug()<<"Ошибка обновления таблицы!";
    delete query;
}
////////////////////////////////////////////////////////////////////////
//////////////////////DB::SendAddedTraining/////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////////DB::SendStatisticsPerTime/////////////////////////
////////////////////////////////////////////////////////////////////////
/// проверяет есть ли статистика написания за период, если есть, то
/// обновляет, иначе создает новую
void DB::SendStatisticsPerTime(const QString &mode_name, const QString &training_name, const int &year, const int &month,
                               const int &day, const int &speed, const int &amount, const float &mistakes){

    if(!Query("SELECT speed FROM statistics_per_time "
              "WHERE id = " +QString::number(user_id)+" AND mode_name = '"+mode_name+"' AND training_name = '"+training_name +"' "
              "AND year = "+QString::number(year)+" AND month = "+QString::number(month)+" AND day = "+QString::number(day))){

        //если не находит скорость по поступившим данным, то такой записи еще не было, нужно добавить
        query = new QSqlQuery(*db);
        if(!record_exist){
            if(query->exec("INSERT INTO statistics_per_time (id, mode_name, training_name, year, month, day, speed, amount, mistakes)"
               "VALUES ("+QString::number(user_id)+", '"+mode_name+"', '"+training_name+"', "+ QString::number(year)+", "+
               QString::number(month)+", "+QString::number(day)+", " +QString::number(speed)+", "+QString::number(amount)+
               ", "+QString::number(mistakes)+")")) qDebug()<<"Данные за сегодня созданы в бд!"; //если записи не было, добавляем

            else qDebug()<<"Ошибка создания данных за сегодня!";
        }

    }else{//иначе обновляем существующую запись
        query = new QSqlQuery(*db);
        if(query->exec("UPDATE statistics_per_time set speed = "+ QString::number(speed) +", mistakes = "+QString::number(mistakes)+
           ", amount = "+QString::number(amount)+" "
           "WHERE id = " +QString::number(user_id)+" AND mode_name = '"+mode_name+"' AND training_name = '"+training_name +"' "
           "AND year = "+QString::number(year)+" AND month = "+QString::number(month)+" AND day = "+QString::number(day)))
        qDebug()<<"Данные за сегодня обновлены!";
        else qDebug()<<"SendStatisticsPerTime::Ошибка обновления таблицы!";

    }
    delete query;

}
////////////////////////////////////////////////////////////////////////
//////////////////////DB::SendStatisticsPerTime/////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////////////DB::CreateCustomTraining///////////////////////////
////////////////////////////////////////////////////////////////////////
/// при создании новой тренировки пользователем, заносит данные в нужные
/// таблицы
bool DB::CreateCustomTraining(const QString &mode_name, const QString &training_name, const QString &content){
    query = new QSqlQuery(*db);
    qDebug()<<"INSERT INTO mode(id, mode_name, training_name, content, people_added, play_counter)"
              "VALUES("+QString::number(user_id)+",'"+mode_name+"','"+training_name+"','"+content+"',1,0);";
    if(query->exec("INSERT INTO mode(id, mode_name, training_name, content, people_added, play_counter)"
                   "VALUES("+QString::number(user_id)+",'"+mode_name+"','"+training_name+"','"+content+"',1,0);")){
        qDebug()<<"Тренировка сохранена успешно!";
        delete query;
        return true;
    }
    qDebug()<<"Ошибка в сохранении тренировки!";
    delete query;
    return false;
}
////////////////////////////////////////////////////////////////////////
/////////////////////DB::CreateCustomTraining///////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////////////DB::Registration//////////////////////////////
////////////////////////////////////////////////////////////////////////
/// проверяет корректность регистрационных данных, если все хорошо, то
/// регистрирует пользователям
bool DB::Registration(QString login, QString password){
    if(!CheckRegistrationData(login, password))return false; // если неккорекны данные регистарции, то выходим
    if(LoginAlreadyExist(login)) return false; // если такой логин уже есть, выходим

    hash = new HASH;
    login = hash->GetHash(login); //хэшируем логин и пароль
    password = hash->GetHash(password);
    delete hash;

    if(!record_exist){
        Query("INSERT INTO users(login, password,date_reg)" // запрос на добавление нового пользователя в бд
              "VALUES ('"+login+"','"+password+"','2000-10-20');"
              "INSERT INTO statistics(id)"
              "VALUES (LAST_INSERT_ID());"
              );

      qDebug()<<"Вы были зарегистрированы!"; // его логин и пароль
      GetUserId(login);
    }else qDebug()<<"Ошибка регистрации!";

    return true;
}
////////////////////////////////////////////////////////////////////////
//////////////////////////DB::Registration//////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////////////////////DB::SignIn/////////////////////////////////
////////////////////////////////////////////////////////////////////////
/// проверяет корректность данных при входе
bool DB::SignIn(QString login, QString password){

    hash = new HASH;
    login = hash->GetHash(login); // хэшируем наши данные для проверки по бд
    password = hash->GetHash(password);
    delete hash;

    if(!Query("SELECT * FROM users WHERE login = '" +login+"'")){ //проверка, что пользователь под таким логином
        qDebug()<<"Пользователь с таким ником не зарегистрирован!"; // существует
        return false;
    }
    else if(!Query("SELECT login, password FROM users WHERE login = '" +login+"' AND password = '" +password+"'")){ // если логин правильный проверяем пароль
        qDebug()<<"Введен неверный пароль!";
        return false;
    }

    GetUserId(login);
    qDebug()<<"Вход в систему!";
    return true;
}
////////////////////////////////////////////////////////////////////////
/////////////////////////////DB::SignIn/////////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////////////////DB::Query/////////////////////////////////
////////////////////////////////////////////////////////////////////////
/// надстройка над обычным запросом (можно узнать инфу есть ли строка с
/// данными или нет, а также корректность запроса)
bool DB::Query(QString query){
    this->query = new QSqlQuery(*db);
    this->record_exist = true;

    if(!this->query->exec(query)){ // проверяем на корректность запроса
        qDebug()<<this->query->lastError().databaseText();
        delete this->query;
        return false;
    }
    else if(!this->query->next()){
        record_exist = false;
        delete this->query;
        return false; // проверяем, что есть результат
    }

    delete this->query;
    return true;
}
////////////////////////////////////////////////////////////////////////
//////////////////////////////DB::Query/////////////////////////////////
////////////////////////////////////////////////////////////////////////




