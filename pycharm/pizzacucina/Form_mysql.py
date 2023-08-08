import sys
import sqlite3
import pymysql
from PyQt5 import QtWidgets
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import QDialog, QWidget, QApplication

from pizzacucina.conveted_ui.allSize_pizza_menu_converted import allSize_pizza_Ui_Form
from pizzacucina.conveted_ui.choice_menu_converted import choice_Ui_Form
from pizzacucina.conveted_ui.classicComboL_menu_converted import classicComboL_menu_Form
from pizzacucina.conveted_ui.classicComboR_menu_converted import classicComboR_menu_Form
from pizzacucina.conveted_ui.cucina_spaghettiSetL_menu_converted import cucina_spaghettiSetL_menu_Form
from pizzacucina.conveted_ui.halfAndHalf_pizzaL_menu_converted import halfAndHalf_menu_Form
from pizzacucina.conveted_ui.largeL_pizza_rice_menu_converted import largeL_pizza_rice_menu_Form
from pizzacucina.conveted_ui.main_converted import Ui_Form
from pizzacucina.conveted_ui.originalComboL_menu_converted import originalComboL_menu_Form
from pizzacucina.conveted_ui.originalComboR_menu_converted import originalComboR_menu_Form
from pizzacucina.conveted_ui.premiumComboL_menu_converted import premiumComboL_menu_Form
from pizzacucina.conveted_ui.premiumComboR_menu_converted import premiumComboR_menu_Form
from pizzacucina.conveted_ui.regularR_pizza_rice_menu_converted import regularR_pizza_rice_menu_Form
from pizzacucina.conveted_ui.shinMenu_Fire_converted import shinMenu_Fire_menu_Form
from pizzacucina.conveted_ui.simple_menu_converted import simple_menu_Ui_Form


