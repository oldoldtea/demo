# -*- encoding:utf-8 -*-
import logging

logging.basicConfig(level=logging.DEBUG,filename='demo.log',
                    filemode='w',
                    format="%(asctime)s|%(filename)s:%(lineno)s|%(message)s",datefmt="%Y-%m-%d %H-%M-%S")

logging.debug("hhh")
logging.error("err")
logging.info("66")
logging.warning("wa")
logging.critical("cr")

name = "6"
id=6
logging.debug("77={}".format(name))
logging.debug("%s",id*name)



