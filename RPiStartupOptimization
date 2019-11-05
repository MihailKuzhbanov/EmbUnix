#проверка времени загрузки
system-analyze
system-analyze blame

#disable/enable - отключение/включение сервиса
#mask/unmask - сокрытие/открытие сервиса, для отключения/включения автоматического включения сервиса

#отключение логов rsyslog и включение логов systemd
sudo systemctl disable rsyslog
sudo systemctl mask rsyslog
sudo systemctl enable systemd-networkd
sudo systemctl enable systemd-resolved
sudo systemctl start systemd-resolved

#создание ссылки на файл конфигурации
sudo rm /etc/resolv.conf
sudo ln -s /run/systemd/resolve/resolv.conf /etc/resolv.conf
sudo systemctl disable networking.service
#настройка DNS в resolv.conf
#nameserver 8.8.8.8

#отключение сервиса выполнения задач по расписанию
sudo systemctl disable cron

#отключение и скрытие сервиса uart
sudo systemctl disable hciuart
sudo systemctl mask hciuart

#отключение и скрытие сервиса dhcp
sudo systemctl disable dhcpcd
sudo systemctl mask dhcpcd

#при отключении DHCP
#необходима настройка статического адреса в /etc/network/interfaces
#пример:
#auto eth0
#iface eth0 inet static
#address 192.168.137.2
#netmask 255.255.255.0
#gateway 192.168.137.1
