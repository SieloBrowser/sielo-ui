#include "ContainerMimeData.hpp"

#include "Views/Container.hpp"

ContainerMimeData::ContainerMimeData() 
{
	// Empty
}

void ContainerMimeData::setContainer(Container* container)
{
	m_container = container;
}

Container* ContainerMimeData::container() const
{
	return m_container;
}

bool ContainerMimeData::hasFormat(const QString& mimetype) const
{
	if (mimetype == "container") {
		return m_container && m_container->isValid();
	}

	return false;
}

QStringList ContainerMimeData::formats() const
{
	return QStringList() << "container";
}

QVariant ContainerMimeData::retrieveData(const QString& mimetype, QVariant::Type preferredType) const
{
	return QVariant();
}
