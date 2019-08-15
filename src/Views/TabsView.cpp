#include "TabsView.hpp"

#include <QStyleOption>
#include <QPainter>

#include <QWidgetItem>

#include "WebRender.hpp"

#include "Container.hpp"

#include "Tab.hpp"

TabsView::TabsView(Container* parent) :
	QScrollArea(parent),
	m_container(parent)
{
	setObjectName("sielo-tabs-view");

	setWidgetResizable(true);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void TabsView::setActiveTab(Tab* tab)
{
	setWidget(tab);

	m_gridView->deleteLater();
}
void TabsView::setActiveTab(int index) {}

void TabsView::organize(OrganisationType organisation)
{
	if (organisation == OrganisationType::Grid) {
		if (!m_gridView) {
			m_gridView = new QWidget(this);
			m_gridLayout = new QGridLayout(m_gridView);

			setWidget(m_gridView);
		}

		auto x{0};
		auto y{0};
		for (auto i{0}; i < m_container->tabs().count(); ++i) {
			if (y == 3) {
				++x;
				y = 0;
			}

			m_gridLayout->addWidget(m_container->tabs()[i], x, y, 1, 1);

			++y;
		}
	}
}

void TabsView::paintEvent(QPaintEvent* event)
{
	QStyleOption options{};
	options.initFrom(this);

	QPainter painter{this};

	style()->drawPrimitive(QStyle::PE_Widget, &options, &painter, this);
}
