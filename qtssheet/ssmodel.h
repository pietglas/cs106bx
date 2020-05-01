/* Author: Piet Glas
 *
 * TODO:
 * - include formulas
 * - parse input for dependencies
 */

#pragma once

#include <QAbstractTableModel>
#include <QString>
#include <QVector>
#include <QObject>

// Model containing the data for our spreadsheet, and an interface which
// SSView and MainWindow use for communicating changes made by the user.
class SSModel : public QAbstractTableModel {
	Q_OBJECT
public:
	SSModel(int rows, int cols, QObject * parent=nullptr);
	~SSModel();
	// following methods return the number of rows and the number of columns;
	// mainly used by the display class SSView
	int rowCount(const QModelIndex & parent=QModelIndex()) const override;
	int columnCount(const QModelIndex & parent=QModelIndex()) const override;
	// SSView obtains data by calling this method
	QVariant data(const QModelIndex & index, 
					int role = Qt::DisplayRole) const override;
	// SSView obtains headerdata by calling this method
	QVariant headerData(int section, Qt::Orientation orientation,
						int role) const override;
	// SSView communicates updates in the data by calling this method
	bool setData(const QModelIndex & index, const QVariant & value, 
	 			int role = Qt::EditRole) override;
	// clears the data
	void clearData();
	// Load data from a .csv file. Expects that the first line is formatted
	// as `row_, col_, `. Thus trying to load a .csv file that wasn't 
	// saved using the saveData() method from this class propably fails.
	bool getDataFromFile(const QString& file_name);
	// Save data in a .csv file. The first line in the file is set to
	// `row_, col_, `, to ensure we properly format when loading a
	// an existing file.
	bool saveData(const QString & file_name) const;

	Qt::ItemFlags flags(const QModelIndex & index) const override;

private:
	int rows_;
	int cols_;
	QVector<QVector<QString>> m_grid_data_;

signals:
	
};