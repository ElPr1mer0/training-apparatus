#ifndef CHAT_H
#define CHAT_H
#include <QWidget>
class QVBoxLayout;
class QLabel;

class CHAT: public QWidget{
    Q_OBJECT

private:
    QVBoxLayout *v_main_chat_l = nullptr;
    QLabel *message_container = nullptr;
    QList <QLabel *> history;

public:
    CHAT();
    void AddMessageToField(const QString &message, const QString &time, int server = 0);
private:
    void AddMessageToHistory(QLabel *message_container);
    void SetMessageContanierStyle(QLabel *message_contaier);
};

#endif // CHAT_H
