#!/usr/bin/python
import serial

PORT ='/dev/ttyUSB0'

ser = serial.Serial(
        port=PORT,\
        baudrate=115200,\
        parity=serial.PARITY_NONE,\
        stopbits=serial.STOPBITS_ONE,\
        bytesize=serial.EIGHTBITS,\
        timeout=0)

print("connected to: " + ser.portstr)
ser.write("help\n")
while True:
	line = ser.readline()
	if line:
		print(line),
        
ser.close()