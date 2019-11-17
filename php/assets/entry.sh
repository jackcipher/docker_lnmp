#!/bin/sh

echo 'step1: sed 换源'

sed -i 's/dl-cdn.alpinelinux.org/mirrors.aliyun.com/g' /etc/apk/repositories 

apk update

echo 'step2: 安装拓展'
apk add --no-cache libmcrypt-dev freetype-dev libjpeg-turbo-dev git libpng-dev jq vim libzip-dev

docker-php-ext-install mysqli pdo pdo_mysql mbstring bcmath zip opcache

docker-php-ext-configure gd --with-freetype-dir=/usr/include/ --with-jpeg-dir=/usr/include/ --with-png-dir=/usr/include/

docker-php-ext-install -j$(nproc) gd

echo 'step3: 安装mcrypt'

tar zxvf /usr/local/assets/mcrypt-1.0.3.tgz -C /usr/local/assets

docker-php-ext-install /usr/local/assets/mcrypt-1.0.3

docker-php-ext-enable mcrypt
