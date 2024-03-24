
def TryGetDictWithDefault(dict: dict, key, default):
    if key in dict:
        return dict[key]
    return default
