from os import path
import sys
import glob
import re

cwd = path.dirname(path.abspath(__file__))

def check_file(abspath):
    errors = []
    relpath = f'./{path.relpath(abspath)}'
    with open(abspath, 'r') as f:
        l1 = f.readline().strip()
        l2 = f.readline().strip()
        filename = path.splitext(path.basename(abspath))[0]
        rifndef = re.compile(r'^#ifndef\s+')
        rdefine = re.compile(r'^#define\s+')
        if rifndef.match(l1):
            actual = re.sub(rifndef, '', l1, 1)
            expected = f'H_{filename.upper()}'
            if actual != expected:
                errors.append(f'{relpath}:1: #ifndef symbol `{actual}` should be `{expected}`')
        else:
            errors.append(f'{relpath}:1: Missing #ifndef')
        if rdefine.match(l2):
            actual = re.sub(rdefine, '', l2, 1)
            expected = f'H_{filename.upper()}'
            if actual != expected:
                errors.append(f'{relpath}:2: #define symbol `{actual}` should be `{expected}`')
        else:
            errors.append(f'{relpath}:2: Missing #define')
        # TODO: check tail endif
        # TODO: autofix
    return errors

errors = []

for filepath in map(path.normpath, glob.iglob(f'{cwd}/../*.h')):
    errors += check_file(filepath)

if errors:
    raise Exception('\n'.join(['Header check failed', *errors]))