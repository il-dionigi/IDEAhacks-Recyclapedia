# -*- coding: utf-8 -*-
"""
Created on Sat Jan 13 14:06:25 2018

@author: jlung20
"""
#import DynamsoftBarcodeReader as DBR
import zbar
import zbar.misc
import matplotlib.image as mpimg

def check_database(database, barcode):
    if barcode in database:
        return 1
    else:
        return 0

def write_database(database, file_name):
    str_1 = input('Enter barcode: ')
    str_2 = input('Enter 1 if recyclable, 0 otherwise: ')
    database[str_1] = str_2
    file = open(file_name, 'a')
    file.write(str_1 + '\n')
    file.write(str_2 + '\n')
    file.close()

def initialize_database(str):
    file = open(str, 'r')
    lines = file.readlines()
    file.close()
    database = {}
    for ii in range(0, int(len(lines)/2)):
        print(lines[2 * ii][:-1])
        print(lines[2 * ii + 1][:-1])
        database[lines[2 * ii][:-1]] = lines[2 * ii + 1][:-1]
    print(database)
    return database
    
def barcode_scanner():
    # capture a picture
    # decode file
    # if not str, return 0
    # else, return results[0][1]?
    #results = DBR.decodeFile('monster.jpg')
    img = mpimg.imread('monster.jpg')
    scanner = zbar.Scanner()
    results = scanner.scan(img)
    if (results):
        print(results)
    else:
        print('No barcode found')
    # acting as a stub right now; replace when appropriate
    # return 0 if no barcode; otherwise return barcode value
    return '5060166693732'
    
def loop(database):
    while(True):
        barcode = barcode_scanner()
        if (barcode):
            if (barcode in database):
                print('Barcode found. Add more stuff here later.')
            else:
                print('Barcode not found. Add more stuff here later too.')
                # message passing stuff, then wait for response
                # write_database(database, str)
                
def main():
    
    # hard-coding the parameter file
    str = 'params.txt'
    database = initialize_database(str)
    loop(database)
    
    #if check_database(database, '092825305385'):
    #    print('check_database() works properly')
    # work on the barcode scanner part of things
  
if __name__== "__main__":
    main()