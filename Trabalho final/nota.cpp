#include "nota.h"
#include "ui_nota.h"
#include "login.h"

int cont=1;
QString usuario, caminho;

nota::nota(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::nota)
{
  ui->setupUi(this);

  caminho =qApp->applicationDirPath();
  QFile user(caminho+"\\usuario.txt");

  if (!user.open(QFile::ReadOnly|QFile::Text)) {
    QMessageBox::warning(this,"ERRO","Não foi possível recuperar o usuário do Banco!");
  }

  QTextStream ler(&user);
  usuario= ler.readAll();
  user.close();

  if(!(abreNome == "" || abreTexto == "")) {
      ui->lineEdit->setText(abreNome);
      ui->plainTextEdit->setPlainText(abreTexto);
  }
}

nota::~nota()
{
  delete ui;
}

void nota::on_fechar_clicked()
{
  QString texto= ui->plainTextEdit->toPlainText();
  QString nome= ui->lineEdit->text();
  QString local= caminho+"/"+usuario+"/"+nome+".txt";
  QFile nota(local);

  if (!QDir(caminho+"/"+usuario).exists())
    QDir().mkdir(caminho+"/"+usuario);

  if (cont == 0) {
    if (!nota.open(QFile::ReadOnly|QFile::Text)) {
      QMessageBox::warning(this,"ERRO","Não foi possível abrir o arquivo!");
    }

    QTextStream ler(&nota);
    QString text= ler.readAll();
    nota.close();

    if (text == texto) {
      this->close();
    }
  }
  else {
    if (nome == "") {
        QMessageBox::warning(this,"Oops","Você esqueceu de dar um nome para a nota!");
        return;
    }
    QMessageBox::StandardButton resposta= QMessageBox::question(this,"Confirmação","O arquivo não foi salvo, deseja salvar antes de sair?", QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes) {
        if (!nota.open(QFile::WriteOnly|QFile::Text)) {
            QMessageBox::warning(this,"ERRO","Não foi possível salvar o arquivo!");
        }

        QTextStream salvar(&nota);
        salvar << texto;
        nota.flush();
        nota.close();
    }
  }
  this->close();
}

void nota::on_salvar_clicked()
{
  QString nome= ui->lineEdit->text();
  QString local= caminho+"/"+usuario+"/"+nome+".txt";
  if (nome == "") {
    QMessageBox::warning(this,"Oops","Você esqueceu de dar um nome para a nota!");
    return;
  }

  cont=0;
  QFile nota(local);
  this->setWindowTitle(nome);
  if (!QDir(caminho+"/"+usuario).exists())
    QDir().mkdir(caminho+"/"+usuario);

  if (!nota.open(QFile::WriteOnly|QFile::Text)) {
    QMessageBox::warning(this,"ERRO","Não foi possível salvar o arquivo!");
  }

  QTextStream salvar(&nota);
  QString texto= ui->plainTextEdit->toPlainText();
  salvar << texto;
  nota.flush();
  nota.close();
}
