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

PROBLEM_CODE = 'SOTUANHOAN'
FILE_LOCATION = 'E:\\Algo\\[J] LQD\\' + PROBLEM_CODE + '\\'

MAX_TESTS = 200

import os

def write_content(name):
    # Relative path
    print('Viewing', name)
    with open(name) as f:
        lines = f.readlines()
        for line in lines: print(line)

def check_input(name):
    print('Checking', name)
    with open(name) as f:
        lines = f.readlines()
        print(len(lines))

        print(lines[0].split()[0])
        print(len(lines[0].split()[1]))
        # n,k = map(int, lines[0].split())
        # a = list(map(int, lines[1].split()))
        # if min(a) < 0:
        #     print('Testcase: ', name, ' has negative number as low as ', min(a))

def extract_num(s):
    if not isinstance(s, str): raise ValueError
    tc = -1
    for c in s:
        if c.isdigit():
            if tc < 0: tc = 0
            tc *= 10
            tc += ord(c) - ord('0')
    return tc

def get_extension(s):
    return s[s.find('.') + 1:]

def tests_traversal(action = None, **kwargs):
    target_tc = int(kwargs.get('test_case', -1))
    extension = kwargs.get('ext', '*')

    os.chdir(FILE_LOCATION)
    childs = os.listdir()

    for name in childs:
        is_file = name.count('.') > 0
        if is_file and get_extension(name) != extension and extension != '*': continue
        tc = extract_num(name)
        if tc > MAX_TESTS or tc < 0 or (tc != target_tc and target_tc != -1):
            continue
        print('Detected ', name, ' for ', tc)
        if is_file:
            action(name)
        else:
            print('Detected directory')
            os.chdir(name)
            files = os.listdir()
            for file in files:
                if extension != '*' and file.count('.') > 0 and get_extension(file) != extension:
                    continue
                action(file)
            os.chdir('..')


tests_traversal(check_input, ext=INP_FORMAT, test_case=25)
# tests_traversal(check_input, ext=INP_FORMAT)
