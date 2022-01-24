#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <cadastro.h>
#include <telaprincipal.h>
#include <QFile>
#include <QTextStream>

namespace Ui {
  class login;
}

class login : public QDialog
{
  Q_OBJECT

public:
  explicit login(QWidget *parent = nullptr);
  ~login();
  bool logado;

private slots:
  void on_loginButton_clicked();

  void on_fecharButton_clicked();

  void on_cadastroButton_clicked();



private:
  Ui::login *ui;
  QSqlDatabase dblogin;
  telaprincipal *telap;
  cadastro *cad;
};

#endif // LOGIN_H
