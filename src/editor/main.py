import sys
import os
from FurryWolfEditor import FurryWolfEditor
import json


configPath = "./EditorSettings/EditorConfig.json"


def main():
    config = {}
    if os.path.exists(configPath):
        f = open(configPath)
        config = json.load(f)
    app = FurryWolfEditor(sys.argv, config=config)
    app.start()


if __name__ == "__main__":
    main()
