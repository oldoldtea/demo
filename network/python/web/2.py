def application(env,fun):
    fun("200 ok",[('content-Type','text/html')])
    return [b'hahahah']