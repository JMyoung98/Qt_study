#ifndef KEYLED_H
#define KEYLED_H

#include <QWidget>
#include <QFile>
#include <QMessageBox>
#include <QSocketNotifier>

class KeyLed : public QWidget
{
    Q_OBJECT

public:
    explicit KeyLed(QWidget *parent = nullptr);
    ~KeyLed();
    int keyledFd;
private:
    QFile * pFile;
    QSocketNotifier * pKeyLedNotifier;
public slots:
    void writeLedData(int);
private slots:
    void readKeyData(int);

signals:
    void updateKeydataSig(int);
};

#endif // KEYLED_H
