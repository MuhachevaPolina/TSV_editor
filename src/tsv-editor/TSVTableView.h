#pragma once 

#include <QTableView>

class TSVTableView: public QTableView
{
  Q_OBJECT
public:
  TSVTableView(QWidget *parent = nullptr);

  int selectedRow() const;
  int selectedColumn() const;
private:
  void setTableView();
};