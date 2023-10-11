#!/bin/bash
var=/etc/network/interfaces

if [ "$1" = "--dhcp" -o "$1" = "-d" ]; then
sudo cat /dev/null > $var
sudo cat << EOF > $var
auto lo
iface lo inet loopback
auto eth0
iface eth0 inet dhcp
EOF

sudo /etc/init.d/networking restart
echo "Network is set for dhcp!"
shift 1
elif [ "$1" = "--head" -o "$1" = "-h" ]; then
sudo cat /dev/null > $var
sudo cat << EOF > $var
auto lo
iface lo inet loopback
auto eth0
iface eth0 inet static
address 10.10.5.6
gateway 10.10.5.1
netmask 255.255.255.0
broadcast 10.10.5.255
EOF
sudo /etc/init.d/networking restart
echo "Network is set for head unit device!"
shift 2
elif [ "$1" = "--ctrl" -o "$1" = "-c" ]; then
sudo cat /dev/null > $var
sudo cat << EOF > $var
auto lo
iface lo inet loopback
auto eth0
iface eth0 inet static
address 10.10.5.7
gateway 10.10.5.1
netmask 255.255.255.0
broadcast 10.10.5.255
EOF
sudo /etc/init.d/networking restart
echo  "Network is set for control unit device!"
shift 3
else
echo "Select option!"
fi

echo "DONE"

