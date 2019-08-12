#include "Container.hpp"

#include <utility>

#include "Utils/ContainerMimeData.hpp"

#include "ContainerDragWidget.hpp"
#include "ContainersView.hpp"
#include "WebRender.hpp"

Container::Container(QString title, ContainersView* containersView, int x, int y, QWidget* parent) :
	QWidget(parent), cordX(x), cordY(y), m_containersView(containersView), m_title(std::move(title))
{
	setupUi();

	setAcceptDrops(true);
	setAutoFillBackground(true);
}

bool Container::isValid() const
{
	return cordX != -1 && cordY != -1;
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
	if (event->mimeData()->hasFormat("container")) {
		event->acceptProposedAction();

		if (!m_highlightFrame) {
			m_highlightFrame = new QFrame(this);
			m_highlightFrame->setObjectName(QLatin1String("sielo-highlight-new-container"));
			m_highlightFrame->setStyleSheet(
				"#sielo-highlight-new-container{background: rgba(66, 134, 244, 0.5);}" + styleSheet());
			m_highlightFrame->setAttribute(Qt::WA_TransparentForMouseEvents);
			m_highlightFrame->show();
		}

		return;
	}

	QWidget::dragEnterEvent(event);
}

void Container::dragMoveEvent(QDragMoveEvent* event)
{
	if (event->mimeData()->hasFormat("container")) {
		const QRect topRect(x(), y(), width(), height() / 3);
		const QRect bottomRect(x(), y() + height() * 2 / 3, width(), height() / 3);
		const QRect leftRect(x(), y(), width() / 2, height());
		const QRect rightRect(x() + width() / 2, y(), width() / 2, height());

		const QRect showingTopRect(mapFromParent(QPoint(x(), y())), QPoint(width(), height() / 3));
		const QRect showingBottomRect(mapFromParent(QPoint(x(), y())).x(), mapFromParent(QPoint(x(), y())).y() + height() * 2/3, width(), height() / 3);
		const QRect showingLeftRect(mapFromParent(QPoint(x(), y())), QPoint(width() / 3, height()));
		const QRect showingRightRect(mapFromParent(QPoint(x(), y())).x() + width() * 2/3, mapFromParent(QPoint(x(), y())).y(), width() / 3, height());

		if (topRect.contains(mapToParent(event->pos()))) {
			m_highlightFrame->setGeometry(showingTopRect);
		}
		else if (bottomRect.contains(mapToParent(event->pos()))) {
			m_highlightFrame->setGeometry(showingBottomRect); 
		}
		else if (leftRect.contains(mapToParent(event->pos()))) {
			m_highlightFrame->setGeometry(showingLeftRect); 
		}
		else if (rightRect.contains(mapToParent(event->pos()))) {
			m_highlightFrame->setGeometry(showingRightRect); ;
		}

		event->acceptProposedAction();

		return;
	}

	QWidget::dragMoveEvent(event);
}

void Container::dragLeaveEvent(QDragLeaveEvent* event)
{
	if (m_highlightFrame) {
		m_highlightFrame->deleteLater();
		m_highlightFrame = nullptr;
	}

	QWidget::dragLeaveEvent(event);
}

void Container::dropEvent(QDropEvent* event)
{
	if (event->mimeData()->hasFormat("container")) {
		Container* dropContainer = qobject_cast<const ContainerMimeData*>(event->mimeData())->container();

		const QRect topRect(x(), y(), width(), height() / 3);
		const QRect bottomRect(x(), y() + height() * 2 / 3, width(), height() / 3);
		const QRect leftRect(x(), y(), width() / 2, height());
		const QRect rightRect(x() + width() / 2, y(), width() / 2, height());

		if (dropContainer != this) {
			// We detach the dropped container
			dropContainer->containersView()->detachContainer(dropContainer);

			// We attach and insert it to his new container, in a new column right now
			dropContainer->setContainersView(m_containersView);
		}

		if (topRect.contains(mapToParent(event->pos()))) {
			if (dropContainer == this) {
				m_highlightFrame->deleteLater();
				m_highlightFrame = nullptr;

				event->acceptProposedAction();

				return;
			}

			m_containersView->insertContainer(dropContainer, cordX, cordY);
		}
		else if (bottomRect.contains(mapToParent(event->pos()))) {
			if (dropContainer == this) {
				m_highlightFrame->deleteLater();
				m_highlightFrame = nullptr;

				event->acceptProposedAction();

				return;
			}

			m_containersView->insertContainer(dropContainer, cordX, cordY + 1);
		}
		else if (leftRect.contains(mapToParent(event->pos()))) {
			m_containersView->insertContainer(dropContainer, cordX, -1);
		}
		else if (rightRect.contains(mapToParent(event->pos()))) {
			m_containersView->insertContainer(dropContainer, cordX + 1, -1);
		}

		m_highlightFrame->deleteLater();
		m_highlightFrame = nullptr;

		event->acceptProposedAction();

		return;
	}

	QWidget::dropEvent(event);
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
