#include <src/tsv-editor/TSVTableModel.h>

#include <QString>

TSVTableModel::TSVTableModel(QObject *parent)
{
}

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
  if (!index.isValid())
  {
    return QVariant();
  }

  int row = index.row();
  int column = index.column();
  if (role == Qt::DisplayRole || role == Qt::EditRole)
  {
    if (row < this->m_table.rowCount() && column < this->m_table.columnCount())
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
    if (orientation == Qt::Horizontal)
    {
      QString answer = QString::fromStdString(this->m_table.getHeaderData(section));
      return QVariant(answer);
    }
    if (orientation == Qt::Vertical)
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
  if (!index.isValid() || row >= this->m_table.rowCount() || column >= this->m_table.columnCount())
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

Qt::ItemFlags TSVTableModel::flags(const QModelIndex &index) const
{
  int row = index.row();
  int column = index.column();
  if (index.isValid())
  {
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
  }
  return Qt::NoItemFlags;
}

bool TSVTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
  this->beginInsertRows(parent, row, row + count - 1);
  for (int i = 0; i < count; ++i)
  {
    this->m_table.addRow(row + i);
  }
  this->endInsertRows();
  return true;
}

bool TSVTableModel::insertColumns(int column, int count, const QModelIndex &parent)
{
  this->beginInsertColumns(parent, column, column + count - 1);
  for (int i = 0; i < count; ++i)
  {
    this->m_table.addColumn("some header", column + i);
  }
  this->endInsertColumns();
  return true;
}

bool TSVTableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
  if (role != Qt::EditRole)
  {
    return false;
  }

  if (orientation == Qt::Horizontal)
  {
    if (section < 0 || section >= this->m_table.columnCount())
    {
      return false;
    }
    this->m_table.setHeaderData(section, value.toString().toStdString());
    emit headerDataChanged(orientation, section, section);
    return true;
  }

  return false;
}

bool TSVTableModel::removeColumns(int column, int count, const QModelIndex &parent)
{
  this->beginRemoveColumns(parent, column, column + count - 1);

  for (int i = 0; i < count; ++i)
  {
    this->m_table.deleteColumn(column);
  }

  this->endRemoveColumns();
  
  return true;
}

bool TSVTableModel::removeRows(int row, int count, const QModelIndex& parent)
{
  this->beginRemoveRows(parent, row, row + count - 1);

  for (int i = 0; i < count; ++i)
  {
    this->m_table.deleteRow(row);
  }

  this->endRemoveRows();
  
  return true;
}

const TSVTable& TSVTableModel::getTable() const
{
  return this->m_table;
}

void TSVTableModel::setTable(TSVTable& table)
{
  this->beginResetModel();

  this->m_table = table;

  this->endResetModel();
}