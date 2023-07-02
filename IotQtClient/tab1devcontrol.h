#ifndef TAB1DEVCONTROL_H
#define TAB1DEVCONTROL_H

#include <QWidget>
#include <QTimer>
#include "keyled.h"

namespace Ui {
class Tab1DevControl;
}

class Tab1DevControl : public QWidget
{
    Q_OBJECT

public:
    explicit Tab1DevControl(QWidget *parent = nullptr);
    ~Tab1DevControl();
    KeyLed* getpKeyled();
public slots:
    void slotDialsetValue(int);
private:
    KeyLed* pKeyled;
    Ui::Tab1DevControl *ui;
    QTimer* pQTimer;
private slots:
    void slotKeyCheckBoxUpdate(int);
    void slotSetValueDial();
    void slotTimerStart(bool);
    void slotTimerValueChanged(QString);
};

#endif // TAB1DEVCONTROL_H
