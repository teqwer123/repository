import sys
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QHBoxLayout, QLabel, QPushButton, QScrollArea

class FoodItem(QWidget):
    def __init__(self, name, price):
        super().__init__()

        self.name_label = QLabel(name)
        self.price_label = QLabel(price)

        layout = QVBoxLayout()
        layout.addWidget(self.name_label)
        layout.addWidget(self.price_label)

        self.setLayout(layout)

class FoodMenu(QWidget):
    def __init__(self):
        super().__init__()

        self.scroll_area = QScrollArea(self)
        self.scroll_area.setWidgetResizable(True)

        self.scrollable_widget = QWidget()
        self.scroll_area.setWidget(self.scrollable_widget)

        self.layout = QVBoxLayout(self.scrollable_widget)

    def add_item(self, name, price):
        food_item = FoodItem(name, price)
        self.layout.addWidget(food_item)

class FoodApp(QWidget):
    def __init__(self):
        super().__init__()

        self.food_menu = FoodMenu()

        add_button = QPushButton("Add Item")
        add_button.clicked.connect(self.on_add_button_clicked)

        layout = QVBoxLayout(self)
        layout.addWidget(self.food_menu)
        layout.addWidget(add_button)

    def on_add_button_clicked(self):
        self.food_menu.add_item("Pizza", "15,000 KRW")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    form = FoodApp()
    form.show()
    sys.exit(app.exec_())
