import requests
import json
import re
import sys
from time import sleep

probname = sys.argv[1].split('.')[0]
print('Submitting', probname)

files = set()

def add_dependency(filename1):
    global files
    files.add(filename1)
    if not filename1.endswith('.c'):
        return
    with open(f'{filename1[:-2]}.c.d') as f:
        text = f.read()
        text = text.split(':')[1].replace('\\', '').replace('\n', ' ').strip()
        filenames = re.split(r'\s+', text)
    for filename in filenames:
        if filename not in files:
            add_dependency(filename)
    with open(f'{filename1[:-2]}.o.d') as f:
        text = f.read()
        text = text.split(':')[1].replace('\\', '').replace('\n', ' ').strip()
        filenames = [s.replace('.o', '.c') for s in  re.split(r'\s+', text)]
    for filename in filenames:
        if filename not in files:
            add_dependency(filename)

add_dependency(f"{probname}.c")

print('These files will be uploaded:', files)

exit()

with open('submit.secrets.json') as f:
    secrets = json.load(f)

url = secrets["url"]

session = requests.Session()

print('Logging in ...')

req = session.post(
    f"{url}/public/login.php",
    data = {
        "cmd": "login",
        "login": secrets["username"],
        "passwd": secrets["password"],
    }
)

req.raise_for_status()

r=re.compile(r'<a href="problem.php\?id=(?P<id>\d+).+?>(?P<name>[a-zA-Z0-9]+)')

probIds = dict([(b,a) for a,b in r.findall(req.text)])

sleep(1)

print('Submitting ...')

req = session.post(
    f"{url}/team/upload.php",
    files=[('code[]', (f'{filename}', open(f'{filename}', 'r'))) for filename in files],
    data={'probid': probIds[probname], 'langid': 'c', "submit": "submit"},
)

req..raise_for_status()
