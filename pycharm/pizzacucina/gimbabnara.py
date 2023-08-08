import sys
from PyQt5 import QtWidgets
from PyQt5.QtGui import QPixmap, QIcon
from PyQt5.QtWidgets import QApplication, QWidget, QDialog, QLabel, QVBoxLayout
from UI_Gimbabnara import Ui_Form
from UI_gimbabmenu import Ui_menu
from UI_cart import Ui_cart
from UI_order import Ui_order
from UI_addmenu import Ui_addmenu
from UI_end import Ui_end

cart_list = []
cart_total = 0
d=[0]
e=[0]
class ginbabmenu(QDialog, QWidget, Ui_menu): #메뉴선택 화면
    def __init__(self, i):
        super(ginbabmenu, self).__init__()
        self.initUI()
        self.i = i
        self.pixmap = None
        self.setup()
        self.setWindowIcon(QIcon('main.png'))
        self.show()  # 두번째창 실행
        self.btn_plus.clicked.connect(self.plus)
        self.btn_minus.clicked.connect(self.minus)
        self.btn_pluscart.clicked.connect(self.cart)
        self.name=""
        self.price=""

    def setup(self):   # 라벨에 이미지 설정
        if self.i == "1":
            self.pixmap = QPixmap("김밥메뉴.jpg")
            self.image = "카트_김밥.jpg"
            self.btn_pluscart.setText("2500원 담기")
            self.menu="김밥"
        elif self.i == "2":
            self.pixmap = QPixmap("참치김밥메뉴.jpg")
            self.image = "카트_참치김밥.jpg"
            self.btn_pluscart.setText("3500원 담기")
        elif self.i == "3":
            self.pixmap = QPixmap("새우김밥.jpg")
            self.image = "카트_새우김밥.jpg"
            self.btn_pluscart.setText("3500원 담기")
        elif self.i == "4":
            self.pixmap = QPixmap("돈가스김밥.jpg")
            self.image = "카트_돈가스김밥.jpg"
            self.btn_pluscart.setText("3500원 담기")
        elif self.i == "5":
            self.pixmap = QPixmap("불고기김밥.jpg")
            self.image = "카트_불고기김밥.jpg"
            self.btn_pluscart.setText("4000원 담기")
        elif self.i == "6":
            self.pixmap = QPixmap("쫄면.jpg")
            self.image = "카트_쫄면.jpg"
            self.btn_pluscart.setText("6500원 담기")
        elif self.i == "7":
            self.pixmap = QPixmap("떡볶이.jpg")
            self.image = "카트_떡볶이.jpg"
            self.btn_pluscart.setText("4500원 담기")
        elif self.i == "8":
            self.pixmap = QPixmap("라볶이.jpg")
            self.image = "카트_라볶이.jpg"
            self.btn_pluscart.setText("4500원 담기")
        elif self.i == "9":
            self.pixmap = QPixmap("우동.jpg")
            self.image = "카트_우동.jpg"
            self.btn_pluscart.setText("4500원 담기")
        elif self.i == "10":
            self.pixmap = QPixmap("오뎅.jpg")
            self.image = "카트_오뎅.jpg"
            self.btn_pluscart.setText("4500원 담기")
        elif self.i == "11":
            self.pixmap = QPixmap("수제비.jpg")
            self.image = "카트_수제비.jpg"
            self.btn_pluscart.setText("6500원 담기")
        elif self.i == "12":
            self.pixmap = QPixmap("칼국수.jpg")
            self.image = "카트_칼국수.jpg"
            self.btn_pluscart.setText("6500원 담기")
        elif self.i == "13":
            self.pixmap = QPixmap("비빔국수.jpg")
            self.image = "카트_비빔국수.jpg"
            self.btn_pluscart.setText("6500원 담기")
        elif self.i == "14":
            self.pixmap = QPixmap("돈가스.jpg")
            self.image = "카트_돈가스.jpg"
            self.btn_pluscart.setText("7000원 담기")
        elif self.i == "15":
            self.pixmap = QPixmap("치즈돈가스.jpg")
            self.image = "카트_치즈돈가스.jpg"
            self.btn_pluscart.setText("7500원 담기")
        elif self.i == "16":
            self.pixmap = QPixmap("고구마돈가스.jpg")
            self.image = "카트_고구마돈가스.jpg"
            self.btn_pluscart.setText("7500원 담기")
        elif self.i == "17":
            self.pixmap = QPixmap("김치볶음밥.jpg")
            self.image = "카트_김볶.jpg"
            self.btn_pluscart.setText("6500원 담기")
        elif self.i == "18":
            self.pixmap = QPixmap("새우볶음밥.jpg")
            self.image = "카트_새볶.jpg"
            self.btn_pluscart.setText("7000원 담기")
        elif self.i == "19":
            self.pixmap = QPixmap("비빔밥.jpg")
            self.image = "카트_비빔밥.jpg"
            self.btn_pluscart.setText("6500원 담기")
        elif self.i == "20":
            self.pixmap = QPixmap("제육덮밥.jpg")
            self.image = "카트_제육.jpg"
            self.btn_pluscart.setText("7000원 담기")
        elif self.i == "21":
            self.pixmap = QPixmap("오징어덮밥.jpg")
            self.image = "카트_오징어.jpg"
            self.btn_pluscart.setText("7000원 담기")
        elif self.i == "22":
            self.pixmap = QPixmap("불고기덮밥.jpg")
            self.image = "카트_불덮.jpg"
            self.btn_pluscart.setText("7000원 담기")
        elif self.i == "23":
            self.pixmap = QPixmap("오므라이스.jpg")
            self.image = "카트_오므.jpg"
            self.btn_pluscart.setText("7500원 담기")
        elif self.i == "24":
            self.pixmap = QPixmap("김치찌개.jpg")
            self.image = "카트_김찌.jpg"
            self.btn_pluscart.setText("7000원 담기")
        elif self.i == "25":
            self.pixmap = QPixmap("된장찌개.jpg")
            self.image = "카트_된찌.jpg"
            self.btn_pluscart.setText("6500원 담기")
        elif self.i == "26":
            self.pixmap = QPixmap("순두부찌개.jpg")
            self.image = "카트_순찌.jpg"
            self.btn_pluscart.setText("6500원 담기")
        elif self.i == "27":
            self.pixmap = QPixmap("부대찌개.jpg")
            self.image = "카트_부찌.jpg"
            self.btn_pluscart.setText("7500원 담기")
        elif self.i == "28":
            self.pixmap = QPixmap("뚝불.jpg")
            self.image = "카트_뚝불.jpg"
            self.btn_pluscart.setText("8000원 담기")
        self.photo1.setPixmap(self.pixmap)

    def plus(self):
        b = int(self.label_number.text()) + 1
        self.label_number.setText(str(b))
        if self.i == "1" :
            c = b * 2500
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "2" :
            c = b * 3500
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "3" :
            c = b * 3500
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "4" :
            c = b * 3500
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "5" :
            c = b * 4000
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "6" :
            c = b * 6500
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "7" :
            c = b * 4500
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "8" :
            c = b * 4500
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "9" :
            c = b * 4500
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "10" :  #오뎅
            c = b * 4500
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "11" :
            c = b * 6500
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "12" :
            c = b * 6500
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "13" :
            c = b * 6500
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "14" :  #돈가스
            c = b * 7000
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "15" :
            c = b * 7500
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "16" :
            c = b * 7500
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "17" :
            c = b * 6500
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "18" :
            c = b * 7000
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "19" : #비빔밥
            c = b * 6500
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "20" :
            c = b * 7000
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "21" :
            c = b * 7000
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "22" :
            c = b * 7000
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "23" :
            c = b * 7500
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "24" :
            c = b * 7000
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "25" :
            c = b * 6500
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "26" :
            c = b * 6500
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "27" :
            c = b * 7500
            self.btn_pluscart.setText(f'{c}원 담기')
        if self.i == "28" :
            c = b * 8000
            self.btn_pluscart.setText(f'{c}원 담기')

    def minus(self):
        b = int(self.label_number.text()) - 1
        if self.i == "1":
            c = b * 2500
        if self.i == "2":
            c = b * 3500
        if self.i == "3":
            c = b * 3500
        if self.i == "4":
            c = b * 3500
        if self.i == "5":
            c = b * 4000
        if self.i == "6":
            c = b * 6500
        if self.i == "7":
            c = b * 4500
        if self.i == "8":
            c = b * 4500
        if self.i == "9":
            c = b * 4500
        if self.i == "10":  # 오뎅
            c = b * 4500
        if self.i == "11":
            c = b * 6500
        if self.i == "12":
            c = b * 6500
        if self.i == "13":
            c = b * 6500
        if self.i == "14":  # 돈가스
            c = b * 7000
        if self.i == "15":
            c = b * 7500
        if self.i == "16":
            c = b * 7500
        if self.i == "17":
            c = b * 6500
        if self.i == "18":
            c = b * 7000
        if self.i == "19":  # 비빔밥
            c = b * 6500
        if self.i == "20":
            c = b * 7000
        if self.i == "21":
            c = b * 7000
        if self.i == "22":
            c = b * 7000
        if self.i == "23":
            c = b * 7500
        if self.i == "24":
            c = b * 7000
        if self.i == "25":
            c = b * 6500
        if self.i == "26":
            c = b * 6500
        if self.i == "27":
            c = b * 7500
        if self.i == "28":
            c = b * 8000

        if int(b) >= 1:
            self.label_number.setText(str(b))
            self.btn_pluscart.setText(f'{c}원 담기')

    def initUI(self):
        self.setupUi(self)
        self.back_btn.clicked.connect(self.back)

    def cart(self):
        if self.i == "1":
            self.name="김밥"
            self.price='2500'
        if self.i == "2":
            self.name="참치김밥"
            self.price='3500'
        if self.i == "3":
            self.name="새우김밥"
            self.price='3500'
        if self.i == "4":
            self.name="돈가스김밥"
            self.price='3500'
        if self.i == "5":
            self.name="불고기김밥"
            self.price='4000'
        if self.i == "6":
            self.name="쫄면"
            self.price='6500'
        if self.i == "7":
            self.name="떡볶이"
            self.price='4500'
        if self.i == "8":
            self.name="라볶이"
            self.price='4500'
        if self.i == "9":
            self.name="우동"
            self.price='4500'
        if self.i == "10":
            self.name="오뎅"
            self.price='4500'
        if self.i == "11":
            self.name="손수제비"
            self.price='6500'
        if self.i == "12":
            self.name="칼국수"
            self.price='6500'
        if self.i == "13":
            self.name="비빔국수"
            self.price='6500'
        if self.i == "14":
            self.name="돈가스"
            self.price='7000'
        if self.i == "15":
            self.name="치즈돈가스"
            self.price='7500'
        if self.i == "16":
            self.name="고구마돈가스"
            self.price='7500'
        if self.i == "17":
            self.name="김치볶음밥"
            self.price='6500'
        if self.i == "18":
            self.name="새우볶음밥"
            self.price='7000'
        if self.i == "19":
            self.name="비빔밥"
            self.price='6500'
        if self.i == "20":
            self.name="제육덮밥"
            self.price='7000'
        if self.i == "21":
            self.name="오징어덮밥"
            self.price='7000'
        if self.i == "22":
            self.name="불고기덮밥"
            self.price='7000'
        if self.i == "23":
            self.name="야채오므라이스"
            self.price='7500'
        if self.i == "24":
            self.name="김치찌개"
            self.price='7000'
        if self.i == "25":
            self.name="된장찌개"
            self.price='6500'
        if self.i == "26":
            self.name="순두부찌개"
            self.price='6500'
        if self.i == "27":
            self.name="부대찌개"
            self.price='7500'
        if self.i == "28":
            self.name="뚝배기불고기"
            self.price='8000'

        self.total=int(self.label_number.text())*int(self.price)
        a=[self.name, self.image, self.price, str(self.total)]
        cart_list.append(a)
        self.close()

    def back(self):
        self.close()  # 창 닫기

