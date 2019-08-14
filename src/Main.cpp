#include <QApplication>

#include "BrowserWindow.hpp"
#include "Views/WebRender.hpp"

#include <QFile>
#include <QDir>

QString readFile(const QString& filename)
{
	QFile file{filename};

	if (!filename.isEmpty() && file.open(QFile::ReadOnly)) {
		const QByteArray array{file.readAll()};

		file.close();

		return QString::fromUtf8(array);
	}

	return QString();
}

int main(int argc, char** argv)
{
	QApplication app{argc, argv};

	const auto relativePath{QDir::current().relativeFilePath(QDir::current().absolutePath() + "/themes/")};
	auto style{readFile(QDir::current().absolutePath() + "/themes/default.sss")};

	style.replace(QRegExp(QStringLiteral("url\\s*\\(\\s*([^\\*:\\);]+)\\s*\\)")),
				QString("url(%1/\\1)").arg(relativePath));

	std::string stdStyle = style.toStdString();

	app.setStyleSheet(style);

	BrowserWindow firstWindow{};
	firstWindow.show();

	return app.exec();
}