#!/bin/env python
import psycopg2
USER='money'
DB='mani'
PASSWD='billion'
PORT='5432'
with open("/home/mint/DAILY_CHECK/rakesh_script/checkall/test/hostfile","r") as f: hosts=f.readlines()

for HOST in hosts:
	try:
		conn=psycopg2.connect(database=DB,user=USER,password=PASSWD,host=HOST.strip(),port=PORT,connect_timeout=2)
	except:
		print "\n",HOST.strip()
		continue
	cur=conn.cursor()
	query="select (select count(distinct order_number ) from ms_oe_request_fo)  , (select count(distinct response_order_number) from ms_trade_confirm_fo) ;"
	cur.execute(query)
	data=cur.fetchmany()
	print "\n",HOST.strip()
	print "Orders: ", int(data[0][0])
	print "Trades: ", int(data[0][1])
	conn.close()

