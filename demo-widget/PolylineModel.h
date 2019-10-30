#ifndef POLYLINEMODEL_H
#define POLYLINEMODEL_H

#include <QAbstractListModel>

// в этой программе класс не используется как модель;
// стандартные методы модели оставлены, вырезать и перенаследоваться некогда
class PolylineModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum {
        PathRole = Qt::UserRole + 1,
    };

    explicit PolylineModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE int tracksSize() const;
    Q_INVOKABLE QVariant trackData(int idx) const;

private:
    QVector<QVariantList> data_;
};

#endif // POLYLINEMODEL_H
