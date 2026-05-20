#include <src/tsv-editor/AppViewer.h>
#include <src/tsv-editor/TSVTableModel.h>

AppViewer::AppViewer(QWidget *parent) : QWidget(parent)
{
  this->m_statusLabel = new QLabel("ready for work", this);
  this->m_quitButton = new QPushButton("exit", this);
  this->m_addRowButton = new QPushButton("addRow", this);
  this->resize(600, 400);

  this->layout = new QVBoxLayout;
  this->m_tableViewer = new TSVTableView(new TSVTableModel);

  this->layout->addWidget(this->m_statusLabel);
  this->layout->addWidget(this->m_tableViewer);
  this->layout->addWidget(this->m_quitButton);
  this->setLayout(this->layout);

  m_tableViewer->show();
  connect(this->m_quitButton, &QPushButton::clicked, this, &AppViewer::close);
  // connect(this->m_addRowButton, &QPushButton::clicked, , );
}
