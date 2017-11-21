import random
import sys

filename = str(sys.argv[1])

f = open(filename, 'r')
text=[]
for line in f.readlines():
   text+=[line[:-1]]
dict = {}
for i in text:
    dict[''.join(sorted(i))] = []
for i in text:
    dict[''.join(sorted(i))].append(i)

print ('-'*80)
print(" Welcome to fengyuz's word unscrambler!")
print ('-'*80)
while True:
    print("First, pick the length of the word you want to be challenged: ")
    number = input('type q to quit or type Enter to pick a random word) : ')
    if number == 'q':
        break
    elif number == '':
        word = random.choice(list(dict.keys()))
    else:
        vector = [i for i in dict if len(i) == int(number)]
        if vector == []:
            print("There is no word with length " + number + ". Choose a different length"+"\n")
            continue
        else:
            word = random.choice(vector)
    answers = dict[word]
    word_shuffle = ''.join(random.sample(word,len(word)))
    answer = input("Unscramble the word '" + str(word_shuffle) + "' : ")
    correct = False
    if answer in answers:
            correct = True
    if correct == True:
        print("Correct!")
    else:
        print("Sorry..incorrect!")
    print ("Correct answer(s) : " + str(answers)+"\n")
    
