#FROM php:7.0-rc-fpm-alpine3.8
#
#ENV MEMCACHED_DEPS zlib-dev libmemcached-dev cyrus-sasl-dev git
#ENV GD_DEPS freetype libpng libjpeg-turbo freetype-dev libpng-dev libjpeg-turbo-dev
#
#RUN php -r "copy('https://getcomposer.org/installer', 'composer-setup.php');" && \
#php composer-setup.php && \
#php -r "unlink('composer-setup.php');" && \
#mv composer.phar /usr/local/bin/composer && \
#composer self-update && \
#apk add $PHPIZE_DEPS && \
#apk add $GD_DEPS && \
#apk add $MEMCACHED_DEPS && \
#pecl install redis memcached msgpack && \
#docker-php-ext-enable redis memcached && \
#docker-php-ext-configure gd \
#    --with-gd \
#    --with-freetype-dir=/usr/include/ \
#    --with-png-dir=/usr/include/ \
#    --with-jpeg-dir=/usr/include/ && \
#  NPROC=$(grep -c ^processor /proc/cpuinfo 2>/dev/null || 1) && \
#  docker-php-ext-install -j${NPROC} gd && \
#docker-php-ext-install zip pdo iconv pdo_mysql mysqli


#FROM tiredoy/php:2.0
#
#RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.aliyun.com/g' /etc/apk/repositories
#
#COPY ./extensions /usr/local/extensions
#COPY main.sh /usr/local/main.sh
#RUN chmod +x /usr/local/main.sh

#RUN /bin/sh /usr/local/main.sh


#FROM phpdockerio/php7-fpm:latest
##FROM php:7.0.33-fpm
#
#COPY ./sources.list /etc/apt
#COPY ./extensions /usr/local/extensions
#
#COPY main.sh /usr/local/main.sh

# change source
#RUN sed -i s/archive.ubuntu.com/mirrors.aliyun.com/g /etc/apt/sources.list \
#    && sed -i s/security.ubuntu.com/mirrors.aliyun.com/g /etc/apt/sources.list \
#    && sed -i s/security.debian.org/mirrors.aliyun.com/g /etc/apt/sources.list \
#    && sed -i s/cdn-fastly.deb.debian.org/mirrors.aliyun.com/g /etc/apt/sources.list \
#    && apt-get update && apt-get upgrade

#
#
#RUN /bin/bash /usr/local/main.sh


#FROM php:7.0.33-fpm-alpine
#
#COPY ./extensions /usr/local/extensions
#COPY main.sh /usr/local/main.sh
#
## GD 拓展依赖库
#ENV GD_DEPS freetype libjpeg libpng libjpeg-turbo freetype-dev libpng-dev libjpeg-turbo-dev
#ENV PHPIZE_DEPS autoconf g++ make re2c
#
## 1. 阿里云换源
#RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.aliyun.com/g' /etc/apk/repositories
#
## 2. php源文件解压
#RUN docker-php-source extract
#
## 3. phpize 拓展依赖
#RUN apk add $PHPIZE_DEPS
#
## 4. GD 拓展依赖
#RUN apk add $GD_DEPS
#
## 5. 安装gd拓展
#RUN docker-php-ext-configure gd \
#        --with-gd \
#        --with-freetype-dir=/usr/include/ \
#        --with-png-dir=/usr/include/ \
#        --with-jpeg-dir=/usr/include/ && \
#      NPROC=$(grep -c ^processor /proc/cpuinfo 2>/dev/null || 1) && \
#      docker-php-ext-install -j${NPROC} gd
#
## 6. 安装 redis 拓展
#RUN pecl install redis && \
#docker-php-ext-enable redis
#
## 7. 常用拓展
#RUN docker-php-ext-install zip pdo iconv pdo_mysql mysqli tokenizer mbstring
#
## 8. 清理 PHP 源文件
#RUN docker-php-source delete

# 9. 其他操作
#RUN /bin/sh /usr/local/main.sh

FROM phpdockerio/php7-fpm:latest

COPY ./extensions /usr/local/extensions
COPY main.sh /usr/local/main.sh
#COPY php-src-php-7.0.33 /usr/local/src

RUN export http_proxy=127.0.0.1:1199; export https_proxy=127.0.0.1:1199

ENV GD_DEPS_APACHE libjpeg-dev libpng-dev libfreetype6-dev

#RUN apt-get install $GD_DEPS_APACHE
#
#RUN docker-php-ext-configure gd \
#        --with-gd \
#        --with-freetype-dir=/usr/include/ \
#        --with-png-dir=/usr/include/ \
#        --with-jpeg-dir=/usr/include/ && \
#      NPROC=$(grep -c ^processor /proc/cpuinfo 2>/dev/null || 1) && \
#      docker-php-ext-install -j${NPROC} gd
#
#RUN /bin/sh /usr/local/main.sh

#RUN yum install wget
#
#RUN wget -O /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-7.repo
#sed -i  's/$releasever/6.8/g' /etc/yum.repos.d/CentOS-Base.repo
