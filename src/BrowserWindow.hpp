#ifndef BROWSERWINDOW_HPP
#define BROWSERWINDOW_HPP

#include <QMainWindow>

class ContainersView;

class BrowserWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit BrowserWindow(QWidget* parent = nullptr);
	~BrowserWindow() = default;

private:
	ContainersView* m_containersView{};
};

#endif // BROWSERWINDOW_HPP
