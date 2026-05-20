#include <src/tsv-editor/AppViewer.h>

#include <QApplication>

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  AppViewer viewer;
  viewer.show();

  return app.exec();
}