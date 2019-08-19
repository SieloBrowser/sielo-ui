#include "ContainersView.hpp"

#include <QStyleOption>
#include <QPainter>

#include "Container.hpp"

ContainersView::ContainersView(QWidget* parent) :
	QWidget(parent)
{
	setObjectName("sielo-view-containers");
	setupUi();

	show();

	auto cont1 = createContainer(0, 0);
	auto cont2 = createContainer(1, 0);
	auto cont3 = createContainer(0, 1);

}

Container* ContainersView::createContainer(int x, int y)
{
	const auto container{new Container(this, x, y)};

	return insertContainer(container, x, y);
}

Container* ContainersView::insertContainer(Container* container, int x, int y)
{
	// First, we dont have any coordinate are there is no column 
	// are that cordX is greater than column count
	if (m_columns.isEmpty() || (x == -1 && y == -1) || x >= m_columns.count()) {
		// We create a new column
		QSplitter* column{new QSplitter(Qt::Vertical, this)};
		column->addWidget(container);

		m_columns.append(column);
		m_containersSplitter->addWidget(column);
		m_containers.append(container);

		// Dont forget to update new column coordinate
		container->cordX = m_columns.count() - 1;
		container->cordY = 0;

		return container;
	}

	// If we want to insert column (cordY is invalid)
	if (x >= 0 && y == -1) {
		// We create a column
		QSplitter* column{new QSplitter(Qt::Vertical, this)};
		column->addWidget(container);

		// We increase the "cordX" value of all containers after the new one
		for (auto i{x}; i < m_columns.count(); ++i) {
			for (auto j{0}; j < m_columns[i]->count(); ++j) {
				Container* containerToModify = dynamic_cast<Container*>(m_columns[i]->widget(j));
				std::string title = containerToModify->title().toStdString();

				containerToModify->cordX = containerToModify->cordX + 1;

				int pause{0};
			}
		}

		m_columns.insert(x, column);
		m_containersSplitter->insertWidget(x, column);
		m_containers.append(container);

		// Dont forget to update new column coordinate
		container->cordX = x;
		container->cordY = 0;

		return container;
	}

	// If we want to insert container in an existing column (both cordX and cordY are valide)
	if (x >= 0 && y >= 0) {
		// We increate the "cordY" value of current column containers
		for (auto i{y}; i < m_columns[x]->count(); ++i) {
			(dynamic_cast<Container*>(m_columns[x]->widget(i)))->cordY = (dynamic_cast<Container*>(m_columns[x]->widget(i)))->cordY + 1;
		}

		// We finally insert the column
		m_columns[x]->insertWidget(y, container);
		m_containers.append(container);

		// Dont forget to update new column coordinate
		container->cordX = x;
		container->cordY = y >= m_columns[x]->count() ? m_columns[x]->count() - 1 : y;

		return container;
	}

	return nullptr;
}

void ContainersView::detachContainer(Container* container)
{
	QSplitter* column = m_columns[container->cordX];

	// If the widget fill the column
	if (column->count() == 1) {
		for (auto i{container->cordX + 1}; i < m_columns.count(); ++i) {
			for (auto j{0}; j < m_columns[i]->count(); ++j) {
				--(dynamic_cast<Container*>(m_columns[i]->widget(j)))->cordX;
			}
		}

		m_columns.removeOne(column);
		column->deleteLater();
	}
	else {
		for (auto i{container->cordY + 1}; i < m_columns[container->cordX]->count(); ++i) {
			--(dynamic_cast<Container*>(m_columns[container->cordX]->widget(i)))->cordY;
		}
	}

	container->setParent(nullptr);
	container->setContainersView(nullptr);
	container->cordX = -1;
	container->cordY = -1;
	m_containers.removeOne(container);
}

void ContainersView::equalizeSize()
{
	QList<int> columnsWidth{};

	for (auto i{0}; i < m_columns.count(); ++i) {
		QList<int> rowHeights{};

		for (auto j{0}; j < m_columns[i]->count(); ++j) {
			rowHeights.append(height() / m_columns[i]->count());
		}

		m_columns[i]->setSizes(rowHeights);
		columnsWidth.append(width() / m_columns.count());
	}

	m_containersSplitter->setSizes(columnsWidth);
}

void ContainersView::paintEvent(QPaintEvent* event)
{
	QStyleOption options{};
	options.initFrom(this);

	QPainter painter{this};
	
	style()->drawPrimitive(QStyle::PE_Widget, &options, &painter, this);
}

void ContainersView::setupUi()
{
	m_layout = new QVBoxLayout(this);

	m_addressBar = new QLineEdit(this);
	m_containersSplitter = new QSplitter(Qt::Horizontal, this);

	m_layout->addWidget(m_addressBar);
	m_layout->addWidget(m_containersSplitter);
}
