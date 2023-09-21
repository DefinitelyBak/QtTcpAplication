#include "tcpserver.h"

TcpServer::TcpServer(const int port,QObject *parent): QTcpServer(parent)
{
    if(!listen(QHostAddress::LocalHost, port)) {
        QMessageBox::critical(0, "Server Error", "Unable to start the server:" + errorString());
        close();
        return;
    }
    connect(this, &QTcpServer::newConnection, this, &TcpServer::slotNewConnection);
}

void TcpServer::sendToClient(QTcpSocket *pSocket, const QString &str) const{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out << payloadSize(0) << QTime::currentTime() << str;
    out.device()->seek(0);
    out << payloadSize(arrBlock.size() - sizeof(payloadSize) );
    pSocket->write(arrBlock);
}

void TcpServer::slotReadyRead(){
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    while (true) {
        if (!m_nNextBlockSize) {
            if (quint64(pClientSocket->bytesAvailable()) < sizeof(payloadSize)) {
                break;
            }
            in >> m_nNextBlockSize;
        }
        if (pClientSocket->bytesAvailable() < m_nNextBlockSize){
            break;
        }
        QTime time;
        QString str;
        in >> time >> str;

        QString strMessage = time.toString() + " " + "Client has sent - " + str;
        emit sendMessageToGUI(strMessage);
        m_nNextBlockSize = 0;

        sendToClient(pClientSocket, "Server response: message has been received"); //+ "Server response: message has been received" - (сообщение принято)
    }
}

void TcpServer::slotNewConnection(){
    QTcpSocket* clienSocket = nextPendingConnection();
    qintptr idusersocs = clienSocket->socketDescriptor();
    //+ "Client сonnectED:" - Past Simple или "Client has connected" - Present Perfect (правильнее)
    //+ сначала время через двоеточие, потом всё остальное
    emit sendMessageToGUI( QTime::currentTime().toString() + " :Client Connected, descriptor:" + QString::number(idusersocs));

    //+ "Client disconnectED:" - Past Simple или "Client has disonnected" - Present Perfect (правильнее)
    connect(clienSocket, &QTcpSocket::disconnected, clienSocket, [=](){emit sendMessageToGUI("Client disconnected");});
    connect(clienSocket, &QTcpSocket::disconnected, clienSocket, &QTcpSocket::deleteLater);
    connect(clienSocket, &QTcpSocket::readyRead, this, &TcpServer::slotReadyRead);

    //+ "Server response: connection has been established" - (соединение установлено)
    sendToClient(clienSocket, "Server response: connection has been established");
}

