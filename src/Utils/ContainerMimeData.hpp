#ifndef CONTAINERMIMEDATA_HPP
#define CONTAINERMIMEDATA_HPP

#include <QMimeData>

class Container;

class ContainerMimeData : public QMimeData {
	Q_OBJECT

public:
	explicit ContainerMimeData();
	~ContainerMimeData() = default;

	void setContainer(Container* container);
	Container* container() const;

	bool hasFormat(const QString& mimetype) const override;
	QStringList formats() const override;

protected:
	QVariant retrieveData(const QString& mimetype, QVariant::Type preferredType) const override;

private:
	Container* m_container{};
};

#endif // CONTAINERMIMEDATA_HPP
