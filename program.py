#!/usr/bin/python

import serial

s = serial.Serial('/dev/ttyUSB0', 437500)

s.write('\x00')
s.flush()
print s.readline()

s.write('\x04')
s.write('\x00')
s.write('\x00')
s.write('\x00')

print s.readline()
