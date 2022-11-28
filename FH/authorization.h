#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QWidget>

class QString;

class AUTHORIZATION : public QWidget{
Q_OBJECT

public:


public slots:
    void CheckLoginField(QString);
    void CheckPasswordField(QString);
};

#endif // AUTHORIZATION_H
