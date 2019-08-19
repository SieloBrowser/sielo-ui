#ifndef LATERALBAR_HPP
#define LATERALBAR_HPP

#include <QWidget>

#include <QScrollArea>

#include <QVBoxLayout>

class BubbleButton;

class Container;

class Tab;

class LateralBar : public QWidget {
	Q_OBJECT

public:
	explicit LateralBar(Container* parent);
	~LateralBar() = default;

	void addTab(Tab* button);
	void removeTab(Tab* button);

	void showTabs();
	void hideTabs();

protected:
	// Workaround for stylesheet
	void paintEvent(QPaintEvent* event) override;
	
private:
	void setupUi();

	QVBoxLayout* m_layout{};

	QVBoxLayout* m_tabsButtonsLayout{};
	QVBoxLayout* m_controlesButtonsLayout{};

	QWidget* m_tabsButtonsWidget{};
	QWidget* m_controlesButtonsWidget{};

	QScrollArea* m_tabsButtonsScrollArea{};

	BubbleButton* m_buttonAddTab{};
	BubbleButton* m_buttonBookmarks{};
	BubbleButton* m_buttonHistory{};
	BubbleButton* m_buttonShowTabs{};
	BubbleButton* m_buttonProfile{};

	Container* m_container{};
};

#endif // LATERALBAR_HPP
