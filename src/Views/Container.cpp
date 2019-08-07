#include "Container.hpp"

#include <utility>

#include "Utils/ContainerMimeData.hpp"

#include "ContainerDragWidget.hpp"
#include "ContainersView.hpp"
#include "WebRender.hpp"

Container::Container(QString title, ContainersView* containersView, int x, int y, QWidget* parent) :
	QWidget(parent), x(x), y(y), m_containersView(containersView), m_title(std::move(title))
{
	setupUi();

	setAcceptDrops(true);
	setAutoFillBackground(true);
}

bool Container::isValid() const
{
	return x != -1 && y != -1;
}

const QString& Container::title() const
{
	return m_title;
}

ContainersView* Container::containersView() const
{
	return m_containersView;
}

void Container::setContainersView(ContainersView* containersView)
{
	m_containersView = containersView;
}

void Container::dragEnterEvent(QDragEnterEvent* event)
{
	if (event->mimeData()->hasFormat("container") && qobject_cast<const ContainerMimeData*>(event->mimeData())->container() != this) {
		event->acceptProposedAction();

		setStyleSheet("background: #FF0000;");
	}
}

void Container::dragMoveEvent(QDragMoveEvent* event)
{
	if (event->mimeData()->hasFormat("container") && qobject_cast<const ContainerMimeData*>(event->mimeData())->container() != this) {
		event->acceptProposedAction();

		setStyleSheet("background: #FF0000;");
	}
}

void Container::dragLeaveEvent(QDragLeaveEvent* event)
{
	setStyleSheet("");
}

void Container::dropEvent(QDropEvent* event)
{
	if (event->mimeData()->hasFormat("container") && qobject_cast<const ContainerMimeData*>(event->mimeData())->container() != this) {
		event->acceptProposedAction();

		setStyleSheet("");

		Container* dropContainer = qobject_cast<const ContainerMimeData*>(event->mimeData())->container();

		// We detach the dropped container
		dropContainer->containersView()->detachContainer(dropContainer);

		// We attach and insert it to his new container, in a new column right now
		dropContainer->setContainersView(m_containersView);
		m_containersView->insertContainer(dropContainer, x + 1, 0);
	}
}

void Container::setupUi()
{
	m_layout = new QHBoxLayout(this);

	m_dragWidget = new ContainerDragWidget(this);
	m_titleDesc = new QLabel(m_title, this);
	m_render = new WebRender(this);

	m_layout->addWidget(m_dragWidget);
	m_layout->addWidget(m_titleDesc);
	m_layout->addWidget(m_render);
}
