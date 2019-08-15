#ifndef TABSVIEW_HPP
#define TABSVIEW_HPP

#include <QWidget>

#include <QScrollArea>

#include <QGridLayout>

class Tab;

class Container;

class TabsView: public QScrollArea {
	Q_OBJECT

		enum OrganisationType { Grid, Windows };
public:
	explicit TabsView(Container* parent);
	~TabsView() = default;

	void addTab(Tab* tab);
	void removeTab(Tab* tab);

	void setActiveTab(Tab* tab);
	void setActiveTab(int index);

	void organize(OrganisationType organisation = Grid);

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	QGridLayout* m_gridLayout{};
	QWidget* m_gridView{};

	Container* m_container{};
};

#endif // TABSVIEW_HPP
