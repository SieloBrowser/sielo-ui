#include "ContainersView.hpp"

#include "Container.hpp"

ContainersView::ContainersView(QWidget* parent) :
	QWidget(parent)
{
	setupUi();

	show();

	auto cont1 = createContainer("Container 1", 0, 0);
	auto cont2 = createContainer("Container 2", 1, 0);
	auto cont3 = createContainer("Container 3", 2, 0);
	auto cont4 = createContainer("Container 4", 0, 1);
	auto cont5 = createContainer("Container 5", 0, 2);
	auto cont6 = createContainer("Container 6", 1, 1);
	auto cont7 = createContainer("Container 7", 1, 2);
	auto cont8 = createContainer("Container 8", 2, 1);
	auto cont9 = createContainer("Container 9", 2, 2);

}

Container* ContainersView::createContainer(const QString& title, int x, int y)
{
	const auto container{new Container(title, this, x, y)};

	return insertContainer(container, x, y);
}

Container* ContainersView::insertContainer(Container* container, int x, int y)
{
	// First, we dont have any coordinate are there is no column 
	// are that x is greater than column count
	if (m_columns.isEmpty() || (x == -1 && y == -1) || x >= m_columns.count()) {
		// We create a new column
		QSplitter* column{new QSplitter(Qt::Vertical, this)};
		column->addWidget(container);

		m_columns.append(column);
		m_containersSplitter->addWidget(column);
		m_containers.append(container);

		// Dont forget to update new column coordinate
		container->x = m_columns.count() - 1;
		container->y = 0;

		return container;
	}

	// If we want to insert column (y is invalid)
	if (x >= 0 && y == -1) {
		// We create a column
		QSplitter* column{new QSplitter(Qt::Vertical, this)};
		column->addWidget(container);

		// We increase the "x" value of all containers after the new one
		for (auto i{x}; i < m_columns.count(); ++i) {
			for (auto j{0}; j < m_columns[i]->count(); ++j) {
				++(dynamic_cast<Container*>(m_columns[i]->widget(j)))->x;
			}
		}

		m_columns.insert(x, column);
		m_containersSplitter->insertWidget(x, column);
		m_containers.append(container);

		// Dont forget to update new column coordinate
		container->x = x;
		container->y = 0;

		return container;
	}

	// If we want to insert container in an existing column (both x and y are valide)
	if (x >= 0 && y >= 0) {
		// We increate the "y" value of current column containers
		for (auto i{y}; i < m_columns[x]->count(); ++i) {
			++(dynamic_cast<Container*>(m_columns[x]->widget(i)))->y;
		}

		// We finally insert the column
		m_columns[x]->insertWidget(y, container);
		m_containers.append(container);

		// Dont forget to update new column coordinate
		container->x = x;
		container->y = y >= m_columns[x]->count() ? m_columns[x]->count() - 1 : y;

		return container;
	}

	return nullptr;
}

void ContainersView::detachContainer(Container* container)
{
	// If the widget fill the column
	if (m_columns[container->x]->count() == 1) {
		for (auto i{container->x + 1}; i < m_columns.count(); ++i) {
			for (auto j{0}; j < m_columns[i]->count(); ++j) {
				--(dynamic_cast<Container*>(m_columns[i]->widget(j)))->x;
			}
		}
	}
	else {
		for (auto i{container->y}; i < m_columns[container->x]->count(); ++i) {
			--(dynamic_cast<Container*>(m_columns[container->x]->widget(i)))->y;
		}
	}

	container->setParent(nullptr);
	container->setContainersView(nullptr);
	container->x = -1;
	container->y = -1;
	m_containers.removeOne(container);
}

void ContainersView::setupUi()
{
	m_layout = new QVBoxLayout(this);

	m_addressBar = new QLineEdit(this);
	m_containersSplitter = new QSplitter(Qt::Horizontal, this);

	m_layout->addWidget(m_addressBar);
	m_layout->addWidget(m_containersSplitter);
}
