#include "ServerWindow.h"

ServerWindow::ServerWindow(int port, QWidget *parent):QWidget(parent)
{
    m_pTcpServer = new TcpServer(port, this);

    m_pMessageOutput = new QTextEdit(this);
    m_pMessageOutput->setReadOnly(true);

    setWindowTitle("TCP-Server");
    setGeometry(0, 0, 500, 500);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlag(Qt::Tool);


    QVBoxLayout* vLayout = new QVBoxLayout(); //+ Опять же GridLayout не очень хорошо
    vLayout->addWidget(new QLabel("<H1>Server</H1>"));
    vLayout->addWidget(m_pMessageOutput);
    setLayout(vLayout);

    connect(m_pTcpServer, &TcpServer::sendMessageToGUI, this, [this](const QString& str){m_pMessageOutput->append(str);});

}
