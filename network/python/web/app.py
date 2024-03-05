#-*- encoding:utf-8 -*-#
import pwd
import web
import User_interface
from datetime import datetime
import logging
import logging.config
import Config
import Error
import ErrorConfig
import json


url=(
    '/register','register',
    '/login','login',
    '/','hello'
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
            return Error.ErrResult(ErrorConfig.EC_REGISTER_PHONE_TYPE_ERROR,ErrorConfig.ER_REGISTER_PHONE_TYPE_ERROR)
        if not User_interface.IS_available_pwd(password):
            return Error.ErrResult(ErrorConfig.EC_LOGIN_PASSWORD_ERROR,ErrorConfig.ER_REGISTER_PASSWORD_TYPE_ERROR)
        if User_interface.regist(phonenum,password,nike,sex,idcard):
            return Error.ErrResult(200,'ok')
        return Error.ErrResult(300,"其它错误")

class login:
    # @CatchError
    def POST(self):
        req=web.input(userid='',password='')
        userid=req.userid
        password=req.password
        if User_interface.login(userid,password):
            return Error.ErrResult(200,'ok')
        return Error.ErrResult(300,"其它错误")
class hello:
    def POST(self):
        return "helo"
