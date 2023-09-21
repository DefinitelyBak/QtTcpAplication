#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QTime>
#include <QTcpServer>

typedef quint16 payloadSize;

class TcpServer: public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(const int port, QObject *parent = nullptr);

private:
    QTcpSocket* m_ptcpClient;
    payloadSize     m_nNextBlockSize = 0;

    void sendToClient(QTcpSocket* pSocket, const QString& str) const;

public slots:
    virtual void slotNewConnection();
    void slotReadyRead();

signals:
    void sendMessageToGUI(const QString& str);
};

#endif // TCPSERVER_H
