#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <QWidget>
#include <QLabel>

#include <QDragEnterEvent>
#include <QDropEvent>

#include <QHBoxLayout>

class WebRender;

class ContainersView;

class ContainerDragWidget;

class Container : public QWidget {
	Q_OBJECT

public:
	explicit Container(QString title, ContainersView* containersView, int x, int y, QWidget* parent = nullptr);
	~Container() = default;

	int x{-1};
	int y{-1};

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

	QHBoxLayout* m_layout{};

	ContainerDragWidget* m_dragWidget{};
	QLabel* m_titleDesc{}; // TODO: remvove this debugging info
	WebRender* m_render{};

	ContainersView* m_containersView;

	QString m_title{"Title"};
};

#endif // CONTAINER_HPP
