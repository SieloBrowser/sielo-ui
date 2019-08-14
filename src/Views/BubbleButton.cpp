#include "BubbleButton.hpp"

#include <QIcon>

#include <QDir>

BubbleButton::BubbleButton(const QString& icon, QWidget* parent) :
	QPushButton(parent)
{
	setObjectName("sielo-bubble-button-" + icon);

	setFixedSize(96, 96);
	setIconSize(QSize(48, 48));

	//setIcon(QIcon::fromTheme(icon, QIcon(":icons/" + icon + ".svg")));
	setIcon(QIcon::fromTheme(icon, QIcon(QDir::current().absolutePath() + "/themes/icons/" + icon + ".svg")));
}
