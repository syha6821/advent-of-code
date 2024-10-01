class Santa:
    def __init__(self):
        self.x = 0
        self.y = 0

    def move(self,direction):
        if direction == '<':
            self.x = self.x - 1
        if direction == '^':
            self.y = self.y + 1
        if direction == '>':
            self.x = self.x + 1
        if direction == 'v':
            self.y = self.y - 1

    def location(self):
        return (self.x,self.y)
