#!/bin/bash
/usr/sbin/service dnsmasq stop
killall hostapd dhcpd
echo "0" > /proc/sys/net/ipv4/ip_forward
ifconfig wlan0 down
nmcli nm wifi on 
