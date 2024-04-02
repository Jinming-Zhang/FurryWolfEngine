from shutil import copytree


def TryGetDictWithDefault(dict: dict, key, default):
    if dict == None or not key in dict:
        return default
    return dict[key]


def CopyDirContent(src, dst):
    copytree(src, dst)
