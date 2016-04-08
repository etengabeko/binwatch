#include "bwatch.h"

#include <QApplication>

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  binwatch::BinaryWatch bw;
  bw.setMaximumSize(bw.size());
  bw.show();
  return app.exec();
}
