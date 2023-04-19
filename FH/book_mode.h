#ifndef BOOK_MODE_H
#define BOOK_MODE_H

#include "mode.h"

#include <QString>

#define BOOK "book" // книжный мод book_mode

class DB;




class BOOK_MODE:public MODE{
public:

    QString book_name;
    QList <QString> book_levels;
    int current_text = 0; // показывает текущий текст из всех
private:
    DB *db = nullptr;
public:
    BOOK_MODE(DB *db);

    void LoadBookNamesFromBookFile();

    QString CreateTextFileFromBook(const QString &file_path);
    QString GetBookTraining(const QString &training_name);

    void UpdateBookStatistics(const QString &training_name);
    void GetBookStatistics(const QString &training_name);

private:
    bool AddBookDataToDB();




};

#endif // BOOK_MODE_H
