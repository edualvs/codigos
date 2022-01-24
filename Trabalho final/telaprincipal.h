#ifndef TELAPRINCIPAL_H
#define TELAPRINCIPAL_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>

namespace Ui {
  class telaprincipal;
}

class telaprincipal : public QMainWindow
{
  Q_OBJECT

public:
  explicit telaprincipal(QWidget *parent = nullptr);
  ~telaprincipal();
  static int const EXIT_CODE_REBOOT;

private slots:
  void on_actionSair_triggered();

  void on_actionSobre_triggered();

  void on_fechar_clicked();

  void on_actionFechar_triggered();

  void on_actionNova_triggered();

  void on_actionNome_triggered();

  void on_actionEmail_triggered();

  void on_actionSenha_triggered();

  void on_actionAbrir_2_triggered();

private:
  Ui::telaprincipal *ui;
};

#endif // TELAPRINCIPAL_H
