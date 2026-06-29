#include <src/tsv-editor/TSVTableView.h>

#include <QHeaderView>

TSVTableView::TSVTableView(TSVTableModel* model, QWidget *parent): m_tableModel(model)
{
  this->m_sortModel = new TSVSortFilterProxyModel(this);
  this->m_sortModel->setSourceModel(this->m_tableModel);
  this->m_sortModel->setDynamicSortFilter(false);
  this->setTableView(this->m_sortModel);
  this->setSortingEnabled(true);
  this->horizontalHeader()->setSectionsClickable(true);
}

void TSVTableView::setTableView(QAbstractItemModel* model)
{
  this->setModel(model);
}

int TSVTableView::selectedRow() const
{
  QModelIndex idx = this->currentIndex();

  if(!idx.isValid())
  {
    return -1;
  }

  return this->m_sortModel->mapToSource(idx).row();
}

int TSVTableView::selectedColumn() const
{
  QModelIndex idx = this->currentIndex();

  if(!idx.isValid())
  {
    return -1;
  }

  return this->m_sortModel->mapToSource(idx).column();
}

TSVTableModel* TSVTableView::getTableModel()
{
  return this->m_tableModel;
}

void TSVTableView::mousePressEvent(QMouseEvent* event)
{
  QModelIndex idx = this->indexAt(event->pos());

  if(!idx.isValid())
  {
    this->clearSelection();
    this->setCurrentIndex(QModelIndex());
    event->accept();
    return;
  }

  QTableView::mousePressEvent(event);
}