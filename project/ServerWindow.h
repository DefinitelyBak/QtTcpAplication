#ifndef GUISERVER_H
#define GUISERVER_H

#include <QVBoxLayout>
#include <QFormLayout>

#include <QTcpSocket>

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include "tcpserver.h"

class ServerWindow: public QWidget
{
    Q_OBJECT
public:
    ServerWindow(const int port, QWidget *parent = nullptr);

private:
    TcpServer* m_pTcpServer;
    QTextEdit* m_pMessageOutput;
};

#endif // GUISERVER_H
