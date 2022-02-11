import os
from pathlib import Path

# file headers contains copyright information
notification = "/* CSAPP - Introduction to Computer Systems.\n" + \
    " * Author:      louchangfeng@outlook.com\n" + \
    " * Github:      https://github.com/hnlcf/simplified-csapp\n" + \
    " *\n" + \
    " * This project is exclusively owned by louchangfeng\n" + \
    " * and shall not be used for commercial and profitting purpose\n" + \
    " * without louchangfeng's permission.\n" + \
    " *\n" + \
    " * Thanks for yangminz's code repository and videos in my learning.\n" + \
    " */\n\n"

print(notification)
# get files with paths
filelist = list(Path(".").rglob("*.[ch]"))

# recursively add lines to every .c and .h file
print("recursively add lines to every .c and .h file")
for filename in filelist:
    with open(filename, "r", encoding='utf-8') as fr:
        content = fr.read()
        if (content.startswith("/* CSAPP - Introduction to Computer Systems.")):
            print("\tskip\t%s" % filename)
            fr.close()
            continue
        else:
            fr.close()
            # reopen and write data: this is a safer approach
            # try to not open in r+ mode
            print("\tprepend\t%s" % filename)
            with open(filename, "w", encoding='utf-8') as fw:
                fw.write(notification + content)
