#pragma once 

#include <src/tsv-editor/TSVTableModel.h>

#include <QTableView>
#include <QSortFilterProxyModel>

class TSVTableView: public QTableView
{
  Q_OBJECT
public:
  TSVTableView(TSVTableModel* model, QWidget *parent = nullptr);

  int selectedRow() const;
  int selectedColumn() const;
private:
  void setTableView(QAbstractItemModel* model);

  QSortFilterProxyModel* m_sortModel;
};