#include "ssview.h"
#include "ssmodel.h"
#include "mainwindow.h"
#include <QApplication>
#include <string>
#include <iostream>

using std::cout;	using std::endl;

int main(int argc, char **argv) {
	QApplication a(argc, argv);
	int rows = 30;
	int cols = 20;
	// convert cmd input to int, to obtain row and column size
	if (argc > 1) {
		std::string rowss(1, argv[1][0]);
		std::string colss(1, argv[2][0]);
		rows = std::stoi(rowss);
		cols = std::stoi(colss);
	}
	MainWindow window(rows, cols);
	window.show();
	return a.exec();
}