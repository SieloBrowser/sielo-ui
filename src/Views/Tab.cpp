#include "Tab.hpp"

#include "BubbleButton.hpp"

#include "WebRender.hpp"

Tab::Tab(const QString& icon, QWidget* parent) :
	QWidget(parent)
{
	m_layout = new QGridLayout(this);

	m_tabIcon = new BubbleButton(icon, this);
	m_closeButton = new QPushButton(tr("Close Tab"), this);
	m_tabRender = new WebRender(this);

	m_layout->addWidget(m_tabIcon, 0, 0, 1, 1);
	m_layout->addWidget(m_closeButton, 0, 1, 1, 1);
	m_layout->addWidget(m_tabRender, 1, 0, 1, 2);
}

void Tab::cardState()
{
	m_layout->addWidget(m_tabIcon, 0, 0, 1, 1);
	m_layout->addWidget(m_closeButton, 0, 1, 1, 1);
	m_layout->addWidget(m_tabRender, 1, 0, 1, 2);
}

BubbleButton* Tab::tabIcon() const
{
	return m_tabIcon;
}

void Tab::setIcon(const QIcon& icon)
{
	m_tabIcon->setIcon(icon);
}

WebRender* Tab::tabRender() const
{
	return m_tabRender;
}
