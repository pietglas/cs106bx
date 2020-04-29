/* TODO:
 * - include formulas
 * - parse input for dependencies
 * - resizing window should increase nr of rows & cols
 */

#pragma once

#include <QAbstractTableModel>
#include <QString>
#include <QVector>

class SSModel : public QAbstractTableModel {
	Q_OBJECT
public:
	SSModel(int rows, int cols, QObject * parent=nullptr);
	~SSModel();

	int rowCount(const QModelIndex & parent=QModelIndex()) const override;
	int columnCount(const QModelIndex & parent=QModelIndex()) const override;
	QVariant data(const QModelIndex & index, 
					int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation,
						int role) const override;

	bool setData(const QModelIndex & index, const QVariant & value, 
	 			int role = Qt::EditRole) override;

	void clearData();

	Qt::ItemFlags flags(const QModelIndex & index) const override;

private:
	int rows_;
	int cols_;
	QVector<QVector<QString>> m_grid_data_;

signals:
	
};