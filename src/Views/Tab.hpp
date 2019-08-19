#ifndef TAB_HPP
#define TAB_HPP

#include <QWidget>

#include <QPushButton>

#include <QGridLayout>

class BubbleButton;

class WebRender;

class Tab : public QWidget {
	Q_OBJECT

public:
	explicit  Tab(const QString& icon = "1", QWidget* parent = nullptr);
	~Tab() = default;

	void cardState();

	BubbleButton* tabIcon() const;
	void setIcon(const QIcon& icon);

	WebRender* tabRender() const;

private:
	QGridLayout* m_layout{};

	BubbleButton* m_tabIcon{};
	QPushButton* m_closeButton{};
	WebRender* m_tabRender{};
};

#endif // TAB_HPP
