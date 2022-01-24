#include "telaprincipal.h"
#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  int currentExitCode = 0;
  QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);

  do {
    QApplication a(argc, argv);
    login log;
    log.exec();
    telaprincipal telap;
    if (log.logado)
      telap.show();
    currentExitCode = a.exec();
  } while( currentExitCode == telaprincipal::EXIT_CODE_REBOOT );

  return currentExitCode;
}
