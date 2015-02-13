import pygame
from pygame.locals import *
import random
import time
pygame.init()

# need to make a random int between -200 and 200 for the pipeTop Y coordinate then use the same value but add 75 on to it for the pipeBottom Y coordinate.

#Variables
frameRate = 20
windowWidth = 700
windowLength = 900
playerX = 150
playerY = 450
movement = 10
startGame = False
score = 0
brownY = 700
brownLength = windowLength - brownY
pipeY = random.randint(-400, 0)
pipe2Y = random.randint(-400, 0)

# Define some colors
white = (255, 255, 255)
black = (0, 0, 0)
LBLUE = (0, 180, 255)

# This class represents the pipes
class Bird(pygame.sprite.Sprite):
    # Constructor. Pass in the picture
    def __init__(self, picture):
        pygame.sprite.Sprite.__init__(self)
        self.image = picture
        self.rect = self.image.get_rect()

class PipeTop(pygame.sprite.Sprite):
    # Constructor. Pass in the picture
    def __init__(self, picture):
        pygame.sprite.Sprite.__init__(self)
        self.image = picture
        self.rect = self.image.get_rect()

    def reset_pos(self):
        self.rect.x = windowWidth
        self.rect.y = pipeY #THIS RANDOM GENERATOR HERE!!!

    # Called each frame
    def update(self):
        # Move block down one pixel
        self.rect.x -= 10
         
        # If block is too far down, reset to top of screen.
        if self.rect.x < -75:
            self.reset_pos()

class PipeBottom(pygame.sprite.Sprite):
    # Constructor. Pass in the picture
    def __init__(self, picture):
        pygame.sprite.Sprite.__init__(self)
        self.image = picture
        self.rect = self.image.get_rect()

    def reset_pos(self):
        self.rect.x = windowWidth
        self.rect.y = pipeY + 600 #THIS RANDOM GENERATOR - 10 HERE!!!

    # Called each frame
    def update(self):
        # Move block down one pixel
        self.rect.x -= 10
         
        # If block is too far down, reset to top of screen.
        if self.rect.x < -75:
            self.reset_pos()

class PipeTop2(pygame.sprite.Sprite):
    # Constructor. Pass in the picture
    def __init__(self, picture):
        pygame.sprite.Sprite.__init__(self)
        self.image = picture
        self.rect = self.image.get_rect()

    def reset_pos(self):
        self.rect.x = windowWidth
        self.rect.y = pipe2Y #THIS RANDOM GENERATOR HERE!!!

    # Called each frame
    def update(self):
        # Move block down one pixel
        self.rect.x -= 10
         
        # If block is too far down, reset to top of screen.
        if self.rect.x < -75:
            self.reset_pos()

class PipeBottom2(pygame.sprite.Sprite):
    # Constructor. Pass in the picture
    def __init__(self, picture):
        pygame.sprite.Sprite.__init__(self)
        self.image = picture
        self.rect = self.image.get_rect()

    def reset_pos(self):
        self.rect.x = windowWidth
        self.rect.y = pipe2Y + 600 #THIS RANDOM GENERATOR - 10 HERE!!!

    # Called each frame
    def update(self):
        # Move block down one pixel
        self.rect.x -= 10
         
        # If block is too far down, reset to top of screen.
        if self.rect.x < -75:
            self.reset_pos()

# Create a screen
size = (windowWidth, windowLength)
screen = pygame.display.set_mode(size)

# This sets the name of the window
pygame.display.set_caption("Flappy Bird")

clock = pygame.time.Clock()

# Before the loop, load the sounds:
click_sound = pygame.mixer.Sound("click.wav")
boom_sound = pygame.mixer.Sound("bigboom.wav")

# Set positions of graphics
background_position = [0,0]
brownBackground_position = [0,brownY]

# Load and set up graphics.
background_image = pygame.image.load("FlappyBackground.png").convert()
background_image = pygame.transform.scale(background_image, (windowWidth, windowLength + 500))

brownBackground_image = pygame.image.load("BrownBackground.png").convert()
brownBackground_image = pygame.transform.scale(brownBackground_image, (windowWidth, brownLength))

player_image = pygame.image.load("FlappyBirdMiddle.png")
player_image = pygame.transform.scale(player_image, (50, 50))

pipeTop_image = pygame.image.load("FlappyPipeTop.png")
pipeTop_image = pygame.transform.scale(pipeTop_image, (75, 450))

