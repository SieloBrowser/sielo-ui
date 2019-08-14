#ifndef TABSVIEW_HPP
#define TABSVIEW_HPP

#include <QWidget>

class TabsView : public QWidget {
	Q_OBJECT

public:
	explicit TabsView(QWidget* parent);
	~TabsView() = default;
};

#endif // TABSVIEW_HPP
