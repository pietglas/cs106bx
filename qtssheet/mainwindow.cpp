#include "mainwindow.h"
#include "ssview.h"
#include "ssmodel.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QCoreApplication>
#include <QInputDialog>
#include <QDir>
#include <QLineEdit>
#include <QRect>
#include <QStyle>

MainWindow::MainWindow(int rows, int cols, QWidget * parent): QMainWindow(parent),
			sheetview(new SSView(this)), sheetmodel(new SSModel(rows, cols, this)) {
	setCentralWidget(sheetview); 
	setGeometry(QRect(QPoint(0,0), QSize(1000, 600)));
	// TODO: center
	
	// connect view with model
	sheetview->setModel(sheetmodel);
	
	// create actions, set up menu bar
	createActions();
	setupMenuBar();
}

MainWindow::~MainWindow() {
	delete sheetview;
	delete sheetmodel;
	delete clear_action;
	delete exit_action;
	delete save_action;
}

void MainWindow::showWindowTitle(const QString & title) {
	setWindowTitle(tr("New File"));
}

void MainWindow::clear() {
	sheetmodel->clearData();
}

void MainWindow::saveToFile() {
	bool ok;
	QString file_name = QInputDialog::getText(this, tr("Save File"),
						tr("Enter File Name"), QLineEdit::Normal,
						QDir::home().dirName(), &ok);
	sheetmodel->saveData(file_name);
}

void MainWindow::createActions() {
	clear_action = new QAction(tr("Clear"), this);
	clear_action->setShortcut(Qt::Key_Delete);
	connect(clear_action, &QAction::triggered, this, &MainWindow::clear);

	exit_action = new QAction(tr("Exit"), this);
	connect(exit_action, &QAction::triggered, qApp, &QCoreApplication::quit);

	save_action = new QAction(tr("Save File"), this);
	connect(save_action, &QAction::triggered, this, &MainWindow::saveToFile);
}

void MainWindow::setupMenuBar() {
	QMenu * filemenu = menuBar()->addMenu(tr("&File"));
	filemenu->addAction(clear_action);
	filemenu->addAction(exit_action);
	filemenu->addAction(save_action);
}