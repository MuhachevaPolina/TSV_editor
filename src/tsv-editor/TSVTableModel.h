#pragma once 

#include <src/tsv-editor/TSVTable.h>

#include <QAbstractTableModel>

class TSVTableModel: public QAbstractTableModel
{
  Q_OBJECT

public:
  TSVTableModel(QObject *parent = nullptr);
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
private:
  TSVTable m_table;
};