#!/usr/bin/env python3
import time
import serial
import subprocess

if __name__ == '__main__':
	ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
	ser.reset_input_buffer()

while True:
	if ser.in_waiting > 0:
		line = ser.readline().decode('utf-8').rstrip()
		if line == "Ardi: Zzzzz":
			print(line)

		elif line == "Button":
			print('Ardi: Oh, someone pressed the button. Water is coming!!!')

		elif line == "Pumped":
			print("Ardi: I hope that was enough pumping!")

		elif line == "Measuring Ph and other sensors":
			print(line)
			p=subprocess.Popen(['/usr/local/bin/node', '/home/pi/node-flower-power/EC_Cagsun_Test.js'], stdout=subprocess.PIPE)
			out=p.stdout.read()
			print(out.decode('utf-8'))
			time.sleep(5.5)
		else:
			print(line)
