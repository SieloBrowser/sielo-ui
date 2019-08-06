#include "Container.hpp"

#include "WebRender.hpp"

Container::Container(int x, int y, QWidget* parent) :
	QWidget(parent), x(x), y(y)
{
	setupUi();
}

bool Container::isValide() const
{
	return x != -1 && y != -1;
}

void Container::setupUi()
{
	m_layout = new QHBoxLayout(this);

	m_render = new WebRender(this);

	m_layout->addWidget(m_render);
}
