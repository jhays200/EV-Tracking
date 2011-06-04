select * from Sensors;

delete from Sensors;

insert into Sensors (sensorName, deviceName, displayName, valueCount, errorCount, descript, minValue, maxValue, valueName)
	values ('mtemp', 'Testing', 'XMLSWFGraph', 1, 0, 'Testing Motor Speed', 0.0, 120.0, 'x');

insert into Sensors (sensorName, deviceName, displayName, valueCount, errorCount, descript, minValue, maxValue, valueName)
	values ('mspeed', 'Testing', 'XMLSWFGraph', 1, 0, 'Testing Motor Speed', 0.0, 200.0, 'x');

insert into Sensors (sensorName, deviceName, displayName, valueCount, errorCount, descript, minValue, maxValue, valueName)
	values ('rpm', 'Testing', 'XMLSWFGraph', 1, 0, 'Testing rpm', 0.0, 8000.0, 'x');

insert into Sensors (sensorName, deviceName, displayName, valueCount, errorCount, descript, minValue, maxValue, valueName)
	values ('dutycycles', 'Testing', 'XMLSWFGraph', 1, 0, 'Testing Motor dutycycles', 0.0, 200.0, 'x');

insert into Sensors (sensorName, deviceName, displayName, valueCount, errorCount, descript, minValue, maxValue, valueName)
	values ('mcurrent', 'Testing', 'XMLSWFGraph', 1, 0, 'Testing Motor Current', 0.0, 1200.0, 'x');

insert into Sensors (sensorName, deviceName, displayName, valueCount, errorCount, descript, minValue, maxValue, valueName)
	values ('charge', 'Testing', 'XMLSWFGraph', 1, 0, 'Testing charge', 0.0, 100.0, 'x');

insert into Sensors (sensorName, deviceName, displayName, valueCount, errorCount, descript, minValue, maxValue, valueName)
	values ('Speed', 'Testing', 'XMLSWFGraph', 1, 0, 'Testing Speed', 0.0, 200.0, 'x');

insert into Sensors (sensorName, deviceName, displayName, valueCount, errorCount, descript, minValue, maxValue, valueName)
	values ('Laditude', 'Testing', 'XMLSWFGraph', 1, 0, 'Testing Laditude', -90.0, 90.0, 'x');


insert into Sensors (sensorName, deviceName, displayName, valueCount, errorCount, descript, minValue, maxValue, valueName)
	values ('Longitude', 'Testing', 'XMLSWFGraph', 1, 0, 'Testing Longitude', -180.0, 180.0, 'x');