#include "voice_acting_mode.h"
#include "training_mode.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextBrowser>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QComboBox>


////////////////////////////////////////////////////////////////////////
////////////////VOICE_ACTING_MODE::VOICE_ACTING_MODE////////////////////
////////////////////////////////////////////////////////////////////////
/// создает объекты всех режимов, чтобы можно было использовать трени-
/// вки,хранящиеся в них, а так же создавать уровни по их правилам.
/// Передает туда указатель на базу данных для взаимодействия с ней,
/// также получает указатель текстового поля, текст которого будет
/// озвучиваться
VOICE_ACTING_MODE::VOICE_ACTING_MODE(QTextBrowser *text_browser, DB *db){
    VOICE_ACTING_MODE::windowTitle();
    training_mode = new TRAINING_MODE(db);
    this->text_browser = text_browser;
}
////////////////////////////////////////////////////////////////////////
////////////////VOICE_ACTING_MODE::VOICE_ACTING_MODE////////////////////
////////////////////////////////////////////////////////////////////////



void VOICE_ACTING_MODE::SetVoiceSettingsWindow(){
    v_main_l = new QVBoxLayout;
    VOICE_ACTING_MODE::setLayout(v_main_l);

    QHBoxLayout *h_volume_l = new QHBoxLayout;
    v_main_l->addLayout(h_volume_l);
    lab_volume = new QLabel("Громкость");
    sl_volume = new QSlider(Qt::Horizontal);
    sl_volume->setRange(0,100);
    sl_volume->setTickInterval(1);

    h_volume_l->addWidget(lab_volume);
    h_volume_l->addWidget(sl_volume);

    QHBoxLayout *h_speed_l = new QHBoxLayout;
    v_main_l->addLayout(h_speed_l);
    lab_speed = new QLabel("Скорость");
    sl_speed = new QSlider(Qt::Horizontal);
    sl_speed->setRange(-100,100);
    sl_speed->setTickInterval(2);
    h_speed_l->addWidget(lab_speed);
    h_speed_l->addWidget(sl_speed);

    QHBoxLayout *h_language_l = new QHBoxLayout;
    v_main_l->addLayout(h_language_l);
    lab_language = new QLabel("Язык");
    box_language = new QComboBox;
    h_language_l->addWidget(lab_language);
    h_language_l->addWidget(box_language);

    QHBoxLayout *h_buttons_l = new QHBoxLayout;
    v_main_l->addLayout(h_buttons_l);
    but_play = new QPushButton("Включить");
    but_stop = new QPushButton("Выключить");
    h_buttons_l->addWidget(but_play);
    h_buttons_l->addWidget(but_stop);


    connect(but_play, &QPushButton::clicked, this, &VOICE_ACTING_MODE::Speak);
    connect(sl_speed, &QSlider::valueChanged, this, &VOICE_ACTING_MODE::SetSpeed);
    connect(sl_volume, &QSlider::valueChanged, this, &VOICE_ACTING_MODE::SetVolume);

    speech = new QTextToSpeech(this);

    SetSpeed(sl_speed->value());
    SetVolume(sl_volume->value());
    connect(but_stop, &QPushButton::clicked, this, &VOICE_ACTING_MODE::Stop);

    connect(speech, &QTextToSpeech::localeChanged, this, &VOICE_ACTING_MODE::LocaleChanged);

    connect(box_language, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &VOICE_ACTING_MODE::SetLanguage);

    const QVector<QLocale> locales = speech->availableLocales();
    QLocale current = speech->locale();
    for (const QLocale &locale : locales) {
        QString name(QString("%1 (%2)").arg(QLocale::languageToString(locale.language())).arg(QLocale::countryToString(locale.country())));
        QVariant localeVariant(locale);
        box_language->addItem(name, localeVariant);
        if (locale.name() == current.name())
            current = locale;
    }
    LocaleChanged(current);
    VOICE_ACTING_MODE::show();
}

void VOICE_ACTING_MODE::Speak(){
    speech->say(text_browser->toPlainText());
}

void VOICE_ACTING_MODE::Stop(){
    speech->stop();
}

void VOICE_ACTING_MODE::SetSpeed(int speed){
    speech->setRate(speed / 100.0);
}

void VOICE_ACTING_MODE::SetVolume(int volume){
    speech->setVolume(volume / 100.0);
}

void VOICE_ACTING_MODE::SetLanguage(int language){
    QLocale locale = box_language->itemData(language).toLocale();
    speech->setLocale(locale);
}

void VOICE_ACTING_MODE::LocaleChanged(const QLocale &locale){
    QVariant localeVariant(locale);
    box_language->setCurrentIndex(box_language->findData(localeVariant));
}
