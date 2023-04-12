#ifndef PRINT_WINDOW_LOGIC_H
#define PRINT_WINDOW_LOGIC_H

#include "qcheckbox.h"
#include <QWidget>

class TRAINING_MODE;
class MODE;
class SOUNDS;
class VOICE_ACTING_MODE;

class QPushButton;
class QLineEdit;
class QComboBox;
class QTextBrowser;
class QLabel;
class QCustomPlot;
class QCPGraph;
class QCPItemTracer;
class QCPCurve;
class QGroupBox;
class QCheckBox;


class PRINT_WINDOW_LOGIC: public QWidget{
    Q_OBJECT

private:
    QPushButton *but_voice_settings = nullptr;
    QPushButton *but_start = nullptr; // в освновном окне print_window
    QPushButton *but_load_training = nullptr;
    QPushButton *but_create_training = nullptr;
    QPushButton *but_add_training = nullptr;
    QPushButton *but_show_group_plot = nullptr;
    QPushButton *but_show_word_statistic = nullptr;
    QPushButton *but_add_file = nullptr;
    QPushButton *but_add_word = nullptr;
    QPushButton *but_publish_training = nullptr;
    QPushButton *but_delete_last_word = nullptr;
    QPushButton *but_delete_word = nullptr;
    QPushButton *but_hide_group_plot = nullptr;
    QPushButton *but_create_errors_training = nullptr;

    QLineEdit *ld_training_name = nullptr; //доп окно create_training
    QLineEdit *ld_add_word = nullptr;
    QLineEdit *ld_current_symbols = nullptr;
    QLineEdit *ld_delete_word = nullptr;
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
    QLineEdit *ld_plot_value = nullptr;

    QTextBrowser *text_browser = nullptr;
    QTextBrowser *browser_training_word = nullptr;
    QTextBrowser *text_mistakes_browser = nullptr;

    QLabel *lab_current_mistakes = nullptr;
    QLabel *lab_status = nullptr;

    QCustomPlot *plot = nullptr; // график
    QCPItemTracer *tracer = nullptr; // для уточнения нажатия на графике
    QCPCurve *vertical_line = nullptr;

    QGroupBox *group_plot = nullptr;
    QGroupBox *group_game_pole = nullptr;
    QGroupBox *group_report = nullptr;

    QComboBox *box_training_name = nullptr;
    QComboBox *box_mode_name = nullptr;
    QComboBox *box_from_year = nullptr;
    QComboBox *box_from_month = nullptr;
    QComboBox *box_to_year = nullptr;
    QComboBox *box_to_month = nullptr;

    QCheckBox *chbox_amount_text = nullptr;
    QCheckBox *chbox_speed = nullptr;
    QCheckBox *chbox_mistake = nullptr;
    QCheckBox *chbox_letter_errors  = nullptr;
    QCheckBox *chbox_syllable_errors = nullptr;
    QCheckBox *chbox_word_errors = nullptr;
    QCheckBox *chbox_words_speed = nullptr;


    MODE *mode = nullptr;
    TRAINING_MODE *training_mode  = nullptr;
    VOICE_ACTING_MODE *voice_acting_mode = nullptr;
    SOUNDS *sounds = nullptr;

    QTimer *timer = nullptr; // для работы таймера
    QTimer *pause_timer = nullptr;
    int min = 0, sec = 0, ms = 0; //
    int pause_time = 0;

    QString edit_text; //тренировочный текст
    QString mistakes_text; // текст, который будет выводиться в конце тренировки со всеми ошибками

    int letter = 0; // для подсчёта кол-ва пройденных символов в editBrowser
    int line_size = 0; // для подсчета реального кол-ва символов, которые были в введенной игроком строке
    int mistakes = 0;// для подсчета кол-ва ошибок при игре

    bool first_time = true;
    bool is_mistake = false; // проверка на ошибку
    bool was_minus = false; // если находим символ -.е,Е

    int start_ms = 0; //нужно для отслеживания начала набора слова (скорость слова/за время)
    int end_ms = 0; // конец отслеживания
    bool start_writing = true; //для запоминания начала

    bool errors_mode = false;

public:
    PRINT_WINDOW_LOGIC(QPushButton *,QPushButton *, QPushButton *,QComboBox *, QComboBox *, QLineEdit *, QLineEdit *, QLineEdit *, QLineEdit *,
                       QLineEdit *, QLineEdit *, QLineEdit *, QLineEdit *, QLineEdit *, QLineEdit *,QTextBrowser *, QTextBrowser *,
                       QLabel*, QPushButton *, QPushButton *, QPushButton *, QCustomPlot *, QPushButton *,QComboBox *,
                       QComboBox *, QComboBox *, QComboBox *, QGroupBox *, QLineEdit *, QGroupBox *, QCheckBox *,
                       QCheckBox *, QCheckBox *, QCheckBox *, QCheckBox *, QCheckBox * , QCheckBox *, QPushButton *,
                       QGroupBox *, QPushButton *);

    ~PRINT_WINDOW_LOGIC();

private:
    void ChangeStyleEnteredLetters(const int &index ); // меняет стиль текста для правильно написанных букв в тренировке
    void AlterMistakesText(QChar right_letter, QChar error_letter);// сюда будем записывать текст с ошибками, для показа их после тренировки

public slots:
    void GetCreateTrainingComponents(QPushButton*, QPushButton*, QPushButton*, QPushButton*, QPushButton*, QLineEdit*,
                                     QLineEdit*, QLineEdit*, QLineEdit*, QLabel*, QTextBrowser*);
private slots:
    void ButAddFileClicked(); //окно create_training
    void ButAddWordClicked();
    void ButCreateTrainingClicked();
    void ButDeleteLastWordClicked();
    void ButDeleteWordClicked();


    void ButStartClicked(); //освновное окно
    void ButLoadTrainingClicked();
    void ButShowGroupPlotClicked();
    void ButHideGroupPlotClicked();
    void ButShowWordStatistic();
    void ButCreateErrorsTrainingClicked();
    void ButVoiceSettingsClicked();

    void LdFieldTextChanged(QString);

    void BoxModeNamesCurrentIndexChanged(int);
    void BoxTrainingCurrentIndexChanged(int);
    void BoxFromYearCurrentIndexChanged(int);
    void BoxFromMonthCurrentIndexChanged(int);
    void BoxToYearCurrentIndexChanged(int);
    void BoxToMonthCurrentIndexChanged(int);

    void PlotMousePress(QMouseEvent *);
    void PlotMouseMove(QMouseEvent *);

    void CHBoxSpeedChecked();
    void CHBoxMistakeChecked();
    void CHBoxAmountTextChecked();
    void CHBoxLetterErrorsChecked();
    void CHBoxSyllableErrorsChecked();
    void CHBoxWordErrorsChecked();
    void CHBoxWordsSpeedChecked();

    void IsWin();
    void OnTime();
    void OnPauseTime();
    void OnUpdateData();

};

#endif // PRINT_WINDOW_LOGIC_H
