#include <QApplication>

#include <QWidget>
#include <QMainWindow>

#include "Widgets/WebRender.hpp"

int main(int argc, char** argv)
{
	QApplication app{argc, argv};

	QMainWindow firstWindow{};
	const auto render{new WebRender(&firstWindow)};

	firstWindow.setWindowTitle(QObject::tr("Sielo Jennysis"));
	firstWindow.setCentralWidget(render);
	firstWindow.show();

	return app.exec();
}