class main_Form(QtWidgets.QWidget, Ui_Form):

    def __init__(self):
        super().__init__()
        self.setupUi(self)

        label_img_arr = [self.img, self.img_2, self.img_3, self.img_4, self.img_5, self.img_6, self.img_7, self.img_8,
                         self.img_9, self.img_10, self.img_11, self.img_12, self.img_13, self.img_14, self.img_15,
                         self.img_16, self.img_17, self.img_18, self.img_19, self.img_20, self.img_21, self.img_22,
                         self.img_23, self.img_24, self.img_25, self.img_26, self.img_27, self.img_28, self.img_29,
                         self.img_30, self.img_31, self.img_32, self.img_33, self.img_34, self.img_35, self.img_36,
                         self.img_37, self.img_38, self.img_39, self.img_40, self.img_41, self.img_42, self.img_43,
                         self.img_44, self.img_45]
        label_name_arr = [self.label_name, self.label_name_2, self.label_name_3, self.label_name_4, self.label_name_5,
                          self.label_name_6, self.label_name_7, self.label_name_8, self.label_name_9,
                          self.label_name_10, self.label_name_11, self.label_name_12, self.label_name_13,
                          self.label_name_14, self.label_name_15, self.label_name_16, self.label_name_17,
                          self.label_name_18, self.label_name_19, self.label_name_20, self.label_name_21,
                          self.label_name_22, self.label_name_23, self.label_name_24, self.label_name_25,
                          self.label_name_26, self.label_name_27, self.label_name_28, self.label_name_29,
                          self.label_name_30, self.label_name_31, self.label_name_32, self.label_name_33,
                          self.label_name_34, self.label_name_35, self.label_name_36, self.label_name_37,
                          self.label_name_38, self.label_name_39, self.label_name_40, self.label_name_41,
                          self.label_name_42, self.label_name_43, self.label_name_44, self.label_name_45,
                          self.label_name_46, self.label_name_47, self.label_name_48, self.label_name_49,
                          self.label_name_50, self.label_name_51, self.label_name_52, self.label_name_53,
                          self.label_name_54, self.label_name_55, self.label_name_56, self.label_name_57]
        label_price_R_arr = [self.price_R, self.price_R_2, self.price_R_3, self.price_R_4, self.price_R_5,
                             self.price_R_6, self.price_R_7, self.price_R_8, self.price_R_9, self.price_R_10,
                             self.price_R_11, self.price_R_12, self.price_R_13, self.price_R_14, self.price_R_15,
                             self.price_R_16, self.price_R_17, self.price_R_18, self.price_R_19, self.price_R_20,
                             self.price_R_21, self.price_R_22, self.price_R_23, self.price_R_24, self.price_R_25,
                             self.price_R_26, self.price_R_27, self.price_R_28, self.price_R_29, self.price_R_30,
                             self.price_R_31, self.price_R_32, self.price_R_33, self.price_R_34, self.price_R_35,
                             self.price_R_36, self.price_R_37, self.price_R_38, self.price_R_39, self.price_R_40,
                             self.price_R_41, self.price_R_42, self.price_R_43, self.price_R_44, self.price_R_45,
                             self.price_R_46, self.price_R_47, self.price_R_48, self.price_R_49, self.price_R_50,
                             self.price_R_51, self.price_R_52, self.price_R_53, self.price_R_54, self.price_R_55,
                             self.price_R_56, self.price_R_57]
        widget_menu_arr = [self.widget_menu, self.widget_menu_2, self.widget_menu_3, self.widget_menu_4,
                           self.widget_menu_5, self.widget_menu_6, self.widget_menu_7, self.widget_menu_8,
                           self.widget_menu_9, self.widget_menu_10, self.widget_menu_11, self.widget_menu_12,
                           self.widget_menu_13, self.widget_menu_14, self.widget_menu_15, self.widget_menu_16,
                           self.widget_menu_17, self.widget_menu_18, self.widget_menu_19, self.widget_menu_20,
                           self.widget_menu_21, self.widget_menu_22, self.widget_menu_23, self.widget_menu_24,
                           self.widget_menu_25, self.widget_menu_26, self.widget_menu_27, self.widget_menu_28,
                           self.widget_menu_29, self.widget_menu_30, self.widget_menu_31, self.widget_menu_32,
                           self.widget_menu_33, self.widget_menu_34, self.widget_menu_35, self.widget_menu_36,
                           self.widget_menu_37, self.widget_menu_38, self.widget_menu_39, self.widget_menu_40,
                           self.widget_menu_41, self.widget_menu_42, self.widget_menu_43, self.widget_menu_44,
                           self.widget_menu_45, self.widget_menu_46, self.widget_menu_47, self.widget_menu_48,
                           self.widget_menu_49, self.widget_menu_50, self.widget_menu_51, self.widget_menu_52,
                           self.widget_menu_53, self.widget_menu_54, self.widget_menu_55, self.widget_menu_56,
                           self.widget_menu_57]

        for i in range(0,57):
            widget_menu_arr[i].mousePressEvent=lambda event, i=i+1: self.onClicked(event,i)

        for i in range(1,46):
            pixmap = QPixmap(f'C:/Users/aiot06/Desktop/쿠치나/{i}.png')
            label_img_arr[i-1].setPixmap(pixmap)

        conn = pymysql.connect(host='127.0.0.1', port=3306, user='root', password='1234', db='cucina', charset='utf8')
        cur = conn.cursor()

        sql = f'SELECT product_name FROM pizza_tbl where product_id =1'
        cur.execute(sql)
        result = cur.fetchall()
        self.label_name.setText(str(result[0][0]))
        sql = f'SELECT price_R FROM pizza_tbl where product_id =1'
        cur.execute(sql)
        result = cur.fetchall()
        self.price_R.setText("R:" + str(result[0][0]))

        for i in range(2,31):
            sql = f'SELECT product_name FROM pizza_tbl where product_id ={i}'
            cur.execute(sql)
            result = cur.fetchall()
            label_name_arr[i-1].setText(str(result[0][0]))
            sql = f'SELECT price_R,price_L FROM pizza_tbl where product_id ={i}'
            cur.execute(sql)
            result = cur.fetchall()
            print(result)

            if result[0][0] is not None:
                label_price_R_arr[i-1].setText("R:"+str(result[0][0]) )
                priceR=label_price_R_arr[i-1].text()+"\t"
            if result[0][1] is not None:
                label_price_R_arr[i - 1].setText(priceR+"L:" + str(result[0][1]))
            priceR=""

        # 시그니처 오리지널 피자
        sql = 'SELECT product_name,price_R,price_L FROM pizza_tbl where categori=\'시그니처 오리지널 피자\''
        cur.execute(sql)
        result= cur.fetchall()
        print('시그니처 오리지널 피자')
        print(result)
        for i in range(31,36):
            label_name_arr[i-1].setText(result[i-31][0])
            label_price_R_arr[i-1].setText("R: "+str(result[i-31][1])+"\tL: "+str(result[i-31][2]))

        # 일반 테이블(16 야채 튀김 까지)
        # 치킨 강정
        sql = 'SELECT product_name,price FROM normal_tbl where product_id>=1 and product_id <=16'
        cur.execute(sql)
        result = cur.fetchall()
        print('일반테이블 16번까지')
        print(result)
        for i in range(36,52):
            label_name_arr[i-1].setText(result[i-36][0])
            label_price_R_arr[i-1].setText(str(result[i-36][1]))

        # 음료
        sql = 'SELECT product_name,price_L,price_ml FROM drink_tbl'
        cur.execute(sql)
        result = cur.fetchall()
        print(result)
        for i in range(52,54):
            label_name_arr[i-1].setText(result[i-52][0])
            label_price_R_arr[i-1].setText("1.25L: "+str(result[i-52][1])+"\t500ml: "+str(result[i-52][2]))

        # 기타
        sql = 'SELECT product_name,price FROM normal_tbl where product_id>=17 and product_id <=20'
        cur.execute(sql)
        result = cur.fetchall()
        for i in range(54,58):
            label_name_arr[i-1].setText(result[i-54][0])
            label_price_R_arr[i-1].setText(str(result[i-54][1]))

        conn.close()

    def onClicked(self,ev,i):
        self.hide()
        if i==1 or i == 7:
            second = choice_menu_Form(i)
            second.exec()
        elif i ==5:
            second = regularR_pizza_rice_menu_Form(i)
            second.exec()
        elif i == 6:
            second = largeL_pizza_rice_menu_Form(i)
            second.exec()
        elif i == 8:
            second = cucina_spaghettiSetL_menu_Form(i)
            second.exec()
        elif i == 9:
            second = halfAndHalf_menu_Form(i)
            second.exec()
        elif i == 10:
            second = originalComboL_menu_Form(i)
            second.exec()
        elif i == 11:
            second = classicComboL_menu_Form(i)
            second.exec()
        elif i == 12:
            second = premiumComboL_menu_Form(i)
            second.exec()
        elif i == 13:
            second = originalComboR_menu_Form(i)
            second.exec()
        elif i == 14:
            second = classicComboR_menu_Form(i)
            second.exec()
        elif i == 15:
            second = premiumComboR_menu_Form(i)
            second.exec()
        elif i == 16:
            second = shinMenu_Fire_menu_Form(i)
            second.exec()
        elif i >= 2 and i <= 4 or i>=17 and i <=35:
            second = allSize_pizza_menu_Form(i)
            second.exec()
        elif i >= 36 and i <= 57:
            second = simple_menu_Form(i)
            second.exec()

        self.show()


