#include "ContainersView.hpp"

#include "Container.hpp"

ContainersView::ContainersView(QWidget* parent) :
	QWidget(parent)
{
	setupUi();

	createContainer(0, 0);
	createContainer(1, 0);
	createContainer(0, 1);
}

void ContainersView::createContainer(int x, int y)
{
	Container* container{new Container(x, y)};

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
		container->x = m_containers.count() - 1;
		container->y = 0;

		return;
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

		return;
	}

	// If we want to insert container in an existing column (both x and y are valide)
	if (x >= 0 && y >= 0) {
		// We increate the "y" value of current column containers
		for (auto i{y}; y < m_columns[x]->count(); ++i) {
			++(dynamic_cast<Container*>(m_columns[x]->widget(i)))->y;
		}

		// We finally insert the column
		m_columns[x]->insertWidget(y, container);
		m_containers.append(container);

		// Dont forget to update new column coordinate
		container->x = x;
		container->y = y;
	}
}

void ContainersView::setupUi()
{
	m_layout = new QVBoxLayout(this);

	m_addressBar = new QLineEdit(this);
	m_containersSplitter = new QSplitter(Qt::Horizontal, this);

	m_layout->addWidget(m_addressBar);
	m_layout->addWidget(m_containersSplitter);
}
