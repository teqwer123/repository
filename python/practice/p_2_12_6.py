class Student_info():
    no = None
    name = None
    math = None
    english = None
    def __init__(self,no,name,math,english):
        self.no = no
        self.name = name
        self.math = math
        self.english = english

    def avg(self):
        print('평균성적: ',(self.math+self.english)/2)

    def __getitem__(self, key):

    def __str__(self):
        return "[for str]"+self.name