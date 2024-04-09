from typing import List

import os
from PyQt6.QtCore import *
from PyQt6.QtGui import *
from PyQt6.QtWidgets import QMainWindow, QWidget,  QPushButton, QFileDialog, QInputDialog, QVBoxLayout

from views.engineEditor.FurryWolfEditor import FurryWolfEditor
from models.log.Logger import Logger

from models.data.DataCenter import DataCenter
from utils.WolfUtils import TryGetDictWithDefault as tryGet
from utils.WolfUtils import CopyDirContent


class LaunchWindow(QMainWindow):

    defaultTitle = "Furry Wolf Engine Launcher"
    defaultWidth = "760"
    defaultHeight = "430"
    defaultEngineResourceDir = "."

    def __init__(self,  *args) -> None:
        super().__init__(*args)
        self.projectEditorMap = {}

        self.config = DataCenter.launcherConfig
        self.__setupRootWindow()

        self.newProjectBtn = QPushButton("Create New Project")
        self.openProjectBtn = QPushButton("Open Project Folder")

        self.newProjectBtn.clicked.connect(self.__newProjectBtnClicked)
        self.openProjectBtn.clicked.connect(self.__openProjectBtnClicked)

        layout = QVBoxLayout()
        layout.addWidget(self.newProjectBtn)
        layout.addWidget(self.openProjectBtn)
        self.root.setLayout(layout)
        self.setCentralWidget(self.root)

    def __setupRootWindow(self):
        self.setWindowTitle(tryGet(
            self.config, 'title', LaunchWindow.defaultTitle))

        self.win_width = int(
            (tryGet(self.config, 'minWidth', LaunchWindow.defaultWidth)))

        self.win_height = int(
            (tryGet(self.config, 'minHeight', LaunchWindow.defaultHeight)))

        self.setMinimumSize(QSize(self.win_width, self.win_height))
        iconPath = tryGet(self.config, "icon", "invalid")
        if iconPath != "invalid":
            icon = QIcon(iconPath)
            self.setWindowIcon(icon)
        self.root = QWidget()

    def __newProjectBtnClicked(self):
        directory = QFileDialog.getExistingDirectory(
            self, "Select Directory", os.path.expanduser("."))
        if directory:
            folderName, ok = QInputDialog.getText(
                self, "New Folder", "Enter Folder Name")
            if ok and folderName:
                folderPath = os.path.join(directory, folderName)
                try:
                    os.mkdir(folderPath)
                    self.__createNewProject(folderPath)
                except OSError as e:
                    print("Failed create project folder", e)

    def __openProjectBtnClicked(self):
        directory = QFileDialog.getExistingDirectory(
            self, "Select Directory", os.path.expanduser("."))
        if directory:
            self.startEditor(directory)

    def startEditor(self, projectLocation):
        if (projectLocation in self.projectEditorMap):
            Logger.log("Project already openned")
            return
        newEditor = FurryWolfEditor(projectLocation, self.onEditorClosed)

        newEditor.show()
        self.projectEditorMap[projectLocation] = newEditor

    def onEditorClosed(self, projectDir):
        if projectDir in self.projectEditorMap:
            del self.projectEditorMap[projectDir]
        else:
            Logger.log("Unidentified Editor window closed.")

    def __createNewProject(self, dst: str):
        srcList = tryGet(self.config, "engineResourceDirs", "invalid")
        if srcList == "invalid":
            Logger.log(
                "Invalid Engine resource folder, failed to create project.")
            return
        for src in srcList:
            absSrcPath = os.path.abspath(src)
            dstName = ""
            for i in range(len(absSrcPath)):
                j = len(absSrcPath)-1-i
                if absSrcPath[j] == os.path.sep:
                    dstName = absSrcPath[j+1:]
                    break

            absDstPath = os.path.abspath(os.path.join(dst, dstName))
            CopyDirContent(absSrcPath, absDstPath)
        self.startEditor(dst)
