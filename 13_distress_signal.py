import copy

input = open("13_distress_signal.txt").readlines()

def compareList(list1, list2):
    longer_list = len(list1) if len(list1) > len(list2) else len(list2)
    for i in range(longer_list):
        # check for lists running out of items
        if (i >= len(list1)):
            return True
        elif (i >= len(list2)):
            return False

        # if one of the compared items is a list, make the other one also a list
        if (not type(list1[i]) is list) and (type(list2[i]) is list):
            list1[i] = [list1[i]]
        if (not type(list2[i]) is list) and (type(list1[i]) is list):
            list2[i] = [list2[i]]

        # recursion moment
        if (type(list1[i]) is list) and (type(list2[i]) is list):
            compareList(list1[i], list2[i])
        
        # the number comparision
        if list1[i] < list2[i]:
            return True
        if list1[i] > list2[i]:
            return False

all_packets = []

for line in input:
    if (line != "\n"):
        newlist = []
        exec("newlist = " + line)
        all_packets.append(newlist)

indices_sum = 0
for i in range(1, len(all_packets), 2):
    if compareList(copy.deepcopy(all_packets[i-1]), copy.deepcopy(all_packets[i])):
        indices_sum += (i+1)/2

# the division turns indices_sum into a float, but we just want an int
print("sum of indices of packets in correct order: ", int(indices_sum))

divider_packets = [[[2]], [[6]]]

for key in divider_packets:
    all_packets.append(key)

# this sort is very unoptimal
# but it's okay
swaps = True
while (swaps):
    swaps = False
    for i in range(1, len(all_packets)):
        # creating deepcopies, because the comparision will turn elements into a list where needbe, but we don't want that change made in the original all_pairs
        # deepcopy will fully copy all the nested lists, not just the outermost list
        if not compareList(copy.deepcopy(all_packets[i-1]), copy.deepcopy(all_packets[i])):
            all_packets.insert(i-1, all_packets.pop(i))
            swaps = True

decoder_key = 1
for i in range(len(all_packets)):
    for packet in divider_packets:
        if all_packets[i] == packet:
            decoder_key *= (i+1)

print("decoder key: ", decoder_key)