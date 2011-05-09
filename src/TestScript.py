import os
import time
import MySQLdb
from io import open

def RunProgram():
	#timeBegan = time.time()
	a = os.spawnl(os.P_NOWAIT, './build/bin/RCAcquisition', './build/bin/RCAcquisition')
	time.sleep(10)
	os.kill(a, 15)
	#timeEnd = time.time()
	
def ProcessData():
	f = open("test.txt", "w")
	
	if f.writable():
		i = 0.0
		conn = MySQLdb.connect(host = "localhost",
								user = "root",
								passwd = "starwars",
								db = "jp")
		cursor = conn.cursor()
		cursor.execute("SELECT Longitude, Lattitude from GPS_DATA")
		result_set = cursor.fetchall()
		
		for row in result_set:
			i = i + 0.2
			print "long: ", row[0], " Latt: ", row[1]
			f.write(unicode (str(row[1]+i) + ', ' + str(row[0]+i) + '\n') )
		
		cursor.execute("DELETE from GPS_DATA;")
		cursor.close()
		conn.close()
	else:
		print "Unable to open file test.txt"
	
	f.close()

print "Testing pulling from db"
RunProgram()
ProcessData()
