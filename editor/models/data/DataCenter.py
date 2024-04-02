from models.data.AppConfigs import AppConfigs
from utils.WolfUtils import TryGetDictWithDefault as tryGet


class DataCenter:
    appConfig = {}
    launcherConfig = {}
    editorConfig = {}

    def initialize(dataJson):
        if dataJson == None:
            return
        if AppConfigs.APP_KEY in dataJson:
            DataCenter.appConfig = dataJson[AppConfigs.APP_KEY]
        if AppConfigs.LAUNCHER_KEY in dataJson:
            DataCenter.launcherConfig = dataJson[AppConfigs.LAUNCHER_KEY]
        if AppConfigs.EDITOR_KEY in dataJson:
            DataCenter.editorConfig = dataJson[AppConfigs.EDITOR_KEY]

    def tryQuery(dic, key, defaultVal):
        return tryGet(dic, key, defaultVal)
