import httplib, urllib, time, math

body = None
headers = {"Content-type": "metrics/xml", "Accept":"text/plain"}
conn = httplib.HTTPConnection("trics.eve-refine.com", 80)

def Test(value):
	