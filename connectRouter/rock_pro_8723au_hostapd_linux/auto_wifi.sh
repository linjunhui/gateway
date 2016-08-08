#!/bin/sh

#Stop named, if already running. dnsmasq cannot run because it take up port 53 
sudo killall named                                                              
#Stop dnsmasq, if already running 
sudo /usr/sbin/service dnsmasq stop 
#Stop hostapd, if already running                                               
sudo /usr/bin/pkill hostapd 
#Bring down wlan0 
sudo /sbin/ip link set down dev wlan0                                           
#stop haveged                                                                   
sudo /etc/init.d/haveged stop
sleep 3
#start the AP service
#Start hostapd, and it will automatically be bringed up 
sudo hostapd -B /etc/hostapd/hostapd.conf
#Set ip on wlan0 
sudo /sbin/ip addr add 192.168.2.1/24 dev wlan0
#Start dnsmasq 
sudo /usr/sbin/service dnsmasq start
#Start ip_forward 
sudo echo 1 > /proc/sys/net/ipv4/ip_forward
#add iptables rule for NAT 
sudo /sbin/iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE
#start haveged
sudo /etc/init.d/haveged start

