#pragma once 

#include <src/tsv-editor/TSVTable.h>

#include <QAbstractTableModel>
#include <QVariant>

class TSVTableModel: public QAbstractTableModel
{
  Q_OBJECT

public:
  TSVTableModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
  Qt::ItemFlags flags(const QModelIndex& index) const override;
  bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
  bool insertColumns(int column, int count, const QModelIndex& parent = QModelIndex()) override;
  bool setHeaderData(int section, Qt::Orientation, const QVariant& value, int role = Qt::EditRole) override;
// private slots:

private:
  TSVTable m_table;
};