#include <QApplication>
#include "ui_main.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	mainDisplay window;
	window.show();
	return app.exec();
}