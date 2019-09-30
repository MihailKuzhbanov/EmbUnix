#address: 192.168.7.2
#user: debian
#password: temppwd

sudo /sbin/route add default gw 192.168.7.1
echo "nameserver 8.8.8.8" >> /etc/resolv.conf
sudo /etc/init.d/networking restart
apt-get update
apt-get install links
wget https://download.teamviewer.com/download/linux/teamviewer_i386.deb
sudo apt-get install ./teamviewer_i386.deb
