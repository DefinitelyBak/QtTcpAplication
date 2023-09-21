#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    MyButton(const QString &text, QWidget *parent = nullptr);

    enum State{ Connect, Disconnect } state = Connect;

signals:
    void connectSignal();
    void disconnectSignal();

public slots:
    void slotStateChanged();

};

#endif // MYBUTTON_H
