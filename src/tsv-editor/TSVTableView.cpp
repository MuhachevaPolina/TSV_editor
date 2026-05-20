#include <src/tsv-editor/TSVTableView.h>

TSVTableView::TSVTableView(TSVTableModel* model, QWidget *parent)
{
  this->setTableView(model);
}

void TSVTableView::setTableView(TSVTableModel* model)
{
  this->setModel(model);
}