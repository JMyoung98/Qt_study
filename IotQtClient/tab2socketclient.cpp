#include "tab2socketclient.h"
#include "ui_tab2socketclient.h"

Tab2SocketClient::Tab2SocketClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab2SocketClient)
{
    ui->setupUi(this);
    pSocketClient = new SocketClient(this);
    ui->pPBsendButton->setEnabled(false);
    connect(ui->pPBServerConnect,SIGNAL(clicked(bool)),this,SLOT(slotConnectToServer(bool)));
    connect(ui->pPBsendButton,SIGNAL(clicked()),this,SLOT(slotSocketSendData()));
    connect(pSocketClient,SIGNAL(sigSocketRecv(QString)),this,SLOT(slotSocketRecvUpdate(QString)));
}

void Tab2SocketClient::slotConnectToServer(bool check){
    bool bOk;
    if(check){
        pSocketClient->slotConnectToServer(bOk);    //참조연산자를 통하여 bool&값을 돌려받음 -> socketclient.cpp파일의 slotConnectToServer함수
        if(bOk){
            ui->pPBsendButton->setEnabled(true);
            ui->pPBServerConnect->setText("서버 해제");
        }
        else
            ui->pPBServerConnect->setChecked(false);
    }
    else{
        pSocketClient->slotClosedByServer();
        ui->pPBServerConnect->setText("서버 연결");
        ui->pPBServerConnect->setChecked(false);
    }
}
void Tab2SocketClient::slotSocketRecvUpdate(QString strValue){
    QString strRecvData;
    QTime time = QTime::currentTime();              //QTime객체 생성과 동시에 currentTime설정
    strValue.chop(1);                               //문자열 끝의 \n을 잘라냄
    strRecvData = time.toString()+ " " + strValue;
    if(!strValue.isEmpty()){
        ui->pTErecvData->append(strRecvData);
    }
    ui->pTErecvData->moveCursor(QTextCursor::End);
    strValue.replace("[","@");
    strValue.replace("]","@");
    QStringList qList = strValue.split("@");
    if(qList[2] == "LED"){
        int ledNo = qList[3].toInt();
        emit sigLedWrite(ledNo);
    }
    //else if(qList[2] == "LAMPON"){
    else if(strValue.indexOf("LAMP") != -1 || strValue.indexOf("GAS") != -1){
        emit sigTab3RecvData(strValue);
    }
    else if(strValue.indexOf("SENSOR") != -1){
        emit sigTab5RecvData(strValue);
        emit sigTab6RecvData(strValue);

    }
}

void Tab2SocketClient::slotSocketSendData(){
    QString strRecvId;
    QString strSendData;

    strRecvId = ui->pLErecvId->text();                  //라인에디터의 문자열을 받아옴
    strSendData = ui->pLEsendData->text();
    if(strRecvId.isEmpty()){
        strSendData = "[ALL_MSG]" + strSendData;
    }
    else
        strSendData = "[" + strRecvId + "]" + strSendData;
    pSocketClient->slotSocketSendData(strSendData);
    ui->pLEsendData->clear();
}

void Tab2SocketClient::slotSocketSendData(QString strValue){
    if(ui->pPBServerConnect->isChecked()){
        pSocketClient->slotSocketSendData(strValue);
    }
}

Tab2SocketClient::~Tab2SocketClient()
{
    delete ui;
}
