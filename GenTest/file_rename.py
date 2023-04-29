'''
Input: 1.inp, 2.inp, 10.inp, 99.inp, 100.inp
Output: 001.inp, 002.inp, 003.inp, .. 025.inp, 100.inp

Possible testcase formats:
- Folder, containing 1.inp 2.inp, ..., i.inp
- Folder, containing folders Test01, TC02, 3, 14, ...,
    each sub-folder has corresponding input and output files
'''
INP_FORMAT = 'inp'
OUT_FORMAT = 'out'

PROBLEM_CODE = 'DAYSODOIXUNG'
FILE_LOCATION = 'E:\\Algo\\[J] LQD\\' + PROBLEM_CODE + '\\'

MAX_TESTS = 200

import os

def find_and_replace_file_names():
    os.chdir(FILE_LOCATION)
    childs = os.listdir()
    max_digits = 0
    tests = {}
    for name in childs:
        is_file = name.count('.') > 0
        tc = -1
        first = -1
        num_digits = 0
        for i in range(len(name)):
            c = name[i]
            if c.isdigit():
                num_digits += 1
                if tc < 0:
                    first = i
                    tc = 0
                tc *= 10
                tc += ord(c) - ord('0')
        if tc > MAX_TESTS or tc < 0:
            continue
        max_digits = max(max_digits, num_digits)
        tests[name] = (first, num_digits)
        print('Detected ', name, ' for ', tc)

    for (old_name, info) in tests.items():
        # print(info)
        new_name = old_name[:info[0]] + '0' * (max_digits - info[1]) + old_name[info[0]:]
        print('From ', old_name, ' to ', new_name)
        os.rename(old_name, new_name)


find_and_replace_file_names()
