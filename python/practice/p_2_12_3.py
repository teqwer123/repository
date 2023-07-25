class Character(object):
    def __init__(self):
        self.life = 1000

    def attacked(self):
        self.life -= 10
        print("공격받음! 생명력 =", self.life)

    def attack(self):
        print("공격!")


class Warrior(Character):

    def __init__(self):
        super(Warrior, self).__init__()
        self.strength = 15
        self.intelligence = 5

    def attack(self):
        print("육탄 공격!")

    def attacked(self):
        self.life -=5
        print("공격받음! 생명력 =",self.life)

class Wizard(Character):

    def __init__(self):
        super(Wizard, self).__init__()
        self.strength = 5
        self.intelligence = 15

    def attack(self):
        print("마법 공격!")

    def attacked(self):
        self.life -= 7
        print("공격받음! 생명력 =",self.life)


a = Warrior()

b = Wizard()

a.attacked()

b.attacked()