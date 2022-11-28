#ifndef SOUNDS_H
#define SOUNDS_H
#include <QString>

class QMediaPlayer;

class SOUNDS{

public:
    const QString print_error = "qrc:/sounds/error2.mp3";
    const QString print_record = "qrc:/sounds/record.mp3";


private:
    QMediaPlayer *sound = nullptr; //
public:
    SOUNDS();
    ~SOUNDS();
    void Play(const QString&);
};

#endif // SOUNDS_H
