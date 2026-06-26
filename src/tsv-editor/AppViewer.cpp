#include <src/tsv-editor/AppViewer.h>
#include <src/tsv-editor/TSVTableModel.h>

#include <QHBoxLayout>
#include <QHeaderView>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>

AppViewer::AppViewer(QWidget *parent) : QWidget(parent)
{
  this->m_statusLabel = new QLabel("ready for work", this);
  this->m_quitButton = new QPushButton("exit", this);
  this->m_addRowButton = new QPushButton("add Row", this);
  this->m_addColumnButton = new QPushButton("add Column", this);
  this->m_deleteColumnButton = new QPushButton("delete Column", this);
  this->m_deleteRowButton = new QPushButton("delete Row", this);
  this->m_openFileButton = new QPushButton("open a file", this);
  this->m_saveFileButton = new QPushButton("save file as...", this);
  this->m_horizLayout = new QHBoxLayout;
  this->m_horizLayout->addWidget(this->m_addRowButton);
  this->m_horizLayout->addWidget(this->m_addColumnButton);
  this->m_horizLayout->addWidget(this->m_deleteColumnButton);
  this->m_horizLayout->addWidget(this->m_deleteRowButton);
  this->m_tmpUpperHorizLayout = new QHBoxLayout;
  this->m_tmpUpperHorizLayout->addWidget(this->m_openFileButton);
  this->m_tmpUpperHorizLayout->addWidget(this->m_saveFileButton);
  this->resize(1200, 800);

  this->layout = new QVBoxLayout;
  this->m_tableViewer = new TSVTableView(new TSVTableModel);

  this->layout->addLayout(this->m_tmpUpperHorizLayout);
  this->layout->addWidget(this->m_statusLabel);
  this->layout->addLayout(this->m_horizLayout);
  this->layout->addWidget(this->m_tableViewer);
  this->layout->addWidget(this->m_quitButton);
  this->setLayout(this->layout);

  m_tableViewer->show();
  connect(this->m_quitButton, &QPushButton::clicked, this, &AppViewer::close);
  connect(this->m_addRowButton, &QPushButton::clicked, this, &AppViewer::addRow);
  connect(this->m_addColumnButton, &QPushButton::clicked, this, &AppViewer::addColumn);
  connect(this->m_tableViewer->horizontalHeader(), &QHeaderView::sectionDoubleClicked, this, &AppViewer::headerDoubleClicked);

  connect(this->m_deleteColumnButton, &QPushButton::clicked, this, &AppViewer::deleteColumn);
  connect(this->m_deleteRowButton, &QPushButton::clicked, this, &AppViewer::deleteRow);

  connect(this->m_openFileButton, &QPushButton::clicked, this, &AppViewer::openFile);
  connect(this->m_saveFileButton, &QPushButton::clicked, this, &AppViewer::saveFile);
}

void AppViewer::addRow()
{
  int row = this->m_tableViewer->model()->rowCount();

  this->m_tableViewer->model()->insertRow(row);

  this->m_statusLabel->setText("row added");
}

void AppViewer::addColumn()
{
  int column = this->m_tableViewer->model()->columnCount();

  this->m_tableViewer->model()->insertColumn(column);

  this->m_statusLabel->setText("column added");
}

void AppViewer::headerDoubleClicked(int idx)
{
  QAbstractItemModel *model = this->m_tableViewer->model();
  QString oldHeader = model->headerData(idx, Qt::Horizontal).toString();
  bool isRight = false;
  QString newHeader = QInputDialog::getText(this, "change header", "new header", QLineEdit::Normal, oldHeader, &isRight);

  if(isRight && !newHeader.isEmpty())
  {
    model->setHeaderData(idx, Qt::Horizontal, newHeader);
    this->m_statusLabel->setText("header changed");
  }
}

void AppViewer::deleteColumn()
{
  int totalColumns = this->m_tableViewer->model()->columnCount();

  if(totalColumns == 0)
  {
    QMessageBox::warning(this, "error", "no columns");
    return;
  }

  bool ok;
  int columnNum = QInputDialog::getInt(this, tr("Удаление столбца"), tr("Введите номер столбца (от 1 до %1):").arg(totalColumns),
                                       1, 1, totalColumns, 1, &ok);

  if(ok)
  {
    int columnIndex = columnNum - 1;
    this->m_tableViewer->model()->removeColumn(columnIndex);
  }
}

void AppViewer::deleteRow()
{
  int totalRow = this->m_tableViewer->model()->rowCount();

  if(totalRow == 0)
  {
    QMessageBox::warning(this, "error", "no Row");
    return;
  }

  bool ok;
  int rowNum = QInputDialog::getInt(this, tr("Удаление строки"), tr("Введите номер строки (от 1 до %1):").arg(totalRow),
                                       1, 1, totalRow, 1, &ok);

  if(ok)
  {
    int rowIndex = rowNum - 1;
    this->m_tableViewer->model()->removeRow(rowIndex);
  }
}

void AppViewer::openFile()
{
  QString fileName = QFileDialog::getOpenFileName(this, "open tsv-file", QString(), "tsv-files (*.tsv);;all files(*)");

  if(fileName.isEmpty())
  {
    return;
  }

  TSVTable table;

  if(this->m_filesHandler.read(fileName, table))
  {
    this->m_tableViewer->getTableModel()->setTable(table);
    this->m_statusLabel->setText("file opening: success");
  }
  else
  {
    this->m_statusLabel->setText("file opening: error");
  }
}

void AppViewer::saveFile()
{
  QString fileName = QFileDialog::getSaveFileName(this, "save tsv-file", QString(), "tsv-files (*.tsv);;all files(*)");

  if(fileName.isEmpty())
  {
    return;
  }

  if(this->m_filesHandler.write(fileName, this->m_tableViewer->getTableModel()->getTable()))
  {
    this->m_statusLabel->setText("file saving: success");
  }
  else
  {
    this->m_statusLabel->setText("file saving: error");
  }
}
