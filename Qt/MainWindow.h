#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtWidgets>
#include <QtGui>

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
//	enum Color{
//		Black = 0,
//		Red = 1,
//		Green = 2,
//		Yellow = 3,
//		Blue = 4,
//		Magenta = 5,
//		Cyan = 6,
//		White = 7,
//		Black_ = 8,
//		Red_ = 9,
//		Green_ = 10,
//		Yellow_ = 11,
//		Blue_ = 12,
//		Maganta_ = 13,
//		Cyan_ = 14,
//		White_ = 15
//	};

private:
	const QList<QString> colorName = {
		"Black",  "Red",  "Green",  "Yellow",  "Blue",  "Magenta",  "Cyan",  "White",
		"Black+", "Red+", "Green+", "Yellow+", "Blue+", "Magenta+", "Cyan+", "White+",
	};
	const QList<QString> colorDisplayName = {
		"Black", "Red", "Green", "Yellow", "Blue", "Maganta", "Cyan", "White",
		"Light Black", "Light Red", "Light Green", "Light Yellow", "Light Blue", "Light Maganta", "Light Cyan", "Light White",
	};
	const QList<QString> colorValue = {
		"#000000", "#bb0000", "#006400", "#c8af00", "#1e90f5", "#bb00bb", "#00cdcd", "#ebebeb",
		"#555555", "#ff5555", "#55ff55", "#fff555", "#50beff", "#ff55ff", "#55ffff", "#ffffff",
	};
	const QHash<QString, int> termHash = {
		{"#000000", 0}, {"#bb0000", 1}, {"#006400", 2}, {"#c8af00", 3}, {"#1e90f5", 4}, {"#bb00bb", 5}, {"#00cdcd", 6}, {"#ebebeb", 7},
		{"#555555", 60}, {"#ff5555", 61}, {"#55ff55", 62}, {"#fff555", 63}, {"#50beff", 64}, {"#ff55ff", 65}, {"#55ffff", 66}, {"#ffffff", 67},
	};

	QList<QAction *> fgColorActions;
	QList<QAction *> bgColorActions;
	QAction *executeAction = new QAction("Execute", this);

	QTextEdit *textEdit = new QTextEdit(this);
	QPlainTextEdit *pTextEdit = new QPlainTextEdit(this);

	QSplitter *splitter = new QSplitter(Qt::Vertical, this);
	QToolBar *foregroundColorToolBar = nullptr;
	QToolBar *backgroundColorToolBar = nullptr;
	QToolBar *toolBar = nullptr;

public:
	MainWindow(QWidget *parent = 0): QMainWindow(parent){
		this->splitter->addWidget(this->textEdit);
		this->splitter->addWidget(this->pTextEdit);
		this->setCentralWidget(this->splitter);
		this->setWindowTitle("C++");

		QPalette pal = this->textEdit->palette();{
			pal.setColor(QPalette::Background, QColor("#000000"));
			pal.setColor(QPalette::Base, QColor("#000000"));
			pal.setColor(QPalette::Foreground, QColor("#ebebeb"));
			pal.setColor(QPalette::Text, QColor("#ebebeb"));
		}
		this->textEdit->setPalette(pal);
		this->pTextEdit->setPalette(pal);
		QFont fnt = this->textEdit->font();{
			fnt.setFamily("courier new");
			fnt.setPixelSize(12);
		}
		this->textEdit->setFont(fnt);

//		this->textEdit->document()->setDefaultStyleSheet("fBlack{color: #000000;}"
//														 "fRed{color: #bb0000;}"
//														 "fGreen{color: #006400;}"
//														 "fYellow{color: #c8af00;}"
//														 "fBlue{color: #1e90f5}"
//														 "fMagenta{color: #bb00bb}"
//														 "fCyan{color: #00cdcd}"
//														 "fWhite{color: #ebebeb}"
//														 "fBlack_{color: #555555}"
//														 "fRed_{color: #ff5555}"
//														 "fGreen_{color: #55ff55}"
//														 "fYellow_{color: #fff555}"
//														 "fBlue_{color: #50beff}"
//														 "fMagenta_{color: #ff55ff}"
//														 "fCyan_{color: #55ffff}"
//														 "fWhite_{color: #ffffff}"
//														 "bBlack{background-color: #000000;}"
//														 "bRed{background-color: #bb0000;}"
//														 "bGreen{background-color: #006400;}"
//														 "bYellow{background-color: #c8af00;}"
//														 "bBlue{background-color: #1e90f5}"
//														 "bMagenta{background-color: #bb00bb}"
//														 "bCyan{background-color: #00cdcd}"
//														 "bWhite{background-color: #ebebeb}"
//														 "bBlack_{background-color: #555555}"
//														 "bRed_{background-color: #ff5555}"
//														 "bGreen_{background-color: #55ff55}"
//														 "bYellow_{background-color: #fff555}"
//														 "bBlue_{background-color: #50beff}"
//														 "bMagenta_{background-color: #ff55ff}"
//														 "bCyan_{background-color: #55ffff}"
//														 "bWhite_{background-color: #ffffff}");

		this->foregroundColorToolBar = this->addToolBar("Foreground Color");
		this->backgroundColorToolBar = this->addToolBar("Background Color");
		this->toolBar = this->addToolBar("Tools");

		this->foregroundColorToolBar->setFloatable(false);
		this->backgroundColorToolBar->setFloatable(false);
		this->toolBar->setFloatable(false);

		this->createToolBar();

//		this->connect(this->textEdit, &QTextEdit::selectionChanged, [this](){
//			//qDebug() << this->textEdit->textCursor().selection().toPlainText();
//		});

		this->textEdit->insertHtml("The quick brown fox jump over the lazy dog.");

	}

	~MainWindow(){

	}
