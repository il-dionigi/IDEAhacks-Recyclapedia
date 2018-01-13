# -*- coding: utf-8 -*-
"""
Created on Sat Jan 13 12:04:03 2018

@author: jlung20
"""

# Going to need to make a couple small changes to go back to Python2
# So this is going to add to the database and append the barcode to the params file
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
    
def main():
    # hard-coding the parameter file
    str = 'params.txt'
    database = initialize_database(str)
    while(input('Enter 1 to enter another barcode. Otherwise, enter another number: ') == '1'):
        write_database(database, str)
        print(database)
    if check_database(database, '092825305385'):
        print('check_database() works properly')
  
if __name__== "__main__":
  main()    
    