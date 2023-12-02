import random

import pygame,sys
from pygame.math import Vector2

pygame.init()

title_font = pygame.font.Font(None,60)
score_font = pygame.font.Font(None,40)

GREEN = (173,204,96)
DARK_GREEN = (43,51,24)

OFFSET = 75

cell_size = 20
number_of_cells = 25

screen = pygame.display.set_mode((2*OFFSET + cell_size * number_of_cells,
                                  2*OFFSET +cell_size * number_of_cells))



pygame.display.set_caption("Retro Snake")

clock = pygame.time.Clock()

class Food:#食物类
    def __init__(self):
        self.position = self.generate_random_pos()

    def draw(self):
        food_rect = pygame.Rect(OFFSET + self.position.x * cell_size,OFFSET + self.position.y * cell_size,cell_size,cell_size)
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
        self.add_segment = False
        self.eat_sound = pygame.mixer.Sound("Sounds/eat.mp3")
        self.wall_hit_sound = pygame.mixer.Sound("Sounds/wall.mp3")

    def draw(self):
        for pos in self.body:
            snake_rect = pygame.Rect(OFFSET + pos.x*cell_size,OFFSET + pos.y*cell_size,cell_size,cell_size)
            pygame.draw.rect(screen,DARK_GREEN,snake_rect,0,7)

    def update(self):
        if self.add_segment == True:
            #蛇吃苹果的功能，用add_segment这个变量标记，吃完将标记重置
            self.body.insert(0,self.body[0]+self.direction)
            self.add_segment = False
        else:
            # 移动的逻辑就是：删除最后一个元素，然后在列表头添加新的元素
            self.body = self.body[:-1]  # 利用python列表的特性，删除最后一个元素
            self.body.insert(0, self.body[0] + self.direction)

    def reset(self):
        self.body = [Vector2(5,9), Vector2(4,9),Vector2(3,9)]
        self.direction = Vector2(1, 0)

class Game:
    def __init__(self):
        self.snake = Snake()
        self.food = Food()
        self.state = "RUNNING"
        self.score = 0

    def draw(self):
        self.food.draw()
        self.snake.draw()

    def update(self):
        if self.state == "RUNNING":
            self.snake.update()
            self.check_collision_with_food()
            self.check_collision_with_edge()
            self.check_collsion_with_tail()

    def check_collision_with_food(self):#完成了蛇吃苹果的功能
        for pos in self.snake.body:
            if pos == self.food.position:
                new_pos = self.food.generate_random_pos()
                while new_pos in self.snake.body:
                    new_pos = self.food.generate_random_pos()
                self.food.position = new_pos
                self.snake.add_segment = True
                self.score += 1
                self.snake.eat_sound.play()

    def check_collision_with_edge(self):
        if self.snake.body[0].x == -1 or self.snake.body[0].x ==number_of_cells or self.snake.body[0].y == -1 or self.snake.body[0].y ==number_of_cells:
            self.snake.wall_hit_sound.play()
            self.game_over()

    def check_collsion_with_tail(self):
        num_of_head = self.snake.body.count(self.snake.body[0])
        if num_of_head > 1:
            self.game_over()


    def game_over(self):
        self.snake.reset()
        self.food.position = self.food.generate_random_pos()
        self.state = "STOPPED"
        self.score = 0

game = Game()
food_surface = pygame.image.load("Graphics/food.png")

SNAKE_UPDATE = pygame.USEREVENT
pygame.time.set_timer(SNAKE_UPDATE,200)

while True:
    for event in pygame.event.get():  #点击关闭进行关闭
        if event.type == SNAKE_UPDATE:
            game.update()
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

        if event.type == pygame.KEYDOWN:
            if game.state =="STOPPED" and event.key == pygame.K_r:
                game.state = "RUNNING"
            if event.key == pygame.K_UP and game.snake.direction != Vector2(0,1):
                game.snake.direction = Vector2(0,-1)
            if event.key ==pygame.K_DOWN and game.snake.direction != Vector2(0,-1):
                game.snake.direction = Vector2(0,1)
            if event.key ==pygame.K_LEFT and game.snake.direction != Vector2(1,0):
                game.snake.direction = Vector2(-1,0)
            if event.key ==pygame.K_RIGHT and game.snake.direction != Vector2(-1,0):
                game.snake.direction = Vector2(1,0)


        screen.fill(GREEN)

        #Drawing
        game.draw()
        pygame.draw.rect(screen,DARK_GREEN,
                         (OFFSET-5,OFFSET-5,cell_size*number_of_cells+10,cell_size*number_of_cells+10),5)
        title_surface = title_font.render("Retro Snake",True,DARK_GREEN)
        score_surface = score_font.render("Score:"+str(game.score),True,DARK_GREEN)
        screen.blit(title_surface,(OFFSET - 5,20))
        screen.blit(score_surface,(OFFSET-5,OFFSET+cell_size*number_of_cells+10))
        pygame.display.update()
        clock.tick(60)  #每秒60帧