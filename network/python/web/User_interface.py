#-*- encoding:utf-8 -*-#

from asyncio.windows_events import NULL
import datetime
from imghdr import what
from unittest import result
import web
import re
import Config

gdb=Config.gdb

def IS_exist(userid):
    return gdb.select('user',where='userid=$userid',vars=dict(userid=userid),what='count(*) as num')[0].num>0

def regist(phonenum,password,nike,sex,idcard):
    now=datetime.datetime.now()
    result=gdb.insert(
        'user',
        userid=int(phonenum),
        password=password,
        secpassword='123456',
        nike=nike,
        phonenum=phonenum,
        sex=sex,
        idcard=idcard,
        status=0,
        createtime=now,
        lastlogintime=now
    )
    return result


def GetPwd(userid):
    return gdb.select('user',where='userid=$userid',vars=dict(userid=userid),what='password as pwd')[0].pwd

def login(userid,password):
    pwd=GetPwd(userid)
    if pwd is NULL or password!=pwd:
        return False
    return True

#判断手机号是否有效
def IS_Phone_Number(phone):
    PHONE_PATTERN = re.compile("^((13[0-9])|(14[5|7])|(15([0-3]|[5-9]))|(18[0,5-9]))\d{8}$")
    phone = str(phone)
    if not phone.isdigit():
        return False
    return bool(PHONE_PATTERN.match(phone))

#判断邮箱是否有效
def IS_Email(email):
    email_pattern = r"^[a-zA-Z0-9_-]+(\.[a-zA-Z0-9_-]+){0,4}@[a-zA-Z0-9_-]+(\.[a-zA-Z0-9_-]+){0,4}$"
    return re.match(email_pattern, email)

#判断密码是否符合规范
def IS_available_pwd(pwd):
    PASSWORD_PATTERN = re.compile(r"^[a-zA-Z_]\w{5,}$")
    if not re.match(PASSWORD_PATTERN,pwd):return False
    PASSWORD_LEVEL = re.compile(r"^(?![0-9]+$)[0-9a-zA-Z\\\,\`\!\@\#\$\%\^\&\*\[\]\{\}\?\<\>\.\/\-\+\=\_]{8,20}$")
    if re.match(PASSWORD_LEVEL,pwd): return False
    PASSWORD_REX = r"^(?=.*[A-Za-z])(?=.*\d)(?=.*[@$!%*?&\.~\\#\^\(\)\-\_/]).{6,20}$"
    return re.match(PASSWORD_REX,pwd)


