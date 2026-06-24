#include <src/tsv-editor/AppViewer.h>
#include <src/tsv-editor/TSVTableModel.h>

#include <QHBoxLayout>
#include <QHeaderView>
#include <QInputDialog>
#include <QMessageBox>

AppViewer::AppViewer(QWidget *parent) : QWidget(parent)
{
  this->m_statusLabel = new QLabel("ready for work", this);
  this->m_quitButton = new QPushButton("exit", this);
  this->m_addRowButton = new QPushButton("add Row", this);
  this->m_addColumnButton = new QPushButton("add Column", this);
  this->m_deleteColumnButton = new QPushButton("delete Column", this);
  this->m_horizLayout = new QHBoxLayout;
  this->m_horizLayout->addWidget(this->m_addRowButton);
  this->m_horizLayout->addWidget(this->m_addColumnButton);
  this->m_horizLayout->addWidget(this->m_deleteColumnButton);
  this->resize(1200, 800);

  this->layout = new QVBoxLayout;
  this->m_tableViewer = new TSVTableView(new TSVTableModel);

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
}

void AppViewer::addRow()
{
  QModelIndex idx = m_tableViewer->currentIndex();
  int row = -1;
  if (idx.isValid())
  {
    row = idx.row() + 1;
  }
  else
  {
    row = m_tableViewer->model()->rowCount();
  }

  this->m_tableViewer->model()->insertRow(row);
  this->m_statusLabel->setText("row added");
}

void AppViewer::addColumn()
{
  QModelIndex idx = m_tableViewer->currentIndex();
  int column = -1;
  if (idx.isValid())
  {
    column = idx.column() + 1;
  }
  else
  {
    column = m_tableViewer->model()->columnCount();
  }

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

void AppViewer::deleteColumn(int colNum)
{
  int totalColumns = this->m_tableViewer->model()->columnCount();

  if(totalColumns == 0)
  {
    QMessageBox::warning(this, "Ошибка", "В таблице нет столбцов для удаления!");
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
