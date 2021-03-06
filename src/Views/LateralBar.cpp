#include "LateralBar.hpp"

#include <QStyleOption>
#include <QPainter>

#include "Container.hpp"

#include "Tab.hpp"

#include "BubbleButton.hpp"

LateralBar::LateralBar(Container* parent) :
	QWidget(parent),
	m_container(parent)
{
	setObjectName("sielo-lateral-bar");
	setupUi();

	//setStyleSheet("#sielo-lateral-bar { background: magenta; }");

	connect(m_buttonAddTab, &BubbleButton::clicked, m_container, &Container::addNewTab);

	connect(m_buttonShowTabs, &BubbleButton::clicked, m_container, &Container::organize);
}

void LateralBar::addTab(Tab* button)
{
	m_tabsButtonsLayout->insertWidget(m_tabsButtonsLayout->count() - 2, button->tabIcon());
}

void LateralBar::removeTab(Tab* button)
{
	m_tabsButtonsLayout->removeWidget(button->tabIcon());
}

void LateralBar::showTabs()
{
	m_tabsButtonsWidget->show();
}

void LateralBar::hideTabs()
{
	m_tabsButtonsWidget->hide();
}

void LateralBar::paintEvent(QPaintEvent* event)
{
	QStyleOption options{};
	options.initFrom(this);

	QPainter painter{this};

	style()->drawPrimitive(QStyle::PE_Widget, &options, &painter, this);
}

void LateralBar::setupUi()
{
	setMaximumWidth(64);

	m_layout = new QVBoxLayout(this);

	m_tabsButtonsLayout = new QVBoxLayout();
	m_controlesButtonsLayout = new QVBoxLayout();

	m_tabsButtonsWidget = new QWidget(this);
	m_tabsButtonsWidget->setObjectName("sielo-lateral-bar-tabs-container");
	m_tabsButtonsWidget->setLayout(m_tabsButtonsLayout);
	m_tabsButtonsWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
	//m_tabsButtonsWidget->setMinimumSize(128, 128);

	m_controlesButtonsWidget = new QWidget(this);
	m_controlesButtonsWidget->setObjectName("sielo-lateral-bar-controles-container");
	m_controlesButtonsWidget->setLayout(m_controlesButtonsLayout);
	m_controlesButtonsWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	m_tabsButtonsScrollArea = new QScrollArea(this);
	m_tabsButtonsScrollArea->setObjectName("sielo-lateral-bar-scrollarea");
	m_tabsButtonsScrollArea->setWidget(m_tabsButtonsWidget);
	m_tabsButtonsScrollArea->setWidgetResizable(true);

	m_layout->addWidget(m_tabsButtonsScrollArea);
	m_layout->addWidget(m_controlesButtonsWidget);

	m_buttonAddTab = new BubbleButton("tab_add", this);
	m_buttonBookmarks = new BubbleButton("bookmarks", this);
	m_buttonHistory = new BubbleButton("history", this);
	m_buttonShowTabs = new BubbleButton("show_tabs", this);
	m_buttonProfile = new BubbleButton("profile", this);

	// TODO: fromalize that
	m_tabsButtonsLayout->addWidget(m_buttonAddTab);
	m_tabsButtonsLayout->addItem(new QSpacerItem(10, 10, QSizePolicy::Preferred, QSizePolicy::Expanding));

	m_controlesButtonsLayout->addWidget(m_buttonBookmarks);
	m_controlesButtonsLayout->addWidget(m_buttonHistory);
	m_controlesButtonsLayout->addWidget(m_buttonShowTabs);
	m_controlesButtonsLayout->addWidget(m_buttonProfile);

	m_layout->setMargin(0);
	m_controlesButtonsLayout->setMargin(8);
	m_tabsButtonsLayout->setMargin(8);
}
