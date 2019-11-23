#https://www.get-edi.io/Real-Time-Linux-on-the-Raspberry-Pi/
#host system
sudo apt-get update
sudo apt install build-essential bc kmod cpio flex cpio libncurses5-dev bison libssl-dev wget
sudo apt-get install gcc-aarch64-linux-gnu
mkdir -p ~/edi-workspace/rt-kernel && cd ~/edi-workspace/rt-kernel
wget https://mirrors.edge.kernel.org/pub/linux/kernel/v4.x/linux-4.19.8.tar.xz
wget https://cdn.kernel.org/pub/linux/kernel/projects/rt/4.19/older/patch-4.19.8-rt6.patch.xz
tar xf linux-4.19.8.tar.xz
cd linux-4.19.8
xzcat ../patch-4.19.8-rt6.patch.xz | patch -p1
wget -O .config https://raw.githubusercontent.com/raspberrypi/linux/rpi-4.18.y/arch/arm64/configs/bcmrpi3_defconfig
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- olddefconfig
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- menuconfig
make -j $(nproc) KBUILD_IMAGE=arch/arm64/boot/Image ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- deb-pkg

#target system
sudo fdisk -l
mkdir /media/usbstick
mount /dev/sda1 /media/usbstick
cd
mkdir /kernel-rt
cd kernel-rt
cp /media/usbstick/rt-kernel
cd /media/usbstick/rt-kernel
sudo apt-get install gdebi
sudo gdebi linux-headers-4.19.8-rt6_4.19.8-rt6-v8-1_arm64.deb linux-image-4.19.8-rt6_4.19.8-rt6-v8-1_arm64.deb
#sudo update-grub
sudo reboot
