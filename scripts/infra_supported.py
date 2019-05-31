#!/usr/bin/env python

import itertools

# The list of OS and kernel versions that have been used successfully as guest VM images
platforms = {
  "Linux": [
    "4.15.0"
  ],
#  "OpenBSD": [
#    "6.4"
#  ],
#  "Windows": [
#    "10.0.17763"
#  ],
#  "MacOS": [
#    "18.5.0"
#  ]
}
platforms = [x+" "+y for x in platforms for y in platforms[x]]

# The list of compilers that have been used successfully in guest VM
compilers = {
  "clang": [
      "9.0"
  ],
  "gcc": [
      "7.4.0"
  ]
}
compilers = [x+" "+y for x in compilers for y in compilers[x]]

# hopefully more supported when we move to qemu
architetures = [
  "i386",
  "x86_64"
]

# calculate the cartesian product of above sets
for x in list(itertools.product(compilers,platforms,architetures)):
  print(x)
