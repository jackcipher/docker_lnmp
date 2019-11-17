FROM php:7.3-fpm

COPY ./sources.list /etc/apt
COPY ./extensions /usr/local/extensions

COPY main.sh /usr/local/main.sh


#RUN sed -i s/archive.ubuntu.com/mirrors.aliyun.com/g /etc/apt/sources.list \
#    && sed -i s/security.ubuntu.com/mirrors.aliyun.com/g /etc/apt/sources.list \
#    && sed -i s/security.debian.org/mirrors.aliyun.com/g /etc/apt/sources.list \
#    && sed -i s/cdn-fastly.deb.debian.org/mirrors.aliyun.com/g /etc/apt/sources.list \
#    && apt-get update && apt-get upgrade



RUN /bin/bash /usr/local/main.sh
