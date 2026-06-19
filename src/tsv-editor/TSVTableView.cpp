#include <src/tsv-editor/TSVTableView.h>

#include <QHeaderView>

TSVTableView::TSVTableView(TSVTableModel* model, QWidget *parent)
{
  this->m_sortModel = new TSVSortFilterProxyModel(this);
  this->m_sortModel->setSourceModel(model);
  this->m_sortModel->setDynamicSortFilter(false);
  this->setTableView(this->m_sortModel);
  this->setSortingEnabled(true);
  this->horizontalHeader()->setSectionsClickable(true);
}

void TSVTableView::setTableView(QAbstractItemModel* model)
{
  this->setModel(model);
}