import serial

ser = serial.Serial('/dev/ttyACM0', 9600, timeout=7)

while True:
    ser.write('2')

    print ser.readline()

ser.close()
