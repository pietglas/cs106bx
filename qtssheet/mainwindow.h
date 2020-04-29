/* TODO:
 * - add save/open functionality 
 */

#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class SSView;	//forward declaration
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT
private:
	SSView * sheetview;
public:
	MainWindow(QWidget * parent=nullptr);
public slots:
	void showWindowTitle(const QString & title);
};