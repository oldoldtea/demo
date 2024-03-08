#-*- encoding:utf-8 -*-#
import web
import redis
IP='192.168.0.145'
REDIS_PORT=6379
MYSQL_PORT=3306

gdb=web.database(
    dbn='mysql',
    host=IP,
    port=MYSQL_PORT,
    user='root',
    pw='123456',
    db='web'
)


connect=redis.Redis(
    host=IP,port=REDIS_PORT,password='123456',encoding='utf-8'
    )


