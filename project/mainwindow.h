#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMap>

#include "ServerWindow.h"
#include "ClientWindow.h"

class MainWindow: public QWidget
{
    Q_OBJECT
public:
    MainWindow();

private:
    QPushButton*  m_pButtonNewClient;
    ServerWindow* m_pTcpServer;

public slots:
    void slotCreateClient();
};

#endif // MAINWINDOW_H
