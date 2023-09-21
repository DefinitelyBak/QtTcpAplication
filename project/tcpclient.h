#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QTime>
#include <QTcpServer>
#include <QThread>

typedef quint16 payloadSize;

class TcpClient: public QTcpSocket
{
    Q_OBJECT

public:
    TcpClient(QObject *parent = nullptr);
    ~TcpClient();
    static int no_objects;

private:
    payloadSize m_nNextBlockSize = 0;

public slots:
    void slotConnect(const QString& port);
    void slotDisconnect();
    void slotError(QAbstractSocket::SocketError) ;
    void slotSendToServer(const QString& str);
    void slotReadyRead();

signals:
    void sendMessageToGUI(const QString& str);
};

#endif // TCPCLIENT_H
