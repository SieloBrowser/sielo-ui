#include <QApplication>

#include <QWidget>

int main(int argc, char** argv)
{
	QApplication app{argc, argv};

	QWidget firstWindow{};

	firstWindow.setWindowTitle(QObject::tr("Sielo Jennysis"));
	firstWindow.show();

	return app.exec();
}