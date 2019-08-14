#ifndef LATERALBAR_HPP
#define LATERALBAR_HPP

#include <QWidget>

#include <QScrollArea>

#include <QVBoxLayout>

class BubbleButton;

class LateralBar : public QWidget {
	Q_OBJECT

public:
	explicit LateralBar(QWidget* parent = nullptr);
	~LateralBar() = default;

	void addTab(BubbleButton* button);
	void removeTab(BubbleButton* button);

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
};

#endif // LATERALBAR_HPP
