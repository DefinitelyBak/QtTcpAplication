#include "mybutton.h"

MyButton::MyButton(const QString &text, QWidget *parent) : QPushButton(text, parent)
{
    connect(this, &QPushButton::clicked, this, &MyButton::slotStateChanged);
}

void MyButton::slotStateChanged(){
    switch (state) {
        case Connect:
            emit connectSignal();
            setText("Disconnect");
            state = Disconnect;
            break;
        case Disconnect:
            emit disconnectSignal();
            setText("Connect");
            state = Connect;
            break;
    }
}
