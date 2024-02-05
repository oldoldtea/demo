# -*- encoding:utf-8 -*-
import logging

logger=logging.getLogger("d.q.1")
logger.setLevel(logging.WARNING)

ch1=logging.StreamHandler()
ch2=logging.FileHandler(filename='1.log')


formatter=logging.Formatter("%(asctime)s|%(filename)s:%(lineno)s|%(message)s")

ch1.setFormatter(formatter)
ch1.setLevel(logging.DEBUG)

ch2.setFormatter(formatter)

logger.addHandler(ch1)
logger.addHandler(ch2)

flt=logging.Filter('d.q')
logger.addFilter(flt)

flt1=logging.Filter('d')
logger.addFilter(flt1)

logger.debug("666")
logger.warning("7777")
