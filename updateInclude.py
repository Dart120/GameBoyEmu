import json
with open('conanbuildinfo.txt') as f:
    lines = f.read().splitlines()
    includePaths = []
    isIncludePath = False
    for line in lines:
        if isIncludePath:
            includePaths.append(line)
            if line == "[libdirs]":
                includePaths = includePaths[:-1]
                break
        if line == "[includedirs]":
            isIncludePath = True
print(includePaths)


json_file_path = ".vscode/c_cpp_properties.json"

with open(json_file_path, 'r') as j:
    props = json.loads(j.read())
 
    currPaths = set(props["configurations"][0]["includePath"])
    for path in includePaths:
        if not path in currPaths:
            currPaths.add(path)
    props["configurations"][0]["includePath"] = list(currPaths)
with open(json_file_path, 'w') as j:
    # j.truncate(0)
    json.dump(props, j)
        