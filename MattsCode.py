import random

def rollstat(dnum,dval,subnum):
    rolls=[]
    for i in range(dnum):
        rolls.append(random.randint(0,dval))
    rolls.sort()
    highrolls=rolls[subnum:]
    stat_total=0
    for i in range(len(highrolls)):
        stat_total+=highrolls[i]
    return stat_total

def makeblock(dnum=4,dval=6,subnum=1):
    stats=[]
    statstrs=["\nStrength: ","Constitution: ","Dexterity: ","Intelligence: ","Wisdom: ","Charisma: "]
    for i in range(6):
        stats.append(rollstat(dnum,dval,subnum))
        print(statstrs[i],stats[i])
def main():
    print("This program will roll up a random stat block for a Dungeons and Dragons character.")

    while True:
        print("By default, this program rolls 4d6 and subtracts the lowest roll. Is that okay?")
        pbp=input("Type Y for 'yes' or N for 'no'. ")
        if pbp.lower()=='y' or pbp.lower()=='n':
            break
        else:
            print("Invalid input.")

    if pbp.lower()=='n':
        while True:
            try:
                dval=float(input("What type of dice will be rolled (6 for d6, 8 for d8, etc.) "))
                if dval%1==0:
                    break
                else:
                    print("Please provide an integer.")
            except ValueError:
                print("Please provide an integer.")

        while True:
            try:
                dnum=float(input("How many dice will be rolled? "))
                if dnum%1==0:
                    break
                else:
                    print("Please provide an integer.")
            except ValueError:
                print("Please provide an integer.")

        while True:
            try:
                subnum=float(input("How many low rolls will be subtracted? "))
                if subnum%1==0:
                    break
                else:
                    print("Please provide an integer.")
            except ValueError:
                print("Please provide an integer.")

        dnum,dval,subnum=int(dnum),int(dval),int(subnum)
        makeblock(dnum,dval,subnum)

    else:
        makeblock()

main()
