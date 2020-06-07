from os import path
import sys
import glob
import re
import fileinput

scriptdir = path.dirname(path.abspath(__file__))
srcdir = path.join(scriptdir, '..') # このスクリプトのあるディレクトリから見たソースディレクトリの相対パス

rifndef = re.compile(r'^#ifndef\s+')
rdefine = re.compile(r'^#define\s+')

def check_file(abspath, autofix=False):
    errors = []
    relpath = f'./{path.relpath(abspath)}'
    filename = path.splitext(path.basename(abspath))[0]
    with fileinput.FileInput(abspath, inplace=autofix, backup='.bak') as f:
        for i, line in enumerate(map(lambda s: s.strip('\n'), f)):
            errprefix = f'{relpath}:{i + 1}:'
            if i == 0:
                expected = f'H_{filename.upper()}'
                ok = True
                if rifndef.match(line):
                    actual = re.sub(rifndef, '', line, 1)
                    if actual != expected:
                        errors.append(f'{errprefix} #ifndef symbol `{actual}` should be `{expected}`')
                        ok = False
                else:
                    errors.append(f'{errprefix} Missing #ifndef')
                    ok = False
                if autofix:
                    if ok:
                        print(line)
                    else:
                        print(f'#ifndef {expected}')
            elif i == 1:
                ok = True
                expected = f'H_{filename.upper()}'
                if rdefine.match(line):
                    actual = re.sub(rdefine, '', line, 1)
                    if actual != expected:
                        errors.append(f'{errprefix} #define symbol `{actual}` should be `{expected}`')
                        ok = False
                else:
                    errors.append(f'{errprefix} Missing #define')
                    ok = False
                if autofix:
                    if ok:
                        print(line)
                    else:
                        print(f'#define {expected}')
            else:
                if autofix:
                    print(line)
    # TODO: check tail endif
    return errors

errors = []
i = 0
for filepath in map(path.normpath, glob.iglob(f'{srcdir}/*.h')):
    errors += check_file(filepath, autofix=True)
    i += 1

print(f'Checked {i} file(s).', file=sys.stderr)

if errors:
    raise Exception('\n'.join(['Header check failed', *errors])) # print all errors
