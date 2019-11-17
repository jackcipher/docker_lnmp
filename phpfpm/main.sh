#!/bin/sh

echo '安装 mycrypt 拓展'


apt-get update
apt-get upgrade
apt-get install vim

cd /usr/local/extensions/mycrypt
phpize
./configure
make
make install
docker-php-ext-enable mycrypt