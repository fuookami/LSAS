#include "LifeguardScheduingAutomaticScheduing.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LifeguardScheduingAutomaticScheduing w;
	w.show();
	return a.exec();
}
