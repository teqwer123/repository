import re
import sys
import sqlite3
import pymysql
from PyQt5 import QtWidgets
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import QDialog, QWidget, QApplication, QVBoxLayout, QLabel

from pizzacucina.conveted_ui.allSize_pizza_menu_converted import allSize_pizza_Ui_Form
from pizzacucina.conveted_ui.choice_menu_converted import choice_Ui_Form
from pizzacucina.conveted_ui.classicComboL_menu_converted import classicComboL_menu_Form
from pizzacucina.conveted_ui.classicComboR_menu_converted import classicComboR_menu_Form
from pizzacucina.conveted_ui.cucina_spaghettiSetL_menu_converted import cucina_spaghettiSetL_menu_Form
from pizzacucina.conveted_ui.halfAndHalf_pizzaL_menu_converted import halfAndHalf_menu_Form
from pizzacucina.conveted_ui.jangbagooni_ui_converted import Ui_jangbagooni_Form
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

        self.btn_jangbagooni.clicked.connect(self.jangbagooni)

        for i in range(1,46):
            pixmap = QPixmap(f'C:/Users/aiot06/Desktop/쿠치나/{i}.png')
            label_img_arr[i-1].setPixmap(pixmap)

        conn = sqlite3.connect('C:/sqlite/cucina.db')
        conn.text_factory = str
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
    def jangbagooni(self):
        self.hide()
        second = jangbagooni_Form()
        second.exec()
        self.show()


class jangbagooni_Form(QDialog, QWidget, Ui_jangbagooni_Form):
    def __init__(self):
        super(jangbagooni_Form, self).__init__()
        self.setupUi(self)
        self.show()

        conn = sqlite3.connect('C:/sqlite/cucina.db')
        conn.text_factory = str
        cur = conn.cursor()
        sql = f'SELECT product_name,price FROM jangbagooni'
        cur.execute(sql)
        cur.fetchall()
        vbox = QVBoxLayout(self.widget_cart)
        self.widget.setLayout(vbox)
        vbox = self.widget_cart.layout()

        vbox.addWidget()
        conn.close()

