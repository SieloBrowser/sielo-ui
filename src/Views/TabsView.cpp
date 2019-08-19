#include "TabsView.hpp"

#include <QStyleOption>
#include <QPainter>

#include <QSize>

#include "WebRender.hpp"

#include "Container.hpp"

#include "Tab.hpp"

TabsView::TabsView(Container* parent) :
	QScrollArea(parent),
	m_container(parent)
{
	setObjectName("sielo-tabs-view");

	m_gridView = new QWidget(this);
	m_gridView->setObjectName("sielo-tabs-view");
	m_gridLayout = new QGridLayout(m_gridView);

	setWidgetResizable(true);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void TabsView::setActiveTab(Tab* tab)
{
	m_state = State::Full;

	takeWidget();
	setWidget(tab->tabRender());
}
void TabsView::setActiveTab(int index) {}

void TabsView::organize(State organisation)
{
	if (organisation == State::Full)
		return;

	m_state = organisation;

	if (organisation == State::Grid) {
		takeWidget();
		setWidget(m_gridView);
			
		if (width() > 730 /*&& m_gridLayout->columnCount() != 3*/) {
			organizeIntThree();
		}
		else if (width() > 508/* && m_gridLayout->columnCount() != 2*/) {
			organizeInTwo();
		}
		else /*if (m_gridLayout->columnCount() != 1)*/ {
			organizeInOne();
		}
	}
}

TabsView::State TabsView::state() const
{
	return m_state;
}

void TabsView::paintEvent(QPaintEvent* event)
{
	QStyleOption options{};
	options.initFrom(this);

	QPainter painter{this};

	style()->drawPrimitive(QStyle::PE_Widget, &options, &painter, this);
}

void TabsView::resizeEvent(QResizeEvent* event)
{
	if (m_state == State::Grid) {
		organize();
	}

	QScrollArea::resizeEvent(event);
}

void TabsView::organizeInOne()
{
	for (auto i{0}; i < m_container->tabs().count(); ++i) {
		m_container->tabs()[i]->cardState();
		m_gridLayout->addWidget(m_container->tabs()[i], i, 0, 1, 1);
	}
}
void TabsView::organizeInTwo()
{
	auto x{0};
	auto y{0};
	for (auto i{0}; i < m_container->tabs().count(); ++i) {
		if (y == 2) {
			++x;
			y = 0;
		}

		m_container->tabs()[i]->cardState();
		m_gridLayout->addWidget(m_container->tabs()[i], x, y, 1, 1);

		++y;
	}
}
void TabsView::organizeIntThree()
{
	auto x{0};
	auto y{0};
	for (auto i{0}; i < m_container->tabs().count(); ++i) {
		if (y == 3) {
			++x;
			y = 0;
		}

		m_container->tabs()[i]->cardState();
		m_gridLayout->addWidget(m_container->tabs()[i], x, y, 1, 1);

		++y;
	}
}
