#include "PolylineModel.h"

#include <cmath>
#include <iostream>

using namespace std;

PolylineModel::PolylineModel(QObject *parent)
    : QAbstractListModel(parent)
{
    // вертикальные полосы
    for (double lon = -180; lon < 179 + 1e-5; lon += 10) {
        data_.push_back(
        {
            -80, lon, 80, lon
        });
    }

    // возле офиса
    data_.push_back(
    {
        55.76644, 37.53251, 55.76622, 37.5344, 55.76654, 37.53483, 55.76684, 37.53484, 55.76692, 37.53454, 55.76827, 37.52835
    });
    // где-то в москве
    data_.push_back(
    {
        55.8215,37.4458,55.8238,37.4365
    });
    // тверь
    data_.push_back(
    {
        56.8541, 35.9444, 56.8669, 35.9444, 56.8631, 35.963
    });
    // шпицберген
    data_.push_back(
    {
        81.637, 63.756, 81.664, 62.226
    });

    // Чукотка
    data_.push_back(
    {
        67.05, 170.447, 66.938,-177.765, 62.932,178.063
    });
    data_.push_back(
    {
        65.05, 170.447, 64.938,-170.765, 62.938,-170.765, 62.932,163.063, 61.932,163.063
    });

    // Ванкувер - Сиэттл
    data_.push_back(
    {
        49.187,-123.046, 47.574, -122.323
    });
}

QHash<int, QByteArray> PolylineModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[PathRole] = "m_path";
    return names;
}

int PolylineModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return data_.size();
}

int PolylineModel::tracksSize() const
{
    return data_.size();
}

QVariant PolylineModel::trackData(int idx) const
{
    if (idx < 0 || idx >= data_.size())
        return QVariant();
    return data_.at(idx);
}

QVariant PolylineModel::data(const QModelIndex &index, int role) const
{
    auto idx = index.row();
    if (!index.isValid() || idx < 0 || idx >= data_.size())
        return QVariant();

    switch (role) {
    case PathRole:
        return data_.at(idx);
    }

    return QVariant();
}
