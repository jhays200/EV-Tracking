#!/usr/bin/env python

#Test script for Velo website
import httplib, urllib, time, math

body = None          #this will hold the string to be sent

headers = {"Content-type": "metrics/xml", "Accept":"text/plain"}
conn = httplib.HTTPConnection("trics.eve-refine.com", 80)

for i in range(0, 32):
    body = '<Testing><Test1>{0}</Test1></Testing>'.format( str( 2 * math.sin( (math.pi * i)/16 ) ))
    conn.request("POST", "/", body, headers)
    conn.close()
    print( body )
    time.sleep(1)
    conn.connect()
    body = '<Testing><Test2>{0}</Test2></Testing>'.format(str( 3 * math.cos( (math.pi * i)/16 )) )
    conn.request("POST", "/", body, headers)
    conn.close()
    print( body )
    time.sleep(1)
    conn.connect()
    

conn.close()
