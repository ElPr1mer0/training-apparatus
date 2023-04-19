#include "book_mode.h"
#include "db.h"


///////////////////////////////////////////////////////////////////////
/////////////////////////BOOK_MODE::BOOK_MODE//////////////////////////
///////////////////////////////////////////////////////////////////////
BOOK_MODE::BOOK_MODE(DB *db):db(db){}
///////////////////////////////////////////////////////////////////////
/////////////////////////BOOK_MODE::BOOK_MODE//////////////////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
//////////////////BOOK_MODE::CreateTextFileFromBook////////////////////
///////////////////////////////////////////////////////////////////////
/// Создает из полученного пользователем текстового файла книги, уже
/// готовую, для использованию книгу, текст которой разделен на уровни
/// и загружает информацию о книге в базу данных, с начальной статисти-
/// кой.
QString BOOK_MODE::CreateTextFileFromBook(const QString &file_path){
    QFile file(file_path); //здесь просто загружаем книгу, которую нужно переработать для дальнейшего использования
    if(!file.exists()){
        qDebug()<<__FUNCTION__ << ":: Файл не существует!";
        return "Ошибка! Файл не существует!";
    }

    QString book;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){

        while(!file.atEnd()){
            book = file.readAll();
        }
    }
    else{
        qDebug()<<__FUNCTION__ << ":: Ошибка в открытии файла!";
        return "Ошибка! Проблема в открытии файла!";
    }
    file.close();


    QFileInfo file_info(file_path);
    if(file_info.fileName() == ""){
        qDebug()<<__FUNCTION__ << ":: Файл не был создан!";         // если отменили сохранение файла
        return "Ошибка! Файл не был создан!";
    }

    book_name = file_info.fileName();//берем имя файла, чтобы узнать есть ли уже файл с таким же именем
    GetTrainingNames(BOOK); //если есть, то эта функция его поменяет, чтобы не было перезаписи
    for(auto it = training_names.begin();it!=training_names.end();++it)
        if(*it == book_name) return "Книга с таким именем уже существует!";


    int words_counter = 0; // счётчик слов (в обычной игре сделаю диапазон слов около allWords,
    int texts_counter = 0; // сколько игровых текстов получим из книги
    QString word = "";
    QString level = "";

    bool was_new_line = false;  // поиск перехода на новую строку
    bool was_gap = false; //нужен только тогда, когда в тексте нет ни одного пробела
    for(int i = 0; i<book.length(); ++i){
        if((book[i].unicode()>=32 && book[i].unicode() <= 126)|| //латинский алфавит + знаки
          (book[i].unicode()>=1040 && book[i].unicode() <= 1071)|| //рус заглавные, снизу маленькие
          (book[i].unicode()>=1072 && book[i].unicode() <= 1103)||
           book[i].unicode()==252 || book[i].unicode()==10 || book[i].unicode()==8211 || book[i].unicode()==8212){ //проверяем, чтобы символ был в таблицы кодировки этого диапазона
            // 252 = № 10 = абзац
            if (book[i]!=" "){
                if (book[i] != "\n"){  // если символ перехода на новую строку, то скипаем его
                     word += book[i];
                }
                else{
                    if(word!="") was_new_line = true;
                    was_gap = true;
                    continue;
                }

            }
            else{
                if(was_new_line){
                    word+=". "; // так как нашли символ абзаца, то нужно сделать пробел, чтобы слова не слиплись
                }

                if(word!=""){ // проверка, если вдруг в тексте будет несколько пробелов подряд
                    level+= word + " ";
                    was_new_line = false;
                    word = "";
                    ++words_counter;

                    if(words_counter >= TOTAL_WORDS_PER_LEVEL){ // если мы уже набрали стандартное кол-во слов для создания текста, то ищем конец предложения
                                                // чтобы закончить записать одного текста для набора
                        while(book[i]!= "." && book[i]!= "?" && book[i]!= "!" && i<book.length() ){ //i<book.length() чтобы не выхода за пределы массива
                            if(book[i] == "\n"){
                                level += " ";
                                i++;
                                continue;
                            }

                            if (book[i]!=" "){ // если вдруг там нет знаков, а строка закончилась
                                word += book[i];
                                i++;
                            }
                            else{
                                if(word!=""){ // проверка, если вдруг в тексте будет несколько пробелов подряд
                                    level += word + " "; // из-за этого в конце каждого текста будет один лишний символ пробела
                                    word = "";              // при игре это надо будет учитывать!!!
                                }
                                i++;
                            }
                        }

                        words_counter = 0; // обнуляем счетчик для записи новой строки файла
                        if(i<book.length()) level += word + book[i];// так как мы ищем конец предложения, то последнее слово и символ точки не записывается, тут это исправляем
                        book_levels.append(level + "\n");
                        level = "";
                        ++texts_counter;
                        word="";
                    }
                }
            }
        }
        else continue;
    }

    if(words_counter != 0 || !was_gap){ // !was_gap это если не было пробелов в тексте
        level += word + "\n";
        book_levels.append(level + "\n");
        ++texts_counter;// значит последний текст будет неполный
    }

    text_amount = texts_counter;
    if(AddBookDataToDB()) return "Книга была успешно создана!";
    else return "Ошибка при сохранении данных в бд!";
}
///////////////////////////////////////////////////////////////////////
//////////////////BOOK_MODE::CreateTextFileFromBook////////////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
//////////////////////BOOK_MODE::AddBookDataToDB///////////////////////
///////////////////////////////////////////////////////////////////////
/// Если удается создать книгу, то данные о ней добавляются в базу дан-
/// ных
bool BOOK_MODE::AddBookDataToDB(){
    if(db->CreateCustomBook(BOOK, book_name, book_levels)){ //добавляем новый режим в таблицу mode
        db->SendTrainingStatistics(BOOK, book_name,"0 0 0 0 0 0 0 0 ");//создаем статистику по режиму в таблицу statistics

        training_names.append(book_name);//добавляем наше имя тренировки в список

        db->SendAddedTraining(BOOK,book_name);//добавляем название новой тренировки в бд

        return true;
    }
    return false;   //если что-то пошло не так при обращении к бд, то возвращаем false
}
///////////////////////////////////////////////////////////////////////
//////////////////////BOOK_MODE::AddBookDataToDB///////////////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
//////////////////////BOOK_MODE::UpdateStatistics//////////////////////
///////////////////////////////////////////////////////////////////////
/// обновляет статистику по набору книги
void BOOK_MODE::UpdateBookStatistics(const QString &training_name){
    QString statistics;
    statistics = QString::number(current_text)+" "+QString::number(text_amount) +" "+ QString::number(record) +" "+QString::number(average_speed) +" "+QString::number(mistakes) +" "+QString::number(play_time_hours) +" "+
    QString::number(play_time_min) +" "+ QString::number(play_time_sec)+" "; // записываем в строку всю статистику

    db->SendTrainingStatistics(BOOK, training_name, statistics); //добавляем ее в бд
}
///////////////////////////////////////////////////////////////////////
//////////////////////BOOK_MODE::UpdateStatistics//////////////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
///////////////////////BOOK_MODE::GetStatistics////////////////////////
///////////////////////////////////////////////////////////////////////
/// отправляет запрос на получение краткой статистики по набору книги
/// в базу данных и обрабатывает полученные данные для отображения и
/// будущей работы с ними
void BOOK_MODE::GetBookStatistics(const QString &training_name){
    QString statistics;
    db->LoadTrainingStatistics(BOOK,training_name, statistics); //отправляем строку для получения статистики по режиму

    QString current_text = "";
    QString record = "";
    QString average_speed = "";
    QString mistakes = "";
    QString play_time_hours = "";
    QString play_time_min = "";
    QString play_time_sec = "";
    QString text_amount = "";


    if(statistics != ""){ //после обрабатываем эту строку, считывая данные и занося в нужные переменные
        for(int i = 0; i<statistics.length();++i){
            GetStatisticsValue(current_text,statistics,i);
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
        this->current_text = 0;
        this->record = 0;
        this->average_speed = 0;
        this->mistakes = 0;
        this->play_time_hours = 0;
        this->play_time_min = 0;
        this->text_amount = 0;
        this->play_time_sec = 0;
        return;
    }

    this->current_text = current_text.toInt();
    this->record = record.toFloat();
    this->average_speed = average_speed.toFloat();
    this->mistakes = mistakes.toFloat();
    this->play_time_hours = play_time_hours.toInt();
    this->play_time_min = play_time_min.toInt();
    this->text_amount = text_amount.toInt();
    this->play_time_sec = play_time_sec.toInt();

    qDebug()<<"Статистика сохранена в переменные успешно!";
}
///////////////////////////////////////////////////////////////////////
///////////////////////BOOK_MODE::GetStatistics////////////////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
//////////////////////BOOK_MODE::GetBookTraining///////////////////////
///////////////////////////////////////////////////////////////////////
/// создает тренировку по книге
QString BOOK_MODE::GetBookTraining(const QString &training_name){
    if(!book_levels.empty()) book_levels.clear();
    db->LoadBookTraining(BOOK,training_name, book_levels);


//    QString line;
//    if(fileText.open(QIODevice::ReadOnly | QIODevice::Text)){
//        int currentText = 0;

//        while(!fileText.atEnd()){
//            line = fileText.readLine();
//            if(currentText == this->currentText){
//                break;
//            }
//            else{
//                currentText++;
//            }
//        }
//        if(currentText!=this->currentText){
//            qDebug()<<"Error! Text haven't founded!";
//            return "Error! Text haven't founded!";
//        }
//    }
//    else{
//        qDebug()<<"File can't be open!";
//        return "Error";
//    }

//    fileText.close();
    return book_levels.first();
}
///////////////////////////////////////////////////////////////////////
//////////////////////BOOK_MODE::GetBookTraining///////////////////////
///////////////////////////////////////////////////////////////////////


