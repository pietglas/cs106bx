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
#include <QKeySequence>
#include <QDesktopWidget>

MainWindow::MainWindow(int rows, int cols, QWidget * parent): QMainWindow(parent),
			sheetview(new SSView(this)), sheetmodel(new SSModel(rows, cols, this)) {
	// set sheetview to be the central widget
	setCentralWidget(sheetview);

	// set up the position and size of the window 
	QPoint fhd_center = QRect(0, 0, 1920, 1080).center();
	QPoint left_upper_corner = QPoint(fhd_center.x() - 500, fhd_center.y() - 300);
	setGeometry(QRect(left_upper_corner, QSize(1000, 600)));
	
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
	delete save_to_file_action;
}

void MainWindow::showWindowTitle(const QString & title) {
	setWindowTitle(tr("New File"));
}

void MainWindow::clear() {
	sheetmodel->clearData();
}

void MainWindow::LoadFromFile() {
	bool ok;
	file_name = QInputDialog::getText(this, tr("Open File"),
						tr("Enter File Name"), QLineEdit::Normal,
						QDir::home().dirName(), &ok);
	sheetmodel->getDataFromFile(file_name);
	setWindowTitle(file_name);
}

void MainWindow::saveToFile() {
	bool ok;
	file_name = QInputDialog::getText(this, tr("Save File"),
						tr("Enter File Name"), QLineEdit::Normal,
						QDir::home().dirName(), &ok);
	sheetmodel->saveData(file_name);
	setWindowTitle(file_name);
}

void MainWindow::save() {
	sheetmodel->saveData(file_name);
}

void MainWindow::createActions() {
	clear_action = new QAction(tr("Clear"), this);
	clear_action->setShortcut(Qt::Key_Delete);
	connect(clear_action, &QAction::triggered, this, &MainWindow::clear);

	exit_action = new QAction(tr("Exit"), this);
	connect(exit_action, &QAction::triggered, qApp, &QCoreApplication::quit);

	open_action = new QAction(tr("Open File"), this);
	open_action->setShortcut(QKeySequence(tr("Ctrl+O")));
	connect(open_action, &QAction::triggered, this, &MainWindow::LoadFromFile);

	save_to_file_action = new QAction(tr("Save As"), this);
	connect(save_to_file_action, &QAction::triggered, this, &MainWindow::saveToFile);

	save_action = new QAction(tr("Save"), this);
	save_action->setShortcut(QKeySequence(tr("Ctrl+S")));
	connect(save_action, &QAction::triggered, this, &MainWindow::save);
}

void MainWindow::setupMenuBar() {
	QMenu * filemenu = menuBar()->addMenu(tr("&File"));
	filemenu->addAction(open_action);
	filemenu->addAction(save_to_file_action);
	filemenu->addAction(save_action);
	filemenu->addAction(clear_action);
	filemenu->addAction(exit_action);
}