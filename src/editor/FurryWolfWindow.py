import sys

from PyQt6.QtCore import QSize, Qt
from PyQt6.QtWidgets import QMainWindow, QPushButton, QWidget

from utils.WolfUtils import TryGetDictWithDefault as tryGet


class FurryWolfWindow(QMainWindow):
    defaultTitle = "Furry Wolf Engine"
    defaultWidth = "760"
    defaultHeight = "430"

    def __init__(self, config=None, *args) -> None:
        super().__init__(*args)
        self.config = config

        self.setWindowTitle(tryGet(
            self.config, 'title', FurryWolfWindow.defaultTitle))

        self.win_width = int(
            (tryGet(self.config, 'minWidth', FurryWolfWindow.defaultWidth)))

        self.win_height = int(
            (tryGet(self.config, 'minHeight', FurryWolfWindow.defaultHeight)))

        self.setMinimumSize(QSize(self.win_width, self.win_height))

        self.igniteButton = QPushButton("Ravup the Engine!")
        self.igniteButton.setMaximumSize(
            QSize(int(self.win_width/2), int(self.win_height/2)))

        self.igniteButton.clicked.connect(self.__runEngine)

        self.setCentralWidget(self.igniteButton)

    def __runEngine(self):
        print("Ravup the Wolf Engine!")
