#ifndef VOICE_ACTING_MODE_H
#define VOICE_ACTING_MODE_H

#include <QWidget>
#include <QTextToSpeech>

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
    int min = 0, sec = 0, ms = 0; //
    int pause_time = 0;

public:
    VOICE_ACTING_MODE();
    void SetPlayingText(const QString &text);

public slots:
    void SetVoiceSettingsWindow();
    void Speak();
    void Stop();

    void SetSpeed(int speed);
    void SetVolume(int volume);

    void SetLanguage(int language);

    void LocaleChanged(const QLocale &locale);

private slots:
    void ButTestClicked();
};

#endif // VOICE_ACTING_MODE_H
