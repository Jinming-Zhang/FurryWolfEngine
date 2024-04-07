from PyQt6.QtCore import QSize
from PyQt6.QtGui import QCloseEvent
from PyQt6.QtWidgets import QMainWindow, QPushButton, QVBoxLayout, QWidget

from models.data.DataCenter import DataCenter
from models.ProcessManager import ProcessManager


from utils.WolfUtils import TryGetDictWithDefault as tryGet


class FurryWolfEditor(QMainWindow):
    defaultTitle = "Furry Wolf Engine"
    defaultWidth = "760"
    defaultHeight = "430"

    def __init__(self, projectDir, onWindowClosed, *args) -> None:
        super().__init__(*args)
        self.config = DataCenter.editorConfig
        self.projectDir = projectDir
        self.closedCB = onWindowClosed

        self.setWindowTitle(tryGet(
            self.config, 'title', FurryWolfEditor.defaultTitle))
        self.win_width = int(
            (tryGet(self.config, 'minWidth', FurryWolfEditor.defaultWidth)))
        self.win_height = int(
            (tryGet(self.config, 'minHeight', FurryWolfEditor.defaultHeight)))
        self.setMinimumSize(QSize(self.win_width, self.win_height))

        self.igniteButton = QPushButton("Ravup the Engine!")
        # self.igniteButton.setMaximumSize(QSize(int(self.win_width/2), int(self.win_height/2)))
        self.igniteButton.clicked.connect(self.__runEngine)

        layout = QVBoxLayout()
        layout.addWidget(self.igniteButton)
        self.root = QWidget()
        self.root.setLayout(layout)
        self.setCentralWidget(self.root)

    def __runEngine(self):
        self.igniteButton.setText("Engine Running...")
        self.igniteButton.setEnabled(False)
        ProcessManager.RunEngine(self.projectDir, self)

    def engineClosed(self):
        self.igniteButton.setText("Ravup the Wolf Engine!")
        self.igniteButton.setEnabled(True)

    def closeEvent(self, a0: QCloseEvent | None) -> None:
        self.closedCB(self.projectDir)
        return super().closeEvent(a0)
