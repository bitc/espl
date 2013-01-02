#!/usr/bin/env python

import sys
import random

wordlib = 'long-words.txt'

def main():
    games = 0
    play_game()
    games += 1

def random_word(filename):
    all_words = []
    try:
        with open(wordlib, 'r') as f:
            for w in f:
                all_words.append(w.strip())
    except IOError as e:
        sys.stderr.write("%s: Missing word library %s\n" % (sys.argv[0], wordlib))
        sys.stderr.write("(online at http://www.intuitive.com/wicked/examples/long-words.txt\n")
        sys.stderr.write("save the file as $wordlib and you're ready to play!)\n")
        sys.exit(1);
    return random.choice(all_words)

def play_game():
    guessed = []

    target = random_word(wordlib)

    partial = ''
    for c in target:
        if c in guessed:
            partial += c
        else:
            partial += '-'

    print partial
    guess = raw_input()

    guessed.append(guess)

main()
