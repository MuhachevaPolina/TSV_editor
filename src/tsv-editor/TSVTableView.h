#pragma once 

#include <src/tsv-editor/TSVTableModel.h>
#include <src/tsv-editor/TSVSortFilterProxyModel.h>

#include <QTableView>
#include <QMouseEvent>

class TSVTableView: public QTableView
{
  Q_OBJECT
public:
  TSVTableView(TSVTableModel* model, QWidget *parent = nullptr);

  int selectedRow() const;
  int selectedColumn() const;

  TSVTableModel* getTableModel();

protected:
  void mousePressEvent(QMouseEvent* event) override;

private:
  void setTableView(QAbstractItemModel* model);

  TSVSortFilterProxyModel* m_sortModel;
  TSVTableModel* m_tableModel;
};