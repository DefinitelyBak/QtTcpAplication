#include "ClientWindow.h"

ClientWindow::ClientWindow(QWidget *parent) : QWidget(parent)
{
    QThread::currentThread()->setObjectName("main thread");
    m_pThread = new QThread;
    m_pThread->setObjectName("client thread");
    m_ptcpClient = new TcpClient;

    m_pLineEditMessage  = new QLineEdit(this);
    m_pLineEditPort     = new QLineEdit("8080", this);
    m_pMessageOutput    = new QTextEdit(this);
    m_pButtonToWrite    = new QPushButton("Send message", this);
    m_pConnectionButton = new MyButton("Connect", this);

    m_pMessageOutput->setReadOnly(true);
    m_pButtonToWrite->setEnabled(connectionStatus);
    m_pLineEditMessage->setEnabled(connectionStatus);

    setWindowTitle("TCP-Client: " + QString::number(TcpClient::no_objects));
    setGeometry(0, 0, 500, 500);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlag(Qt::Tool);

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Message", m_pLineEditMessage);
    formLayout->addRow("Port",m_pLineEditPort);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(new QLabel("<H1>Client</H1>"));
    vLayout->addWidget(m_pMessageOutput);
    vLayout->addLayout(formLayout);
    vLayout->addWidget(m_pConnectionButton);
    vLayout->addWidget(m_pButtonToWrite);

    setLayout(vLayout);

    connect(m_pConnectionButton, &MyButton::connectSignal, this, [this](){emit serverConnection(m_pLineEditPort->text());});
    connect(this, &ClientWindow::serverConnection, m_ptcpClient, &TcpClient::slotConnect);

    connect(m_pConnectionButton, &MyButton::disconnectSignal, m_ptcpClient, &TcpClient::slotDisconnect);

    connect(m_ptcpClient, &TcpClient::sendMessageToGUI, this, [this](const QString& message){m_pMessageOutput->append(message);});

    connect(m_ptcpClient, &TcpClient::connected, this, &ClientWindow::slotStateChanged);
    connect(m_pConnectionButton, &MyButton::disconnectSignal, this, &ClientWindow::slotStateChanged);

    connect(m_pButtonToWrite, &QPushButton::clicked, this, [this](){emit sendMessageToServer(m_pLineEditMessage->text());});
    connect(this, &ClientWindow::sendMessageToServer, m_ptcpClient, &TcpClient::slotSendToServer);

    m_ptcpClient->moveToThread(m_pThread);
    m_pThread->start();

}

ClientWindow::~ClientWindow(){
    m_pThread->quit();
    m_pThread->wait();
    delete m_pThread;
    delete m_ptcpClient;
}

void ClientWindow::slotStateChanged(){
    connectionStatus = !connectionStatus;
    m_pButtonToWrite->setEnabled(connectionStatus);
    m_pLineEditMessage->setEnabled(connectionStatus);
}
