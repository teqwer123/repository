class square_gidoong():
    a=None
    b=None
    h=None
    def __init__(self,a,b,h):
        self.a=a
        self.b=b
        self.h=h

    def volume(self):
        return self.a*self.b*self.h
    
    def serface(self):
        return ((self.a*self.b)+(self.a*self.h)+(self.b*self.h))*2
    
s = square_gidoong(3,4,5)

print(s.volume())
print(s.serface())