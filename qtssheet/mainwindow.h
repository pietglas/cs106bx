/* MainWindow class, containg a pointer to (and parent of) SSView
 * TODO:
 * - window should be larger when starting program
 * - add save/open functionality 
 */

#pragma once

#include <QMainWindow>
#include <QString>
#include <QWidget>
#include <QToolBar>
#include <QAction>
#include "ssview.h"
#include "ssmodel.h"

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow(int rows, int cols, QWidget * parent=nullptr);
	~MainWindow();
public slots:
	void LoadFromFile();
	void saveToFile();
	void save();	
	void showWindowTitle(const QString & title);
	void clear();
protected:
	void setupMenuBar();
	void createActions();
private:
	QString file_name;
	SSView * sheetview;
	SSModel * sheetmodel;
	QAction * open_action;
	QAction * save_to_file_action;
	QAction * save_action;
	QAction * clear_action;
	QAction * exit_action;	
};