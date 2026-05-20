#include <src/tsv-editor/TSVTableModel.h>

#include <QString>

TSVTableModel::TSVTableModel(QObject *parent)
{}

int TSVTableModel::rowCount(const QModelIndex &parent) const
{
  return this->m_table.rowCount();
}

int TSVTableModel::columnCount(const QModelIndex &parent) const
{
  return this->m_table.columnCount();
}

QVariant TSVTableModel::data(const QModelIndex &index, int role) const
{
  if(!index.isValid())
  {
    return QVariant();
  }

  int row = index.row();
  int column = index.column();
  if (role == Qt::DisplayRole || role == Qt::EditRole)
  {
    if(row < this->m_table.rowCount() && column < this->m_table.columnCount())
    {
      QString answer = QString::fromStdString(this->m_table.getCellData(row, column));
      return QVariant(answer);
    }
  }
  return QVariant();
}

QVariant TSVTableModel::headerData(int section, Qt::Orientation orientation, int role) const 
{
  if (role == Qt::DisplayRole)
  {
    if(orientation == Qt::Horizontal)
    {
      QString answer = QString::fromStdString(this->m_table.getHeaderData(section));
      return QVariant(answer);
    }
    if(orientation == Qt::Vertical)
    {
      QString answer = QString::fromStdString(std::to_string(section));
      return QVariant(answer);
    }
  }
  return QVariant();
}

bool TSVTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  int row = index.row();
  int column = index.column();
  if(!index.isValid() || row >= this->m_table.rowCount() || column >= this->m_table.columnCount())
  {
    return false;
  }

  if (role == Qt::EditRole)
  {
    this->m_table.setCellData(row, column, value.toString().toStdString());
    emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
    return true;
  }

  return false;
}

Qt::ItemFlags TSVTableModel::flags(const QModelIndex& index) const
{
  int row = index.row();
  int column = index.column();
  if(row < this->m_table.rowCount() && column < this->m_table.columnCount())
  {
    return Qt::ItemIsEditable;
  }
  return Qt::NoItemFlags;
}

