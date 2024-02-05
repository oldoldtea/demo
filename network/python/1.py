#-*- encoding:utf-8 -*-#

import sys
reload(sys)
sys.setdefaultencoding('utf-8')
import time
from wsgiref.simple_server import make_server
class ResponseTimingMiddleware(object):
    def __init__(self,app):
        self.app=app
    def __call__(self, environ, start_response) :
        start_time=time.time()
        response=self.app(environ,start_response)
        response_time=(time.time()-start_time)*1000
        timing_text="本次耗时:{:.10f}\n\n\n".format(response_time)
        response.append(timing_text.encode('utf-8'))
        return response
def simple_app(environ, start_response):
    status="200 ok"
    response_header=[('content-type','text/plain;charset=utf-8')]
    start_response(status,response_header)
    return_body=[]
    for key,value in environ.items():
        return_body.append("{}:{}".format(key,value))
    return_body.append("\nhello wsgi")
    return ["\n".join(return_body).encode('utf-8')]
app=ResponseTimingMiddleware(simple_app)
httpd=make_server('192.168.0.140',8080,app)
httpd.serve_forever()