pipeBottom_image = pygame.image.load("FlappyPipeBottom.png")
pipeBottom_image = pygame.transform.scale(pipeBottom_image, (75, 500))

pipeTop2_image = pygame.image.load("FlappyPipeTop.png")
pipeTop2_image = pygame.transform.scale(pipeTop2_image, (75, 450))

pipeBottom2_image = pygame.image.load("FlappyPipeBottom.png")
pipeBottom2_image = pygame.transform.scale(pipeBottom2_image, (75, 500))

# List of pipe sprites.
pipe_list = pygame.sprite.Group()

# This is a list of every sprite. All blocks and the player block as well.
all_sprites_list = pygame.sprite.Group()

# Pipe picture variable
# while startGame == True:
pipeTop = PipeTop(pipeTop_image)
pipeTop.rect.x = windowWidth
pipeTop.rect.y = pipeY

pipeBottom = PipeBottom(pipeBottom_image)
pipeBottom.rect.x = windowWidth
pipeBottom.rect.y = pipeY + 600

pipeTop2 = PipeTop2(pipeTop2_image)
pipeTop2.rect.x = windowWidth + 400
pipeTop2.rect.y = pipe2Y

pipeBottom2 = PipeBottom2(pipeBottom2_image)
pipeBottom2.rect.x = windowWidth + 400
pipeBottom2.rect.y = pipe2Y + 600
# Add sprites to list
pipe_list.add(pipeTop)
all_sprites_list.add(pipeTop)
pipe_list.add(pipeBottom)
all_sprites_list.add(pipeBottom)

pipe_list.add(pipeTop2)
all_sprites_list.add(pipeTop2)
pipe_list.add(pipeBottom2)
all_sprites_list.add(pipeBottom2)
# Player picture variable
player = Bird(player_image)
# Set the bird starting position
player.rect.x = playerX
player.rect.y = playerY
all_sprites_list.add(player)

done = False

while done == False:
    clock.tick(frameRate)    
    for event in pygame.event.get():
        # When the user hits red x
        if event.type == pygame.QUIT:
            done = True
        else:
            # While the Player hasn't died and he clicks, do this
            if event.type == pygame.MOUSEBUTTONDOWN and player.rect.y < windowLength and player.rect.y > -10:
                startGame = True
                movement = 0
                screen.blit(background_image, background_position)
                all_sprites_list.draw(screen)
                screen.blit(brownBackground_image, brownBackground_position)
                pygame.display.flip()
                movement -= 20
                click_sound.play()
    if pipeTop.rect.x == 0:
        pipeY = random.randint(-400, 0)
    if pipeTop2.rect.x == 0:
        pipe2Y = random.randint(-400, 0)
    # When the Game hasn't been started    
    if startGame == False:
        screen.blit(background_image, background_position)
        all_sprites_list.draw(screen)
        screen.blit(brownBackground_image, brownBackground_position)
        myfont = pygame.font.SysFont("Comic Sans", 45)
        label = myfont.render("Click To Start Game", 1, white)
        screen.blit(label, (200, 200))
        pygame.display.flip()
    # User gets a point
    if pipeTop.rect.x == player.rect.x or pipeTop2.rect.x == player.rect.x:
        score += 1
        #frameRate += 1
    # Game Over Condition
    if player.rect.y > (brownY - 50) or pygame.sprite.spritecollide(player, pipe_list, False):
        screen.blit(background_image, background_position)
        player.rect.y = brownY-50
        all_sprites_list.draw(screen)
        screen.blit(brownBackground_image, brownBackground_position)
        myfont = pygame.font.SysFont("Comic Sans", 45)
        label = myfont.render("Game Over", 1, white)
        screen.blit(label, (250, 200))
        myfont1 = pygame.font.SysFont("Comic Sans", 45)
        label1 = myfont1.render("Score: " + str(score), 1, white)
        screen.blit(label1, (275, 250))
        pygame.display.flip()
        boom_sound.play()
        pygame.time.wait(3000)
        done = True
    # When Game has started, continue to do this
    elif startGame == True:
        player.rect.y += movement
        movement += 3        
        # Copy image to screen:
        screen.blit(background_image, background_position)
        # Copy image to screen:
        all_sprites_list.draw(screen)
        all_sprites_list.update()
        screen.blit(brownBackground_image, brownBackground_position)
        myfont = pygame.font.SysFont("Comic Sans", 60)
        label = myfont.render(str(score), 1, white)
        screen.blit(label, (350, 200))
        pygame.display.flip()
pygame.quit ()
