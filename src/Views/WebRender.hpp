#ifndef WEBRENDER_HPP
#define WEBRENDER_HPP

#include <QWidget>
#include <QLabel>

#include <QVBoxLayout>

class WebRender: public QWidget {
	Q_OBJECT

public:
	explicit WebRender(QWidget* parent = nullptr);
	~WebRender() = default;

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	QVBoxLayout* m_layout{};
	QLabel* m_info{};
};
#endif // WEBRENDER_HPP
