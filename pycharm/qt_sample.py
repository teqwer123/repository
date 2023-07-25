import sys

from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QVBoxLayout, QHBoxLayout
from sample import Ui_Form

class MyApplication(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("나의 GUI 프로그램")
        self.setGeometry(700,100,500,800)
        hbox = QHBoxLayout(self) #ctrl + p : hint
        self.setLayout(hbox)
        hbox.addWidget(QtWidgets.QLineEdit(self))
        hbox.addWidget(QtWidgets.QPushButton("버튼 2번"))

class MyApp2(QtWidgets.QWidget, Ui_Form):
    def __init__(self):
        super().__init__()
        self.setUpUi(self)


if __name__ == '__main__':
    myapp = QtWidgets.QApplication(sys.argv)
    a_widget = MyApp2()
    a_widget.show()

    myapp.exec()