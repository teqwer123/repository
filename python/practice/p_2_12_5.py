
from p_2_12_4 import Car

class SportCar(Car):
    def __init__(self):
        super().__init__()
        self.max_speed = 200

    def speed_up(self):
        self.speed += 45
        if self.speed > self.max_speed:
            self.speed = self.max_speed
        print('현재 속도 :',self.speed)

    def speed_down(self):
        self.speed -= 45
        if self.speed < 0:
            self.speed = 0
        print('현재 속도 :',self.speed)

class Truck(Car):
    def __init__(self):
        super().__init__()
        self.max_speed = 100

    def speed_up(self):
        self.speed += 15
        if self.speed > self.max_speed:
            self.speed = self.max_speed
        print('현재 속도 :',self.speed)

    def speed_down(self):
        self.speed -= 15
        if self.speed < 0:
            self.speed = 0
        print('현재 속도 :',self.speed)


sportcar = SportCar()
truck = Truck()

sportcar.speed_up()
sportcar.speed_up()
sportcar.speed_up()
sportcar.speed_up()
sportcar.speed_up()
sportcar.speed_up()
sportcar.speed_up()
sportcar.speed_up()
sportcar.speed_up()
sportcar.speed_up()
sportcar.speed_up()

sportcar.speed_down()
sportcar.speed_down()
sportcar.speed_down()
sportcar.speed_down()
sportcar.speed_down()
sportcar.speed_down()
sportcar.speed_down()
sportcar.speed_down()
sportcar.speed_down()
sportcar.speed_down()
sportcar.speed_down()
sportcar.speed_down()

truck.speed_up()
truck.speed_up()
truck.speed_up()
truck.speed_up()
truck.speed_up()
truck.speed_up()
truck.speed_up()
truck.speed_up()
truck.speed_up()
truck.speed_up()
truck.speed_up()
truck.speed_up()
truck.speed_up()

truck.speed_down()
truck.speed_down()
truck.speed_down()
truck.speed_down()
truck.speed_down()
truck.speed_down()
truck.speed_down()
truck.speed_down()
truck.speed_down()
truck.speed_down()
truck.speed_down()
truck.speed_down()
truck.speed_down()
truck.speed_down()
truck.speed_down()
truck.speed_down()