#ifndef CADASTRO_H
#define CADASTRO_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
  class cadastro;
}

class cadastro : public QDialog
{
  Q_OBJECT

public:
  explicit cadastro(QWidget *parent = nullptr);
  ~cadastro();

private slots:
  void on_voltarButton_clicked();

  void on_cadButton_clicked();

private:
  Ui::cadastro *ui;
  QSqlDatabase dblogin;
};

#endif // CADASTRO_H
