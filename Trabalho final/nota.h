#ifndef NOTA_H
#define NOTA_H

#include <QDialog>
#include <QtSql>
#include <QFileInfo>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

namespace Ui {
  class nota;
}

class nota : public QDialog
{
  Q_OBJECT
friend class abrir;

public:
  explicit nota(QWidget *parent = nullptr);
  ~nota();
  QString abreTexto, abreNome;

friend class abrir;

private slots:
  void on_fechar_clicked();

  void on_salvar_clicked();

private:
  Ui::nota *ui;
};

#endif // NOTA_H
