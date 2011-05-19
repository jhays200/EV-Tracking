import httplib, urllib, time, math

body = None
headers = {"Content-type": "metrics/xml", "Accept":"text/plain"}
conn = httplib.HTTPConnection("trics.eve-refine.com", 80)

def Init():
  body = None
  headers = {"Content-type": "metrics/xml", "Accept":"text/plain"}
  conn = httplib.HTTPConnection("trics.eve-refine.com", 80)

def Test(value):
	body = '<Testing><Test1>{0}</Test1></Testing>'.format( str( 2 * math.sin( (math.pi * value)/16 ) ))
	conn.request("POST", "/", body, headers)
	conn.close()
	print( body )
	time.sleep(1)
	conn.connect()
	body = '<Testing><Test2>{0}</Test2></Testing>'.format(str( 3 * math.cos( (math.pi * value)/16 )) )
	conn.request("POST", "/", body, headers)
	conn.close()
	print( body )
	time.sleep(1)
	conn.connect()