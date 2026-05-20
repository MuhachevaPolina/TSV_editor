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
private:
  QLabel *m_statusLabel;

  QPushButton *m_quitButton;
  QPushButton* m_addRowButton;

  QVBoxLayout* layout;
  TSVTableView* m_tableViewer;
};