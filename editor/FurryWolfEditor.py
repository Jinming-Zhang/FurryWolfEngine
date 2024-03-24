from typing import List
import sys

from PyQt6.QtWidgets import QApplication
from FurryWolfWindow import FurryWolfWindow


class FurryWolfEditor(QApplication):
    def __init__(self, argv: List[str], config={}) -> None:
        super().__init__(argv)
        self.config = config
        self.mainWindow = FurryWolfWindow(config=self.config['window'])

    def start(self):
        self.mainWindow.show()
        self.exec()