class ItemWidget(QtWidgets.QWidget, Ui_addmenu):
    def __init__(self, i, cart_instance): # 디폴트값
        super(ItemWidget, self).__init__()
        self.cart_instance=cart_instance
        self.pixmap = None
        self.setupUi(self)
        self.i = i
        self.set()

        self.pushButton.clicked.connect(lambda state: self.remove_widget(i))

    def set(self):
        self.picture = cart_list[self.i][1]
        self.pixmap = QPixmap(self.picture)
        # 라벨에 이미지 설정
        self.menuname.setText(cart_list[self.i][0])
        self.menuimage.setPixmap(self.pixmap)
        self.cost.setText(f'{cart_list[self.i][2]}원')
        self.sum.setText(f'합계 :     {cart_list[self.i][3]}원')

    def remove_widget(self, i):
        for j in range(len(cart_list)):
            if cart_list[j][0]==self.menuname.text():
                self.i=j
        self.setParent(None)
        self.deleteLater()
        d[0] = int(self.cart_instance.label_11.text()[:-1])-int(cart_list[self.i][2])
        self.cart_instance.label_11.setText(f'{d[0]}원')
        e[0] = d[0]-3500
        self.cart_instance.label_10.setText(f'{e[0]}원')
        self.cart_instance.total.setText(f'{d[0]}원')

        del cart_list[self.i]


    # def delete_item(self):
    #     # 아이템 삭제 로직
    #     del cart_list[self.i]
    #     self.cart_instance.remove_item_widget(self)

