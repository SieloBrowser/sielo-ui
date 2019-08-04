#include "WebRender.hpp"

WebRender::WebRender(QWidget* parent) : 
	QWidget(parent)
{
	m_layout = new QVBoxLayout(this);

	m_info = new QLabel(tr("This is a render zone for the web engine"), this);

	m_layout->addWidget(m_info);
}

WebRender::~WebRender()
{
	// Empty
}
