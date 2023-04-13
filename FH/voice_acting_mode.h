#ifndef VOICE_ACTING_MODE_H
#define VOICE_ACTING_MODE_H

#include <QWidget>
#include <QTextToSpeech>

#define TEXT_ACTING "text acting"

class TRAINING_MODE;
class DB;
class QComboBox;
class QSlider;
class QLabel;
class QPushButton;
class QTextBrowser;
class QVBoxLayout;

class VOICE_ACTING_MODE : public QWidget{
    Q_OBJECT
public:
    int pause_time_between_words = 1000;//время(в мс), которые будет ожидать пользователем после каждого озвученного слова
    QList <QString> acting_words; // сборник слов для озвучки пословно
private:
    QVBoxLayout *v_main_l = nullptr;

    QLabel *lab_volume = nullptr;
    QLabel *lab_speed= nullptr;
    QLabel *lab_language = nullptr;

    QSlider *sl_volume = nullptr;
    QSlider *sl_speed = nullptr;

    QPushButton *but_test = nullptr;

    QComboBox *box_language = nullptr;

    QTextToSpeech *speech = nullptr;

    TRAINING_MODE *training_mode = nullptr;
    QString text = ""; 

    QTimer *pause_timer = nullptr; //пауза перед озвучкой текста
    int sec = 0, ms = 0; //

public:
    VOICE_ACTING_MODE();
    void SetPlayingText(const QString &text);

private:


public slots:
    void SetVoiceSettingsWindow();
    void Speak();
    void Stop();

    void SetSpeed(int speed);
    void SetVolume(int volume);

    void SetLanguage(int language);

    void LocaleChanged(const QLocale &locale);

private slots:
    void OnPauseTime();
    void ButTestClicked();
};

#endif // VOICE_ACTING_MODE_H
