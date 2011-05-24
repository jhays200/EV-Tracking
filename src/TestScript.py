#!/usr/bin/python2.7

#TestScript.py
#
#Description: Test Driver for our system, so we could reduce manual testing.
#
#Functions:
#	RunProgram()
#		This starts our RCAcquisition service and ends the program
#		after a specified number seconds
#
#	ProcessData()
#		This program pulls data from the database.  Displays it to the user and
#		Processes the data to be used with the GPS visualizer websites in csv format.


import os
import time
import MySQLdb
from io import open

def RunProgram():
       #timeBegan = time.time()
       t = raw_input("Enter trip time in secs: ")
       a = os.spawnl(os.P_NOWAIT, './build/bin/RCAcquisition', './build/bin/RCAcquisition')
       try:
         time.sleep(int(t))
         os.kill(a, 15)
       except:
         os.kill(a, 15)
       #timeEnd = time.time()

def ProcessGPS():
       f = open("gps_test.txt", "w")

       if f.writable():
               i = 0
               conn = MySQLdb.connect(host = "localhost",
                                                               user = "root",
                                                               passwd = "maverick",
                                                               db = "jp")
               cursor = conn.cursor()
               cursor.execute("SELECT Longitude, Lattitude from GPS_DATA")
               result_set = cursor.fetchall()
               f.write(unicode("name,latitude,longitude\n"))

               for row in result_set:
                       i = i + 1
                       print "long: ", row[0], " Latt: ", row[1]
                       f.write(unicode (str(i) + ',' + str(row[1]) + ',' + str(row[0]) + '\n') )

               if(raw_input("Do you want to clear gps data (y/n): ") == "y"):
                       cursor.execute("DELETE from GPS_DATA;")

               cursor.close()
               conn.close()
       else:
               print "Unable to open file test.txt"

       f.close()

def ProcessEMC():
	f = open("emc_test.txt", "w")

	if f.writable():
			i = 0
			conn = MySQLdb.connect(host = "localhost",
															user = "root",
															passwd = "maverick",
															db = "jp")
			cursor = conn.cursor()
			cursor.execute("SELECT SPEED, RPM from MOTOR_DATA")
			result_set = cursor.fetchall()
			f.write(unicode("speed,rpm\n"))

			for row in result_set:
					i = i + 1
					print "Speed: ", row[0], " RPM: ", row[1]
					f.write(unicode (str(i) + ',' + str(row[1]) + '\n') )

			if(raw_input("Do you want to clear emc data (y/n): ") == "y"):
					cursor.execute("DELETE from MOTOR_DATA;")

			cursor.close()
			conn.close()
	else:
			print "Unable to open file test.txt"

	f.close()
       
def ProcessBMS():
	f = open("bms_test.txt", "w")

	if f.writable():
			i = 0
			conn = MySQLdb.connect(host = "localhost",
															user = "root",
															passwd = "maverick",
															db = "jp")
			cursor = conn.cursor()
			cursor.execute("SELECT Charge from BMS")
			result_set = cursor.fetchall()
			f.write(unicode("charge\n"))

			for row in result_set:
					i = i + 1
					print "Charge: ", row[0]
					f.write(unicode (str(i) + '\n') )

			if(raw_input("Do you want to clear bms data (y/n): ") == "y"):
					cursor.execute("DELETE from BMS;")

			cursor.close()
			conn.close()
	else:
			print "Unable to open file test.txt"

	f.close()
       
print "Testing pulling from db"
try:
 RunProgram()
 ProcessBMS()
 ProcessEMC()
 ProcessGPS()
except:
 print "Unexpected Error"
 exit(1)

exit(0)