private:
	void createToolBar(){
		if(this->foregroundColorToolBar == nullptr || this->backgroundColorToolBar == nullptr){
			return;
		}
		const QString prefix = "data/image/";
		const QString suffix = ".png";
//		this->fBlackAct->setIcon(QIcon(prefix % "fBlack" % suffix));
//		this->connect(this->fBlackAct, &QAction::triggered, [this](bool){
//			QTextCursor cursor = this->textEdit->textCursor();
//			QTextCharFormat format = cursor.charFormat();
//			format.setForeground(QBrush(QColor("#000000")));
//			this->textEdit->mergeCurrentCharFormat(format);
//		});
//		this->backgroundColorToolBar->addAction(this->fBlackAct);

		QString groundPrefix = "f";
		QString groundDisplaySuffix = "Foreground";
		for(int i = 0; i < this->colorName.length(); i++){
			QAction *action = new QAction(this->colorDisplayName[i] % " " % groundDisplaySuffix, this);
			this->fgColorActions.append(action);
			action->setIcon(QIcon(prefix % groundPrefix % this->colorName[i] % suffix));
			qDebug() << prefix % groundPrefix % this->colorName[i] % suffix;
			this->connect(action, &QAction::triggered, [this, i](bool){
				QTextCursor cursor = this->textEdit->textCursor();
				QTextCharFormat format = cursor.charFormat();
				format.setForeground(QBrush(QColor(this->colorValue[i])));
				this->textEdit->mergeCurrentCharFormat(format);
			});
		}
		this->foregroundColorToolBar->addActions(this->fgColorActions);

		groundPrefix = "b";
		groundDisplaySuffix = "Background";
		for(int i = 0; i < this->colorName.length(); i++){
			QAction *action = new QAction(this->colorDisplayName[i] % " " % groundDisplaySuffix, this);
			this->bgColorActions.append(action);
			action->setIcon(QIcon(prefix % groundPrefix % this->colorName[i] % suffix));
			this->connect(action, &QAction::triggered, [this, i](bool){
				QTextCursor cursor = this->textEdit->textCursor();
				QTextCharFormat format = cursor.charFormat();
				format.setBackground(QBrush(QColor(this->colorValue[i])));
				this->textEdit->mergeCurrentCharFormat(format);
			});
		}
		this->backgroundColorToolBar->addActions(this->bgColorActions);

		this->executeAction->setIcon(QIcon(prefix % "execute" % suffix));
		this->connect(this->executeAction, &QAction::triggered, [this](bool){
			QString html = this->textEdit->toHtml();
			QRegularExpression regex = QRegularExpression("\\<p[^\\>]+\\>(.+)\\<\\/p\\>", QRegularExpression::MultilineOption);
			QRegularExpression spanRegex = QRegularExpression("<span style=\"[^\"]+\">", QRegularExpression::MultilineOption);
			QRegularExpression fgRegex = QRegularExpression("[^-]color:(#[0-9A-Fa-f]{6});");
			QRegularExpression bgRegex = QRegularExpression("background-color:(#[0-9A-Fa-f]{6});");
			QRegularExpressionMatchIterator matchG = regex.globalMatch(html);
			while(matchG.hasNext()){
				QRegularExpressionMatch matchP = matchG.next();
				QString content = matchP.captured(1);
				content.replace("</span>", "\\e[0m");
				//this->pTextEdit->insertPlainText(content);
				QRegularExpressionMatchIterator matchI = spanRegex.globalMatch(content);
				while(matchI.hasNext()){
					QString echoStr = "\\e[";
					bool resume = false;
					QRegularExpressionMatch match = matchI.next();
					QString spanText = match.captured(0);
					//QString spanContent = match.captured(1);
					QRegularExpressionMatch colorMatched = fgRegex.match(spanText);
					if(colorMatched.hasMatch()){
						QString color = colorMatched.captured(1);
						echoStr.append(QString::number(this->termHash.value(color, 0) + 30));
						resume = true;
					}
					QRegularExpressionMatch backColorMatched = bgRegex.match(spanText);
					if(backColorMatched.hasMatch()){
						QString backcolor = backColorMatched.captured(1);
						if(resume){
							echoStr.append(";");
						}
						echoStr.append(QString::number(this->termHash.value(backcolor, 0) + 40));
						resume = true;
					}
					echoStr.append("m");
					content.replace(spanText, echoStr);
				}
				this->pTextEdit->insertPlainText(content % "\n");
			}
		});
		this->toolBar->addAction(this->executeAction);

	}
};

#endif // MAINWINDOW_H
