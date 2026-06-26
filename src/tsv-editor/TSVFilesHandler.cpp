// #include <src/tsv-editor/TSVFilesHandler.h>
#include "TSVFilesHandler.h"

#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QStringList>

#include <vector>

TSVFilesHandler::TSVFilesHandler()
{
}

bool TSVFilesHandler::read(QString fileName, TSVTable &table)
{
  QFile file(fileName);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    qDebug() << "can't open file for reading: " << fileName << file.errorString();
    return false;
  }

  QTextStream stream(&file);
  stream.setCodec("UTF-8");

  if (stream.atEnd())
  {
    qDebug() << "can't read because file is empty";
    return false;
  }

  QString headerLine = stream.readLine();
  QStringList headersList = headerLine.split('\t', Qt::KeepEmptyParts);

  if (headersList.isEmpty())
  {
    qDebug() << "no headers";
    return false;
  }

  std::vector<QStringList> rows;
  QString line;
  QStringList rowCells;

  while (!stream.atEnd())
  {
    line = stream.readLine();
    rowCells = line.split('\t', Qt::KeepEmptyParts);
    if (rowCells.size() > headersList.size())
    {
      qDebug() << "too many cells";
    }

    rows.push_back(rowCells);
  }

  int rowCount = rowCells.size();
  int columnCount = headersList.size();

  if (rowCount == 0)
  {
    rowCount = 1;
  }

  TSVTable newTable(rowCount, columnCount);

  for (int column = 0; column < columnCount; column++)
  {
    newTable.setHeaderData(column, headersList[column].toStdString());
  }

  for (int row = 0; row < rowCount; row++)
  {
    for (int column = 0; column < columnCount; column++)
    {
      newTable.setCellData(row, column, rows[row][column].toStdString());
    }
  }

  table = newTable;
  return true;
}

bool TSVFilesHandler::write(QString fileName, const TSVTable &table)
{
  QFile file(fileName);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    qDebug() << "can't open file for reading: " << fileName << file.errorString();
    return false;
  }

  QTextStream stream(&file);
  stream.setCodec("UTF-8");

  for (int column = 0; column < table.columnCount(); column++)
  {
    if (column != 0)
    {
      stream << '\t';
    }

    stream << QString::fromStdString(table.getHeaderData(column));
  }

  stream << '\n';

  for (int row = 0; row < table.rowCount(); row++)
  {
    for (int column = 0; column < table.columnCount(); column++)
    {
      if (column != 0)
      {
        stream << '\t';
      }

      stream << QString::fromStdString(table.getCellData(row, column));
    }
    stream << '\n';
  }
  return true;
}