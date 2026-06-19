#pragma once 

#include <src/tsv-editor/TSVTableModel.h>
#include <src/tsv-editor/TSVSortFilterProxyModel.h>

#include <QTableView>

class TSVTableView: public QTableView
{
  Q_OBJECT
public:
  TSVTableView(TSVTableModel* model, QWidget *parent = nullptr);

  int selectedRow() const;
  int selectedColumn() const;
private:
  void setTableView(QAbstractItemModel* model);

  TSVSortFilterProxyModel* m_sortModel;
};