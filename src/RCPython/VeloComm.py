import httplib, urllib, time, math

headers = {"Content-type": "metrics/xml", "Accept":"text/plain"}
conn = httplib.HTTPConnection("trics.eve-refine.com", 80)

def Init():
  headers = {"Content-type": "metrics/xml", "Accept":"text/plain"}
  conn = httplib.HTTPConnection("trics.eve-refine.com", 80)

def Send(body):
	conn.connect()
	conn.request("POST", "/", body, headers)
	conn.close()
	print body