#pragma once

#include <src/tsv-editor/TSVTable.h>

#include <QString>

class TSVFilesHandler
{
public:
  TSVFilesHandler();

  bool write(QString fileName, const TSVTable& table);
  bool read(QString fileName, TSVTable& table);
};