#include "ssmodel.h"
#include <QDebug>
#include <QBrush>
#include <QFont>
#include <QTime>

SSModel::SSModel(QObject * parent) : QAbstractTableModel(parent) {}

SSModel::~SSModel() {}

int SSModel::rowCount(const QModelIndex & /*parent*/) const {
	return 2;
}

int SSModel::columnCount(const QModelIndex & /*parent*/) const {
	return 2; 
}

QVariant SSModel::data(const QModelIndex & index, int role) const {
	if (role == Qt::DisplayRole && index.isValid())
		return m_grid_data[index.row()][index.column()];
	return QVariant();
}

QVariant SSModel::headerData(int section, Qt::Orientation orientation,
						int role) const {
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		switch (section) {
		case 0:
			return QString("A");
		case 1:
			return QString("B");
		}
	}
	if (role == Qt::DisplayRole && orientation == Qt::Vertical) {
		switch (section) {
		case 0:
			return 1;
		case 1:
			return 2;
		}
	}
	return QVariant();
}

bool SSModel::setData(const QModelIndex & index, const QVariant & value, int role) {
	if (role == Qt::EditRole) {
		if (!index.isValid())
			return false;
		// save value from editor to model
		m_grid_data[index.row()][index.column()] = value.toString();
		// emit the data as title of main window
		QString result;
		for (int row = 0; row != rows; row++) {
			for (int col = 0; col != cols; col++)
				result += m_grid_data[row][col] + ' ';
		}
		emit editCompleted(result);
		return true;
	}	
	return false;
}

Qt::ItemFlags SSModel::flags(const QModelIndex & index) const {
	return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}