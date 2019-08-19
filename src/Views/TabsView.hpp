#ifndef TABSVIEW_HPP
#define TABSVIEW_HPP

#include <QWidget>

#include <QScrollArea>

#include <QGridLayout>

class Tab;

class Container;

class TabsView: public QScrollArea {
	Q_OBJECT

public:
	enum State { Full = 0, Grid = 1, Windows = 2 };

	explicit TabsView(Container* parent);
	~TabsView() = default;

	void addTab(Tab* tab);
	void removeTab(Tab* tab);

	void setActiveTab(Tab* tab);
	void setActiveTab(int index);

	void organize(State organisation = Grid);

	State state() const;

protected:
	void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;

private:
	void organizeInOne();
	void organizeInTwo();
	void organizeIntThree();

	QGridLayout* m_gridLayout{};
	QWidget* m_gridView{};

	QWidget* m_activeTab{};
	Container* m_container{};

	State m_state{Full};
};

#endif // TABSVIEW_HPP
