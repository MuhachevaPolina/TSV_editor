#pragma once

#include <src/tsv-editor/TSVTableView.h>

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include <QVBoxLayout>

class AppViewer: public QWidget
{
  Q_OBJECT
public:
  AppViewer(QWidget* parent = nullptr);

private slots:
  void addRow();
  void addColumn();
  void deleteColumn(int colNum);
  void headerDoubleClicked(int idx);

private:
  QLabel *m_statusLabel;

  QPushButton *m_quitButton;
  QPushButton* m_addRowButton;
  QPushButton* m_addColumnButton;
  QPushButton* m_deleteColumnButton;
  QPushButton* m_deleteRowButton;

  QHBoxLayout* m_horizLayout;
  QVBoxLayout* layout;
  TSVTableView* m_tableViewer;
};