#include "alterar.h"
#include "ui_alterar.h"
#include "telaprincipal.h"

alterar::alterar(int oq, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::alterar)
{
  ui->setupUi(this);

  if (oq == 1) {
      ui->label->setText("1");
    }
}

alterar::~alterar()
{
  delete ui;
}

void alterar::on_alterar_clicked()
{
    QString novo= ui->lineEdit->text();
    QString campo= ui->label->text();
    QSqlQuery qry;

    qry.prepare("update Users set nome=?, senha=?, email=? where ");
   /* qry.bindValue(0, user);
    qry.bindValue(1, password);
    qry.bindValue(2, email);
   */
    if (qry.exec()) {
      QMessageBox::information(this,"Alterar","Informação alterada com sucesso!!");
    }
    else {
      QMessageBox::warning(this,"ERRO","Houve um problema com o banco de dados, não foi possível alterar as informações!");
    }
   // dblogin.close();


}
