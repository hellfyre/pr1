#!/usr/bin/python

import os
import sys

filename = str.split(os.path.basename(sys.argv[1]), '.')
filename[0] += '_speedup'
outputfilename = filename[0] + '.' + filename[1]

inputfile = open(sys.argv[1], 'r')
outputfile = open(outputfilename, 'w')

outputfile.write('P  Speedup  Parallel_efficiency\n\n')

inputfile.readline()
inputfile.readline()

data = inputfile.readlines()
for line in data:
  cells = str.split(line, ' ')
  speedup = float(sys.argv[2]) / float(cells[1])
  parallel_eff = speedup / float(cells[0])
  outputfile.write(cells[0] + ' ' + str(speedup) + ' ' + str(parallel_eff) + '\n')
