#include <QApplication>

#include "BrowserWindow.hpp"
#include "Views/WebRender.hpp"

int main(int argc, char** argv)
{
	QApplication app{argc, argv};

	BrowserWindow firstWindow{};
	firstWindow.show();

	return app.exec();
}