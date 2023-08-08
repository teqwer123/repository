import sqlite3

conn = sqlite3.connect('C:/sqlite/test.db')
conn.text_factory = str
cur = conn.cursor()

cur.execute('create table test_tbl(name varchar(20),age int)')
cur.execute('insert into test_tbl values(\'박\',21)')

conn.commit()
cur.execute('select * from test_tbl')
row = cur.fetchall()
print(row)
conn.close()