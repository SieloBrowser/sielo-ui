#ifndef CONTAINERSVIEW_HPP
#define CONTAINERSVIEW_HPP

#include <QWidget>

#include <QLineEdit>
#include <QSplitter>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QVector>

class Container;

class ContainersView: public QWidget {
	Q_OBJECT

public:
	explicit ContainersView(QWidget* parent = nullptr);
	~ContainersView() = default;

	Container* createContainer(const QString& title, int x = -1, int y = -1);
	Container* insertContainer(Container *container, int x, int y);
	void detachContainer(Container* container);

	void equalizeSize();

private:
	void setupUi();

	QVBoxLayout* m_layout{};

	QLineEdit* m_addressBar{};
	QSplitter* m_containersSplitter{};
	QVector<QSplitter*> m_columns{};

	QVector<Container*> m_containers{};
};

#endif // CONTAINERSVIEW_HPP
