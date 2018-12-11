# -*- coding: utf-8 -*-

from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *

import re

class MainWindow(QMainWindow):
    colorName = [
        "Black", "Red", "Green", "Yellow", "Blue", "Magenta", "Cyan", "White",
        "Black+", "Red+", "Green+", "Yellow+", "Blue+", "Magenta+", "Cyan+", "White+",
    ]

    colorDisplayName = [
        "Black", "Red", "Green", "Yellow", "Blue", "Maganta", "Cyan", "White",
        "Light Black", "Light Red", "Light Green", "Light Yellow", "Light Blue", "Light Maganta", "Light Cyan", "Light White",
    ]

    colorValue = [
        "#000000", "#bb0000", "#006400", "#c8af00", "#1e90f5", "#bb00bb", "#00cdcd", "#ebebeb",
        "#555555", "#ff5555", "#55ff55", "#fff555", "#50beff", "#ff55ff", "#55ffff", "#ffffff",
    ]

    termHash = {
        "#000000": 0, "#bb0000": 1, "#006400": 2, "#c8af00": 3, "#1e90f5": 4, "#bb00bb": 5, "#00cdcd": 6, "#ebebeb": 7,
        "#555555": 60, "#ff5555": 61, "#55ff55": 62, "#fff555": 63, "#50beff": 64, "#ff55ff": 65, "#55ffff": 66, "#ffffff": 67,
    }

    def __init__(self, parent=None):
        super().__init__(parent, Qt.Window)
        self.fgColorActions = []
        self.bgColorActions = []
        self.executeAction: QAction = QAction("Execute", self)

        self.textEdit: QTextEdit = QTextEdit(self)
        self.pTextEdit: QPlainTextEdit = QPlainTextEdit(self)

        self.splitter: QSplitter = QSplitter(Qt.Vertical, self)
        self.foregroundColorToolBar: QToolBar = None
        self.backgroundColorToolBar: QToolBar = None
        self.toolBar: QToolBar = None

        self.splitter.addWidget(self.textEdit)
        self.splitter.addWidget(self.pTextEdit)
        self.setCentralWidget(self.splitter)
        self.setWindowTitle("Python")

        pal: QPalette = self.textEdit.palette()
        (
            pal.setColor(QPalette.Background, QColor("#000000")),
            pal.setColor(QPalette.Base, QColor("#000000")),
            pal.setColor(QPalette.Foreground, QColor("#ebebeb")),
            pal.setColor(QPalette.Text, QColor("#ebebeb"))
        )
        self.textEdit.setPalette(pal)
        self.pTextEdit.setPalette(pal)
        fnt: QFont = self.textEdit.font()
        (
            fnt.setFamily("courier new"),
            fnt.setPixelSize(12)
        )
        self.textEdit.setFont(fnt)

        self.foregroundColorToolBar = self.addToolBar("Foreground Color")
        self.backgroundColorToolBar = self.addToolBar("Background Color")
        self.toolBar = self.addToolBar("Tools")

        self.foregroundColorToolBar.setFloatable(False)
        self.backgroundColorToolBar.setFloatable(False)
        self.toolBar.setFloatable(False)

        self.createToolBar()

        self.textEdit.insertHtml("The quick brown fox jump over the lazy dog.")

    def __del__(self):
        pass

    def createToolBar(self):
        if (not self.foregroundColorToolBar) or (not self.backgroundColorToolBar):
            return

        prefix = "data/image/"
        suffix = ".png"

        groundPrefix = "f"
        groundDisplaySuffix = "Foreground"
        for i in range(len(self.colorName)):
            action: QAction = QAction(self.colorDisplayName[i] + " " + groundDisplaySuffix, self)
            self.fgColorActions.append(action)
            action.setIcon(QIcon(prefix + groundPrefix + self.colorName[i] + suffix))
            def setForegroundColor(_, i=i):
                format_: QTextCharFormat = self.textEdit.textCursor().charFormat()
                format_.setForeground(QBrush(QColor(self.colorValue[i])))
                self.textEdit.mergeCurrentCharFormat(format_)
            action.triggered.connect(setForegroundColor)
        self.foregroundColorToolBar.addActions(self.fgColorActions)

        groundPrefix = "b"
        groundDisplaySuffix = "Background"
        for i in range(len(self.colorName)):
            action: QAction = QAction(self.colorDisplayName[i] + " " + groundDisplaySuffix, self)
            self.bgColorActions.append(action)
            action.setIcon(QIcon(prefix + groundPrefix + self.colorName[i] + suffix))
            def setBackgroundColor(_, i=i):
                format_: QTextCharFormat = self.textEdit.textCursor().charFormat()
                format_.setBackground(QBrush(QColor(self.colorValue[i])))
                self.textEdit.mergeCurrentCharFormat(format_)
            action.triggered.connect(setBackgroundColor)
        self.backgroundColorToolBar.addActions(self.bgColorActions)

        self.executeAction.setIcon(QIcon(prefix + "execute" + suffix))
        self.executeAction.triggered.connect(self.executeBtnTriggeredSlot)

        self.toolBar.addAction(self.executeAction)

    def executeBtnTriggeredSlot(self, _):
        html: str = self.textEdit.toHtml()
        regex = re.compile(r"\<p[^\>]+\>(.+)\<\/p\>", re.I | re.M)
        spanRegex = re.compile(r"<span style=\"[^\"]+\">", re.I | re.M)
        fgRegex = re.compile(r"[^-]color:(#[0-9A-Fa-f]{6});")
        bgRegex = re.compile(r"background-color:(#[0-9A-Fa-f]{6});")
        matchG = regex.finditer(html)
        for matchP in matchG:
            content: str = matchP.group(1)
            content = content.replace(r"</span>", r"\e[0m")
            matchI = spanRegex.finditer(content)
            for match in matchI:
                echoStr: str = r"\e["
                resume: bool = False
                spanText: str = match.group()
                colorMatched = fgRegex.search(spanText)
                if colorMatched:
                    color: str = colorMatched.group(1)
                    echoStr += str(self.termHash.get(color, 0) + 30)
                    resume = True
                backColorMatched = bgRegex.search(spanText)
                if backColorMatched:
                    backcolor: str = backColorMatched.group(1)
                    if resume:
                        echoStr += ";"
                    echoStr += str(self.termHash.get(backcolor, 0) + 40)
                    resume = True
                echoStr += "m"
                content = content.replace(spanText, echoStr)
            self.pTextEdit.insertPlainText(content + "\n")