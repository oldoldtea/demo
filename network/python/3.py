# -*- utf-8 -*-
import logging
import logging.config
log=logging.config.fileConfig('o.conf')

logger=logging.getLogger('applog')

logger.debug("hhh")