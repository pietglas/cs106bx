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
	void showWindowTitle(const QString & title);
	void clear();
	void saveToFile();
	// void loadFromFile();
protected:
	void setupMenuBar();
	void createActions();
private:
	SSView * sheetview;
	SSModel * sheetmodel;
	QAction * clear_action;
	QAction * exit_action;
	QAction * save_action;
	// QAction * open_action;
	// TODO:
	
	// QAction * save_as_action;
	
};