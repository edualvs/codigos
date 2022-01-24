#include "telaprincipal.h"
#include "ui_telaprincipal.h"
#include "sobre.h"
#include "nota.h"
#include "alterar.h"
#include "abrir.h"

int const telaprincipal::EXIT_CODE_REBOOT = -123456789;
QAction* actionReboot;

telaprincipal::telaprincipal(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::telaprincipal)
{
  ui->setupUi(this);

   actionReboot = new QAction( this );
}

telaprincipal::~telaprincipal()
{
  delete ui;
}

void telaprincipal::on_actionSair_triggered()
{
  actionReboot->trigger();
  qApp->exit( telaprincipal::EXIT_CODE_REBOOT );
}

void telaprincipal::on_actionSobre_triggered()
{
  sobre sobre;
  sobre.exec();
}

void telaprincipal::on_fechar_clicked()
{
  QMessageBox::StandardButton resposta= QMessageBox::question(this,"Confirmação","Realmente deseja fechar o programa? ", QMessageBox::Yes | QMessageBox::No);

  if (resposta == QMessageBox::Yes) {
    QApplication::quit();
  }
}

void telaprincipal::on_actionFechar_triggered()
{
  QMessageBox::StandardButton resposta= QMessageBox::question(this,"Confirmação","Realmente deseja fechar o programa? ", QMessageBox::Yes | QMessageBox::No);

  if (resposta == QMessageBox::Yes) {
    QApplication::quit();
  }
}

void telaprincipal::on_actionNova_triggered()
{
  nota novanota;
  novanota.exec();
}

void telaprincipal::on_actionNome_triggered()
{

}

void telaprincipal::on_actionEmail_triggered()
{

}

void telaprincipal::on_actionSenha_triggered()
{

}

void telaprincipal::on_actionAbrir_2_triggered()
{
  abrir* abri= new abrir;
  abri->setModal(false);
  abri->show();
}
