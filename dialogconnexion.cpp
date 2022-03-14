#include "dialogconnexion.h"
#include "ui_dialogconnexion.h"
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QFile>
#include <QFileDialog>

#include <QDebug>

DialogConnexion::DialogConnexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConnexion)
{
    ui->setupUi(this);

    //on dit que le driver par défaut est server
    driver = "QMYSQL";

    //on cache le bouton à l'ouverture de l'app
    ui->pushButtonFind->setVisible(false);
}

DialogConnexion::~DialogConnexion()
{
    delete ui;
}

QString DialogConnexion::getUsername()
{
    return username;
}

QString DialogConnexion::getPassword()
{
    return password;
}

QString DialogConnexion::getDatabaseName()
{
    return databaseName;
}

QString DialogConnexion::getDatabaseIP()
{
    return databaseIP;
}

void DialogConnexion::on_pushButtonDialogDelete_clicked()
{
    ui->lineEditDialogUsername->setText("");
    ui->lineEditDialogPassword->setText("");
    ui->lineEditDialogDatabaseName->setText("");
    ui->lineEditDatabaseIP->setText("");
}

void DialogConnexion::on_pushButtonDialogConnection_clicked()
{
    //on recupere les info
    username = ui->lineEditDialogUsername->text();
    qDebug()<<username;
    password = ui->lineEditDialogPassword->text();
    qDebug()<<password;
    databaseName = ui->lineEditDialogDatabaseName->text();
    qDebug()<<databaseName;
    databaseIP = ui->lineEditDatabaseIP->text();
    qDebug()<<databaseIP;

    qDebug()<<driver;

    if(driver == "QMYSQL") {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
              db.setHostName(databaseIP);
              db.setDatabaseName(databaseName);
              db.setUserName(username);
              db.setPassword(password);
              bool ok = db.open();
              qDebug()<<"SQL "<<ok;

              if (ok)
                  accept();
              else
              ui->labelError->setText("An error has occurred !");
    }

    if(driver == "QSQLITE") {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
              db.setDatabaseName(databaseName);
              bool ok = db.open();
              qDebug()<<"SQLITE"<<ok;

              if (ok)
                  accept();
              else
              ui->labelError->setText("An error has occurred !");
    }

}

void DialogConnexion::on_pushButtonClose_clicked()
{
    close();
}


void DialogConnexion::on_pushButtonDbServer_clicked()
{
    ui->lineEditDialogUsername->setVisible(true);
    ui->labelDialogUsername->setVisible(true);
    ui->lineEditDialogPassword->setVisible(true);
    ui->labelDialogPassword->setVisible(true);
    ui->lineEditDialogDatabaseName->setVisible(true);
    ui->labelDialogDatabaseName->setVisible(true);
    ui->lineEditDatabaseIP->setVisible(true);
    ui->labelDialogDatabaseIP->setVisible(true);
    ui->pushButtonFind->setVisible(false);

    driver = "QMYSQL";
}


void DialogConnexion::on_pushButtonMonoDb_clicked()
{
    ui->lineEditDialogUsername->setVisible(false);
    ui->labelDialogUsername->setVisible(false);
    ui->lineEditDialogPassword->setVisible(false);
    ui->labelDialogPassword->setVisible(false);
    ui->lineEditDialogDatabaseName->setVisible(true);
    ui->labelDialogDatabaseName->setVisible(true);
    ui->lineEditDatabaseIP->setVisible(false);
    ui->labelDialogDatabaseIP->setVisible(false);
    ui->pushButtonFind->setVisible(true);


    driver = "QSQLITE";


}


void DialogConnexion::on_pushButtonFind_clicked()
{
    QString filePath =QFileDialog::getOpenFileName(this, "Choose a database");
    ui->lineEditDialogDatabaseName->setText(filePath);
}