class Cart(QDialog, QWidget, Ui_cart): #장바구니 화면
    def __init__(self):
        super(Cart, self).__init__()
        self.setWindowIcon(QIcon('main.png'))
        self.initUI()
        self.show()  # 장바구니창 실행
        self.total1 = 0
        self.btn_order.clicked.connect(lambda: self.button_Order())

        for i in range(len(cart_list)):
            self.add_widget(i)
            self.total1 += int(cart_list[i][3])
        self.label_10.setText(f'{str(self.total1)}원')
        self.label_11.setText(f'{str(self.total1+3500)}원')
        self.total.setText(self.label_11.text())

    def add_widget(self, i):
        if self.addWidget.layout() is None:
            vbox = QVBoxLayout(self.addWidget)
            self.addWidget.setLayout(vbox)
        vbox = self.addWidget.layout()
        Item_widget = ItemWidget(i, self)  # self (현재 Cart 클래스의 인스턴스)를 전달
        vbox.addWidget(Item_widget)


    def initUI(self):
        self.setupUi(self)
        self.back_btn.clicked.connect(self.back)

    def button_Order(self):
        #self.hide()  # 메인 윈도우 숨김
        self.order = Order()
        self.order.exec()  # 주문하기창 닫을때까지 기다림
        #self.show()  # 주문하기창 닫으면 다시 첫 번째 창 보여짐

    def back(self):
        self.close()  # 창 닫기


