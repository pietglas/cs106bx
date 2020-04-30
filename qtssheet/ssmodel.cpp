#include "ssmodel.h"
#include <QDebug>
#include <QBrush>
#include <QFont>
#include <QString>
#include <QObject>
#include <QModelIndex>
#include <QVariant>
#include <QFile>
#include <QTextStream>

SSModel::SSModel(int rows, int cols, QObject * parent) : 
				QAbstractTableModel(parent), rows_{rows}, cols_{cols} {
	m_grid_data_.resize(rows);
	for (int row = 0; row != m_grid_data_.size(); row++)
		m_grid_data_[row].resize(cols);
}

SSModel::~SSModel() {}

int SSModel::rowCount(const QModelIndex & /*parent*/) const {
	return rows_;
}

int SSModel::columnCount(const QModelIndex & /*parent*/) const {
	return cols_; 
}

QVariant SSModel::data(const QModelIndex & index, int role) const {
	if (role == Qt::DisplayRole && index.isValid())
		return m_grid_data_[index.row()][index.column()];
	return QVariant();
}

QVariant SSModel::headerData(int section, Qt::Orientation orientation,
						int role) const {
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		QString alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		return QString(alph[section]);
	}
	if (role == Qt::DisplayRole && orientation == Qt::Vertical) {
		return section + 1;
	}
	return QVariant();
}

bool SSModel::setData(const QModelIndex & index, const QVariant & value, int role) {
	if (role == Qt::EditRole) {
		if (!index.isValid())
			return false;
		// save value from editor to model
		m_grid_data_[index.row()][index.column()] = value.toString();
		return true;
	}	
	return false;
}

void SSModel::clearData() {
	for (int row = 0; row != rows_; row++) {
		for (int col = 0; col != cols_; col++)
			m_grid_data_[row][col] = QString("");
	}
}

bool SSModel::saveData(const QString & file_name) const {
	QString data;
	for (int row = 0; row != rows_; row++) {
		for (int col = 0; col != cols_; col++) {
			data += m_grid_data_[row][col];
			data += ", ";
		}
		data += "\n";
	}
	QFile csvFile(file_name);
	if (csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
		QTextStream output(&csvFile);
		output << data;

		csvFile.close();
		return true;
	}
	return false;
}

Qt::ItemFlags SSModel::flags(const QModelIndex & index) const {
	return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}