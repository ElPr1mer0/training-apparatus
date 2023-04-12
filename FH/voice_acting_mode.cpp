#include "voice_acting_mode.h"

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
VOICE_ACTING_MODE::VOICE_ACTING_MODE(){//
    VOICE_ACTING_MODE::windowTitle();

    speech = new QTextToSpeech();
    v_main_l = new QVBoxLayout;
    VOICE_ACTING_MODE::setLayout(v_main_l);
    setWindowTitle("Настройка озвучки");
    setFixedSize(300,150);

    QHBoxLayout *h_volume_l = new QHBoxLayout;
    v_main_l->addLayout(h_volume_l);
    lab_volume = new QLabel("Громкость");
    sl_volume = new QSlider(Qt::Horizontal);
    sl_volume->setRange(0,100);
    sl_volume->setValue(60);
    sl_volume->setTickInterval(1);

    h_volume_l->addWidget(lab_volume);
    h_volume_l->addWidget(sl_volume);

    QHBoxLayout *h_speed_l = new QHBoxLayout;
    v_main_l->addLayout(h_speed_l);
    lab_speed = new QLabel("Скорость");
    sl_speed = new QSlider(Qt::Horizontal);
    sl_speed->setRange(-100,100);
    sl_speed->setValue(-60);
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
    but_test = new QPushButton("тест");
    h_buttons_l->addWidget(but_test);

    connect(but_test, &QPushButton::clicked, this, &VOICE_ACTING_MODE::ButTestClicked);
    connect(sl_speed, &QSlider::valueChanged, this, &VOICE_ACTING_MODE::SetSpeed);
    connect(sl_volume, &QSlider::valueChanged, this, &VOICE_ACTING_MODE::SetVolume);

    SetSpeed(sl_speed->value());
    SetVolume(sl_volume->value());

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

}

void VOICE_ACTING_MODE::SetPlayingText(const QString &text){
    this->text = text;
}
////////////////////////////////////////////////////////////////////////
////////////////VOICE_ACTING_MODE::VOICE_ACTING_MODE////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
////////////VOICE_ACTING_MODE::SetVoiceSettingsWindow///////////////////
////////////////////////////////////////////////////////////////////////
/// создает окно настройки озвучки речи, соединяет слоты с сигналами,
/// добавляет доступные языки для озвучки текста в бокс
void VOICE_ACTING_MODE::SetVoiceSettingsWindow(){

    VOICE_ACTING_MODE::show();
}
////////////////////////////////////////////////////////////////////////
////////////VOICE_ACTING_MODE::SetVoiceSettingsWindow///////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////////VOICE_ACTING_MODE::Speak//////////////////////////
////////////////////////////////////////////////////////////////////////
/// запускает озвучку
void VOICE_ACTING_MODE::Speak(){
    speech->say(text);
}
////////////////////////////////////////////////////////////////////////
//////////////////////VOICE_ACTING_MODE::Speak//////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////////VOICE_ACTING_MODE::Stop///////////////////////////
////////////////////////////////////////////////////////////////////////
/// останавливает озвучку
void VOICE_ACTING_MODE::Stop(){
    speech->stop();
}
////////////////////////////////////////////////////////////////////////
//////////////////////VOICE_ACTING_MODE::Stop///////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/////////////////////VOICE_ACTING_MODE::SetSpeed////////////////////////
////////////////////////////////////////////////////////////////////////
/// настройка скорости чтения (диапазон от -1.0 до 1.0, с шагом 0.02)
void VOICE_ACTING_MODE::SetSpeed(int speed){
    speech->setRate(speed / 100.0);
}
////////////////////////////////////////////////////////////////////////
/////////////////////VOICE_ACTING_MODE::SetSpeed////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
///////////////////VOICE_ACTING_MODE::SetVolume/////////////////////////
////////////////////////////////////////////////////////////////////////
/// настройка громкости звука (диапазон от 0 до 100 с шагом 1)
void VOICE_ACTING_MODE::SetVolume(int volume){
    speech->setVolume(volume / 100.0);
}
////////////////////////////////////////////////////////////////////////
///////////////////VOICE_ACTING_MODE::SetVolume/////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////VOICE_ACTING_MODE::SetLanguage////////////////////////
////////////////////////////////////////////////////////////////////////
/// устанавливает доступный язык для озвучки из бокса в setLocale
void VOICE_ACTING_MODE::SetLanguage(int language){
    QLocale locale = box_language->itemData(language).toLocale();
    speech->setLocale(locale);
}
////////////////////////////////////////////////////////////////////////
//////////////////VOICE_ACTING_MODE::SetLanguage////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////VOICE_ACTING_MODE::LocaleChanged//////////////////////
////////////////////////////////////////////////////////////////////////
/// при смене языка
void VOICE_ACTING_MODE::LocaleChanged(const QLocale &locale){
    QVariant localeVariant(locale);
    box_language->setCurrentIndex(box_language->findData(localeVariant));
}
////////////////////////////////////////////////////////////////////////
//////////////////VOICE_ACTING_MODE::LocaleChanged//////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//////////////////VOICE_ACTING_MODE::ButTestClicked/////////////////////
////////////////////////////////////////////////////////////////////////
/// для теста скорости и громкости озвучки
void VOICE_ACTING_MODE::ButTestClicked(){
    if(box_language->currentText() == "Russian (Russia)"){
        SetPlayingText("Это русский текст для оценки скорости и звука настраиваемой озвучки!");
        Speak();
    }else{
        SetPlayingText("This is english text to evaluate the speed and sound of custom voice acting!");
        Speak();
    }
}
////////////////////////////////////////////////////////////////////////
//////////////////VOICE_ACTING_MODE::ButTestClicked/////////////////////
////////////////////////////////////////////////////////////////////////