class Order(QDialog, QWidget, Ui_order): # 주문하기 화면
    def __init__(self):
        super(Order, self).__init__()
        self.setWindowIcon(QIcon('main.png'))
        self.initUI()
        self.total1 = 0
        self.show()

        self.pushButton.clicked.connect(lambda: self.button_End())

        for i in range(len(cart_list)):
            self.total1 += int(cart_list[i][3])
        self.label_6.setText(f'                    {e[0]}원')
        self.label_8.setText(f'                    {d[0]}원')
        self.label_5.setText(f'     {d[0]}원')

    def initUI(self):
        self.setupUi(self)
        self.back_btn.clicked.connect(self.back)

    def button_End(self):
        self.hide()  # 메인 윈도우 숨김
        self.end = End()
        self.end.exec()  # 장바구니창 닫을때까지 기다림
        self.show()  # 장바구니창 닫으면 다시 첫 번째 창 보여짐

    def back(self):
        self.close()  # 창 닫기

class End(QDialog, QWidget, Ui_end):
    def __init__(self):
        super(End, self).__init__()
        self.setWindowIcon(QIcon('main.png'))
        self.initUI()
        self.show()

    def initUI(self):
        self.setupUi(self)

class MyForm(QtWidgets.QWidget, Ui_Form): #첫번째 화면
    def __init__(self):
        super().__init__()
        self.setWindowIcon(QIcon('main.png'))
        self.setupUi(self)
        self.gimbab_btn.clicked.connect(lambda: self.button_Second("1"))
        self.tunagimbab_btn.clicked.connect(lambda: self.button_Second("2"))
        self.shrimp_btn.clicked.connect(lambda: self.button_Second("3"))
        self.dongimbab_btn.clicked.connect(lambda: self.button_Second("4"))
        self.bulgimbab_btn.clicked.connect(lambda: self.button_Second("5"))
        self.zzol_btn.clicked.connect(lambda: self.button_Second("6"))
        self.ttok_btn.clicked.connect(lambda: self.button_Second("7"))
        self.la_btn.clicked.connect(lambda: self.button_Second("8"))
        self.udong_btn.clicked.connect(lambda: self.button_Second("9"))
        self.od_btn.clicked.connect(lambda: self.button_Second("10"))
        self.suje_btn.clicked.connect(lambda: self.button_Second("11"))
        self.kal_btn.clicked.connect(lambda: self.button_Second("12"))
        self.bi_btn.clicked.connect(lambda: self.button_Second("13"))
        self.don_dtn.clicked.connect(lambda: self.button_Second("14"))
        self.chdon_btn.clicked.connect(lambda: self.button_Second("15"))
        self.godon_btn.clicked.connect(lambda: self.button_Second("16"))
        self.kimbok_btn.clicked.connect(lambda: self.button_Second("17"))
        self.shbok_btn.clicked.connect(lambda: self.button_Second("18"))
        self.bibim_btn.clicked.connect(lambda: self.button_Second("19"))
        self.je_btn.clicked.connect(lambda: self.button_Second("20"))
        self.oj_btn.clicked.connect(lambda: self.button_Second("21"))
        self.buldup_btn.clicked.connect(lambda: self.button_Second("22"))
        self.om_btn.clicked.connect(lambda: self.button_Second("23"))
        self.kimzzi_btn.clicked.connect(lambda: self.button_Second("24"))
        self.dzzi_btn.clicked.connect(lambda: self.button_Second("25"))
        self.sun_btn.clicked.connect(lambda: self.button_Second("26"))
        self.budae_btn.clicked.connect(lambda: self.button_Second("27"))
        self.ttuk_btn.clicked.connect(lambda: self.button_Second("28"))
        self.cart_btn.clicked.connect(lambda :self.button_Cart())

    def button_Second(self, i):
        self.hide()  # 메인 윈도우 숨김
        second = ginbabmenu(i)
        second.exec()  # 두번째창 닫을때까지 기다림
        self.show()  # 두번째창 닫으면 다시 첫 번째 창 보여짐

    def button_Cart(self):
        self.hide()  # 메인 윈도우 숨김
        self.cart = Cart()
        self.cart.exec()  # 장바구니창 닫을때까지 기다림
        self.show()  # 장바구니창 닫으면 다시 첫 번째 창 보여짐


def show_error_message(message, traceback):
    msg_box = QtWidgets.QMessageBox()
    msg_box.setIcon(QtWidgets.QMessageBox.Critical)
    msg_box.setWindowTitle("Error")
    msg_box.setText(message)
    msg_box.exec()
    traceback.print_exc()


if __name__ == '__main__':
    myapp = QApplication(sys.argv)
    myform = MyForm()
    myform.show()
    sys.excepthook = lambda exctype, value, traceback: show_error_message(str(value), traceback)
    sys.exit(myapp.exec())