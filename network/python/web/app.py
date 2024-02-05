#-*- encoding:utf-8 -*-#
import web
import User_interface
from datetime import datetime
import logging
import logging.config
import Config
import Error


url=(
    '/register','register',
    '/login','login',
)

logging.config.fileConfig("o.conf")
logger=logging.getLogger("webpy")

def CatchError(func):
    def wrapper(*args,**kw):
        try:
            return func(*args,**kw)
        except Exception as e:
            logger.exception(e)
        return wrapper

app=web.application(url,globals())
application=app.wsgifunc()


class register:
    @CatchError
    def POST(self):
        req=web.input(phonenum='',password='',nike='',sex='1',idcard='')
        phonenum=req.phonenum
        password=req.password
        nike=req.nike
        sex=req.sex
        idcard=req.idcard
        if not User_interface.IS_Phone_Number(phonenum):
            return 


class login:
    @CatchError
    def POST(self):
        req=web.input(userid='',password='')
        userid=req.userid
        password=req.password
        
class hello:
    def GET(self,name):
        if not name:
            name='world'
        return 'hh '+name

