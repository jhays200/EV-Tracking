<%@ Control Language="C#" AutoEventWireup="true" CodeFile="GoogleMaps.ascx.cs" Inherits="GoogleMaps" %>

<script type="text/javascript" src="http://www.google.com/jsapi?key=ABQIAAAA3LLHrvZLyni1ZQu5UI8EKRRW2Q5vJGiyJT2QM93JEWQRZZyYbxSlMXC6T0a1pEKM-DnhvzBLkvbAMg"></script>

<script type="text/javascript">
	google.load("jquery", '1.2.6');
	google.load("maps", "2.x");
</script>

<script type="text/javascript">
$(document).ready(function() {
    BuildMap();
});

$(document).unload(function() {
    GUnload();
});

var map;
var bounds;

function BuildMap()
{
	if (GBrowserIsCompatible())
	{
		map = new GMap2(document.getElementById("map_canvas"));
		
		map.addControl(new GSmallMapControl());
        map.addControl(new GMapTypeControl());

		map.setCenter(new GLatLng(42.25648, -121.78551), 10);
		
		LoadPoints();
	}
}

// initial load points
function LoadPoints()
{
    GDownloadUrl("GoogleMaps.ashx", function(data, responseCode)
    {    
		map.clearOverlays();
		bounds = new GLatLngBounds();
        var xml = GXml.parse(data);
        var markers = xml.documentElement.getElementsByTagName("marker");
        
        var point;
        var prev = new GLatLng(parseFloat(markers[0].getAttribute("lat")),
                                parseFloat(markers[0].getAttribute("lng")));
                                   
        for (var i = 1; i < markers.length; i++)
        {
            point = prev;
            prev = new GLatLng(parseFloat(markers[i].getAttribute("lat")),
                               parseFloat(markers[i].getAttribute("lng")));
                               
            var polyline = new GPolyline([ prev, point ], "#ff0000", 10 - (i/1.5));
            map.addOverlay(polyline);
            
            var marker = new GMarker(point);
            bounds.extend(marker.getPoint());
        }				
        zoomToBounds();
    });	
	setTimeout ( "LoadPoints()", 15000 );
}
function zoomToBounds() {
	map.setCenter(bounds.getCenter());
	map.setZoom(map.getBoundsZoomLevel(bounds)-1);
}
</script>
<div id="map_canvas" style="width: 400px; height: 250px;"></div>
