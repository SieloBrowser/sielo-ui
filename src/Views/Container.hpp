#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <QWidget>

#include <QHBoxLayout>

class WebRender;

class Container : public QWidget {
	Q_OBJECT

public:
	explicit Container(int x, int y, QWidget* parent = nullptr);
	~Container() = default;

	int x{-1};
	int y{-1};

	bool isValide() const;

private:
	void setupUi();

	QHBoxLayout* m_layout{};

	WebRender* m_render{};
};

#endif // CONTAINER_HPP
