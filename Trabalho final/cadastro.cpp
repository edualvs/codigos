#include "cadastro.h"
#include "ui_cadastro.h"

cadastro::cadastro(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::cadastro)
{
  ui->setupUi(this);
}

cadastro::~cadastro()
{
  delete ui;
}

void cadastro::on_voltarButton_clicked()
{
  this->close();
}

void cadastro::on_cadButton_clicked()
{
  QString user = ui->txtnome->text();
  QString email = ui->txtemail->text();
  QString password = ui->txtsenha->text();
  QString reppas = ui->txtrepsenha->text();
  QSqlQuery qry;
  int c=0;

  if (!ui->termos->isChecked()) {
    QMessageBox::information(this,"Oops","Parece que você não aceitou os termos de uso!");
    c++;
    }
  else if (user == "" || email == "" || password == "" || reppas == "") {
    QMessageBox::information(this,"Oops","Um ou mais campos não foram preenchidos");
    if (user == "")
      ui->txtnome->setFocus();
    else if (email == "")
      ui->txtemail->setFocus();
    else if (password == "")
      ui->txtsenha->setFocus();
    else if (reppas == "")
      ui->txtrepsenha->setFocus();
    c++;
  }
  else if (password != reppas) {
    QMessageBox::information(this,"Oops","As senhas digitadas não são iguais!");
    ui->txtsenha->clear();
    ui->txtrepsenha->clear();
    ui->txtsenha->setFocus();
    c++;
  }
  else {
    qry.prepare("select * from Users where email=?");
    qry.bindValue(0, email);
    int count=0;
    while(qry.next())
      count++;

    if (count >= 1) {
      QMessageBox::information(this,"Oops","Já existe uma conta com esse email");
      ui->txtemail->clear();
      ui->txtsenha->clear();
      ui->txtrepsenha->clear();
      ui->txtemail->setFocus();
      c++;
    }
  }
  if (c == 0) {
    qry.prepare("insert into Users (nome, senha, email) values(?,?,?)");
    qry.bindValue(0, user);
    qry.bindValue(1, password);
    qry.bindValue(2, email);

    if (qry.exec()) {
      QMessageBox::information(this,"Cadastro","Usuário cadastrado com sucesso!!");
      ui->txtnome->clear();
      ui->txtemail->clear();
      ui->txtsenha->clear();
      ui->txtrepsenha->clear();
      ui->txtnome->setFocus();
    }
    else {
      QMessageBox::warning(this,"ERRO","Houve um problema com o banco de dados, não foi possível cadastrar o usuário!");
    }
    dblogin.close();
  }
}
