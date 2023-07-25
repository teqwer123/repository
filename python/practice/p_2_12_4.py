class Car():
    max_speed = None
    speed = None
    def __init__(self):
        self.max_speed = 160
        self.speed = 0
        print('최고 속도 :',self.max_speed)
        print('현재 속도 :',self.speed)

    def speed_up(self):
        self.speed += 20
        if self.speed >self.max_speed:
            self.speed = self.max_speed
        print('최고 속도 :',self.max_speed)
        print('현재 속도 :',self.speed)

    def speed_down(self):
        self.speed -= 20
        if self.speed < 0:
            self.speed = 0
        print('최고 속도 :',self.max_speed)
        print('현재 속도 :',self.speed)

if __name__ == '__main__':
    a = Car()

    a.speed_up()
    a.speed_up()
    a.speed_up()
    a.speed_up()
    a.speed_up()
    a.speed_up()
    a.speed_up()
    a.speed_up()
    a.speed_up()
    a.speed_up()
    a.speed_up()
    a.speed_up()
    a.speed_up()
    a.speed_up()

    a.speed_down()
    a.speed_down()
    a.speed_down()
    a.speed_down()
    a.speed_down()
    a.speed_down()
    a.speed_down()
    a.speed_down()
    a.speed_down()
    a.speed_down()
    a.speed_down()
    a.speed_down()
    a.speed_down()