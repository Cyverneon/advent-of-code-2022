import sys
import re

assignments = open("4_camp_cleanup.txt").readlines()

full_overlaps = 0
partial_overlaps = 0

for line in assignments:
    # input given like a-b,c-d
    # where a is first elf's start point, b is their end point
    # c is the second elf's start point and d is their end point

    # get all the numbers, then use them to get sets of all sections each elf has to clean
    sections = re.findall('\d+', line)
    elf1 = {i for i in range(int(sections[0]), int(sections[1])+1)}
    elf2 = {i for i in range(int(sections[2]), int(sections[3])+1)}

    # check if either set is a subset of the other
    if elf1.issubset(elf2) or elf2.issubset(elf1):
        full_overlaps += 1
    
    # check if the sets are not not intersecting (lol)
    if not elf1.isdisjoint(elf2):
        partial_overlaps += 1

print("full overlaps: ", full_overlaps)
print("partial overlaps: ", partial_overlaps)