class choice_menu_Form(QDialog, QWidget, choice_Ui_Form):
    def __init__(self, i):
        super(choice_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        checkBox_arr = [self.checkBox_1, self.checkBox_2, self.checkBox_3, self.checkBox_4, self.checkBox_5,
                        self.checkBox_6, self.checkBox_7, self.checkBox_8, self.checkBox_9, self.checkBox_10,
                        self.checkBox_11, self.checkBox_12, self.checkBox_13, self.checkBox_14, self.checkBox_15,
                        self.checkBox_16, self.checkBox_17, self.checkBox_18, self.checkBox_19, self.checkBox_20,
                        self.checkBox_21, self.checkBox_22, self.checkBox_23, self.checkBox_24, self.checkBox_25,
                        self.checkBox_26, self.checkBox_27, self.checkBox_28, self.checkBox_29, self.checkBox_30,
                        self.checkBox_31, self.checkBox_32, self.checkBox_33, self.checkBox_34, self.checkBox_35,
                        self.checkBox_36, self.checkBox_37, self.checkBox_38, self.checkBox_39, self.checkBox_40,
                        self.checkBox_41, self.checkBox_42, self.checkBox_43, self.checkBox_44, self.checkBox_45,
                        self.checkBox_46, self.checkBox_47, self.checkBox_48, self.checkBox_49, self.checkBox_50,
                        self.checkBox_51, self.checkBox_52, self.checkBox_53, self.checkBox_54, self.checkBox_55,
                        self.checkBox_56, self.checkBox_57, self.checkBox_58, self.checkBox_59]

        conn = sqlite3.connect('C:/sqlite/cucina.db')
        conn.text_factory = str
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

        for i in range(0,59):
            checkBox_arr[i].stateChanged.connect(lambda state, i=i+1:self.addMenu(state,i))

        self.btn.clicked.connect(self.janbagooni)

    def addMenu(self,state,i):
        global temp
        temp=0
        print(state,i)
        if i >=1 and i<=4 or i >=20 and i <=21:
            print(0)
        elif i >=5 and i<=11 or i==41 or i==42 or i == 50:
            print(2000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))+2000

            else:
                temp = 2000
                print("once")
            print("temp:"+str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i >=12 and i <=19:
            print(5000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))+5000

            else:
                temp = 5000
                print("once")
            print("temp:"+str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==22 or i==23 or i >= 51 and i <= 59:
            print(3000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))+3000

            else:
                temp = 3000
                print("once")
            print("temp:"+str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i ==24 or i==26:
            print(2500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))+2500

            else:
                temp = 2500
                print("once")
            print("temp:"+str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==25 or i==27:
            print(1500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))+1500

            else:
                temp = 1500
                print("once")
            print("temp:"+str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==28:
            print(500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))+500

            else:
                temp = 500
                print("once")
            print("temp:"+str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==29:
            print(400)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))+400

            else:
                temp = 400
                print("once")
            print("temp:"+str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==30:
            print(100)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))+100

            else:
                temp = 100
                print("once")
            print("temp:"+str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==31 or i>=43 and i<=49:
            print(1000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))+1000

            else:
                temp = 1000
                print("once")
            print("temp:"+str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==32 or i==33 or i==37:
            print(7900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 7900

            else:
                temp = 7900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==34:
            print(3900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3900

            else:
                temp = 3900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==35:
            print(2900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2900

            else:
                temp = 2900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==36:
            print(8900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 8900

            else:
                temp = 8900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==38:
            print(5900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 5900

            else:
                temp = 5900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==39:
            print(6900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 6900

            else:
                temp = 6900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
    def janbagooni(self):
        price = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))
        conn = sqlite3.connect('C:/sqlite/cucina.db')
        print('sql connected')
        conn.text_factory = str
        cur = conn.cursor()
        temp = re.sub(r'[^0-9]', '', self.label_sumPrice.text())
        sql = f'insert into jangbagooni values(\'{self.label_product_name.text()}\',{temp})'
        cur.execute(sql)
        conn.commit()
        conn.close()
class regularR_pizza_rice_menu_Form(QDialog, QWidget,regularR_pizza_rice_menu_Form):
    def __init__(self, i):
        global result
        super(regularR_pizza_rice_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()
        checkBox_arr = [self.checkBox_1, self.checkBox_2, self.checkBox_3, self.checkBox_4, self.checkBox_5,
                        self.checkBox_6, self.checkBox_7, self.checkBox_8, self.checkBox_9, self.checkBox_10,
                        self.checkBox_11, self.checkBox_12, self.checkBox_13, self.checkBox_14, self.checkBox_15,
                        self.checkBox_16, self.checkBox_17, self.checkBox_18, self.checkBox_19, self.checkBox_20,
                        self.checkBox_21, self.checkBox_22, self.checkBox_23, self.checkBox_24, self.checkBox_25,
                        self.checkBox_26, self.checkBox_27, self.checkBox_28, self.checkBox_29, self.checkBox_30,
                        self.checkBox_31, self.checkBox_32, self.checkBox_33, self.checkBox_34, self.checkBox_35,
                        self.checkBox_36, self.checkBox_37, self.checkBox_38, self.checkBox_39, self.checkBox_40,
                        self.checkBox_41, self.checkBox_42, self.checkBox_43, self.checkBox_44, self.checkBox_45,
                        self.checkBox_46, self.checkBox_47, self.checkBox_48, self.checkBox_49, self.checkBox_50,
                        self.checkBox_51, self.checkBox_52, self.checkBox_53, self.checkBox_54, self.checkBox_55,
                        self.checkBox_56, self.checkBox_57, self.checkBox_58, self.checkBox_59]

        conn = sqlite3.connect('C:/sqlite/cucina.db')
        conn.text_factory = str
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
        for i in range(0,59):
            checkBox_arr[i].stateChanged.connect(lambda state, i=i+1:self.addMenu(state,i))

        self.btn.clicked.connect(self.janbagooni)
    def addMenu(self,state,i):
        global temp
        temp=0
        print(state,i)
        if i>=1 and i<=4 or i==20 or i==21:
            pass
        elif i>=5 and i<=11 or i==41 or i==42 or i==50:
            print(2000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))+2000

            else:
                temp = 2000
                print("once")
            print("temp:"+str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i >= 12 and i <= 19:
            print(5000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 5000

            else:
                temp = 5000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==22 or i==23 or i >= 51 and i <= 59:
            print(3000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))+3000

            else:
                temp = 3000
                print("once")
            print("temp:"+str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i ==24 or i==26:
            print(2500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))+2500

            else:
                temp = 2500
                print("once")
            print("temp:"+str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==25 or i==27:
            print(1500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))+1500

            else:
                temp = 1500
                print("once")
            print("temp:"+str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==28:
            print(500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))+500

            else:
                temp = 500
                print("once")
            print("temp:"+str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==29:
            print(400)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))+400

            else:
                temp = 400
                print("once")
            print("temp:"+str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==30:
            print(100)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))+100

            else:
                temp = 100
                print("once")
            print("temp:"+str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==31 or i>=43 and i<=49:
            print(1000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))+1000

            else:
                temp = 1000
                print("once")
            print("temp:"+str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==32 or i==33 or i==37:
            print(7900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 7900

            else:
                temp = 7900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==34:
            print(3900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3900

            else:
                temp = 3900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==35:
            print(2900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2900

            else:
                temp = 2900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==36:
            print(8900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 8900

            else:
                temp = 8900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==38:
            print(5900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 5900

            else:
                temp = 5900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==39:
            print(6900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 6900

            else:
                temp = 6900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')

    def janbagooni(self):
        price = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))
        conn = sqlite3.connect('C:/sqlite/cucina.db')
        print('sql connected')
        conn.text_factory = str
        cur = conn.cursor()
        temp = re.sub(r'[^0-9]', '', self.label_sumPrice.text())
        sql = f'insert into jangbagooni values(\'{self.label_product_name.text()}\',{temp})'
        cur.execute(sql)
        conn.commit()
        conn.close()
class largeL_pizza_rice_menu_Form(QDialog, QWidget,largeL_pizza_rice_menu_Form):
    def __init__(self, i):
        global result
        super(largeL_pizza_rice_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()
        checkBox_arr = [self.checkBox_1, self.checkBox_2, self.checkBox_3, self.checkBox_4, self.checkBox_5,
                        self.checkBox_6, self.checkBox_7, self.checkBox_8, self.checkBox_9, self.checkBox_10,
                        self.checkBox_11, self.checkBox_12, self.checkBox_13, self.checkBox_14, self.checkBox_15,
                        self.checkBox_16, self.checkBox_17, self.checkBox_18, self.checkBox_19, self.checkBox_20,
                        self.checkBox_21, self.checkBox_22, self.checkBox_23, self.checkBox_24, self.checkBox_25,
                        self.checkBox_26, self.checkBox_27, self.checkBox_28, self.checkBox_29, self.checkBox_30,
                        self.checkBox_31, self.checkBox_32, self.checkBox_33, self.checkBox_34, self.checkBox_35,
                        self.checkBox_36, self.checkBox_37, self.checkBox_38, self.checkBox_39, self.checkBox_40,
                        self.checkBox_41, self.checkBox_42, self.checkBox_43, self.checkBox_44, self.checkBox_45,
                        self.checkBox_46, self.checkBox_47, self.checkBox_48, self.checkBox_49, self.checkBox_50,
                        self.checkBox_51, self.checkBox_52, self.checkBox_53, self.checkBox_54, self.checkBox_55,
                        self.checkBox_56, self.checkBox_57, self.checkBox_58, self.checkBox_59]

        conn = sqlite3.connect('C:/sqlite/cucina.db')
        conn.text_factory = str
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

        for i in range(0,59):
            checkBox_arr[i].stateChanged.connect(lambda state, i=i+1:self.addMenu(state,i))

        self.btn.clicked.connect(self.janbagooni)
    def addMenu(self,state,i):
        global temp
        temp=0
        print(state,i)

        if i>=1 and i<=4 or i==20 or i==21:
            pass
        elif i==5 or i>=51 and i<=59:
            print(3000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3000

            else:
                temp = 3000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==6 or i==7 or i==10 or i==11 or i==41 or i==42 or i==50:
            print(2000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2000

            else:
                temp = 2000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==8 or i==9 or i==24 or i==26:
            print(2500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2500

            else:
                temp = 2500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==12 or i==15:
            print(7000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 7000

            else:
                temp = 7000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==13 or i==14 or i>=16 and i<=19:
            print(6000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 6000

            else:
                temp = 6000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==22 or i==23:
            print(4000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 4000

            else:
                temp = 4000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==25 or i==27:
            print(1500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1500

            else:
                temp = 1500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==28:
            print(500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 500

            else:
                temp = 500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==29:
            print(400)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 400

            else:
                temp = 400
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==30:
            print(100)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 100

            else:
                temp = 100
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==31 or i>=43 and i<=49:
            print(1000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1000

            else:
                temp = 1000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==32 or i==33 or i==37:
            print(7900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 7900

            else:
                temp = 7900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==34:
            print(3900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3900

            else:
                temp = 3900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==35:
            print(2900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2900

            else:
                temp = 2900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==36:
            print(5900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 5900

            else:
                temp = 5900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==38:
            print(8900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 8900

            else:
                temp = 8900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==39 or i==40:
            print(6900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 6900

            else:
                temp = 6900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')

    def janbagooni(self):
        price = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))
        conn = sqlite3.connect('C:/sqlite/cucina.db')
        print('sql connected')
        conn.text_factory = str
        cur = conn.cursor()
        temp = re.sub(r'[^0-9]', '', self.label_sumPrice.text())
        sql = f'insert into jangbagooni values(\'{self.label_product_name.text()}\',{temp})'
        cur.execute(sql)
        conn.commit()
        conn.close()
class cucina_spaghettiSetL_menu_Form(QDialog, QWidget,cucina_spaghettiSetL_menu_Form):
    def __init__(self, i):
        global result
        super(cucina_spaghettiSetL_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        checkBox_arr = [self.checkBox_1, self.checkBox_2, self.checkBox_3, self.checkBox_4, self.checkBox_5,
                        self.checkBox_6, self.checkBox_7, self.checkBox_8, self.checkBox_9, self.checkBox_10,
                        self.checkBox_11, self.checkBox_12, self.checkBox_13, self.checkBox_14, self.checkBox_15,
                        self.checkBox_16, self.checkBox_17, self.checkBox_18, self.checkBox_19, self.checkBox_20,
                        self.checkBox_21, self.checkBox_22, self.checkBox_23, self.checkBox_24, self.checkBox_25,
                        self.checkBox_26, self.checkBox_27, self.checkBox_28, self.checkBox_29, self.checkBox_30,
                        self.checkBox_31, self.checkBox_32, self.checkBox_33, self.checkBox_34, self.checkBox_35,
                        self.checkBox_36, self.checkBox_37, self.checkBox_38, self.checkBox_39, self.checkBox_40,
                        self.checkBox_41, self.checkBox_42, self.checkBox_43, self.checkBox_44, self.checkBox_45,
                        self.checkBox_46, self.checkBox_47, self.checkBox_48, self.checkBox_49, self.checkBox_50,
                        self.checkBox_51, self.checkBox_52, self.checkBox_53, self.checkBox_54, self.checkBox_55,
                        self.checkBox_56, self.checkBox_57, self.checkBox_58, self.checkBox_59]

        conn = sqlite3.connect('C:/sqlite/cucina.db')
        conn.text_factory = str
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

        for i in range(0,59):
            checkBox_arr[i].stateChanged.connect(lambda state, i=i+1:self.addMenu(state,i))

        self.btn.clicked.connect(self.janbagooni)
    def addMenu(self,state,i):
        global temp
        temp=0
        print(state,i)

        if i>=1 and i<=4 or i==20 or i==21:
            pass
        elif i==5 or i>=51 and i<=59:
            print(3000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3000

            else:
                temp = 3000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==6 or i==7 or i==10 or i==11 or i==41 or i==42 or i==50:
            print(2000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2000

            else:
                temp = 2000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==8 or i==9 or i==24 or i==26:
            print(2500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2500

            else:
                temp = 2500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==12 or i==15:
            print(7000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 7000

            else:
                temp = 7000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==13 or i==14 or i>=16 and i<=19:
            print(6000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 6000

            else:
                temp = 6000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==22 or i==23:
            print(4000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 4000

            else:
                temp = 4000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==25 or i==27:
            print(1500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1500

            else:
                temp = 1500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==28:
            print(500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 500

            else:
                temp = 500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==29:
            print(400)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 400

            else:
                temp = 400
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==30:
            print(100)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 100

            else:
                temp = 100
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==31 or i>=43 and i<=49:
            print(1000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1000

            else:
                temp = 1000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==32 or i==33 or i==37:
            print(7900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 7900

            else:
                temp = 7900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==34:
            print(3900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3900

            else:
                temp = 3900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==35:
            print(2900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2900

            else:
                temp = 2900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==36:
            print(5900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 5900

            else:
                temp = 5900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==38:
            print(8900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 8900

            else:
                temp = 8900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==39 or i==40:
            print(6900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 6900

            else:
                temp = 6900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')

    def janbagooni(self):
        price = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))
        conn = sqlite3.connect('C:/sqlite/cucina.db')
        print('sql connected')
        conn.text_factory = str
        cur = conn.cursor()
        temp = re.sub(r'[^0-9]', '', self.label_sumPrice.text())
        sql = f'insert into jangbagooni values(\'{self.label_product_name.text()}\',{temp})'
        cur.execute(sql)
        conn.commit()
        conn.close()
class halfAndHalf_menu_Form(QDialog, QWidget,halfAndHalf_menu_Form):
    def __init__(self, i):
        global result
        super(halfAndHalf_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        checkBox_arr = [self.checkBox_1, self.checkBox_2, self.checkBox_3, self.checkBox_4, self.checkBox_5,
                        self.checkBox_6, self.checkBox_7, self.checkBox_8, self.checkBox_9, self.checkBox_10,
                        self.checkBox_11, self.checkBox_12, self.checkBox_13, self.checkBox_14, self.checkBox_15,
                        self.checkBox_16, self.checkBox_17, self.checkBox_18, self.checkBox_19, self.checkBox_20,
                        self.checkBox_21, self.checkBox_22, self.checkBox_23, self.checkBox_24, self.checkBox_25,
                        self.checkBox_26, self.checkBox_27, self.checkBox_28, self.checkBox_29, self.checkBox_30,
                        self.checkBox_31, self.checkBox_32, self.checkBox_33, self.checkBox_34, self.checkBox_35,
                        self.checkBox_36, self.checkBox_37, self.checkBox_38, self.checkBox_39, self.checkBox_40,
                        self.checkBox_41, self.checkBox_42, self.checkBox_43, self.checkBox_44, self.checkBox_45,
                        self.checkBox_46, self.checkBox_47, self.checkBox_48, self.checkBox_49, self.checkBox_50,
                        self.checkBox_51, self.checkBox_52, self.checkBox_53, self.checkBox_54, self.checkBox_55,
                        self.checkBox_56, self.checkBox_57, self.checkBox_58, self.checkBox_59]

        conn = sqlite3.connect('C:/sqlite/cucina.db')
        conn.text_factory = str
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

        for i in range(0, 59):
            checkBox_arr[i].stateChanged.connect(lambda state, i=i + 1: self.addMenu(state, i))

        self.btn.clicked.connect(self.janbagooni)
    def addMenu(self, state, i):
        global temp
        temp = 0
        print(state, i)

        if i >= 1 and i <= 4 or i == 20 or i == 21:
            pass
        elif i == 5 or i >= 51 and i <= 59:
            print(3000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3000

            else:
                temp = 3000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 6 or i == 7 or i == 10 or i == 11 or i == 41 or i == 42 or i == 50:
            print(2000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2000

            else:
                temp = 2000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 8 or i == 9 or i == 24 or i == 26:
            print(2500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2500

            else:
                temp = 2500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 12 or i == 15:
            print(7000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 7000

            else:
                temp = 7000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 13 or i == 14 or i >= 16 and i <= 19:
            print(6000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 6000

            else:
                temp = 6000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 22 or i == 23:
            print(4000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 4000

            else:
                temp = 4000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 25 or i == 27:
            print(1500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1500

            else:
                temp = 1500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 28:
            print(500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 500

            else:
                temp = 500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 29:
            print(400)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 400

            else:
                temp = 400
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 30:
            print(100)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 100

            else:
                temp = 100
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 31 or i >= 43 and i <= 49:
            print(1000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1000

            else:
                temp = 1000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 32 or i == 33 or i == 37:
            print(7900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 7900

            else:
                temp = 7900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 34:
            print(3900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3900

            else:
                temp = 3900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 35:
            print(2900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2900

            else:
                temp = 2900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 36:
            print(5900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 5900

            else:
                temp = 5900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 38:
            print(8900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 8900

            else:
                temp = 8900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 39 or i == 40:
            print(6900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 6900

            else:
                temp = 6900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')

    def janbagooni(self):
        price = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))
        conn = sqlite3.connect('C:/sqlite/cucina.db')
        print('sql connected')
        conn.text_factory = str
        cur = conn.cursor()
        temp = re.sub(r'[^0-9]', '', self.label_sumPrice.text())
        sql = f'insert into jangbagooni values(\'{self.label_product_name.text()}\',{temp})'
        cur.execute(sql)
        conn.commit()
        conn.close()
class originalComboL_menu_Form(QDialog, QWidget,originalComboL_menu_Form):
    def __init__(self, i):
        global result
        super(originalComboL_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        checkBox_arr = [self.checkBox_1, self.checkBox_2, self.checkBox_3, self.checkBox_4, self.checkBox_5,
                        self.checkBox_6, self.checkBox_7, self.checkBox_8, self.checkBox_9, self.checkBox_10,
                        self.checkBox_11, self.checkBox_12, self.checkBox_13, self.checkBox_14, self.checkBox_15,
                        self.checkBox_16, self.checkBox_17, self.checkBox_18, self.checkBox_19, self.checkBox_20,
                        self.checkBox_21, self.checkBox_22, self.checkBox_23, self.checkBox_24, self.checkBox_25,
                        self.checkBox_26, self.checkBox_27, self.checkBox_28, self.checkBox_29, self.checkBox_30,
                        self.checkBox_31, self.checkBox_32, self.checkBox_33, self.checkBox_34, self.checkBox_35,
                        self.checkBox_36, self.checkBox_37, self.checkBox_38, self.checkBox_39, self.checkBox_40,
                        self.checkBox_41, self.checkBox_42, self.checkBox_43, self.checkBox_44, self.checkBox_45]

        conn = sqlite3.connect('C:/sqlite/cucina.db')
        conn.text_factory = str
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

        for i in range(0, 45):
            checkBox_arr[i].stateChanged.connect(lambda state, i=i + 1: self.addMenu(state, i))

        self.btn.clicked.connect(self.janbagooni)
    def addMenu(self, state, i):
        global temp
        temp = 0
        print(state, i)

        if i>=1 and i<=7:
            pass
        elif i==8 or i==9:
            print(4000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 4000

            else:
                temp = 4000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==10 or i==12:
            print(2500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2500

            else:
                temp = 2500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==11 or i==13:
            print(1500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1500

            else:
                temp = 1500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==14:
            print(500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 500

            else:
                temp = 500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==15:
            print(400)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 400

            else:
                temp = 400
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==16:
            print(100)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 100

            else:
                temp = 100
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==17 or i>=29 and i<=35:
            print(1000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1000

            else:
                temp = 1000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==18 or i==19 or i==23:
            print(7900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 7900

            else:
                temp = 7900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==20:
            print(3900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3900

            else:
                temp = 3900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==21:
            print(2900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2900

            else:
                temp = 2900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==22:
            print(5900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 5900

            else:
                temp = 5900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==24:
            print(8900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 8900

            else:
                temp = 8900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==25 or i==26:
            print(6900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 6900

            else:
                temp = 6900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==27 or i==28 or i==36:
            print(2000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2000

            else:
                temp = 2000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i>=37 and i<=45:
            print(3000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3000

            else:
                temp = 3000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')

    def janbagooni(self):
        price = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))
        conn = sqlite3.connect('C:/sqlite/cucina.db')
        print('sql connected')
        conn.text_factory = str
        cur = conn.cursor()
        temp = re.sub(r'[^0-9]', '', self.label_sumPrice.text())
        sql = f'insert into jangbagooni values(\'{self.label_product_name.text()}\',{temp})'
        cur.execute(sql)
        conn.commit()
        conn.close()
class originalComboR_menu_Form(QDialog, QWidget,originalComboR_menu_Form):
    def __init__(self, i):
        global result
        super(originalComboR_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        checkBox_arr = [self.checkBox_1, self.checkBox_2, self.checkBox_3, self.checkBox_4, self.checkBox_5,
                        self.checkBox_6, self.checkBox_7, self.checkBox_8, self.checkBox_9, self.checkBox_10,
                        self.checkBox_11, self.checkBox_12, self.checkBox_13, self.checkBox_14, self.checkBox_15,
                        self.checkBox_16, self.checkBox_17, self.checkBox_18, self.checkBox_19, self.checkBox_20,
                        self.checkBox_21, self.checkBox_22, self.checkBox_23, self.checkBox_24, self.checkBox_25,
                        self.checkBox_26, self.checkBox_27, self.checkBox_28, self.checkBox_29, self.checkBox_30,
                        self.checkBox_31, self.checkBox_32, self.checkBox_33, self.checkBox_34, self.checkBox_35,
                        self.checkBox_36, self.checkBox_37, self.checkBox_38, self.checkBox_39, self.checkBox_40,
                        self.checkBox_41, self.checkBox_42, self.checkBox_43, self.checkBox_44, self.checkBox_45]

        conn = sqlite3.connect('C:/sqlite/cucina.db')
        conn.text_factory = str
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

        for i in range(0, 45):
            checkBox_arr[i].stateChanged.connect(lambda state, i=i + 1: self.addMenu(state, i))

        self.btn.clicked.connect(self.janbagooni)
    def addMenu(self, state, i):
        global temp
        temp = 0
        print(state, i)

        if i >= 1 and i <= 7:
            pass

        elif i == 10 or i == 12:
            print(2500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2500

            else:
                temp = 2500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 11 or i == 13:
            print(1500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1500

            else:
                temp = 1500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 14:
            print(500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 500

            else:
                temp = 500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 15:
            print(400)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 400

            else:
                temp = 400
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 16:
            print(100)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 100

            else:
                temp = 100
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 17 or i >= 29 and i <= 35:
            print(1000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1000

            else:
                temp = 1000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 18 or i == 19 or i == 23:
            print(7900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 7900

            else:
                temp = 7900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 20:
            print(3900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3900

            else:
                temp = 3900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 21:
            print(2900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2900

            else:
                temp = 2900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 22:
            print(5900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 5900

            else:
                temp = 5900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 24:
            print(8900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 8900

            else:
                temp = 8900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 25 or i == 26:
            print(6900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 6900

            else:
                temp = 6900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 27 or i == 28 or i == 36:
            print(2000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2000

            else:
                temp = 2000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==8 or i==9 or i >= 37 and i <= 45:
            print(3000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3000

            else:
                temp = 3000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')

    def janbagooni(self):
        price = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))
        conn = sqlite3.connect('C:/sqlite/cucina.db')
        print('sql connected')
        conn.text_factory = str
        cur = conn.cursor()
        temp = re.sub(r'[^0-9]', '', self.label_sumPrice.text())
        sql = f'insert into jangbagooni values(\'{self.label_product_name.text()}\',{temp})'
        cur.execute(sql)
        conn.commit()
        conn.close()
class classicComboL_menu_Form(QDialog, QWidget,classicComboL_menu_Form):
    def __init__(self, i):
        global result
        super(classicComboL_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        checkBox_arr = [self.checkBox_1, self.checkBox_2, self.checkBox_3, self.checkBox_4, self.checkBox_5,
                        self.checkBox_6, self.checkBox_7, self.checkBox_8, self.checkBox_9, self.checkBox_10,
                        self.checkBox_11, self.checkBox_12, self.checkBox_13, self.checkBox_14, self.checkBox_15,
                        self.checkBox_16, self.checkBox_17, self.checkBox_18, self.checkBox_19, self.checkBox_20,
                        self.checkBox_21, self.checkBox_22, self.checkBox_23, self.checkBox_24, self.checkBox_25,
                        self.checkBox_26, self.checkBox_27, self.checkBox_28, self.checkBox_29, self.checkBox_30,
                        self.checkBox_31, self.checkBox_32, self.checkBox_33, self.checkBox_34, self.checkBox_35,
                        self.checkBox_36, self.checkBox_37, self.checkBox_38, self.checkBox_39, self.checkBox_40,
                        self.checkBox_41, self.checkBox_42, self.checkBox_43, self.checkBox_44, self.checkBox_45,
                        self.checkBox_46, self.checkBox_47, self.checkBox_48]

        conn = sqlite3.connect('C:/sqlite/cucina.db')
        conn.text_factory = str
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

        for i in range(0, 48):
            checkBox_arr[i].stateChanged.connect(lambda state, i=i + 1: self.addMenu(state, i))

        self.btn.clicked.connect(self.janbagooni)
    def addMenu(self, state, i):
        global temp
        temp = 0
        print(state, i)

        if i==1 or i==20 or i>=32 and i<=38:
            print(1000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1000

            else:
                temp = 1000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==2 or i==4 or i==6 or i==17:
            print(500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 500

            else:
                temp = 500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==3 or i==5 or i>=7 and i<=10:
            pass
        elif i==11 or i==12:
            print(4000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 4000

            else:
                temp = 4000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==13 or i==15:
            print(2500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2500

            else:
                temp = 2500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==14 or i==16:
            print(1500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1500

            else:
                temp = 1500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==18:
            print(400)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 400

            else:
                temp = 400
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==19:
            print(100)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 100

            else:
                temp = 100
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==21 or i==22 or i==26:
            print(7900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 7900

            else:
                temp = 7900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==23:
            print(3900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3900

            else:
                temp = 3900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==24:
            print(2900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2900

            else:
                temp = 2900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==25:
            print(5900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 5900

            else:
                temp = 5900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==27:
            print(8900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 8900

            else:
                temp = 8900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==28 or i==29:
            print(6900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 6900

            else:
                temp = 6900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==30 or i==31 or i==39:
            print(2000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2000

            else:
                temp = 2000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i>=40 and i<=48:
            print(3000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3000

            else:
                temp = 3000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
    def janbagooni(self):
        price = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))
        conn = sqlite3.connect('C:/sqlite/cucina.db')
        print('sql connected')
        conn.text_factory = str
        cur = conn.cursor()
        temp = re.sub(r'[^0-9]', '', self.label_sumPrice.text())
        sql = f'insert into jangbagooni values(\'{self.label_product_name.text()}\',{temp})'
        cur.execute(sql)
        conn.commit()
        conn.close()
class classicComboR_menu_Form(QDialog, QWidget,classicComboR_menu_Form):
    def __init__(self, i):
        global result
        super(classicComboR_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        checkBox_arr = [self.checkBox_1, self.checkBox_2, self.checkBox_3, self.checkBox_4, self.checkBox_5,
                        self.checkBox_6, self.checkBox_7, self.checkBox_8, self.checkBox_9, self.checkBox_10,
                        self.checkBox_11, self.checkBox_12, self.checkBox_13, self.checkBox_14, self.checkBox_15,
                        self.checkBox_16, self.checkBox_17, self.checkBox_18, self.checkBox_19, self.checkBox_20,
                        self.checkBox_21, self.checkBox_22, self.checkBox_23, self.checkBox_24, self.checkBox_25,
                        self.checkBox_26, self.checkBox_27, self.checkBox_28, self.checkBox_29, self.checkBox_30,
                        self.checkBox_31, self.checkBox_32, self.checkBox_33, self.checkBox_34, self.checkBox_35,
                        self.checkBox_36, self.checkBox_37, self.checkBox_38, self.checkBox_39, self.checkBox_40,
                        self.checkBox_41, self.checkBox_42, self.checkBox_43, self.checkBox_44, self.checkBox_45,
                        self.checkBox_46, self.checkBox_47, self.checkBox_48]

        conn = sqlite3.connect('C:/sqlite/cucina.db')
        conn.text_factory = str
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

        for i in range(0, 48):
            checkBox_arr[i].stateChanged.connect(lambda state, i=i + 1: self.addMenu(state, i))

        self.btn.clicked.connect(self.janbagooni)
    def addMenu(self, state, i):
        global temp
        temp = 0
        print(state, i)

        if i == 20 or i >= 32 and i <= 38:
            print(1000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1000

            else:
                temp = 1000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 17:
            print(500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 500

            else:
                temp = 500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i>=1 and i <= 10:
            pass
        elif i == 13 or i == 15:
            print(2500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2500

            else:
                temp = 2500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 14 or i == 16:
            print(1500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1500

            else:
                temp = 1500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 18:
            print(400)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 400

            else:
                temp = 400
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 19:
            print(100)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 100

            else:
                temp = 100
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 21 or i == 22 or i == 26:
            print(7900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 7900

            else:
                temp = 7900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 23:
            print(3900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3900

            else:
                temp = 3900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 24:
            print(2900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2900

            else:
                temp = 2900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 25:
            print(5900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 5900

            else:
                temp = 5900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 27:
            print(8900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 8900

            else:
                temp = 8900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 28 or i == 29:
            print(6900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 6900

            else:
                temp = 6900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 30 or i == 31 or i == 39:
            print(2000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2000

            else:
                temp = 2000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==11 or i==12 or i >= 40 and i <= 48:
            print(3000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3000

            else:
                temp = 3000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')

    def janbagooni(self):
        price = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))
        conn = sqlite3.connect('C:/sqlite/cucina.db')
        print('sql connected')
        conn.text_factory = str
        cur = conn.cursor()
        temp = re.sub(r'[^0-9]', '', self.label_sumPrice.text())
        sql = f'insert into jangbagooni values(\'{self.label_product_name.text()}\',{temp})'
        cur.execute(sql)
        conn.commit()
        conn.close()
class premiumComboL_menu_Form(QDialog, QWidget,premiumComboL_menu_Form):
    def __init__(self, i):
        global result
        super(premiumComboL_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        checkBox_arr = [self.checkBox_1, self.checkBox_2, self.checkBox_3, self.checkBox_4, self.checkBox_5,
                        self.checkBox_6, self.checkBox_7, self.checkBox_8, self.checkBox_9, self.checkBox_10,
                        self.checkBox_11, self.checkBox_12, self.checkBox_13, self.checkBox_14, self.checkBox_15,
                        self.checkBox_16, self.checkBox_17, self.checkBox_18, self.checkBox_19, self.checkBox_20,
                        self.checkBox_21, self.checkBox_22, self.checkBox_23, self.checkBox_24, self.checkBox_25,
                        self.checkBox_26, self.checkBox_27, self.checkBox_28, self.checkBox_29, self.checkBox_30,
                        self.checkBox_31, self.checkBox_32, self.checkBox_33, self.checkBox_34, self.checkBox_35,
                        self.checkBox_36, self.checkBox_37, self.checkBox_38, self.checkBox_39, self.checkBox_40,
                        self.checkBox_41, self.checkBox_42, self.checkBox_43, self.checkBox_44, self.checkBox_45,
                        self.checkBox_46, self.checkBox_47, self.checkBox_48, self.checkBox_49]

        conn = sqlite3.connect('C:/sqlite/cucina.db')
        conn.text_factory = str
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

        for i in range(0, 49):
            checkBox_arr[i].stateChanged.connect(lambda state, i=i + 1: self.addMenu(state, i))
        self.btn.clicked.connect(self.janbagooni)
    def addMenu(self, state, i):
        global temp
        temp = 0
        print(state, i)

        if i==1 or i==5 or i==21 or i>=33 and i<=39:
            print(1000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1000

            else:
                temp = 1000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i>=2 and i<=4 or i>=6 and i<=11:
            pass
        elif i==12 or i==13:
            print(4000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 4000

            else:
                temp = 4000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==14 or i==16:
            print(2500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2500

            else:
                temp = 2500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==15 or i==17:
            print(1500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1500

            else:
                temp = 1500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==18:
            print(500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 500

            else:
                temp = 500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==19:
            print(400)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 400

            else:
                temp = 400
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==20:
            print(100)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 100

            else:
                temp = 100
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==22 or i==23 or i==27:
            print(7900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 7900

            else:
                temp = 7900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==24:
            print(3900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3900

            else:
                temp = 3900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==25:
            print(2900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2900

            else:
                temp = 2900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==26:
            print(5900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 5900

            else:
                temp = 5900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==28:
            print(8900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 8900

            else:
                temp = 8900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==29 or i==30:
            print(6900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 6900

            else:
                temp = 6900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==31 or i==32 or i==40:
            print(2000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2000

            else:
                temp = 2000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i>=41 and i<=49:
            print(3000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3000

            else:
                temp = 3000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
    def janbagooni(self):
        price = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))
        conn = sqlite3.connect('C:/sqlite/cucina.db')
        print('sql connected')
        conn.text_factory = str
        cur = conn.cursor()
        temp = re.sub(r'[^0-9]', '', self.label_sumPrice.text())
        sql = f'insert into jangbagooni values(\'{self.label_product_name.text()}\',{temp})'
        cur.execute(sql)
        conn.commit()
        conn.close()
class premiumComboR_menu_Form(QDialog, QWidget, premiumComboR_menu_Form):
    def __init__(self, i):
        global result
        super(premiumComboR_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        checkBox_arr = [self.checkBox_1, self.checkBox_2, self.checkBox_3, self.checkBox_4, self.checkBox_5,
                        self.checkBox_6, self.checkBox_7, self.checkBox_8, self.checkBox_9, self.checkBox_10,
                        self.checkBox_11, self.checkBox_12, self.checkBox_13, self.checkBox_14, self.checkBox_15,
                        self.checkBox_16, self.checkBox_17, self.checkBox_18, self.checkBox_19, self.checkBox_20,
                        self.checkBox_21, self.checkBox_22, self.checkBox_23, self.checkBox_24, self.checkBox_25,
                        self.checkBox_26, self.checkBox_27, self.checkBox_28, self.checkBox_29, self.checkBox_30,
                        self.checkBox_31, self.checkBox_32, self.checkBox_33, self.checkBox_34, self.checkBox_35,
                        self.checkBox_36, self.checkBox_37, self.checkBox_38, self.checkBox_39, self.checkBox_40,
                        self.checkBox_41, self.checkBox_42, self.checkBox_43, self.checkBox_44, self.checkBox_45,
                        self.checkBox_46, self.checkBox_47, self.checkBox_48, self.checkBox_49]

        conn = sqlite3.connect('C:/sqlite/cucina.db')
        conn.text_factory = str
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

        for i in range(0, 49):
            checkBox_arr[i].stateChanged.connect(lambda state, i=i + 1: self.addMenu(state, i))
        self.btn.clicked.connect(self.janbagooni)
    def addMenu(self, state, i):
        global temp
        temp = 0
        print(state, i)

        if i == 1 or i == 5 or i == 21 or i >= 33 and i <= 39:
            print(1000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1000

            else:
                temp = 1000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i >= 2 and i <= 4 or i >= 6 and i <= 11:
            pass

        elif i == 14 or i == 16:
            print(2500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2500

            else:
                temp = 2500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 15 or i == 17:
            print(1500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1500

            else:
                temp = 1500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 18:
            print(500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 500

            else:
                temp = 500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 19:
            print(400)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 400

            else:
                temp = 400
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 20:
            print(100)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 100

            else:
                temp = 100
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 22 or i == 23 or i == 27:
            print(7900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 7900

            else:
                temp = 7900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 24:
            print(3900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3900

            else:
                temp = 3900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 25:
            print(2900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2900

            else:
                temp = 2900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 26:
            print(5900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 5900

            else:
                temp = 5900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 28:
            print(8900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 8900

            else:
                temp = 8900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 29 or i == 30:
            print(6900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 6900

            else:
                temp = 6900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i == 31 or i == 32 or i == 40:
            print(2000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2000

            else:
                temp = 2000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==12 or i==13 or i >= 41 and i <= 49:
            print(3000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3000

            else:
                temp = 3000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')

    def janbagooni(self):
        price = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))
        conn = sqlite3.connect('C:/sqlite/cucina.db')
        print('sql connected')
        conn.text_factory = str
        cur = conn.cursor()
        temp = re.sub(r'[^0-9]', '', self.label_sumPrice.text())
        sql = f'insert into jangbagooni values(\'{self.label_product_name.text()}\',{temp})'
        cur.execute(sql)
        conn.commit()
        conn.close()
class shinMenu_Fire_menu_Form(QDialog, QWidget,shinMenu_Fire_menu_Form):
    def __init__(self, i):
        global result
        super(shinMenu_Fire_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        checkBox_arr = [self.checkBox_1, self.checkBox_2, self.checkBox_3, self.checkBox_4, self.checkBox_5,
                        self.checkBox_6, self.checkBox_7, self.checkBox_8, self.checkBox_9, self.checkBox_10,
                        self.checkBox_11, self.checkBox_12, self.checkBox_13, self.checkBox_14, self.checkBox_15,
                        self.checkBox_16, self.checkBox_17, self.checkBox_18, self.checkBox_19, self.checkBox_20,
                        self.checkBox_21, self.checkBox_22, self.checkBox_23, self.checkBox_24, self.checkBox_25,
                        self.checkBox_26, self.checkBox_27, self.checkBox_28, self.checkBox_29, self.checkBox_30,
                        self.checkBox_31, self.checkBox_32, self.checkBox_33, self.checkBox_34, self.checkBox_35,
                        self.checkBox_36, self.checkBox_37, self.checkBox_38, self.checkBox_39, self.checkBox_40,
                        self.checkBox_41, self.checkBox_42, self.checkBox_43]

        conn = sqlite3.connect('C:/sqlite/cucina.db')
        conn.text_factory = str
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

        for i in range(0, 43):
            checkBox_arr[i].stateChanged.connect(lambda state, i=i + 1: self.addMenu(state, i))
        self.btn.clicked.connect(self.janbagooni)
    def addMenu(self, state, i):
        global temp
        temp = 0
        print(state, i)

        if i>=1 and i<=3:
            pass
        elif i==4 or i==5 or i>=35 and i<=43:
            print(3000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3000

            else:
                temp = 3000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==6 or i==7:
            print(4000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 4000

            else:
                temp = 4000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==8 or i==10:
            print(2500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2500

            else:
                temp = 2500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==9 or i==11:
            print(1500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1500

            else:
                temp = 1500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==12:
            print(500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 500

            else:
                temp = 500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==13:
            print(400)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 400

            else:
                temp = 400
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==14:
            print(100)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 100

            else:
                temp = 100
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==15 or i>=27 and i<=33:
            print(1000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1000

            else:
                temp = 1000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==16 or i==17 or i==21:
            print(7900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 7900

            else:
                temp = 7900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==18:
            print(3900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3900

            else:
                temp = 3900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==19:
            print(2900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2900

            else:
                temp = 2900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==20:
            print(5900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 5900

            else:
                temp = 5900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==22:
            print(8900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 8900

            else:
                temp = 8900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==23 or i==24:
            print(6900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 6900

            else:
                temp = 6900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==25 or i==26 or i==34:
            print(2000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2000

            else:
                temp = 2000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
    def janbagooni(self):
        price = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))
        conn = sqlite3.connect('C:/sqlite/cucina.db')
        print('sql connected')
        conn.text_factory = str
        cur = conn.cursor()
        temp = re.sub(r'[^0-9]', '', self.label_sumPrice.text())
        sql = f'insert into jangbagooni values(\'{self.label_product_name.text()}\',{temp})'
        cur.execute(sql)
        conn.commit()
        conn.close()
class allSize_pizza_menu_Form(QDialog, QWidget, allSize_pizza_Ui_Form):
    def __init__(self, i):
        global result
        super(allSize_pizza_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        checkBox_arr = [self.checkBox_1, self.checkBox_2, self.checkBox_3, self.checkBox_4, self.checkBox_5,
                        self.checkBox_6, self.checkBox_7, self.checkBox_8, self.checkBox_9, self.checkBox_10,
                        self.checkBox_11, self.checkBox_12, self.checkBox_13, self.checkBox_14, self.checkBox_15,
                        self.checkBox_16, self.checkBox_17, self.checkBox_18, self.checkBox_19, self.checkBox_20,
                        self.checkBox_21, self.checkBox_22, self.checkBox_23, self.checkBox_24, self.checkBox_25,
                        self.checkBox_26, self.checkBox_27, self.checkBox_28, self.checkBox_29, self.checkBox_30,
                        self.checkBox_31, self.checkBox_32, self.checkBox_33, self.checkBox_34, self.checkBox_35,
                        self.checkBox_36, self.checkBox_37, self.checkBox_38, self.checkBox_39, self.checkBox_40]

        conn = sqlite3.connect('C:/sqlite/cucina.db')
        conn.text_factory = str
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

        for i in range(0, 40):
            checkBox_arr[i].stateChanged.connect(lambda state, i=i + 1: self.addMenu(state, i))
        self.btn.clicked.connect(self.janbagooni)
    def addMenu(self, state, i):
        global temp
        temp = 0
        print(state, i)

        if i==1 or i==2 or i>=32 and i<=40:
            print(3000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3000

            else:
                temp = 3000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==3 or i==4:
            print(4000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 4000

            else:
                temp = 4000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==5 or i==7:
            print(2500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2500

            else:
                temp = 2500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==6 or i==8:
            print(1500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1500

            else:
                temp = 1500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==9:
            print(500)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 500

            else:
                temp = 500
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==10:
            print(400)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 400

            else:
                temp = 400
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==11:
            print(100)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 100

            else:
                temp = 100
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==12 or i>=24 and i<=30:
            print(1000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 1000

            else:
                temp = 1000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==13 or i==14 or i==18:
            print(7900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 7900

            else:
                temp = 7900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==15:
            print(3900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 3900

            else:
                temp = 3900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==16:
            print(2900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2900

            else:
                temp = 2900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==17:
            print(5900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 5900

            else:
                temp = 5900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==19:
            print(8900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 8900

            else:
                temp = 8900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==20 or i==21:
            print(6900)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 6900

            else:
                temp = 6900
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
        elif i==22 or i==23 or i==31:
            print(2000)
            if self.label_sumPrice.text() != '':
                print("twice")

                temp = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text())) + 2000

            else:
                temp = 2000
                print("once")
            print("temp:" + str(temp))
            self.label_sumPrice.setText(f'{temp}원')
    def janbagooni(self):
        price = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))
        conn = sqlite3.connect('C:/sqlite/cucina.db')
        print('sql connected')
        conn.text_factory = str
        cur = conn.cursor()
        temp = re.sub(r'[^0-9]', '', self.label_sumPrice.text())
        sql = f'insert into jangbagooni values(\'{self.label_product_name.text()}\',{temp})'
        cur.execute(sql)
        conn.commit()
        conn.close()
class simple_menu_Form(QDialog, QWidget,simple_menu_Ui_Form):
    def __init__(self, i):
        global result
        super(simple_menu_Form, self).__init__()
        self.setupUi(self)
        self.show()

        conn = sqlite3.connect('C:/sqlite/cucina.db')
        conn.text_factory = str
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

        self.btn.clicked.connect(self.janbagooni)
    def janbagooni(self):
        price = int(re.sub(r'[^0-9]', '', self.label_sumPrice.text()))
        conn = sqlite3.connect('C:/sqlite/cucina.db')
        print('sql connected')
        conn.text_factory = str
        cur = conn.cursor()
        temp = re.sub(r'[^0-9]', '', self.label_sumPrice.text())
        sql = f'insert into jangbagooni values(\'{self.label_product_name.text()}\',{temp})'
        cur.execute(sql)
        conn.commit()
        conn.close()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    form = main_Form()
    form.show()
    sys.exit(app.exec())