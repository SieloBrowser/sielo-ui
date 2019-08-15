#include "ContainerDragWidget.hpp"

#include <QApplication>

#include <QDrag>

#include "Utils/ContainerMimeData.hpp"

#include "Container.hpp"

ContainerDragWidget::ContainerDragWidget(Container* parent) :
	QWidget(parent),
	m_parent(parent)
{
	setObjectName("sielo-widget-container-drag");

	setAutoFillBackground(true);

	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::black);
	setPalette(pal);

	setMinimumSize(16, 16);
}

void ContainerDragWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton) {
		m_dragStartPosition = event->pos();
	}
}

void ContainerDragWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (!event->buttons() & Qt::LeftButton) {
		return;
	}

	if ((event->pos() - m_dragStartPosition).manhattanLength() < QApplication::startDragDistance()) {
		return;
	}

	auto drag{new QDrag(this)};
	auto mimeData{new ContainerMimeData()};

	mimeData->setData("container", m_parent->title().toUtf8());
	mimeData->setContainer(m_parent);

	drag->setMimeData(mimeData);

	auto dropAction = drag->exec(Qt::CopyAction);
}
