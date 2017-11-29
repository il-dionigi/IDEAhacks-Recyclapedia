import serial
import time

ser = serial.Serial('/dev/ttyACM0', 9600, timeout=100000)
while (True):
    ser.write("013300")
    time.sleep(2)
ser.close()
