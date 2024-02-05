#-*- coding:utf-8 -*-

#商城版本 1.0.1
SHOP_VERSION = 10001

#客户端版本version 1.0.0 10000  5.2.1 50201

#双倍经验卡 1001
#改名卡 ID_RENAMECARD
#战机清零卡 ID_GAMECLEARCARD
#年会员 ID_YEARVIP
#月会员 ID_MONTHVIP
ID_EXPCARD = 1001
ID_RENAMECARD = 1002
ID_GAMECLEARCARD = 1003
ID_YEARVIP = 1004
ID_MONTHVIP = 1005

SHOP_LIST = [
    ID_EXPCARD,
    ID_RENAMECARD,
    ID_GAMECLEARCARD,
    ID_YEARVIP,
    ID_MONTHVIP,
]

#1 消耗型
#2 时间型
TYPE_USE = 1
TYPE_TIME = 2

#1 money
#2 coin
TYPE_PAY_MONEY = 1
TYPE_PAY_COIN = 2

#0 没有限购
#1 每日限购
#2 每月限购
#3 每年限购

SHOP_CFG = {
    ID_EXPCARD:{"pid":ID_EXPCARD, "ename":"expcard", "name":"双倍经验卡", "type": TYPE_TIME, "money": 200, "coin": -1, "paytype":TYPE_PAY_MONEY, "iconid":1001, "version":10000, "discount":1, "inventory":-1, "buylimittype":0, "buylimitnum": -1, "proplist":[{"id":ID_EXPCARD, "num":1}]},
    ID_RENAMECARD:{"pid":ID_RENAMECARD, "ename":"renamecard", "name":"改名卡", "type": TYPE_USE, "money": 100, "coin": -1, "paytype":TYPE_PAY_MONEY, "iconid":1002, "version":10000, "discount":1, "inventory":-1, "buylimittype":0, "buylimitnum": -1, "proplist":[{"id":ID_RENAMECARD, "num":1}]},
    ID_GAMECLEARCARD:{"pid":ID_GAMECLEARCARD, "ename":"gameclearcard", "name":"战机清零卡", "type": TYPE_USE, "money": 100, "coin": -1, "paytype":TYPE_PAY_MONEY, "iconid":1003, "version":10000, "discount":1, "inventory":-1, "buylimittype":0, "buylimitnum": -1, "proplist":[{"id":ID_GAMECLEARCARD, "num":1}]},
    ID_YEARVIP:{"pid":ID_YEARVIP, "ename":"yearvip", "name":"年会员", "type": TYPE_TIME, "money": 100, "coin": -1, "paytype":TYPE_PAY_MONEY, "iconid":1004, "version":10000, "discount":1, "inventory":-1, "buylimittype":0, "buylimitnum": -1, "proplist":[{"id":ID_YEARVIP, "num":1}]},
    ID_MONTHVIP:{"pid":ID_MONTHVIP, "ename":"monthvip", "name":"月会员", "type": TYPE_TIME, "money": 100, "coin": -1, "paytype":TYPE_PAY_MONEY, "iconid":1005, "version":10000, "discount":1, "inventory":-1, "buylimittype":0, "buylimitnum": -1, "proplist":[{"id":ID_MONTHVIP, "num":1}]},
}
