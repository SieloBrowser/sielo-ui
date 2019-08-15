#ifndef TAB_HPP
#define TAB_HPP

#include <QWidget>

class BubbleButton;

class WebRender;

class Tab : public QWidget {
	Q_OBJECT

public:
	explicit  Tab(const QString& icon = "1", QWidget* parent = nullptr);
	~Tab() = default;

	BubbleButton* tabIcon() const;
	void setIcon(const QIcon& icon);

	WebRender* tabRender() const;

private:
	BubbleButton* m_tabIcon{};
	WebRender* m_tabRender{};
};

#endif // TAB_HPP
