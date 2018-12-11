#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
from MainWindow import MainWindow
from PyQt5.QtWidgets import QApplication

__application__ = "TermColor"
__author__ = "Ruilx"
__version__ = "0.1"
__organization__ = "GT-Soft"

def main(argv):
    a = QApplication(sys.argv)
    a.setApplicationDisplayName(__application__)
    a.setOrganizationName(__organization__)

    w = MainWindow()
    w.show()

    return a.exec()

if __name__ == "__main__":
    main(sys.argv)