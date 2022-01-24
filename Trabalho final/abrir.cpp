#include "abrir.h"
#include "ui_abrir.h"
#include "nota.h"

QString pasta, nomeuser, f;

abrir::abrir(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::abrir)
{
  ui->setupUi(this);
  pasta= QApplication::applicationDirPath();
  QFile user(pasta+"/usuario.txt");

  if (!user.open(QFile::ReadOnly|QFile::Text)) {
    QMessageBox::warning(this,"ERRO","Não foi possível recuperar o usuário do Banco!");
  }

  QTextStream ler(&user);
  nomeuser= ler.readAll();
  user.close();

  QDir directory(pasta+"/"+nomeuser);
  QStringList notes = directory.entryList(QStringList() << "*.txt", QDir::Files);
  ui->escolha->addItems(notes);
}

abrir::~abrir()
{
  delete ui;
}

void abrir::on_abrir_2_clicked()
{
  nota n;

  QFile pegar(pasta+"/"+nomeuser+"/"+f);

  if (!pegar.open(QFile::ReadOnly|QFile::Text)) {
    QMessageBox::warning(this,"ERRO","Não foi possível ler o arquivo!");
  }

  QTextStream ler(&pegar);
  QString x= ler.readAll();
  pegar.close();

  n.exec();
  n.abreNome= f;
  n.abreTexto= x;

}

void abrir::on_apagar_clicked()
{
  QDir(pasta+"/"+nomeuser).remove(f);
  ui->escolha->removeItem(ui->escolha->currentIndex());
  if (ui->escolha->currentText() == "Escolha uma nota")
    ui->textBrowser->setText("");
}

void abrir::on_escolha_currentIndexChanged(const QString &arg1)
{
  f= arg1;
  QFile pegar(pasta+"/"+nomeuser+"/"+arg1);
  if (arg1 == "Escolha uma nota") {
      return;
  }
  if (!pegar.open(QFile::ReadOnly|QFile::Text)) {
    QMessageBox::warning(this,"ERRO","Não foi possível ler o arquivo!");
  }

  QTextStream ler(&pegar);
  ui->textBrowser->setText(ler.readAll());
  pegar.close();
}
