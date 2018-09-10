# LNMP stack on Docker


![lnmp Stack version](https://img.shields.io/badge/lnmp-v1-green.svg)


使用 [Docker](https://www.docker.com/) 与 [Docker-compose](https://docs.docker.com/compose/) 编排技术构造简单实用的 LNMP 环境。


本环境栈用到的镜像为：

* [tiredoy/php](https://hub.docker.com/r/tiredoy/php/)
* [nginx](https://hub.docker.com/_/nginx/)
* [mysql](https://hub.docker.com/_/mysql/)

 
默认情况下, 本环境栈暴露以下端口:
* 80: web端口.
* 3306: Mysql 数据库端口
* 9000: FPM运行时端口
* 6379: Redis端口


## 目录

1. [运行](#运行)
   * [环境建立](#环境建立)
   * [拉取分支](#拉取分支)
2. [环境配置](#环境配置)
   * [Web目录配置](#Web目录配置)
   * [Nginx配置](#Nginx配置)
   * [其他配置](#其他配置)
3. [执行](#执行)
   * [up命令](#up命令)
   * [后台运行](#后台运行)
   * [销毁](#销毁)
4. [深入一点](#深入一点)
   * [容器互联](容器互联)
5. [后续](后续)


## 运行

    
    

### 环境建立

为了能够正常地使用本环境，我假设你具备以下条件

1. 安装最新的 [Docker](https://www.docker.com/community-edition#/download)  
2. 安装最新的 [Docker Compose](https://docs.docker.com/compose/install/)  **(Docker for mac已内置)**

### 拉取分支

在任意目录拉取最新分支

```console
$ git clone xxx
```



## 环境配置

### Web目录配置

**Note**: 这里仅仅以laravel为例，你可以根据自己的需求，随意地创建项目或将web目录复制至web目录下。

切到 web 目录，并创建web项目

```console
$ cd www
$ composer create-project laravel/laravel larawork
```

OK.通过composer，我们创建了一个空的laravel项目。下一步要做的就是将laravel目录中的public目录设置为ngixn的root目录。

### Nginx配置

nginx/conf.d/xxx

### 其他配置
xxx


## 执行

### up命令
所有环境建立好之后，只需要在根目录执行一条指令，docker就会自动跑起来

```console
$ docker-compose up
```

### 后台运行
```console
$ docker-compose -d
```

观察日志
```console
$ docker logs nginx
$ docker logs phpfpm
```

### 销毁
```console
docker-compose down
```

由于创建了映射，实例销毁后，数据仍然存在，在任何需要重新建立实例的时候，再次建立实例即可。

## 深入一点

### 容器互联

为了让不同的容器能够彼此通信，我们使用了 --link 参数进行容器互联。随着 Docker网络的完善，强烈建议使用 network 进行多容器连接。


创建网络

```console
$ docker network create -d bridge my-net
```

接入网络
```console
$ docker run -it -rm --name app1 --network my-net alpine /bin/sh
```

再次接入
```console
$ docker run -it -rm --name app2 --network my-net alpine /bin/sh
```

至次，`app1`与`app2`都连接至`my-net`网络，且实现了互联。

**提示**: 如果想了解更多的 Network 技术细节，请移步至官网 [Network Overview](https://docs.docker.com/network/) 章节.

## 后续

如果本文对你的学习或工作有一定的帮助，请记得star一下，略表支持。

后续不定期更新，如有疑问，可mail至 tiredoy@gmail.com.
