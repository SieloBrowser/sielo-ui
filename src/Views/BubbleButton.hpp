#ifndef BUBBLEBUTTON_HPP
#define BUBBLEBUTTON_HPP

#include <QWidget>

#include <QPushButton>

class BubbleButton : public QPushButton {
	Q_OBJECT

public:
	explicit BubbleButton(const QString& icon, QWidget* parent = nullptr);
	~BubbleButton() = default;
};

#endif // BUBBLEBUTTON_HPP
