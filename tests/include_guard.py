from os import path
import sys
import glob
import re
import fileinput
import argparse

scriptdir = path.dirname(path.abspath(__file__))
srcdir = path.join(scriptdir, '..') # このスクリプトのあるディレクトリから見たソースディレクトリの相対パス

rifndef = re.compile(r'^#ifndef\s+')
rdefine = re.compile(r'^#define\s+')

def check_file(abspath, autofix=False):
    errors = []
    def writefixed(text):
        if autofix:
            print(text)
    relpath = f'./{path.relpath(abspath)}'
    filename = path.splitext(path.basename(abspath))[0]
    with fileinput.FileInput(abspath, inplace=autofix, backup='.bak') as f:
        for i, line in enumerate(map(lambda s: s.strip('\n'), f)):
            if i == 0:
                expected = f'H_{filename.upper()}'
                if rifndef.match(line):
                    actual = re.sub(rifndef, '', line, 1)
                    if actual == expected:
                        writefixed(line)
                    else:
                        errors.append(dict(i=i, fixable=True, msg=f'#ifndef symbol `{actual}` should be `{expected}`'))
                        writefixed(f'#ifndef {expected}')
                else:
                    errors.append(dict(i=i, fixable=False, msg=f'Missing #ifndef'))
                    writefixed(line)
            elif i == 1:
                ok = True
                expected = f'H_{filename.upper()}'
                if rdefine.match(line):
                    actual = re.sub(rdefine, '', line, 1)
                    if actual == expected:
                        writefixed(line)
                    else:
                        errors.append(dict(i=i, fixable=True, msg=f'#define symbol `{actual}` should be `{expected}`'))
                        writefixed(f'#define {expected}')
                else:
                    errors.append(msg=dict(i=i, fixable=False, msg=f'Missing #define'))
                    writefixed(line)
            else:
                writefixed(line)
    # TODO: check tail endif
    return [{"path": relpath, **err} for err in errors]

parser = argparse.ArgumentParser()
parser.add_argument("--fix", help="autofix fixable problems", action='store_true')
args = parser.parse_args()

errors = []
i = 0
for filepath in map(path.normpath, glob.iglob(f'{srcdir}/*.h')):
    errors += check_file(filepath, autofix=args.fix)
    i += 1

print(f'Checked {i} file(s).', file=sys.stderr)

fixability_text = {
    True: {
        True:  '[   FIXED   ]',
        False: '[ NOT FIXED ]'
    },
    False: {
        True:  '[   FIXABLE   ]',
        False: '[ NON-FIXABLE ]',
    },
}

if errors:
    raise Exception('\n'.join([
        'Header check failed',
        *[f"{fixability_text[args.fix][e['fixable']]} {e['path']}:{e['i'] + 1}: {e['msg']}" for e in errors]
    ])) # print all errors
