#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

class QLineEdit;
class QTextBrowser;
class CHAT;

class CLIENT: public QTcpSocket{
    Q_OBJECT
public:
    QTcpSocket *socket = nullptr;
private:

    QByteArray data;
    quint16 block_size;

    CHAT *text_browser = nullptr;
    QLineEdit *ld_message = nullptr;

public:
    CLIENT(CHAT *text_browser, QLineEdit*ld_message);
    void SendToServer(QString message);

public slots:
    void SlotReadyRead();
};

#endif // CLIENT_H
