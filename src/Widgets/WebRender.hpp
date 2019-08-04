#include <qwidget.h>

#include <qlabel.h>

#include <qlayout.h>

class WebRender: public QWidget {
	Q_OBJECT

public:
	explicit WebRender(QWidget* parent = nullptr);
	~WebRender();

private:
	QVBoxLayout* m_layout{};
	QLabel* m_info{};
};