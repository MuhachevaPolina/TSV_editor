#include <src/tsv-editor/TSVTableModel.h>

#include <QString>

int TSVTableModel::rowCount(const QModelIndex &parent = QModelIndex()) const
{
  return this->m_table.rowCount();
}

int TSVTableModel::columnCount(const QModelIndex &parent = QModelIndex()) const
{
  return this->m_table.columnCount();
}

QVariant TSVTableModel::data(const QModelIndex &index, int role = Qt::DisplayRole) const
{
  int row = index.row();
  int column = index.column();
  if (role == Qt::DisplayRole)
  {
    QString answer = QString::fromStdString(this->m_table.getCellData(row, column));
// look how to make answer to my situation
    return QVariant(answer);
  }
  return QVariant();
}

QVariant TSVTableModel::headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const 
{
  if (role == Qt::DisplayRole)
  {
    QString answer = QString::fromStdString(this->m_table.getHeaderData(section));
    return QVariant(answer);
  }
  return QVariant();
}

bool TSVTableModel::setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)
{
  int row = index.row();
  int column = index.column();
  if (role == Qt::EditRole)
  {
    this->m_table.setCellData(row, column, value.toString().toStdString());
    return true;
  }
  return false;
  // should do dataChanged signal
}

Qt::ItemFlags TSVTableModel::flags(const QModelIndex& index) const
{
  int row = index.row();
  int column = index.column();
  if(row < this->m_table.rowCount() && column < this->m_table.columnCount())
  {
    return Qt::ItemIsEditable;
  }
}

