// Programa baseado no codigo disponibilizado em:
// Derek Molloy, Exploring Raspberry Pi: Interfacing to the Real World with Embedded Linux,
// Wiley 2016, ISBN 978-1-119-1868-1, http://www.exploringrpi.com/

#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
int main(int argc, char *argv[ ]){
   QApplication app(argc, argv);
   QLabel label("Um texto qualquer...");
   label.resize(200, 40);
   label.show();
   return app.exec();
}
