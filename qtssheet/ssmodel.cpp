/* author: Piet Glas
 */
#include "ssmodel.h"
#include "formula/tokenizer.h"
#include "formula/expression.h"
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
	QPair<int, int> normindex = qMakePair(index.x, index.y);
	QString strindex = convertIndexToString(normindex);
	bool index_found = data_.contains(strindex);
	if (role == Qt::DisplayRole && index.isValid() && index_found)
		return data_[strindex].first;
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

bool SSModel::setData(const QModelIndex & index, 
						const QVariant & value, int role) {
	if (role == Qt::EditRole && index.isValid()) {
		// save value from editor to model
		QPair<int, int> normindex = qMakePair(index.x, index.y);
		QString strindex = convertIndexToString(normindex);
		QVector<QString> empty_vec;
		QPair<QVariant, QVector<QString>> val = qMakePair(value, empty_vec);
		data_.insert(strindex, val);
		return true;
	}	
	return false;
}

void SSModel::clearData() {
	data_.clear();
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
	if (tokenizer.tokenize(formula)) {	// turn string into vector of tokens
		if (tokenizer.validate()) {	// check for correct syntax
			// update existing formula or add a new one
			QString key = tokenizer.tokenized()[0];
			QVector<QString> second = tokenizer.tokenized().mid(2, -1);

			// set data displayed
			auto formula_ptr = std::make_shared<Expression>(second);
			double first = SSModel::calculateFormula(formula_ptr);
			QPair<QVariant, QVector<QString>> value = qMakePair(first, second);

			data_.insert(key, value);
		
			return true;
		}
		return false;
	}
	return false;
}

double SSModel::calculateFormula(std::shared_ptr<Expression> formula) {
	if (formula->lhs() == nullptr) {
		bool ok;
		double try_conv = formula->token().toDouble(&ok);
		if (ok)
			return try_conv;
		else {
			QPair<int, int> index = SSModel::convertStrToIndex(formula->token());
			return data_[formula->token()].first.toDouble();
		}
	}
	else {
		if (formula->token() == "+")
			return calculateFormula(formula->lhs()) + 
					calculateFormula(formula->rhs());
		else if (formula->token() == "-")
			return calculateFormula(formula->lhs()) - 
					calculateFormula(formula->rhs());
		else if (formula->token() == "*")
			return calculateFormula(formula->lhs()) * 
					calculateFormula(formula->rhs());
		else if (formula->token() == "/")
			return calculateFormula(formula->lhs()) / 
					calculateFormula(formula->rhs());
		else
			return pow(calculateFormula(formula->lhs()),
						calculateFormula(formula->rhs()));
	}
}

QPair<int, int> SSModel::convertStrToIndex(const QString & index) const {
	int col = 0;
	while (alph_[col] != index[0]) 
		++col;
	int row = index.mid(1, -1).toInt() - 1;
	return qMakePair(row, col);
}

QString convertIndexToStr(const QPair<int, int> & index) const {
	int row = index.first + 1;
	int col = index.second;
	QString dindex;
	dindex += alph_[col];
	dindex += QString::number(row);
	return dindex;
}


Qt::ItemFlags SSModel::flags(const QModelIndex & index) const {
	return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}