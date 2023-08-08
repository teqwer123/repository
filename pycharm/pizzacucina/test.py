import sqlite3

print(sqlite3.version)
print(sqlite3.sqlite_version)

conn = sqlite3.connect('C:/sqlite/cucina.db')
print(type(conn))
conn.text_factory = str
cursor = conn.cursor()

# cursor.execute('insert into pizza_tbl values(1,\'대표메뉴\',\'[주문율 1등]쿠치나스파게티세트R\',21800,null)')
# cursor.execute('insert into pizza_tbl values(2,\'대표메뉴\',\'[BEST]비프&쉬림프 피자\',21800,25800)')
# cursor.execute('insert into pizza_tbl values(3,\'대표메뉴\',\'갈릭버터포테이토\',18800,21800)')
# cursor.execute('insert into pizza_tbl values(4,\'대표메뉴\',\'더고구마\',16800,19800)')
#
# cursor.execute('insert into pizza_tbl values(5,\'세트메뉴\',\'[가성비최고]레귤러R 피자+라이스\',20800,null)')
# cursor.execute('insert into pizza_tbl values(6,\'세트메뉴\',\'라지L피자+라이스\',null,23800)')
#
# cursor.execute('insert into pizza_tbl values(7,\'쿠치나스파게티세트\',\'[주문율 1등]쿠치나스파게티세트R\',21800,null)')
# cursor.execute('insert into pizza_tbl values(8,\'쿠치나스파게티세트\',\'쿠치나스파게티세트L\',null,24800)')
#
# cursor.execute('insert into pizza_tbl values(9,\'하프&하프피자 피자\',\'하프&하프 피자 L사이즈\',null,20800)')
#
# cursor.execute('insert into pizza_tbl values(10,\'피자&치킨강정 콤보\',\'오리지널콤보L\',null,31800)')
# cursor.execute('insert into pizza_tbl values(11,\'피자&치킨강정 콤보\',\'클래식콤보L\',null,33800)')
# cursor.execute('insert into pizza_tbl values(12,\'피자&치킨강정 콤보\',\'프리미엄콤보L\',null,37800)')
# cursor.execute('insert into pizza_tbl values(13,\'피자&치킨강정 콤보\',\'오리지널콤보R\',28800,null)')
# cursor.execute('insert into pizza_tbl values(14,\'피자&치킨강정 콤보\',\'클래식콤보R\',30800,null)')
# cursor.execute('insert into pizza_tbl values(15,\'피자&치킨강정 콤보\',\'프리미엄콤보R\',33800,null)')
#
# cursor.execute('insert into pizza_tbl values(16,\'시그니처 프리미엄 피자\',\'[신메뉴]불타오르네\',21800,25800)')
# cursor.execute('insert into pizza_tbl values(17,\'시그니처 프리미엄 피자\',\'콘치즈핫도그\',21800,25800)')
# cursor.execute('insert into pizza_tbl values(18,\'시그니처 프리미엄 피자\',\'[BEST]비프&쉬림프 피자\',21800,25800)')
# cursor.execute('insert into pizza_tbl values(19,\'시그니처 프리미엄 피자\',\'핵토핑\',21800,25800)')
# cursor.execute('insert into pizza_tbl values(20,\'시그니처 프리미엄 피자\',\'트리플매니아\',21800,26800)')
# cursor.execute('insert into pizza_tbl values(21,\'시그니처 프리미엄 피자\',\'올뉴쉬림프\',21800,26800)')
# cursor.execute('insert into pizza_tbl values(22,\'시그니처 프리미엄 피자\',\'비프스테이션\',21800,25800)')
# cursor.execute('insert into pizza_tbl values(23,\'시그니처 프리미엄 피자\',\'판타스틱4\',21800,25800)')
#
# cursor.execute('insert into pizza_tbl values(24,\'시그니처 클래식 피자\',\'더블치즈포테이토\',18800,21800)')
# cursor.execute('insert into pizza_tbl values(25,\'시그니처 클래식 피자\',\'[인기]수퍼 슈프림 피자\',18800,21800)')
# cursor.execute('insert into pizza_tbl values(26,\'시그니처 클래식 피자\',\'비프불고기\',18800,22300)')
# cursor.execute('insert into pizza_tbl values(27,\'시그니처 클래식 피자\',\'미트&씨푸드\',18800,22800)')
# cursor.execute('insert into pizza_tbl values(28,\'시그니처 클래식 피자\',\'프레쉬모짜렐라\',18800,22300)')
# cursor.execute('insert into pizza_tbl values(29,\'시그니처 클래식 피자\',\'에그토스트\',18800,22300)')
# cursor.execute('insert into pizza_tbl values(30,\'시그니처 클래식 피자\',\'갈릭버터포테이토\',18800,21800)')
#
# cursor.execute('insert into pizza_tbl values(31,\'시그니처 오리지널 피자\',\'더고구마\',16800,19800)')
# cursor.execute('insert into pizza_tbl values(32,\'시그니처 오리지널 피자\',\'레드페퍼로니\',16800,19800)')
# cursor.execute('insert into pizza_tbl values(33,\'시그니처 오리지널 피자\',\'그릴드핫치킨\',16800,19800)')
# cursor.execute('insert into pizza_tbl values(34,\'시그니처 오리지널 피자\',\'베이컨체다\',16800,19800)')
# cursor.execute('insert into pizza_tbl values(35,\'시그니처 오리지널 피자\',\'칠리페페로니\',16800,19800)')
#
#
# cursor.execute('insert into normal_tbl values(1,\'치킨강정\',\'허니갈릭치킨강정\',15500)')
# cursor.execute('insert into normal_tbl values(2,\'치킨강정\',\'고추간장치킨강정\',15500)')
# cursor.execute('insert into normal_tbl values(3,\'치킨강정\',\'오리지널치킨강정\',15500)')
#
# cursor.execute('insert into normal_tbl values(4,\'사이드\',\'로제불닭라이스\',6900)')
# cursor.execute('insert into normal_tbl values(5,\'사이드\',\'소세지마요라이스\',6900)')
# cursor.execute('insert into normal_tbl values(6,\'사이드\',\'미트스파게티\',7900)')
# cursor.execute('insert into normal_tbl values(7,\'사이드\',\'베이컨크림스파게티\',7900)')
# cursor.execute('insert into normal_tbl values(8,\'사이드\',\'치즈볼\',3900)')
# cursor.execute('insert into normal_tbl values(9,\'사이드\',\'오징어링\',2900)')
# cursor.execute('insert into normal_tbl values(10,\'사이드\',\'버팔로윙\',5900)')
# cursor.execute('insert into normal_tbl values(11,\'사이드\',\'쿠치나떡볶이\',7900)')
# cursor.execute('insert into normal_tbl values(12,\'사이드\',\'로제투움바떡볶이\',8900)')
# cursor.execute('insert into normal_tbl values(13,\'사이드\',\'고구마튀김\',2000)')
# cursor.execute('insert into normal_tbl values(14,\'사이드\',\'고추튀김\',2000)')
# cursor.execute('insert into normal_tbl values(15,\'사이드\',\'김말이튀김\',2000)')
# cursor.execute('insert into normal_tbl values(16,\'사이드\',\'야채튀김\',2900)')
# cursor.execute('insert into normal_tbl values(17,\'기타\',\'피클\',500)')
# cursor.execute('insert into normal_tbl values(18,\'기타\',\'갈릭디핑소스\',400)')
# cursor.execute('insert into normal_tbl values(19,\'기타\',\'핫소스\',100)')
# cursor.execute('insert into normal_tbl values(20,\'기타\',\'꿀\',1000)')
#
# cursor.execute('insert into drink_tbl values(1,\'음료\',\'펩시\',2500,1500)')
# cursor.execute('insert into drink_tbl values(2,\'음료\',\'칠성사이다\',2500,1500)')
# conn.commit()
cursor.execute('select * from jangbagooni')
rows = cursor.fetchall()
for row in rows:
    print(row)


conn.close()

