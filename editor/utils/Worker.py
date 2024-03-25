from PyQt6.QtGui import *
from PyQt6.QtWidgets import *
from PyQt6.QtCore import *


class Worker(QRunnable):

    def setup(self, action, cb):
        self.action = action
        self.cb = cb

    @pyqtSlot()
    def run(self):
        if self.action != None:
            self.action()
        if self.cb != None:
            self.cb()
