/* author: Piet Glas
 */
#include "ssmodel.h"
#include "tokenizer.h"
#include "expression.h"
#include <math.h>
#include <QDebug>
#include <QDebug>
#include <QBrush>
#include <QFont>
#include <QString>
#include <QObject>
#include <QModelIndex>
#include <QVariant>
#include <QFile>
#include <QDataStream>

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
		return QString(alph_[section]);
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
		m_grid_data_[index.row()][index.column()] = value;
		return true;
	}	
	return false;
}

void SSModel::clearData() {
	for (int row = 0; row != rows_; row++) {
		for (int col = 0; col != cols_; col++)
			m_grid_data_[row][col] = QVariant();
	}
}

bool SSModel::getDataFromFile(const QString& file_name) {
	QFile file(file_name);
	if (file.open(QIODevice::ReadOnly)) {
		QDataStream input(&file);
		input >> rows_ >> cols_;
		for (int row = 0; row != rows_; row++) {
			for (int col = 0; col != cols_; col++)
				input >> m_grid_data_[row][col];
		}
		file.close();
		return true;
	}
	return false;
}

bool SSModel::saveData(const QString & file_name) const {
	QFile file(file_name);
	if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
		QDataStream output(&file);
		output << rows_ << cols_;
		for (int row = 0; row != rows_; row++) {
			for (int col = 0; col != cols_; col++)
				output << m_grid_data_[row][col];
		}
		file.close();
		return true;
	}
	return false;
}

bool SSModel::setFormula(const QString & formula) {
	Tokenizer tokenizer;
	if (tokenizer.tokenize(formula)) {
		if (tokenizer.validate()) {
			// update existing formula or add a new one
			QString key = tokenizer.tokenized()[0];
			QVector value = tokenizer.tokenized().mid(2, -1);
			formulas_.insert(key, value);

			// update the actual data displayed
			auto formula_ptr = std::make_shared<Expression>(value);
			double val = SSModel::calculateFormula(expression);
			QPair index = SSModel::convertStrToIndex(key);
			m_grid_data_[index.first][index.second] = val;
		}
	}
	return false;
}

double calculateFormula(std::shared_ptr<Expression> formula) {
	if (formula->left() == nullptr) {
		bool ok;
		double try_conv = formula.token().toDouble(&ok);
		if (*ok)
			return try_conv;
		else {
			QPair index = SSModel::convertStrToIndex(formula.token());
			return m_grid_data_[index.first][index.second];
		}
	}
	else {
		if (formula.token() == "+")
			return calculateFormula(formula.left()) + 
					calculateFormula(formula.right());
		else if (formula.token() == "-")
			return calculateFormula(formula.left()) - 
					calculateFormula(formula.right());
		else if (formula.token() == "*")
			return calculateFormula(formula.left()) * 
					calculateFormula(formula.right());
		else if (formula.token() == "/")
			return calculateFormula(formula.left()) / 
					calculateFormula(formula.right());
		else
			return pow(calculateFormula(formula.left()),
						calculateFormula(formula.right()));
	}
}

QPair SSModel::convertStrToIndex(const QString & index) {
	int col = 0;
	while (alph_[col] != index[0]) 
		++col;
	int row = index.mid(1, -1).toInt();
	return qMakePair(row, col);
}


Qt::ItemFlags SSModel::flags(const QModelIndex & index) const {
	return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}