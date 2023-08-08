import sys
import time

from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QApplication, QLineEdit, QPushButton, QVBoxLayout, QWidget
from PyQt5.QtCore import Qt

from calculator.calculater_converted_ui import Ui_Form
num1 = 0
num2 = 0
plusPushed = 0
minusPushed =0
multiPushed =0
divPushed=0

class calculate_Form(QtWidgets.QWidget, Ui_Form ):
    global num1,num2,plusPushed,minusPushed,multiPushed,divPushed
    equalPushed =0
    def __init__(self):
        super().__init__()
        self.setupUi(self)


        # 라인에딧 오른쪽 정렬
        self.lineEdit.setAlignment(Qt.AlignRight)

        self.pushButton_0.clicked.connect(lambda: self.when_button_pushed(0))
        self.pushButton_1.clicked.connect(lambda: self.when_button_pushed(1))
        self.pushButton_2.clicked.connect(lambda: self.when_button_pushed(2))
        self.pushButton_3.clicked.connect(lambda: self.when_button_pushed(3))
        self.pushButton_4.clicked.connect(lambda: self.when_button_pushed(4))
        self.pushButton_5.clicked.connect(lambda: self.when_button_pushed(5))
        self.pushButton_6.clicked.connect(lambda: self.when_button_pushed(6))
        self.pushButton_7.clicked.connect(lambda: self.when_button_pushed(7))
        self.pushButton_8.clicked.connect(lambda: self.when_button_pushed(8))
        self.pushButton_9.clicked.connect(lambda: self.when_button_pushed(9))

        # 사칙연산 버튼
        self.pushButton_plus.clicked.connect((lambda : self.when_4operate_pushed('+')))
        self.pushButton_minus.clicked.connect((lambda : self.when_4operate_pushed('-')))
        self.pushButton_x.clicked.connect((lambda : self.when_4operate_pushed('x')))
        self.pushButton_div.clicked.connect((lambda : self.when_4operate_pushed('/')))

        # equal
        self.pushButton_equal.clicked.connect(self.when_equal_pushed)

        # C
        self.pushButton_C.clicked.connect(self.when_C_pushed)
    def when_C_pushed(self):
        self.lineEdit.setText('0')
    def when_equal_pushed(self):
        global num1,num2,plusPushed,minusPushed,multiPushed,divPushed
        if plusPushed ==1:
            num2 = int(self.lineEdit.text())
            result = int(num1)+int(num2)
            self.lineEdit.setText(str(result))
            plusPushed =0
        elif minusPushed ==1:
            num2 = int(self.lineEdit.text())
            result = int(num1) - int(num2)
            if result <0:
                result =0
            self.lineEdit.setText(str(result))
            minusPushed = 0
        elif multiPushed ==1:
            num2 = int(self.lineEdit.text())
            result = int(num1) * int(num2)
            self.lineEdit.setText(str(result))
            multiPushed = 0
        elif divPushed ==1:
            num2 = int(self.lineEdit.text())
            result = int(num1) // int(num2)
            self.lineEdit.setText(str(result))
            divPushed = 0
    def when_4operate_pushed(self, operation):
        global plusPushed,minusPushed,multiPushed,divPushed,num1
        if operation == '+':
            if plusPushed == 0:
                num1 = int(self.lineEdit.text())
                self.lineEdit.setText('0')
                plusPushed=1

        if operation == '-':
            if minusPushed == 0:
                num1 = int(self.lineEdit.text())
                self.lineEdit.setText('0')
                minusPushed=1
        if operation == 'x':
            if multiPushed == 0:
                num1 = int(self.lineEdit.text())
                self.lineEdit.setText('0')
                multiPushed=1
        if operation == '/':
            if divPushed == 0:
                num1 = int(self.lineEdit.text())
                self.lineEdit.setText('0')
                divPushed=1

    def when_button_pushed(self,num):
        number = num
        current_text = self.lineEdit.text()
        if current_text == '0':
            self.lineEdit.setText(str(number))
        elif current_text != '0':
            current_text+= str(number)
            self.lineEdit.setText(current_text)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    form = calculate_Form()
    form.show()

app.exec()