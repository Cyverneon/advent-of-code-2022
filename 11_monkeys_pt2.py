import re
import math

class Monkey:
    def __init__(self):
        self.items = []
    
        self.inspection_operator = '+'
        self.inspection_value = 0

        self.test_divisor = 1

        self.true_monkey = 0
        self.false_monkey = 0

        self.inspections = 0
    
    def __str__(self):
        return f"{self.items}, {self.inspection_operator}, {self.inspection_value}, {self.test_divisor}, {self.true_monkey}, {self.false_monkey}"

    def setStartingItems(self, new_starting_items):
        self.items = new_starting_items
    
    def addItem(self, new_item):
        self.items.append(new_item)

    def setInspectionValues(self, new_operator, new_value):
        self.inspection_operator = new_operator
        self.inspection_value = new_value
    
    def setTestDivisor(self, new_test_divisor):
        self.test_divisor = new_test_divisor
    
    def getTestDivisor(self):
        return int(self.test_divisor)
    
    def setTrueMonkey(self, new_true_monkey):
        self.true_monkey = new_true_monkey
    
    def getTrueMonkey(self):
        return self.true_monkey
    
    def getFalseMonkey(self):
        return self.false_monkey
    
    def setFalseMonkey(self, new_false_monkey):
        self.false_monkey = new_false_monkey
    
    def getInspections(self):
        return self.inspections

    def inspectItem(self, i):
        if self.inspection_operator == "*":
            if self.inspection_value == "old":
                self.items[i] = int(self.items[i]) * int(self.items[i])
            else:
                self.items[i] = int(self.items[i]) * int(self.inspection_value)
        elif self.inspection_operator == "+":
            if self.inspection_value == "old":
                self.items[i] = int(self.items[i]) + int(self.items[i])
            else:
                self.items[i] = int(self.items[i]) + int(self.inspection_value)
        # self.items[i] = math.floor(self.items[i]/3)
        self.items[i] = self.items[i] % getDivisorProduct()
        self.inspections += 1
    
    def throwItem(self, i):
        if self.items[i] % int(self.test_divisor) == 0:
            monkeys[int(self.true_monkey)].addItem(self.items.pop(i))
        else:
            monkeys[int(self.false_monkey)].addItem(self.items.pop(i))

    def turn(self):
        for i in range(len(self.items)):
            # since throwing an item removes it, we'll always be dealing with the first item in the list
            self.inspectItem(0)
            self.throwItem(0)

def getDivisorProduct():
    return_value = 1
    for i in range(len(monkeys)):
        return_value = return_value * monkeys[i].getTestDivisor()
    return return_value

def round():
    for i in range(len(monkeys)):
        monkeys[i].turn()

def setupMonkeysFromInput(filename):
    input = open(filename).readlines()
    current_monkey = Monkey()
    for line in input:
        if re.search("(Monkey)", line):
            current_monkey = Monkey()
        # can have any amount of integers representing the starting items
        if re.search("(Starting items:)", line):
            current_monkey.setStartingItems((re.findall('\d+', line)))
        # fifth item in the split string is the operator
        # sixth item in the split string is either 'old' or a value to add/multiply
        # (0-based indexing)
        elif re.search("(Operation:)", line):
            current_monkey.setInspectionValues(line.split()[4], line.split()[5])
        # fourth item in the split string is the value to divide by for the test
        elif re.search("(Test:)", line):
            current_monkey.setTestDivisor(line.split()[3])
        # sixth item in the split string is the index of the monkey to throw to
        elif re.search("(If true:)", line):
            current_monkey.setTrueMonkey(line.split()[5])
        elif re.search("(If false:)", line):
            current_monkey.setFalseMonkey(line.split()[5])
            # If false is the last line of info for a monkey
            monkeys.append(current_monkey)


monkeys = []

setupMonkeysFromInput("11_monkeys.txt")

for i in range(10000):
    round()

most_active_monkeys = [0 for i in range(2)]

for i in range(len(monkeys)):
    for j in range( len(most_active_monkeys)):
        if monkeys[i].getInspections() > most_active_monkeys[j]:
            most_active_monkeys.insert(j, monkeys[i].getInspections())
            most_active_monkeys.pop()
            break

monkey_business = most_active_monkeys[0]
for i in range(1, len(most_active_monkeys)):
    monkey_business *= most_active_monkeys[i]

print(monkey_business)