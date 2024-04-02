from typing import List
from PyQt6.QtWidgets import QApplication
from views.launcher.LaunchWindow import LaunchWindow


class FurrywolfApp(QApplication):
    def __init__(self, argv: List[str]) -> None:
        super().__init__(argv)
        self.mainWindow = LaunchWindow()

    def start(self):
        self.mainWindow.show()
        self.exec()
