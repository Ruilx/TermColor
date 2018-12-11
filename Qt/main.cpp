#include "MainWindow.h"
#include <QApplication>

QString __application__  = "TermColor";
QString __author__       = "Ruilx";
QString __version__      = "0.1";
QString __organization__ = "GT-Soft";

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setApplicationDisplayName(__application__);
	a.setOrganizationName(__organization__);

	MainWindow w(nullptr);
	w.show();

	return a.exec();
}
