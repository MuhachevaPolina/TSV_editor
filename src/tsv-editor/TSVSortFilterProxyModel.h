#pragma once

#include <QVariant>
#include <QSortFilterProxyModel>

class TSVSortFilterProxyModel: public QSortFilterProxyModel
{
public:
  TSVSortFilterProxyModel(QObject* parent = nullptr);
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};