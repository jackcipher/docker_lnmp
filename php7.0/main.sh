#!/bin/sh

echo '安装 mycrypt 拓展'

apt-get update -y && apt-get upgrade -y

apt-get install -y $GD_DEPS

docker-php-ext-configure gd \
        --with-gd \
        --with-freetype-dir=/usr/include/ \
        --with-png-dir=/usr/include/ \
        --with-jpeg-dir=/usr/include/ && \
      NPROC=$(grep -c ^processor /proc/cpuinfo 2>/dev/null || 1) && \
      docker-php-ext-install -j${NPROC} gd

apt-get install vim

docker-php-ext-install /usr/local/extensions/mycrypt/
docker-php-ext-enable mycrypt

#cd /usr/local/extensions/mycrypt
#phpize
#./configure
#make
#make install
#docker-php-ext-enable mycrypt