#include "LateralBar.hpp"

#include <QStyleOption>
#include <QPainter>

#include "BubbleButton.hpp"

LateralBar::LateralBar(QWidget* parent) :
	QWidget(parent)
{
	setObjectName("sielo-lateral-bar");
	setupUi();

	//setStyleSheet("#sielo-lateral-bar { background: magenta; }");
}

void LateralBar::addTab(BubbleButton* button)
{
	m_tabsButtonsLayout->insertWidget(m_tabsButtonsLayout->count() - 2, button);
}

void LateralBar::removeTab(BubbleButton* button)
{
	m_tabsButtonsLayout->removeWidget(button);
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
	setMaximumWidth(146);

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

	// TODO: fromalize that
	m_tabsButtonsLayout->addWidget(new BubbleButton("tab_add", this));
	m_tabsButtonsLayout->addItem(new QSpacerItem(10, 10, QSizePolicy::Preferred, QSizePolicy::Expanding));

	m_controlesButtonsLayout->addWidget(new BubbleButton("bookmarks", this));
	m_controlesButtonsLayout->addWidget(new BubbleButton("history", this));
	m_controlesButtonsLayout->addWidget(new BubbleButton("show_tabs", this));
	m_controlesButtonsLayout->addWidget(new BubbleButton("profile", this));

	m_layout->setMargin(0);
	m_controlesButtonsLayout->setMargin(24);
	m_tabsButtonsLayout->setMargin(24);
}
