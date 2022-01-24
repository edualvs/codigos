#include "login.h"
#include "ui_login.h"
#include "cadastro.h"
#include "nota.h"

QString dir;
QString a;

login::login(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::login)
{
  ui->setupUi(this);
  logado= false;
  dir=qApp->applicationDirPath();
  QString banco= dir+"/DataBase/login.db";

  dblogin=QSqlDatabase::addDatabase("QSQLITE");
  dblogin.setDatabaseName(banco);

  if (!dblogin.open()) {
    ui->status->setText("ERRO - Banco de dados não aberto");
  }
}

login::~login() {
  delete ui;
}

void login::on_loginButton_clicked() {
  QString user = ui->txtuser->text();
  QString password = ui->txtpasswd->text();
  QSqlQuery qry;

  if (!dblogin.isOpen()) {
    ui->txtpasswd->clear();
    ui->txtpasswd->setFocus();
    ui->txtpasswd->setCursorPosition(0);
    QMessageBox::critical(this,"ERRO","ERRO - Banco de dados não aberto");
    return;
  }

  qry.prepare("select nome from Users where email=? and senha=?");
  qry.bindValue(0, user);
  qry.bindValue(1, password);

  if(qry.exec()) {
    int count=0;
    while(qry.next()) {
      a= qry.value(0).toString();
      count++;
    }

    if (count == 1) {
      dblogin.close();
      QFile user(dir+"/usuario.txt");

      if (!user.open(QFile::WriteOnly|QFile::Text)) {
        QMessageBox::warning(this,"ERRO","Não foi possível abrir o arquivo!");
      }

      QTextStream salvar(&user);
      salvar << a;
      user.flush();
      user.close();

      ui->errologin->setText("");
      logado= true;
      this->hide();
    }

    else {
      ui->txtpasswd->clear();
      ui->txtpasswd->setFocus();
      ui->txtpasswd->setCursorPosition(0);
      ui->errologin->setText("Usuário ou Senha incorretos!");
    }
  }

  else {
    qDebug() << qry.lastError();
  }
}

void login::on_cadastroButton_clicked() {
  cadastro cad;
  cad.setModal(true);
  cad.exec();
}

void login::on_fecharButton_clicked() {
  QMessageBox::question(this,"Confirmação","Realmente deseja fechar o programa? ", QMessageBox::Yes | QMessageBox::No);

  if (QMessageBox::Yes) {
    QApplication::quit();
  }
}
