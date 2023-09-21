#ifndef GUICLIENT_H
#define GUICLIENT_H

#include <QVBoxLayout>
#include <QFormLayout>

#include <QTcpSocket>
#include <QThread>

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include "tcpclient.h"
#include "mybutton.h"

class ClientWindow: public QWidget
{
    Q_OBJECT
public:
    ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

private:
    bool connectionStatus = false;

    QThread*     m_pThread;
    TcpClient*   m_ptcpClient;
    QLineEdit*   m_pLineEditMessage;
    QLineEdit*   m_pLineEditPort;
    QTextEdit*   m_pMessageOutput;
    QPushButton* m_pButtonToWrite;
    MyButton*    m_pConnectionButton; //+ по мне лучше m_pConnectionButton

public slots:
    void slotStateChanged();

signals:
    void sendMessageToServer(const QString& message);
    void serverConnection(const QString& port);

};

#endif // GUICLIENT_H
