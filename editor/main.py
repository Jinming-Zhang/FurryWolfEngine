import sys
import os
import json

from views.FurrywolfApp import FurrywolfApp
from models.data.DataCenter import DataCenter


configPath = "./EditorSettings/EditorConfig.json"


def initData():
    config = {}
    if os.path.exists(configPath):
        f = open(configPath)
        config = json.load(f)
    DataCenter.initialize(config)


def main():
    initData()
    app = FurrywolfApp(sys.argv)
    app.start()


if __name__ == "__main__":
    main()
