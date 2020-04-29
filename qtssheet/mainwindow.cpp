#include "mainwindow.h"
#include "ssview.h"
#include "ssmodel.h"

MainWindow::MainWindow(QWidget * parent): QMainWindow(parent),
			sheetview(new SSView(this)) {
	setCentralWidget(sheetview);
	SSModel * sheetmodel = new SSModel(this);
	sheetview->setModel(sheetmodel);

	// transfer changes to the model to the window title
	connect(sheetmodel, &SSModel::editCompleted, this, 
			&MainWindow::showWindowTitle);
}

void MainWindow::showWindowTitle(const QString & title) {
	setWindowTitle(title);
}