class choice_menu_Form(QDialog, QWidget, choice_Ui_Form):
    def __init__(self, i):
        global result
        super(choice_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        conn = pymysql.connect(host='127.0.0.1', port=3306, user='root', password='1234', db='cucina', charset='utf8')
        cur = conn.cursor()
        print('Clicked' + f'{i}')
        sql = f'SELECT product_name,price_R,price_L FROM pizza_tbl where product_id = {i}'
        print('1-35')

        cur.execute(sql)
        result = cur.fetchall()
        print(result)

        pixmap = QPixmap(f'C:/Users/aiot06/Desktop/쿠치나/{i}.png')
        self.label_img.setPixmap(pixmap)

        print('여기까지')

        self.label_product_name.setText(result[0][0])

        self.label_price.setText("R : "+str(result[0][1])+"원")

        conn.close()
        # 아직 덜 끝남요!!!!!11111111111 여기서부터
        #1~19
        # widget_serveMenu_arr = [self.widget_1, self.widget_3, self.widget_4, self.widget_5, self.widget_6,
        #                         self.widget_7, self.widget_8, self.widget_9, self.widget_10, self.widget_11,
        #                         self.widget_12, self.widget_13, self.widget_14, self.widget_15, self.widget_16,
        #                         self.widget_17, self.widget_18, self.widget_19, self.widget_20]
        # self.widget_1.mousePressEvent = lambda event, i=1: self.addMenu(event,i)
        # for i in range(0,20):
        #     widget_serveMenu_arr[i].mousePressEvent = lambda event, i=i+1: self.addMenu(event,i)



    def addMenu(self,ev,i):
        global temp
        # while
        if i >=1 and i <=4:
            pass
        elif i >=5 and i <=11:
            temp =int(temp)+int(self.btn.text())+2000
        elif i >= 12 and i <= 19:
            temp = int(temp) + int(self.btn.text()) + 5000

        self.btn.setText(temp)
        # 아직 덜 끝남요!!!!!11111111111 여기까지

class regularR_pizza_rice_menu_Form(QDialog, QWidget,regularR_pizza_rice_menu_Form):
    def __init__(self, i):
        global result
        super(regularR_pizza_rice_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        conn = pymysql.connect(host='127.0.0.1', port=3306, user='root', password='1234', db='cucina', charset='utf8')
        cur = conn.cursor()
        print('Clicked' + f'{i}')

        sql = f'SELECT product_name,price_R,price_L FROM pizza_tbl where product_id = {i}'
        print('1-35')
        cur.execute(sql)
        result = cur.fetchall()
        print(result)

        pixmap = QPixmap(f'C:/Users/aiot06/Desktop/쿠치나/{i}.png')

        self.label_img.setPixmap(pixmap)

        print('여기까지')
        self.label_product_name.setText(result[0][0])

        self.label_price.setText("R : "+str(result[0][1]) + "원")

        conn.close()
class largeL_pizza_rice_menu_Form(QDialog, QWidget,largeL_pizza_rice_menu_Form):
    def __init__(self, i):
        global result
        super(largeL_pizza_rice_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        conn = pymysql.connect(host='127.0.0.1', port=3306, user='root', password='1234', db='cucina', charset='utf8')
        cur = conn.cursor()
        print('Clicked' + f'{i}')

        sql = f'SELECT product_name,price_R,price_L FROM pizza_tbl where product_id = {i}'
        print('1-35')
        cur.execute(sql)
        result = cur.fetchall()
        print(result)

        pixmap = QPixmap(f'C:/Users/aiot06/Desktop/쿠치나/{i}.png')

        self.label_img.setPixmap(pixmap)

        print('여기까지')
        self.label_product_name.setText(result[0][0])

        self.label_price.setText("L : "+str(result[0][2]) + "원")

        conn.close()
class cucina_spaghettiSetL_menu_Form(QDialog, QWidget,cucina_spaghettiSetL_menu_Form):
    def __init__(self, i):
        global result
        super(cucina_spaghettiSetL_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        conn = pymysql.connect(host='127.0.0.1', port=3306, user='root', password='1234', db='cucina', charset='utf8')
        cur = conn.cursor()
        print('Clicked' + f'{i}')

        sql = f'SELECT product_name,price_R,price_L FROM pizza_tbl where product_id = {i}'
        print('1-35')
        cur.execute(sql)
        result = cur.fetchall()
        print(result)

        pixmap = QPixmap(f'C:/Users/aiot06/Desktop/쿠치나/{i}.png')

        self.label_img.setPixmap(pixmap)

        print('여기까지')
        self.label_product_name.setText(result[0][0])

        self.label_price.setText("L : "+str(result[0][2]) + "원")

        conn.close()
class halfAndHalf_menu_Form(QDialog, QWidget,halfAndHalf_menu_Form):
    def __init__(self, i):
        global result
        super(halfAndHalf_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        conn = pymysql.connect(host='127.0.0.1', port=3306, user='root', password='1234', db='cucina', charset='utf8')
        cur = conn.cursor()
        print('Clicked' + f'{i}')

        sql = f'SELECT product_name,price_R,price_L FROM pizza_tbl where product_id = {i}'
        print('1-35')
        cur.execute(sql)
        result = cur.fetchall()
        print(result)

        pixmap = QPixmap(f'C:/Users/aiot06/Desktop/쿠치나/{i}.png')

        self.label_img.setPixmap(pixmap)

        print('여기까지')
        self.label_product_name.setText(result[0][0])

        self.label_price.setText("L : "+str(result[0][2]) + "원")

        conn.close()
class originalComboL_menu_Form(QDialog, QWidget,originalComboL_menu_Form):
    def __init__(self, i):
        global result
        super(originalComboL_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        conn = pymysql.connect(host='127.0.0.1', port=3306, user='root', password='1234', db='cucina', charset='utf8')
        cur = conn.cursor()
        print('Clicked' + f'{i}')

        sql = f'SELECT product_name,price_R,price_L FROM pizza_tbl where product_id = {i}'
        print('1-35')
        cur.execute(sql)
        result = cur.fetchall()
        print(result)

        pixmap = QPixmap(f'C:/Users/aiot06/Desktop/쿠치나/{i}.png')

        self.label_img.setPixmap(pixmap)

        print('여기까지')
        self.label_product_name.setText(result[0][0])

        self.label_price.setText("L : "+str(result[0][2]) + "원")

        conn.close()
class originalComboR_menu_Form(QDialog, QWidget,originalComboR_menu_Form):
    def __init__(self, i):
        global result
        super(originalComboR_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        conn = pymysql.connect(host='127.0.0.1', port=3306, user='root', password='1234', db='cucina', charset='utf8')
        cur = conn.cursor()
        print('Clicked' + f'{i}')

        sql = f'SELECT product_name,price_R,price_L FROM pizza_tbl where product_id = {i}'
        print('1-35')
        cur.execute(sql)
        result = cur.fetchall()
        print(result)

        pixmap = QPixmap(f'C:/Users/aiot06/Desktop/쿠치나/{i}.png')

        self.label_img.setPixmap(pixmap)

        print('여기까지')
        self.label_product_name.setText(result[0][0])

        self.label_price.setText("R : "+str(result[0][1]) + "원")

        conn.close()
class classicComboL_menu_Form(QDialog, QWidget,classicComboL_menu_Form):
    def __init__(self, i):
        global result
        super(classicComboL_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        conn = pymysql.connect(host='127.0.0.1', port=3306, user='root', password='1234', db='cucina', charset='utf8')
        cur = conn.cursor()
        print('Clicked' + f'{i}')

        sql = f'SELECT product_name,price_R,price_L FROM pizza_tbl where product_id = {i}'
        print('1-35')
        cur.execute(sql)
        result = cur.fetchall()
        print(result)

        pixmap = QPixmap(f'C:/Users/aiot06/Desktop/쿠치나/{i}.png')

        self.label_img.setPixmap(pixmap)

        print('여기까지')
        self.label_product_name.setText(result[0][0])

        self.label_price.setText("L : "+str(result[0][2]) + "원")

        conn.close()
class classicComboR_menu_Form(QDialog, QWidget,classicComboR_menu_Form):
    def __init__(self, i):
        global result
        super(classicComboR_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        conn = pymysql.connect(host='127.0.0.1', port=3306, user='root', password='1234', db='cucina', charset='utf8')
        cur = conn.cursor()
        print('Clicked' + f'{i}')

        sql = f'SELECT product_name,price_R,price_L FROM pizza_tbl where product_id = {i}'
        print('1-35')
        cur.execute(sql)
        result = cur.fetchall()
        print(result)

        pixmap = QPixmap(f'C:/Users/aiot06/Desktop/쿠치나/{i}.png')

        self.label_img.setPixmap(pixmap)

        print('여기까지')
        self.label_product_name.setText(result[0][0])

        self.label_price.setText("R : "+str(result[0][1]) + "원")

        conn.close()
class premiumComboL_menu_Form(QDialog, QWidget,premiumComboL_menu_Form):
    def __init__(self, i):
        global result
        super(premiumComboL_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        conn = pymysql.connect(host='127.0.0.1', port=3306, user='root', password='1234', db='cucina', charset='utf8')
        cur = conn.cursor()
        print('Clicked' + f'{i}')

        sql = f'SELECT product_name,price_R,price_L FROM pizza_tbl where product_id = {i}'
        print('1-35')
        cur.execute(sql)
        result = cur.fetchall()
        print(result)

        pixmap = QPixmap(f'C:/Users/aiot06/Desktop/쿠치나/{i}.png')

        self.label_img.setPixmap(pixmap)

        print('여기까지')
        self.label_product_name.setText(result[0][0])

        self.label_price.setText("L : "+str(result[0][2]) + "원")

        conn.close()
class premiumComboR_menu_Form(QDialog, QWidget, premiumComboR_menu_Form):
    def __init__(self, i):
        global result
        super(premiumComboR_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        conn = pymysql.connect(host='127.0.0.1', port=3306, user='root', password='1234', db='cucina', charset='utf8')
        cur = conn.cursor()
        print('Clicked' + f'{i}')

        sql = f'SELECT product_name,price_R,price_L FROM pizza_tbl where product_id = {i}'
        print('1-35')
        cur.execute(sql)
        result = cur.fetchall()
        print(result)

        pixmap = QPixmap(f'C:/Users/aiot06/Desktop/쿠치나/{i}.png')

        self.label_img.setPixmap(pixmap)

        print('여기까지')
        self.label_product_name.setText(result[0][0])

        self.label_price.setText("R : "+str(result[0][1]) + "원")

        conn.close()
class shinMenu_Fire_menu_Form(QDialog, QWidget,shinMenu_Fire_menu_Form):
    def __init__(self, i):
        global result
        super(shinMenu_Fire_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        conn = pymysql.connect(host='127.0.0.1', port=3306, user='root', password='1234', db='cucina', charset='utf8')
        cur = conn.cursor()
        print('Clicked' + f'{i}')

        sql = f'SELECT product_name,price_R,price_L FROM pizza_tbl where product_id = {i}'
        print('1-35')
        cur.execute(sql)
        result = cur.fetchall()
        print(result)

        pixmap = QPixmap(f'C:/Users/aiot06/Desktop/쿠치나/{i}.png')

        self.label_img.setPixmap(pixmap)

        print('여기까지')
        self.label_product_name.setText(result[0][0])

        self.label_price.setText("R : "+str(result[0][1]) + "원\tR : "+str(result[0][2]) + "원")

        conn.close()
class allSize_pizza_menu_Form(QDialog, QWidget, allSize_pizza_Ui_Form):
    def __init__(self, i):
        global result
        super(allSize_pizza_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        conn = pymysql.connect(host='127.0.0.1', port=3306, user='root', password='1234', db='cucina', charset='utf8')
        cur = conn.cursor()
        print('Clicked' + f'{i}')

        sql = f'SELECT product_name,price_R,price_L FROM pizza_tbl where product_id = {i}'
        print('1-35')
        cur.execute(sql)
        result = cur.fetchall()
        print(result)

        pixmap = QPixmap(f'C:/Users/aiot06/Desktop/쿠치나/{i}.png')

        self.label_img.setPixmap(pixmap)

        print('여기까지')
        self.label_product_name.setText(result[0][0])

        self.label_price.setText(str(result[0][1]) + "원," + str(result[0][2]) + "원")

        conn.close()

class simple_menu_Form(QDialog, QWidget,simple_menu_Ui_Form):
    def __init__(self, i):
        global result
        super(simple_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        conn = pymysql.connect(host='127.0.0.1', port=3306, user='root', password='1234', db='cucina', charset='utf8')
        cur = conn.cursor()
        print('Clicked' + f'{i}')

        if i <= 51:
            sql = f'SELECT product_name,price FROM normal_tbl where product_id = {i - 35}'
            cur.execute(sql)
            result = cur.fetchall()
            print('not drink')
            print(result)
        elif i >=54:
            sql = f'SELECT product_name,price FROM normal_tbl where product_id = {i - 37}'
            cur.execute(sql)
            result = cur.fetchall()
            print('not drink')
            print(result)

        elif i == 52 or i == 53:
            sql = f'SELECT product_name,price_L,price_ml FROM drink_tbl where product_id = {i - 51}'
            cur.execute(sql)
            result = cur.fetchall()
            print('drink')
            print(result)


        print('여기까지')
        self.label_product_name.setText(result[0][0])
        if i >= 36 and i <= 51 or i >= 54:
            self.label_price.setText(str(result[0][1]) + "원")
        elif i == 52 or i == 53:
            self.label_price.setText("L : " + str(result[0][1]) + "\tml : " + str(result[0][2]))

        conn.close()



if __name__ == '__main__':
    app = QApplication(sys.argv)
    form = main_Form()
    form.show()
    sys.exit(app.exec())