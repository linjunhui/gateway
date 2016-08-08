#!/bin/sh

sed -i '/auto_wifi.sh/d' /etc/init.d/rc.local

apt-get remove dnsmasq -y
apt-get remove haveged -y

rm -rf /etc/auto_wifi.sh > /dev/null
rm -rf /etc/dnsmasq.conf > /dev/null
rm -rf /etc/network/interfaces > /dev/null
rm -rf /etc/auto_wifi.sh > /dev/null
rm -rf /etc/hostapd/hostapd.conf > /dev/null
