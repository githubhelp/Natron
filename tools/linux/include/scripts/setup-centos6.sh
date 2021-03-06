#!/bin/sh

rm -f /etc/yum.repos.d/CentOS-Base.repo || exit 1
sed -i 's#baseurl=file:///media/CentOS/#baseurl=http://vault.centos.org/6.4/os/$basearch/#;s/enabled=0/enabled=1/;s/gpgcheck=1/gpgcheck=0/;/file:/d' /etc/yum.repos.d/CentOS-Media.repo || exit 1
yum -y install wget || exit 1
if [ ! -f /etc/yum.repos.d/devtools-2.repo ]; then
  wget http://people.centos.org/tru/devtools-2/devtools-2.repo -O /etc/yum.repos.d/devtools-2.repo
fi
yum -y install vixie-cron crontabs libxslt-devel pango-devel librsvg2-devel libxml2-devel unzip rsync git screen file tree bc devtoolset-2-toolchain gcc-c++ kernel-devel libX*devel fontconfig-devel freetype-devel zlib-devel *GL*devel *xcb*devel xorg*devel libdrm-devel mesa*devel *glut*devel dbus-devel xz patch bzip2-devel glib2-devel bison flex expat-devel libtool-ltdl-devel || exit 1

chkconfig crond on
service crond start

echo "All done"
exit 0

