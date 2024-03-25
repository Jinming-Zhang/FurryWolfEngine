import sys
import os
import threading

from PyQt6.QtCore import QSize, QThreadPool

from PyQt6.QtWidgets import QMainWindow, QPushButton

from utils.WolfUtils import TryGetDictWithDefault as tryGet

from bindings.modules import FurrywolfEngine
from utils.Worker import Worker


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
        self.igniteButton.setText("Engine Running...")
        self.igniteButton.setEnabled(False)
        self.threadpool = QThreadPool()
        self.worker = Worker()
        self.worker.setup(self.__startEngineThread, None)
        self.threadpool.start(self.worker)
        # try:
        #     os.chdir("C:\\Users\\wolfy\\Projects\\CppProjects\\FurryWolfEngine")
        #     FurrywolfEngine.RavUp(
        #         "C:\\Users\\wolfy\\Projects\\CppProjects\\FurryWolfEngine")
        #     self.igniteButton.setText("Ravup the Wolf Engine!")
        #     self.igniteButton.setEnabled(True)
        # except:
        #     print("Engine failed...")

    def __startEngineThread(self):
        os.chdir("C:\\Users\\wolfy\\Projects\\CppProjects\\FurryWolfEngine")
        FurrywolfEngine.RavUp(
            "C:\\Users\\wolfy\\Projects\\CppProjects\\FurryWolfEngine")
        self.igniteButton.setText("Ravup the Wolf Engine!")
        self.igniteButton.setEnabled(True)
