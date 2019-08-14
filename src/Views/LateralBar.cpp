#include "LateralBar.hpp"

LateralBar::LateralBar(QWidget* parent) :
	QWidget(parent)
{
	setObjectName("sielo-lateral-bar");
	setupUi();

	//setStyleSheet("#sielo-lateral-bar { background: magenta; }");

	addTab(new QPushButton("Onglet 1", this));
	addTab(new QPushButton("Onglet 2", this));
}

void LateralBar::addTab(QPushButton* button)
{
	m_tabsButtonsLayout->insertWidget(m_tabsButtonsLayout->count() - 2, button);
}

void LateralBar::removeTab(QPushButton* button)
{
	m_tabsButtonsLayout->removeWidget(button);
}

void LateralBar::setupUi()
{
	setMaximumWidth(196);

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
	m_tabsButtonsScrollArea->setWidget(m_tabsButtonsWidget);
	m_tabsButtonsScrollArea->setWidgetResizable(true);

	m_layout->addWidget(m_tabsButtonsScrollArea);
	m_layout->addWidget(m_controlesButtonsWidget);

	// TODO: fromalize that
	m_tabsButtonsLayout->addWidget(new QPushButton("+", this));
	m_tabsButtonsLayout->addItem(new QSpacerItem(10, 10, QSizePolicy::Preferred, QSizePolicy::Expanding));

	m_controlesButtonsLayout->addWidget(new QPushButton("<3", this));
	m_controlesButtonsLayout->addWidget(new QPushButton("()", this));
	m_controlesButtonsLayout->addWidget(new QPushButton("[]", this));
	m_controlesButtonsLayout->addWidget(new QPushButton(":3", this));
}
