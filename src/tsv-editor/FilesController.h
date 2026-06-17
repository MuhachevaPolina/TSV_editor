#pragma once

#include <src/tsv-editor/TSVFilesHandler.h>

#include <QObject>

class FilesController: public QObject
{
  Q_OBJECT
public:

private:
  TSVFilesHandler m_filesHandler;
};
