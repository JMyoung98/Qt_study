#include "tab6database.h"
#include "ui_tab6database.h"

Tab6Database::Tab6Database(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab6Database)
{
    ui->setupUi(this);
    sqlDb = QSqlDatabase::addDatabase("QSQLITE");
    sqlDb.setDatabaseName("temp1.db");
    if(sqlDb.open()) {
        qDebug() << "success DB connection";
    }
    else {
        qDebug() << "fail DB connection";
    }
    QString query = "CREATE TABLE temp_db1 ("
                    "id integer primary key,"
                    "date DATETIME,"
                    "illu VARCHAR(10),"
                    "temp VARCHAR(10),"
                    "humi VARCHAR(10))";
    QSqlQuery qry;
    if(!qry.exec(query))
    {

    }
    else
    {
        qDebug() << "create table";
    }
    connect(ui->pPBSearchButton,SIGNAL(clicked()),this,SLOT(slotSearchDb()));
    connect(ui->pPBDeleteButton,SIGNAL(clicked()),this,SLOT(slotDeleteDb()));
}

Tab6Database::~Tab6Database()
{
    delete ui;
}
void Tab6Database::slotTab6RecvData(QString recvData)
{
//    qDebug() << recvData;
    QDateTime dateTime = QDateTime::currentDateTime();
    QSqlQuery qry;
    QString query;

    recvData.replace("[","@");
    recvData.replace("]","@");
    QStringList qlist = recvData.split("@");
    QString illu = qlist[3];   //조도
    QString temp = qlist[4];    //온도
    QString humi = qlist[5];    //습도

    query = "insert into temp_db1(date,illu,temp,humi) values('" +
            dateTime.toString("yy/MM/dd hh:mm:ss") +
            "', '" + illu + "', '" + temp + "', '"+humi + "')";
    if(qry.exec(query))
    {
//        qDebug() << "insert Ok";
    }
    else
    {
        qDebug() << qry.lastError().text();
    }
}
void Tab6Database::slotSearchDb()
{
    QSqlQuery qry;
    QString query;
    QDateTime dateTimeFrom = ui->pDateTimeEditFrom->dateTime();
    QString strFrom = dateTimeFrom.toString("yy/MM/dd hh:mm:ss");
    QDateTime dateTimeTo = ui->pDateTimeEditTo->dateTime();
    QString strTo = dateTimeTo.toString("yy/MM/dd hh:mm:ss");

    int rowCount = 0;
    ui->pTableWidget->clearContents();
    query = "select * from temp_db1 where date>'"+strFrom+"' AND date < '" + strTo +"'";
    if(qry.exec(query)) {
        while(qry.next()) {
           rowCount++;
           ui->pTableWidget->setRowCount(rowCount);
           QTableWidgetItem *id = new QTableWidgetItem();
           QTableWidgetItem *date = new QTableWidgetItem();
           QTableWidgetItem *illu = new QTableWidgetItem();
           QTableWidgetItem *temp = new QTableWidgetItem();
           QTableWidgetItem *humi = new QTableWidgetItem();

           id->setText(qry.value("id").toString());
           date->setText(qry.value("date").toString());
           illu->setText(qry.value("illu").toString());
           temp->setText(qry.value("temp").toString());
           humi->setText(qry.value("humi").toString());
           ui->pTableWidget->setItem(rowCount-1,0,id);
           ui->pTableWidget->setItem(rowCount-1,1,date);
           ui->pTableWidget->setItem(rowCount-1,2,illu);
           ui->pTableWidget->setItem(rowCount-1,3,temp);
           ui->pTableWidget->setItem(rowCount-1,4,humi);
           id->setTextAlignment(Qt::AlignCenter);
           date->setTextAlignment(Qt::AlignCenter);
           illu->setTextAlignment(Qt::AlignCenter);
           temp->setTextAlignment(Qt::AlignCenter);
           humi->setTextAlignment(Qt::AlignCenter);
        }
    }
}
void Tab6Database::slotDeleteDb()
{
    QSqlQuery qry;
    QString query;
    QDateTime dateTimeFrom = ui->pDateTimeEditFrom->dateTime();
    QString strFrom = dateTimeFrom.toString("yy/MM/dd hh:mm:ss");
    QDateTime dateTimeTo = ui->pDateTimeEditTo->dateTime();
    QString strTo = dateTimeTo.toString("yy/MM/dd hh:mm:ss");

    query = "delete from temp_db1 where date >'" + strFrom + "' AND date < '"+ strTo + "'";
    if(qry.exec(query)) {
    }
}
