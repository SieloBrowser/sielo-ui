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

	void createContainer(int x = -1, int y = -1);

private:
	void setupUi();

	QVBoxLayout* m_layout{};

	QLineEdit* m_addressBar{};
	QSplitter* m_containersSplitter{};
	QVector<QSplitter*> m_columns{};

	QVector<Container*> m_containers{};
};

#endif // CONTAINERSVIEW_HPP
