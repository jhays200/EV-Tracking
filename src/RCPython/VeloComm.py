import httplib, urllib, time, math

body = None
headers = {"Content-type": "metrics/xml", "Accept":"text/plain"}
conn = httplib.HTTPConnection("trics.eve-refine.com", 80)

def Test(value):
	body = '<Testing><Test1>{0}</Test1></Testing>'.format(str(value))
	conn.request("POST", "/", body, headers)
	conn.close()
	time.sleep(100)