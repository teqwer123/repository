# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'my_sample_ui.ui'
#
# Created by: PyQt5 UI code generator 5.15.9
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MyForm(object):
    def setupUi(self, MyForm):
        MyForm.setObjectName("MyForm")
        MyForm.resize(629, 542)
        self.horizontalLayout = QtWidgets.QHBoxLayout(MyForm)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.widget = QtWidgets.QWidget(MyForm)
        self.widget.setMaximumSize(QtCore.QSize(300, 16777215))
        self.widget.setObjectName("widget")
        self.verticalLayout_4 = QtWidgets.QVBoxLayout(self.widget)
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.widget_6 = QtWidgets.QWidget(self.widget)
        self.widget_6.setMaximumSize(QtCore.QSize(16777215, 120))
        self.widget_6.setObjectName("widget_6")
        self.horizontalLayout_4 = QtWidgets.QHBoxLayout(self.widget_6)
        self.horizontalLayout_4.setObjectName("horizontalLayout_4")
        self.widget_5 = QtWidgets.QWidget(self.widget_6)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.widget_5.sizePolicy().hasHeightForWidth())
        self.widget_5.setSizePolicy(sizePolicy)
        self.widget_5.setMinimumSize(QtCore.QSize(0, 0))
        self.widget_5.setMaximumSize(QtCore.QSize(200, 120))
        self.widget_5.setObjectName("widget_5")
        self.verticalLayout_3 = QtWidgets.QVBoxLayout(self.widget_5)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.widget_3 = QtWidgets.QWidget(self.widget_5)
        self.widget_3.setMaximumSize(QtCore.QSize(150, 40))
        self.widget_3.setObjectName("widget_3")
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout(self.widget_3)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.label = QtWidgets.QLabel(self.widget_3)
        self.label.setObjectName("label")
        self.horizontalLayout_2.addWidget(self.label)
        self.lineEdit_login_id = QtWidgets.QLineEdit(self.widget_3)
        self.lineEdit_login_id.setObjectName("lineEdit_login_id")
        self.horizontalLayout_2.addWidget(self.lineEdit_login_id)
        self.verticalLayout_3.addWidget(self.widget_3)
        self.widget_4 = QtWidgets.QWidget(self.widget_5)
        self.widget_4.setMaximumSize(QtCore.QSize(150, 40))
        self.widget_4.setObjectName("widget_4")
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout(self.widget_4)
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.label_2 = QtWidgets.QLabel(self.widget_4)
        self.label_2.setObjectName("label_2")
        self.horizontalLayout_3.addWidget(self.label_2)
        self.lineEdit_login_pw = QtWidgets.QLineEdit(self.widget_4)
        self.lineEdit_login_pw.setEchoMode(QtWidgets.QLineEdit.Password)
        self.lineEdit_login_pw.setObjectName("lineEdit_login_pw")
        self.horizontalLayout_3.addWidget(self.lineEdit_login_pw)
        self.verticalLayout_3.addWidget(self.widget_4)
        self.horizontalLayout_4.addWidget(self.widget_5)
        self.pushButton = QtWidgets.QPushButton(self.widget_6)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.pushButton.sizePolicy().hasHeightForWidth())
        self.pushButton.setSizePolicy(sizePolicy)
        self.pushButton.setMaximumSize(QtCore.QSize(16777215, 60))
        self.pushButton.setObjectName("pushButton")
        self.horizontalLayout_4.addWidget(self.pushButton)
        self.verticalLayout_4.addWidget(self.widget_6)
        spacerItem = QtWidgets.QSpacerItem(20, 377, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.verticalLayout_4.addItem(spacerItem)
        self.horizontalLayout.addWidget(self.widget)
        self.widget_2 = QtWidgets.QWidget(MyForm)
        self.widget_2.setObjectName("widget_2")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.widget_2)
        self.verticalLayout.setObjectName("verticalLayout")
        self.frame = QtWidgets.QFrame(self.widget_2)
        self.frame.setFrameShape(QtWidgets.QFrame.WinPanel)
        self.frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame.setObjectName("frame")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.frame)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.label_3 = QtWidgets.QLabel(self.frame)
        self.label_3.setObjectName("label_3")
        self.verticalLayout_2.addWidget(self.label_3)
        self.label_login_result = QtWidgets.QLabel(self.frame)
        self.label_login_result.setObjectName("label_login_result")
        self.verticalLayout_2.addWidget(self.label_login_result)
        spacerItem1 = QtWidgets.QSpacerItem(20, 156, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.verticalLayout_2.addItem(spacerItem1)
        self.verticalLayout.addWidget(self.frame)
        self.frame_2 = QtWidgets.QFrame(self.widget_2)
        self.frame_2.setMinimumSize(QtCore.QSize(0, 300))
        self.frame_2.setFrameShape(QtWidgets.QFrame.Box)
        self.frame_2.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_2.setObjectName("frame_2")
        self.verticalLayout.addWidget(self.frame_2)
        self.horizontalLayout.addWidget(self.widget_2)

        self.retranslateUi(MyForm)
        QtCore.QMetaObject.connectSlotsByName(MyForm)

    def retranslateUi(self, MyForm):
        _translate = QtCore.QCoreApplication.translate
        MyForm.setWindowTitle(_translate("MyForm", "Form"))
        self.label.setText(_translate("MyForm", "아이디"))
        self.label_2.setText(_translate("MyForm", "비밀번호"))
        self.pushButton.setText(_translate("MyForm", "로그인"))
        self.label_3.setText(_translate("MyForm", "결과"))
        self.label_login_result.setText(_translate("MyForm", "TextLabel"))
