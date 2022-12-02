import sys

calories = open("1_calorie_counting.txt").readlines()

# change range to change the amount of tracked elves
max_calories = [0 for i in range(3)]

current_calories = 0

for line in calories:
    if (line == "\n"):
        for i in range( len(max_calories)):
            if current_calories > max_calories[i]:
                max_calories.insert(i, current_calories)
                max_calories.pop()
                break
        current_calories = 0
    else:
        current_calories += int(line)

total_max_calories = 0
for i in range(len(max_calories)):
    total_max_calories += max_calories[i]
    
print(total_max_calories)