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
$ git clone git@github.com:tiredoy/docker_lnmp.git
```



**note:**建议在Home目录拉取目录，这样可以确保当前用户对目录具有所有权限。如果你对文件权限比较熟悉，请忽略此条建议。

## 环境配置

### Web目录配置

**Note**: 这里仅仅以laravel为例，你可以根据自己的需求，随意地创建项目或将web目录复制至web目录下。

切到 web 目录，并创建web项目

```console
$ cd www
$ composer create-project laravel/laravel larawork -vvv
```

OK.通过composer，我们创建了一个空的laravel项目，这是一个很常规的做法。你完全可以把你自己的PHP项目放置到`www`目录，这没有任何问题，也比较推荐你这样去做。

由于拉取了PHP的镜像，我们无须过多地关注其他的配置。我们可以假设我们已经处理好了`PHP-FPM`的环境，以及其他的端口等配置。那么下一步要做的就是，将laravel目录中的public目录设置为ngixn的root目录，让Nginx的80端口可以访问得到www目录的静态资源，以及转发任何的PHP文件至9000端口，如果你以前稍微有一点点的配置环境的常识，那么这绝对不是一件难事。

### Nginx配置

上一步，我们初始化了`www`目录，并通过`compose`创建了一个空的`laravel`项目。这一步，我们要做两件事：

- 指定`root`目录
- 配置`fastcgi_pass`等参数

我们切换到nginx的配置目录

```console
$ cd nginx/conf.d
```

为了方便，我已经内置了一个简单的配置文件`larawork.conf`

```console
$ cat larawork.conf
```

这个文件很常规，需要注意一点的是，larawork中配置的目录，是指docker实例中的目录，也就是nginx实例的目录，通过docker-compose.yml，我们把宿主机器当前目录下的www目录，分别映射给了PHPFPM容器中的/www,以及nginx容器中的/www.

他们之间的映射关系如下：

```
{your-path}/docker_lnmp/www => /www (phpfpm)
{your-path}/docker_lnmp/www => /www (nginx)
```

通过这种配置，你可以大胆地把你的`{your-path}/docker_lnmp/www` 拖动到编辑器或IDE，进行开发。当文件发生变动时，`phpfpm`和`nginx`容器会同时追踪到文件的变化。

所以，当你想进行其他项目的配置，一定要注意，你填写的对应的容器中所需要的目录，而不是本地宿主的目录。

事实上，这种做法存在一定的文件冗余。具体来讲，访问静态资源时，我们只需要将静态资源放置在`nginx`容器中，`phpfpm`容器是不需要静态资源的，因为这部分工作，仅仅由`nginx`处理；同时，php文件，只用放置在phpfpm容器中，nginx只是将php文件的解析通过9000端口传递给phpfpm容器解析，而nginx本身是无法解析的，这部分文件同样存在冗余。之所这样做，是因为让phpfpm和nginx保持文件一致的好处颇多，我们不用去思考文件放在哪里。

### 其他配置

当你看到这里时，一个具备基本功能的lnmp环境栈已经ok了，你完全可以忽略这一步。去执行吧！




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
