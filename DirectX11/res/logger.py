from time import sleep
import os
import sys

class FileReader:

    def __init__(self, filePath:str):
        self.io = open(filePath, "r")
        self.base_name = os.path.basename(filePath)
        print(f"\tRegistering \'{self.base_name}\' in logger")

    def update(self):
        content = self.io.read()
        if content:
            if content.startswith('\n'):
                content = content.removeprefix('\n')
            print(f"{content}")

files = []

print(f"Starting logger with {len(sys.argv)} files...")

for i in range(1, len(sys.argv)):   # Skip arg 0 because it will be this script's name
    file = sys.argv[i]
    files.append(FileReader(file))
    
while True:
    for file in files:
        file.update()
    sleep(0.5)
    