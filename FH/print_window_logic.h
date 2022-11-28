#ifndef PRINT_WINDOW_LOGIC_H
#define PRINT_WINDOW_LOGIC_H

#include <QWidget>

class QPushButton;
class QLineEdit;
class QComboBox;
class TRAINING;
class QTextBrowser;
class QLabel;
class SOUNDS;



class PRINT_WINDOW_LOGIC: public QWidget{
    Q_OBJECT

private:

    QPushButton *but_start = nullptr; // в освновном окне print_window
    QPushButton *but_load_training = nullptr;
    QPushButton *but_create_training = nullptr;
    QPushButton *but_add_training = nullptr;
    QComboBox *box_training = nullptr;
    QLineEdit *ld_game_pole = nullptr;
    QLineEdit *ld_current_mistakes = nullptr;
    QLineEdit *ld_current_speed = nullptr;
    QLineEdit *ld_text_amount = nullptr;
    QLineEdit *ld_record = nullptr;
    QLineEdit *ld_average_speed = nullptr;
    QLineEdit *ld_mistakes = nullptr;
    QLineEdit *ld_all_time = nullptr;
    QLineEdit *ld_current_min = nullptr;
    QLineEdit *ld_current_sec = nullptr; 
    QTextBrowser *text_browser = nullptr;
    QLabel *lab_current_mistakes = nullptr;

    QLineEdit *ld_training_name = nullptr; //доп окно create_training
    QLineEdit *ld_add_word = nullptr;
    QLineEdit *ld_current_symbols = nullptr;
    QLineEdit *ld_delete_word = nullptr;
    QPushButton *but_add_file = nullptr;
    QPushButton *but_add_word = nullptr;
    QPushButton *but_publish_training = nullptr;
    QPushButton *but_delete_last_word = nullptr;
    QPushButton *but_delete_word = nullptr;
    QLabel *lab_status = nullptr;
    QTextBrowser *browser_training_word = nullptr;


    TRAINING *training  = nullptr;
    SOUNDS *sounds = nullptr;

    QTimer *timer = nullptr; // для работы таймера
    QTimer *pause_timer = nullptr;
    int min = 0, sec = 0, ms = 0; //
    int pause_time = 0;

    QString edit_text; //тренировочный текст

    int letter = 0; // для подсчёта кол-ва пройденных символов в editBrowser
    int line_size = 0; // для подсчета реального кол-ва символов, которые были в введенной игроком строке
    int mistakes = 0;// для подсчета кол-ва ошибок при игре

    bool first_time = true;
    bool is_mistake = false; // проверка на ошибку
    bool was_minus = false; // если находим символ -.е,Е

    int start_ms = 0; //нужно для отслеживания начала набора слова (скорость слова/за время)
    int end_ms = 0; // конец отслеживания
    bool start_writing = true; //для запоминания начала

public:
    PRINT_WINDOW_LOGIC(QPushButton *, QPushButton *, QComboBox *, QLineEdit *, QLineEdit *, QLineEdit *, QLineEdit *,
                       QLineEdit *, QLineEdit *, QLineEdit *, QLineEdit *, QLineEdit *, QLineEdit *, QTextBrowser *,
                       QLabel*, QPushButton *, QPushButton *);

    ~PRINT_WINDOW_LOGIC();

public slots:
    void GetCreateTrainingComponents(QPushButton*, QPushButton*, QPushButton*, QPushButton*, QPushButton*, QLineEdit*,
                                     QLineEdit*, QLineEdit*, QLineEdit*, QLabel*, QTextBrowser*);
private slots:
    void ButAddFileClicked(); //окно create_training
    void ButAddWordClicked();
    void ButCreateTrainingClicked();
    void ButDeleteLastWordClicked();
    void ButDeleteWordClicked();

    void LdFieldTextChanged(QString);
    void ButStartClicked();
    void ButLoadTrainingClicked();
    void BoxTrainingCurrentIndexChanged(int);

    void IsWin();
    void OnTime();
    void OnPauseTime();
    void OnUpdateData();
};

#endif // PRINT_WINDOW_LOGIC_H
