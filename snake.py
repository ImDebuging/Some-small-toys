import random

import pygame,sys
from pygame.math import Vector2

pygame.init()

GREEN = (173,204,96)
DARK_GREEN = (43,51,24)

cell_size = 30
number_of_cells = 25

screen = pygame.display.set_mode((cell_size*number_of_cells,cell_size*number_of_cells))



pygame.display.set_caption("Retro Snake")

clock = pygame.time.Clock()

class Food:#食物类
    def __init__(self):
        self.position = self.generate_random_pos()

    def draw(self):
        food_rect = pygame.Rect(self.position.x * cell_size,self.position.y * cell_size,cell_size,cell_size)
        screen.blit(food_surface,food_rect)

    def generate_random_pos(self):
        x = random.randint(0,number_of_cells-1)
        y = random.randint(0,number_of_cells-1)
        position = Vector2(x,y)
        return position

class Snake:
    def __init__(self):
        self.body = [Vector2(5,9), Vector2(4,9),Vector2(3,9)]
        self.direction = Vector2(1,0)

    def draw(self):
        for pos in self.body:
            snake_rect = pygame.Rect(pos.x*cell_size,pos.y*cell_size,cell_size,cell_size)
            pygame.draw.rect(screen,DARK_GREEN,snake_rect,0,7)

    def update(self):
        #移动的逻辑就是：删除最后一个元素，然后在列表头添加新的元素
        self.body = self.body[:-1]#利用python列表的特性，删除最后一个元素
        self.body.insert(0,self.body[0]+self.direction)





food = Food()
snake = Snake()
food_surface = pygame.image.load("Graphics/food.png")

SNAKE_UPDATE = pygame.USEREVENT
pygame.time.set_timer(SNAKE_UPDATE,200)

while True:
    for event in pygame.event.get():  #点击关闭进行关闭
        if event.type == SNAKE_UPDATE:
            snake.update()
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_UP and snake.direction != Vector2(0,1):
                snake.direction = Vector2(0,-1)
            if event.key ==pygame.K_DOWN and snake.direction != Vector2(0,-1):
                snake.direction = Vector2(0,1)
            if event.key ==pygame.K_LEFT and snake.direction != Vector2(1,0):
                snake.direction = Vector2(-1,0)
            if event.key ==pygame.K_RIGHT and snake.direction != Vector2(-1,0):
                snake.direction = Vector2(1,0)


        screen.fill(GREEN)

        #Drawing
        food.draw()
        snake.draw()
        pygame.display.update()
        clock.tick(60)  #每秒60帧