#-*- encoding:utf-8 -*-#
import time
from wsgiref.simple_server import make_server
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

def home(items):
    return items

def login(items):
    return items

def index(items):
    return items

url={
    '/':home,
    '/login':login,
    '/index':index
}

def app(env, start_response):
    print(env.get('PATH_INFO'))
    path_info=env.get('PATH_INFO')
    items=env.get('QUERY_STRING')
    print(items)
    if path_info is None or path_info not in url:
        start_response('404 e',[('content-type','text/plain;charset=utf-8')])
        return [b'error']
    result=url.get(path_info)
    start_response('200 ok',[('content-type','text/plain')])
    return [result(items).encode('utf-8')]

server=make_server('192.168.0.140',8080,app)
server.serve_forever()