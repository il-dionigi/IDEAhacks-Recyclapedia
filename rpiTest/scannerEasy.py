import serial
import time
import os.path
from mcr12_serial import BarcodeScanner

# hard-coding the relevant files
file_name = 'params.txt'
count_file_name = 'count.txt'
#initializing barcode scanner
bcd = BarcodeScanner("/dev/ttyACM0", baudrate=9600)

# add another entry to database and update text file for database
def write_database(database, barcode, is_recyclable):
    database[barcode] = is_recyclable
    file = open(file_name, 'a')
    file.write(barcode + '\n')
    file.write(is_recyclable + '\n')
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
    
# reads from the text file containing lifetime count, if present
def get_lifetime_count():
    lifetime_count = 0
    if (os.path.isfile(count_file_name)):
        with open(count_file_name, 'r') as count_file:
            count_str = count_file.read()
            lifetime_count = int(count_str[:-1]) 
    return lifetime_count

# return 4 digits, right justified, indicating the lifetime count
def make_lifetime_count_string():
    count_str = str(get_lifetime_count())
    return '0' * (4 - len(count_str)) + count_str

# increment count of number of items recycled and store in text file
def increment_lifetime_count():
    lifetime_count = get_lifetime_count() + 1
    with open(count_file_name, 'w') as count_file:
        count_file.write(str(lifetime_count) + '\n')
    
# alert Arduino and update count and database if necessary upon barcode scan
def loop(database, ser):
    while(True):
        time.sleep(2)
        barcode = bcd.scan()
        print(barcode)
        if (barcode):
            if (barcode in database):
                print('Barcode found in database.')
                if database[barcode] == '1':
                    increment_lifetime_count()
                print(database[barcode][0])
                ser.write(database[barcode][0])
                time.sleep(2) # sleep for a bit after sending message to Arduino
            else:
                print('Barcode not found in database.')
                print('2')
                ser.write('2')
                time.sleep(0.2)
                ser.reset_input_buffer()
                time.sleep(0.1)
                response = ser.readline()
                if (response):
                    print('response: ' + response)
                    print('response[0]: ' + response[0])
                    if(response[0] != '2'):
                        write_database(database, barcode, response[0])

# initialize serial connection and database, then begin the infinite loop
def main():
    ser = serial.Serial('/dev/ttyACM1', 9600, timeout=8)
    database = initialize_database()
    # send lifetime count
    time.sleep(10)
    print(make_lifetime_count_string())
    ser.write(make_lifetime_count_string())
    loop(database, ser)
  
if __name__== "__main__":
    main()
