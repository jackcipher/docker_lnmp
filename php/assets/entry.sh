#!/bin/sh

echo 'step1: sed 换源'

sed -i 's/dl-cdn.alpinelinux.org/mirrors.aliyun.com/g' /etc/apk/repositories 

apk update

echo 'step2: 安装拓展 - 系统自带'
apk add --no-cache gcc g++ make autoconf libmcrypt-dev freetype-dev libjpeg-turbo-dev git libpng-dev jq vim libzip-dev

docker-php-ext-install mysqli pdo pdo_mysql bcmath zip opcache

docker-php-ext-configure gd --with-freetype-dir=/usr/include/ --with-jpeg-dir=/usr/include/ --with-png-dir=/usr/include/

docker-php-ext-install -j$(nproc) gd

echo 'step3: 安装拓展 - PECL'

pecl install /usr/local/assets/redis-5.1.1.tgz
docker-php-ext-enable redis
