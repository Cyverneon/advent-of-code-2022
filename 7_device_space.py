import re

filesys = {
    "info":
    {
        "size": 0
    },
    "content": {}
}

def get_nested_dict_from_path(full_dict, path): 
    temp_dict = full_dict
    for i in range(len(path)):
        temp_dict = temp_dict.get("content").get(path[i])
    return temp_dict

def add_file_to_dir_size(full_dict, path, size):
    temp_dict = full_dict
    temp_dict["info"]["size"] += size
    for i in range(len(path)):
        temp_dict = temp_dict.get("content").get(path[i])
        temp_dict["info"]["size"] += size

def get_dir_size(full_dict, path):
    temp_dict = get_nested_dict_from_path(full_dict, path)
    return temp_dict["info"]["size"]

# start off with an empty path for the root directory
all_dir_paths = [[]]

input = open("7_device_space.txt").readlines()

current_dir = filesys
current_dir_path = []

for line in input:

    if re.search("^\$", line):

        # if the command was cd, modify the current_dir_path appropriately
        # then set the current dir
        if re.search("cd", line):
            dir = line.split()[2]
            if dir == "/":
                # back to the root of the filesystem
                current_dir_path = []
            elif dir == "..":
                # back to the parent directory
                current_dir_path.pop()
            else:
                # go to the given child directory
                current_dir_path.append(dir)
            current_dir = get_nested_dict_from_path(filesys, current_dir_path).get("content")

    # if it wasn't a command, it will be the result of listing everything in a directory
    else:
        item_info = line.split()
        # first part of the line "dir", second part name of the directory
        if item_info[0] == "dir":
            current_dir[item_info[1]] = {"info": {"size": 0}, "content": {}}
            all_dir_paths.append(current_dir_path + [item_info[1]])
        # first part of the line the size of a file, second part the name of a file
        else:
            current_dir[item_info[1]] = {"size": int(item_info[0])}
            add_file_to_dir_size(filesys, current_dir_path, int(item_info[0]))


max_consideration_size = 100000
sum_of_small_dirs = 0

total_size = 70000000
needed_update_size = 30000000

required_space = needed_update_size - (total_size - filesys["info"]["size"])

smallest_usable_dir = filesys["info"]["size"]

for i in range(len(all_dir_paths)):
    dir_size = get_dir_size(filesys, all_dir_paths[i])
    if (dir_size <= max_consideration_size):
        sum_of_small_dirs += dir_size
    if (dir_size > required_space and dir_size < smallest_usable_dir):
        smallest_usable_dir = dir_size

print("total size of directories less than " + str(max_consideration_size) + ": " + str(sum_of_small_dirs))
print("size of smallest directory that would free up enough space: " + str(smallest_usable_dir))