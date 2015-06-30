cd rootfs;
pwd;
mkdir root dev boot etc lib proc sys mnt tmp var home
chmod 1777 tmp
mkdir usr/lib usr/modules
mkdir mnt/etc mnt/jffs2 mnt/yaffs mnt/data mnt/temp
mkdir var/lib var/lock var/log var/run var/tmp
chmod 1777 var/tmp
mknod -m 600 dev/console c 5 1
mknod -m 600 dev/null c 1 3

#append inittab 

echo "::sysinit:/etc/init.d/rcS
::askfirst:-/bin/sh
::respawn:-/bin/sh
::restart:/sbin/init 
::ctrlaltdel:/sbin/reboot
::shutdown:/bin/umount -a -r
::shutdown:/sbin/swapoff -a
" > etc/inittab

#create rcS file

mkdir etc/init.d
echo "#!/bin/sh
# mount all filesystem defined in \"fstab\"
echo \"#mount all.......\"
/bin/mount -a
" > etc/init.d/rcS 

#
chmod 1777 etc/init.d/rcS
echo "proc	/proc	proc	defaults	0 0
none	/tmp	ramfs	defaults	0 0
sysfs  		/sys         sysfs    defaults   0 0 
mdev       /dev         ramfs    defaults   0 0
" > etc/fstab

#add lib
cp -a cp -a  /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/lib/*.so* lib/
