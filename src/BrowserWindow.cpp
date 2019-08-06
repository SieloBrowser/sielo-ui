#include "BrowserWindow.hpp"

#include "Views/ContainersView.hpp"

BrowserWindow::BrowserWindow(QWidget* parent) :
	QMainWindow(parent)
{
	setWindowTitle(tr("Sielo Browser"));

	m_containersView = new ContainersView(this);

	setCentralWidget(m_containersView);
}
