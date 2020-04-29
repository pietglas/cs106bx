/* TODO:
 * - parse input for dependencies
 */

#pragma once

#include <QAbstractTableModel>

const int rows = 2;
const int cols = 2;

class SSModel : public QAbstractTableModel {
	Q_OBJECT
public:
	SSModel(QObject * parent=nullptr);
	~SSModel();

	int rowCount(const QModelIndex & parent=QModelIndex()) const override;
	int columnCount(const QModelIndex & parent=QModelIndex()) const override;
	QVariant data(const QModelIndex & index, 
					int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation,
						int role) const override;

	bool setData(const QModelIndex & index, const QVariant & value, 
	 			int role = Qt::EditRole) override;

	Qt::ItemFlags flags(const QModelIndex & index) const override;

private:
	QString m_grid_data[rows][cols];

signals:
	void editCompleted(const QString & );
};