#ifndef CONTAINERDRAGWIDGET_HPP
#define CONTAINERDRAGWIDGET_HPP

#include <QWidget>

#include <QMouseEvent>

#include <QPoint>  

class Container;

class ContainerDragWidget : public QWidget {
	Q_OBJECT

public:
	explicit ContainerDragWidget(Container* parent);
	~ContainerDragWidget() = default;

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

private:
	Container* m_parent{};

	QPoint m_dragStartPosition{};
};

#endif // CONTAINERDRAGWIDGET_HPP
