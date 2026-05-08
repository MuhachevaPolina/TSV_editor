#pragma once

#include <src/tsv-editor/TSVTableView.h>

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class AppViewer: public QWidget
{
  Q_OBJECT
public:
  AppViewer(QWidget* parent = nullptr);
private:
  QLabel *m_statusLabel;
  QPushButton *m_quitButton;
  TSVTableView m_tableViewer;
};