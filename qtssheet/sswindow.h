/* Author: Piet Glas
 *
 * TODO:
 * -
 */

#pragma once

#include <QMainWindow>
#include <QObject>
#include <QString>
#include <QWidget>
#include <QToolBar>
#include <QAction>
#include "ssview.h"
#include "ssmodel.h"

// Sets the main window of the spreadsheet. 
// Contains a pointer to SSView which inherits QTableView; 
// this is set to be the central widget. 
// Also contains a pointer to the model, SSModel, which
// inherits QAbstractTableModel. The actions allow
// the main window to communicate changes to the model.
class SSWindow : public QMainWindow {
	Q_OBJECT
public:
	SSWindow(int rows, int cols, QWidget * parent=nullptr);
	~SSWindow();
public slots:
	void loadFromFile();
	void saveToFile();
	void save();	
	void showWindowTitle(const QString & title);
	void clear();
protected:
	void setupMenuBar();
	void createActions();
private:
	QString file_name_;
	SSView * sheetview_;
	SSModel * sheetmodel_;
	QAction * open_action_;
	QAction * save_to_file_action_;
	QAction * save_action_;
	QAction * clear_action_;
	QAction * exit_action_;	
};