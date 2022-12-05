import sys
import re

input = open("5_supply_stacks.txt").readlines()

# 1: initial crate stacks, 2: movement instructions
input_section = 1

crate_stacks = [[]]

for line in input:
    if (input_section == 1):
        # once we reach the line with the numbers for each stack of crates, it's time to move on
        if (line[1].isdigit()):
            input_section = 2
            continue

        # every field is 4 characters long
        # but the last one is missing its separating space, so the +1
        for i in range(int((len(line)+1)/4)):
            if i >= len(crate_stacks):
                crate_stacks.append([])
            
            # there's a letter representing a crate every four characters
            # offset by 1 (e.g., at the second character, at the fifth character)
            crate_i = (i*4)+1
            if (not line[crate_i].isspace()):
                crate_stacks[i].insert(0, line[crate_i])
    
    elif (input_section == 2):
        # skipping that empty line before the second section of the input :/
        if (not line.isspace()):
            # instructions given like "move x from y to z"
            # x: amount of crates to move, y: stack to move from, z: stack to move to
            instruction_nums = re.findall('\d+', line)
            amount = int(instruction_nums[0])
            # - 1 because 0-based indexing
            stack_from = int(instruction_nums[1]) - 1
            stack_to = int(instruction_nums[2]) - 1
            for i in range(amount):
                crate_stacks[stack_to].append(crate_stacks[stack_from].pop())

final_string = ""

for i in range (len(crate_stacks)):
    final_string += crate_stacks[i][-1]
    
print(crate_stacks)
print(final_string)