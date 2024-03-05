#-*- encoding:utf-8 -*-#
import web
import redis
IP='192.168.1.7'
REDIS_PORT='6379'


connect=redis.Redis(
    host=IP,port=REDIS_PORT,password='123456',encoding='utf-8'
    )


