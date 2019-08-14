#ifndef LATERALBAR_HPP
#define LATERALBAR_HPP

#include <QWidget>

#include <QPushButton>

#include <QScrollArea>

#include <QVBoxLayout>

class LateralBar : public QWidget {
	Q_OBJECT

public:
	explicit LateralBar(QWidget* parent = nullptr);
	~LateralBar() = default;

	void addTab(QPushButton* button);
	void removeTab(QPushButton* button);

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
