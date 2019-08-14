#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <QWidget>
#include <QLabel>
#include <QFrame>

#include <QDragEnterEvent>
#include <QDropEvent>

#include <QHBoxLayout>

class LateralBar;
class TabsView;

class ContainersView;

class ContainerDragWidget;

class Container : public QWidget {
	Q_OBJECT

public:
	explicit Container(ContainersView* containersView, int x, int y, QWidget* parent = nullptr);
	~Container() = default;

	int cordX{-1};
	int cordY{-1};

	bool isValid() const;

	const QString& title() const;

	ContainersView* containersView() const;
	void setContainersView(ContainersView* containersView);

protected:
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dragMoveEvent(QDragMoveEvent* event) override;
	void dragLeaveEvent(QDragLeaveEvent* event) override;
	void dropEvent(QDropEvent* event) override;

private:
	void setupUi();

	QGridLayout* m_layout{};

	ContainerDragWidget* m_dragWidget{};
	LateralBar* m_lateralBar{};
	TabsView* m_tabsView{};

	QFrame* m_highlightFrame{};

	ContainersView* m_containersView;

	QString m_title{"Title"};
};

#endif // CONTAINER_HPP
