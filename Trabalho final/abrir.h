#ifndef ABRIR_H
#define ABRIR_H

#include <QDialog>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include "ui_nota.h"

namespace Ui {
  class abrir;
}

class abrir : public QDialog
{
  Q_OBJECT

public:
  explicit abrir(QWidget *parent = nullptr);
  ~abrir();

public slots:
  void on_abrir_2_clicked();

  void on_apagar_clicked();

  void abre(QString, QString);

private slots:

  void on_escolha_currentIndexChanged(const QString &arg1);

private:
  Ui::abrir *ui;
};

#endif // ABRIR_H
