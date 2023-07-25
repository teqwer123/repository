import sys

from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QApplication

from converted_ui import Ui_MyForm


class MySuperForm(QtWidgets.QWidget, Ui_MyForm):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        # 나의 실제 관리자 아이디 / 비밀번호
        self.admin_login_id = "park"
        self.admin_login_pw = "1234"

        # lineEdit 에 작성된 테스트를 콘솔로 찍어보기
        # 버튼에 트리거(trigger) 설정
        self.pushButton.clicked.connect(self.show_text)
        self.lineEdit_login_pw.returnPressed.connect(self.show_text)

    def show_text(self):
        login_id = self.lineEdit_login_id.text()
        login_pw = self.lineEdit_login_pw.text()
        print(login_id, login_pw)
        if (self.admin_login_id == login_id) and (self.admin_login_pw == login_pw):
            self.label_login_result.setText("로그인 성공")
        else:
            self.label_login_result.setText("로그인 실패")


if __name__ == '__main__':
    myapp = QApplication(sys.argv)
    myform = MySuperForm()
    myform.show()

    def show_error_message(message, traceback):
        msg_box = QtWidgets.QMessageBox()
        msg_box.setIcon(QtWidgets.QMessageBox.Critical)
        msg_box.setWindowTitle("Error")
        msg_box.setText(message)
        msg_box.exec()
        traceback.print_exc()
    sys.excepthook = lambda exctype, value, traceback: show_error_message(str(value), traceback)

    myapp.exec()