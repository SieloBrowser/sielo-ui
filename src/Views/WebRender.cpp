#include "WebRender.hpp"

#include <QStyleOption>
#include <QPainter>

WebRender::WebRender(QWidget* parent) : 
	QWidget(parent)
{
	setObjectName("sielo-web-render");
	setMinimumHeight(248);

	m_layout = new QVBoxLayout(this);

	m_info = new QLabel(tr("This is a render zone for the web engine"), this);

	m_layout->addWidget(m_info);
}

void WebRender::paintEvent(QPaintEvent* event)
{
	QStyleOption options{};
	options.initFrom(this);

	QPainter painter{this};

	style()->drawPrimitive(QStyle::PE_Widget, &options, &painter, this);
}
