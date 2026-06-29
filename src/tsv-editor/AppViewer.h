#pragma once

#include <src/tsv-editor/TSVTableView.h>
#include <src/tsv-editor/TSVFilesHandler.h>

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
  void deleteColumn();
  void deleteRow();
  void headerDoubleClicked(int idx);
  void openFile();
  void saveFile();
  void updateDeleteButtons();

private:
  QLabel *m_statusLabel;

  QPushButton *m_quitButton;
  QPushButton* m_addRowButton;
  QPushButton* m_addColumnButton;
  QPushButton* m_deleteColumnButton;
  QPushButton* m_deleteRowButton;
  QPushButton* m_openFileButton;
  QPushButton* m_saveFileButton;

  QHBoxLayout* m_horizLayout;
  QHBoxLayout* m_tmpUpperHorizLayout;
  QVBoxLayout* layout;
  TSVTableView* m_tableViewer;
  TSVFilesHandler m_filesHandler;
};