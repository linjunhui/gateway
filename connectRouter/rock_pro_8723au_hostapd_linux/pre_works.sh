#!/bin/sh

ntpdate 0.rhel.pool.ntp.org
sleep 5



ifconfig eth0 up
sleep 3
dhclient eth0
sleep 

apt-get install dnsmasq -y
apt-get install haveged -y

rm -rf /etc/auto_wifi.sh > /dev/null
cp auto_wifi.sh /etc

rm -rf /etc/dnsmasq.conf > /dev/null
cp dnsmasq.conf /etc

rm -rf /etc/network/interfaces > /dev/null
cp interfaces /etc/network

rm -rf /etc/auto_wifi.sh > /dev/null
cp auto_wifi.sh /etc

mkdir -p /etc/hostapd/
cp hostapd.conf /etc/hostapd
