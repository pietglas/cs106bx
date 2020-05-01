/* author: Piet Glas
 */
#include "sswindow.h"
#include "ssview.h"
#include "ssmodel.h"
#include <QObject>
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

SSWindow::SSWindow(int rows, int cols, QWidget * parent): QMainWindow(parent),
			sheetview_(new SSView(this)), sheetmodel_(new SSModel(rows, cols, this)) {
	// set sheetview_ to be the central widget
	setCentralWidget(sheetview_);

	// set up the position and size of the window 
	QPoint fhd_center = QRect(0, 0, 1920, 1080).center();
	QPoint left_upper_corner = QPoint(fhd_center.x() - 500, fhd_center.y() - 300);
	setGeometry(QRect(left_upper_corner, QSize(1000, 600)));
	
	// connect view with model
	sheetview_->setModel(sheetmodel_);
	
	// create actions, set up menu bar
	createActions();
	setupMenuBar();
}

SSWindow::~SSWindow() {
	delete sheetview_;
	delete sheetmodel_;
	delete open_action_;
	delete save_to_file_action_;
	delete save_action_;
	delete clear_action_;
	delete exit_action_;
}

void SSWindow::showWindowTitle(const QString & title) {
	setWindowTitle(tr("New File"));
}

void SSWindow::clear() {
	sheetmodel_->clearData();
}

void SSWindow::loadFromFile() {
	bool ok;
	file_name_ = QInputDialog::getText(this, tr("Open File"),
						tr("Enter File Name"), QLineEdit::Normal,
						QDir::home().dirName(), &ok);
	sheetmodel_->getDataFromFile(file_name_);
	setWindowTitle(file_name_);
}

void SSWindow::saveToFile() {
	bool ok;
	file_name_ = QInputDialog::getText(this, tr("Save File"),
						tr("Enter File Name"), QLineEdit::Normal,
						QDir::home().dirName(), &ok);
	sheetmodel_->saveData(file_name_);
	setWindowTitle(file_name_);
}

void SSWindow::save() {
	sheetmodel_->saveData(file_name_);
}

void SSWindow::createActions() {
	clear_action_ = new QAction(tr("Clear"), this);
	clear_action_->setShortcut(Qt::Key_Delete);
	connect(clear_action_, &QAction::triggered, this, &SSWindow::clear);

	exit_action_ = new QAction(tr("Exit"), this);
	connect(exit_action_, &QAction::triggered, qApp, &QCoreApplication::quit);

	open_action_ = new QAction(tr("Open File"), this);
	open_action_->setShortcut(QKeySequence(tr("Ctrl+O")));
	connect(open_action_, &QAction::triggered, this, &SSWindow::loadFromFile);

	save_to_file_action_ = new QAction(tr("Save As"), this);
	connect(save_to_file_action_, &QAction::triggered, this, &SSWindow::saveToFile);

	save_action_ = new QAction(tr("Save"), this);
	save_action_->setShortcut(QKeySequence(tr("Ctrl+S")));
	connect(save_action_, &QAction::triggered, this, &SSWindow::save);
}

void SSWindow::setupMenuBar() {
	QMenu * filemenu = menuBar()->addMenu(tr("&File"));
	filemenu->addAction(open_action_);
	filemenu->addAction(save_to_file_action_);
	filemenu->addAction(save_action_);
	filemenu->addAction(clear_action_);
	filemenu->addAction(exit_action_);
}