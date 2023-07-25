class triangle():
    b=None
    h=None
    def __init__(self,b,h):
        self.b=b
        self.h=h

    def area(self):
        return (self.b*self.h)/2
    
t = triangle(3,4)
print(t.area())