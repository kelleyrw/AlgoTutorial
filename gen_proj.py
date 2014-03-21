#!/usr/bin/python

import sys
import os
import fnmatch

sys.path.append(os.path.join(os.path.dirname(sys.argv[0]), 'external_tools/gyp/pylib'))
import gyp

def main(argv):
    gypfile = "all.gyp"
    gypdir = os.path.dirname(os.path.abspath(gypfile))
    includefile = "defaults.gypi"
    gyp.main(argv[1:] + ["--include=" + includefile, "--depth=" + gypdir, gypfile])
    return 0

if __name__ == '__main__':
    sys.exit(main(sys.argv))
