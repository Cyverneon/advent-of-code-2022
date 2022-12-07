import re

# https://adventofcode.com/2022/day/7

total_size = 70000000
needed_update_size = 30000000

# format of directory:
# "type": "dir"
# "info":
# {
#   "size": int
# }
# "content":
# {
# another directory: {...}
# a file: {...}
# }

# format of file
# "type": "file",
# "size": int

# any other details needed in future could be added inside a directory's "info" dictionary or as another key to a file's dictionary

filesys = {
    "type": "dir",
    "info": { "size": 0 },
    "content": {}
}

# this is useful for comparing the sizes of each directory
# (it starts off with an empty path for the root directory)
all_dir_paths = [[]]

# these all work because dictionaries are passed by reference
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

def get_filesys_from_commands(filename):
    input = open(filename).readlines()

    current_dir = filesys
    current_dir_path = []

    for line in input:

        # check if input was a command
        if re.search("^\$", line):

            # if the command was cd, modify the current_dir_path appropriately
            # then set the current_dir
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
                current_dir[item_info[1]] = {"type" : "dir", "info": {"size": 0}, "content": {}}
                all_dir_paths.append(current_dir_path + [item_info[1]])
            # first part of the line the size of a file, second part the name of a file
            else:
                current_dir[item_info[1]] = {"type": "file", "size": int(item_info[0])}
                add_file_to_dir_size(filesys, current_dir_path, int(item_info[0]))


get_filesys_from_commands("7_device_space.txt")

# required space = total size of update - current free space
required_space = needed_update_size - (total_size - filesys["info"]["size"])
# size of the total filesystem, as an arbritrary upper limit, so any suitable directory will be checked if its smallest
# downside is if there is no suitable directory, it will just return the size of the whole filesystem
# the given puzzle input definintely has a suitable directory however!
smallest_usable_dir = filesys["info"]["size"]

max_consideration_size = 100000
sum_of_small_dirs = 0

for i in range(len(all_dir_paths)):
    dir_size = get_dir_size(filesys, all_dir_paths[i])
    if (dir_size <= max_consideration_size):
        sum_of_small_dirs += dir_size
    if (dir_size > required_space and dir_size < smallest_usable_dir):
        smallest_usable_dir = dir_size

print("total size of directories less than " + str(max_consideration_size) + ": " + str(sum_of_small_dirs))
print("size of smallest directory that would free up enough space: " + str(smallest_usable_dir))