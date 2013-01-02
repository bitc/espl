#!/usr/bin/env python

import csv

grades_sum = 0
grades_num = 0

grades_count = {}

with open('grades.csv', 'rb') as csvfile:
    reader = csv.reader(csvfile)
    # Skip the header row
    reader.next()
    for row in reader:
        grade = int(row[2])
        test_id = int(row[0])
        grades_sum += grade
        grades_num += 1
        if grade in grades_count:
            grades_count[grade].append(test_id)
        else:
            grades_count[grade] = [test_id]

grades_avg = float(grades_sum) / grades_num

print "Grades Average: " + str(grades_avg)

print "Grades Distribution:"
for k, v in grades_count.iteritems():
        print "Grade: " + str(k) + ", Num students: " + str(len(v)) + ", Test ids: " + str(v)
