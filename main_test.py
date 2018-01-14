# -*- coding: utf-8 -*-
"""
Created on Sat Jan 13 14:06:25 2018

@author: jlung20
"""

import zbar
import matplotlib.image as mpimg
import scan_image
import serial
import time
import os.path
import picamera

# hard-coding the relevant files
file_name = 'params.txt'
count_file_name = 'count.txt'
camera = picamera.PiCamera()
camera.resolution = (2592, 1944)

# add another entry to database and update text file for database
def write_database(database):
    str_1 = input('Enter barcode: ')
    str_2 = input('Enter 1 if recyclable, 0 otherwise: ')
    database[str_1] = str_2
    file = open(file_name, 'a')
    file.write(str_1 + '\n')
    file.write(str_2 + '\n')
    file.close()

# load all entries from text file to dictionary
def initialize_database():
    file = open(file_name, 'r')
    lines = file.readlines()
    file.close()
    database = {}
    for ii in range(0, int(len(lines)/2)):
        print(lines[2 * ii][:-1])
        print(lines[2 * ii + 1][:-1])
        database[lines[2 * ii][:-1]] = lines[2 * ii + 1][:-1]
    print(database)
    return database
    
# increment count of number of items recycled and store in text file
def increment_lifetime_count():
    lifetime_count = 0
    if (os.path.isfile(count_file_name)):
        with open(count_file_name, 'r') as count_file:
            count_str = count_file.read()
            lifetime_count = int(count_str[:-1])
    lifetime_count = lifetime_count + 1
    with open(count_file_name, 'w') as count_file:
        count_file.write(str(lifetime_count) + '\n')
    
# capture a picture, then scan it and return empty string or string containing barcode
def barcode_scanner():
    # capture a picture
    # decode file
    # if not str, return 0
    # else, return results[0][1]?
    camera.capture('foo.jpg')
    barcode = scan_image.read_barcode('monster.jpg')
    if (barcode):
        print(barcode)
    else:
        print('No barcode found')
    return barcode
    
# regularly check if there's a barcode in view of the webcam and if so, alert Arduino
def loop(database, ser):
    while(True):
        barcode = barcode_scanner()
        #if (barcode):
        #    if (barcode in database):
        #        print('Barcode found in database. Add more stuff here later.')
        #        if database[barcode] == 0:
        #            ser.write('1')
        #        else:
        #            ser.write('0')
        #            increment_lifetime_count()
        #        time.sleep(1) # sleep for a second after sending message to Arduino
        #    else:
        #        print('Barcode not found in database. Add more stuff here later too.')
        #        ser.write('2')
        #        response = ser.readline()
        #        if (response):
        #            write_database(database)

# initialize serial connection and database, then begin the infinite loop
def main():
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=8)
    # might want to delay so camera can warm up
    database = initialize_database()
    loop(database, ser)
  
if __name__== "__main__":
    main()