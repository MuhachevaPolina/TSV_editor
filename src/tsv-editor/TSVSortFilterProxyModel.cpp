#include <src/tsv-editor/TSVSortFilterProxyModel.h>

TSVSortFilterProxyModel::TSVSortFilterProxyModel(QObject* parent): QSortFilterProxyModel(parent)
{}

QVariant TSVSortFilterProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if(orientation == Qt::Vertical && role == Qt::DisplayRole)
  {
    return section + 1;
  }
  
  return QSortFilterProxyModel::headerData(section, orientation, role);
}