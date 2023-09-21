#include "tcpclient.h"

int TcpClient::no_objects = 0;

TcpClient::TcpClient(QObject *parent):QTcpSocket(parent)
{
    TcpClient::no_objects++;

    connect(this, &QTcpSocket::connected, this, [this](){emit sendMessageToGUI("Connection has been established");}); //+ emit sendMessageToGUI("Connection has been established") - соединение установлено
    connect(this, &QTcpSocket::readyRead, this, &TcpClient::slotReadyRead);
    connect(this, &QAbstractSocket::errorOccurred, this, &TcpClient::slotError);

    qDebug() << QThread::currentThread()->objectName() + "1"; //
}

TcpClient::~TcpClient(){
    TcpClient::no_objects--;
    qDebug() << QThread::currentThread()->objectName() + "2"; //
}


void TcpClient::slotConnect(const QString& port)
{
    connectToHost(QHostAddress::LocalHost, port.toInt());
    qDebug() << QThread::currentThread()->objectName() + "3"; //
}

void TcpClient::slotDisconnect(){
    emit sendMessageToGUI("Client has disconnected from host");
    disconnectFromHost();
    qDebug() << QThread::currentThread()->objectName() + "4"; //
}


void TcpClient::slotSendToServer(const QString& str)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out << payloadSize(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << payloadSize(arrBlock.size() - sizeof(payloadSize));

    write(arrBlock);
    qDebug() << QThread::currentThread()->objectName()+ "5"; //
}

void TcpClient::slotError(QAbstractSocket::SocketError err){
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(errorString())
        );
    emit sendMessageToGUI(strError);
    qDebug() << QThread::currentThread()->objectName()+ "6"; //
}

void TcpClient::slotReadyRead(){
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    while (true) {
        if (!m_nNextBlockSize) {
            if (quint64(bytesAvailable()) < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        if (bytesAvailable() < m_nNextBlockSize)
            break;
        }
        QTime time;
        QString str;
        in >> time >> str;
        emit sendMessageToGUI(time.toString() + " " + str);
        m_nNextBlockSize = 0;
    }
    qDebug() << QThread::currentThread()->objectName() + "7"; //
}
