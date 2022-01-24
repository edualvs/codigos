#ifndef ALTERAR_H
#define ALTERAR_H

#include <QDialog>

namespace Ui {
  class alterar;
}

class alterar : public QDialog
{
  Q_OBJECT

public:
  explicit alterar(int oq, QWidget *parent = nullptr);
  ~alterar();

private slots:
  void on_alterar_clicked();

private:
  Ui::alterar *ui;
};

#endif // ALTERAR_H
