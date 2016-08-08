#!/bin/sh

while true
do
	sleep 10s
	echo "start submitIp gateUpnp\n"
	/home/rock/gateApp/gateUpnp
	/home/rock/gateApp/submitIp
done
