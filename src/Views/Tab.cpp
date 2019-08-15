#include "Tab.hpp"

#include "BubbleButton.hpp"

#include "WebRender.hpp"

Tab::Tab(const QString& icon, QWidget* parent) :
	QWidget(parent)
{
	m_tabIcon = new BubbleButton(icon, this);
	m_tabRender = new WebRender(this);
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
