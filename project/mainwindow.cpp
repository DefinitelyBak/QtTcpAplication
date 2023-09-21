#include "mainwindow.h"

MainWindow::MainWindow() : QWidget()
{
    m_pTcpServer = new ServerWindow(8080, this);
    m_pTcpServer->show();

    m_pButtonNewClient = new QPushButton("Create TCP Client");

    connect(m_pButtonNewClient, &QPushButton::clicked, this, &MainWindow::slotCreateClient);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_pButtonNewClient);
    setLayout(layout);
}

void MainWindow::slotCreateClient(){
    ClientWindow* TcpClient = new ClientWindow(this);
    TcpClient->show();
}
