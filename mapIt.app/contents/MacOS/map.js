	new QWebChannel(qt.webChannelTransport, function(channel)
	{
 		var webobj = channel.objects.webobj;
 		window.mainwindow = webobj;
 	});

	function updateCPP(event)
	{
	   window.mainwindow.updateLatLong(L.toString());
	}

	document.onclick = update;

	var mymap = L.map('mapid').setView([34.13889, -118.21360], 13);

	L.tileLayer('https://api.tiles.mapbox.com/v4/{id}/{z}/{x}/{y}.png?access_token=pk.eyJ1IjoibWFwYm94IiwiYSI6ImNpejY4NXVycTA2emYycXBndHRqcmZ3N3gifQ.rJcFIG214AriISLbB6B5aw', {
		maxZoom: 18,
		attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/">OpenStreetMap</a> contributors, ' +
			'<a href="https://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, ' +
			'Imagery © <a href="https://www.mapbox.com/">Mapbox</a>',
		id: 'mapbox.streets'
	}).addTo(mymap);

	L.marker([34.13889, -118.21360]).addTo(mymap);

	L.circle([34.139548, -118.210927], {
		color: 'red',
		fillColor: '#f03',
		fillOpacity: 0.5,
		radius: 50
	}).addTo(mymap);

	L.circle([34.123918, -118.218535], {
                color: 'red',
                fillColor: '#f03',
                fillOpacity: 0.5,
                radius: 50
        }).addTo(mymap);

 	L.circle([34.111193, -118.190268], {
                color: 'red',    
                fillColor: '#f03',
                fillOpacity: 0.5,
                radius: 50
        }).addTo(mymap);
	
	var latlngs = [
    		[34.111193, -118.190268],
		[34.123918, -118.218535],
		[34.139548, -118.210927]
	];
	
	var polyline = L.polyline(latlngs, {color: 'blue'}).addTo(mymap);
	// zoom the map to the polyline
	mymap.fitBounds(polyline.getBounds());

