import pygame
from pygame.locals import *
import random
import time
pygame.init()

#Variables
frameRate = 20
windowWidth = 1000
windowLength = 800
score = 0
playerX = 20
playerY = 400
startGame = False
global HORIZ_MOV_INCR
HORIZ_MOV_INCR = 10 #speed of movement

# Define some colors
white = (255, 255, 255)
black = (0, 0, 0)
LBLUE = (0, 180, 255)

class Crate(pygame.sprite.Sprite):
    def __init__(self, x, y, boxPicture):
        self.x = x
        self.y = y
        pygame.sprite.Sprite.__init__(self)
        self.image = boxPicture
        self.rect = self.image.get_rect()
        self.rect.topleft = [self.x, self.y]
        self.crate_break = [cratebreak1,cratebreak2,cratebreak3,cratebreak4,
                            cratebreak5,cratebreak6]
        self.frame = 0
        
    def breaking(self):
        k = 0
        while k < 6:
            self.image = self.crate_break[k]
            box_list.draw(screen)
            sprite_list.draw(screen)
            pygame.display.flip()
            pygame.time.wait(15)
            k += 1
        
# Crash Bandicoot
class Crash(pygame.sprite.Sprite):
    # Constructor. Pass in the picture
    def __init__(self, x, y):
        pygame.sprite.Sprite.__init__(self)
        self.movy = 0
        self.movx = 0
        self.x = x
        self.y = y
        self.image = run4
        self.rect = self.image.get_rect()
        self.run_left = [leftrun1,leftrun2,leftrun3,leftrun4,
                         leftrun5,leftrun6,leftrun7,leftrun8]
        self.run_right = [run1,run2,run3,run4,run5,run6,run7,run8]
        self.spin = [spin1,spin2,spin3,spin4,spin5,spin6,spin7,spin8]
        self.jump = [jump1,jump2,jump3,jump4,jump5,jump6,jump7,jump8,jump9]
        self.direction = "right"
        self.rect.topleft = [x, y]
        self.frame = 0

    def update(self, jump, left, right, spin):

        if jump and pygame.sprite.spritecollide(player, all_boxes, False):
            #jump = False
            self.movy -= 50

            



                
        if left:
            self.direction = "left"
            self.movx = -HORIZ_MOV_INCR
            if not pygame.sprite.spritecollide(player, box_list, False):
                self.frame += 1
                self.image = self.run_left[self.frame]
                if self.frame == 7: self.frame = 0



        if right:
            self.direction = "right"
            self.movx = +HORIZ_MOV_INCR
            if not pygame.sprite.spritecollide(player, box_list, False):
                self.frame += 1
                self.image = self.run_right[self.frame]
                if self.frame == 7: self.frame = 0


        if spin:
            if not pygame.sprite.spritecollide(player, box_list, False):
                self.frame += 1
                self.image = self.spin[self.frame]
                if self.frame == 7: self.frame = 0
            else:
                woodenBox.breaking()
                woodenBox.kill()

        if not (left or right or spin or jump):
            self.movx = 0
            self.image = run4 # when left or right is not pressed change to run4.png

        self.rect.right += self.movx
        self.rect.bottom += self.movy

        if not pygame.sprite.spritecollide(player, all_boxes, False) and self.movy < 50:
            self.movy += 10
        else:
            self.movy = 0
            
        
# Create a screen
size = (windowWidth, windowLength)
screen = pygame.display.set_mode(size)

# This sets the name of the window
pygame.display.set_caption("Crash Bandicoot")

clock = pygame.time.Clock()

# Set positions of graphics
background_position = [0,0]

# Load and set up graphics.
welcome_background_image = pygame.image.load("crashBackgroundStart.png").convert()
welcome_background_image = pygame.transform.scale(welcome_background_image, (windowWidth, windowLength))

background_image = pygame.image.load("CrashBackground.png").convert()
background_image = pygame.transform.scale(background_image, (windowWidth, windowLength))

run1 = pygame.transform.scale(pygame.image.load("run1.png"), (80, 150)) 
run2 = pygame.transform.scale(pygame.image.load("run2.png"), (80, 150))
run3 = pygame.transform.scale(pygame.image.load("run3.png"), (80, 150))
run4 = pygame.transform.scale(pygame.image.load("run4.png"), (80, 150))
run5 = pygame.transform.scale(pygame.image.load("run5.png"), (80, 150)) 
run6 = pygame.transform.scale(pygame.image.load("run6.png"), (80, 150)) 
run7 = pygame.transform.scale(pygame.image.load("run7.png"), (80, 150))
run8 = pygame.transform.scale(pygame.image.load("run8.png"), (80, 150))

leftrun1 = pygame.transform.scale(pygame.image.load("leftrun1.png"), (80, 150)) 
leftrun2 = pygame.transform.scale(pygame.image.load("leftrun2.png"), (80, 150))
leftrun3 = pygame.transform.scale(pygame.image.load("leftrun3.png"), (80, 150))
leftrun4 = pygame.transform.scale(pygame.image.load("leftrun4.png"), (80, 150)) 
leftrun5 = pygame.transform.scale(pygame.image.load("leftrun5.png"), (80, 150))
leftrun6 = pygame.transform.scale(pygame.image.load("leftrun6.png"), (80, 150))
leftrun7 = pygame.transform.scale(pygame.image.load("leftrun7.png"), (80, 150))
leftrun8 = pygame.transform.scale(pygame.image.load("leftrun8.png"), (80, 150))

spin1 = pygame.transform.scale(pygame.image.load("spin1.png"), (80, 150))
spin2 = pygame.transform.scale(pygame.image.load("spin2.png"), (80, 150))
spin3 = pygame.transform.scale(pygame.image.load("spin3.png"), (80, 150))
spin4 = pygame.transform.scale(pygame.image.load("spin4.png"), (80, 150))
spin5 = pygame.transform.scale(pygame.image.load("spin5.png"), (80, 150))
spin6 = pygame.transform.scale(pygame.image.load("spin6.png"), (80, 150))
spin7 = pygame.transform.scale(pygame.image.load("spin7.png"), (80, 150))
spin8 = pygame.transform.scale(pygame.image.load("spin8.png"), (80, 150))

jump1 = pygame.transform.scale(pygame.image.load("jump1.png"), (80, 150))
jump2 = pygame.transform.scale(pygame.image.load("jump2.png"), (80, 150))
jump3 = pygame.transform.scale(pygame.image.load("jump3.png"), (80, 150))
jump4 = pygame.transform.scale(pygame.image.load("jump4.png"), (80, 150))
jump5 = pygame.transform.scale(pygame.image.load("jump5.png"), (80, 150))
jump6 = pygame.transform.scale(pygame.image.load("jump6.png"), (80, 150))
jump7 = pygame.transform.scale(pygame.image.load("jump7.png"), (80, 150))
jump8 = pygame.transform.scale(pygame.image.load("jump8.png"), (80, 150))
jump9 = pygame.transform.scale(pygame.image.load("jump9.png"), (80, 150))

metalCrate = pygame.transform.scale(pygame.image.load( "MetalBox.png"), (50, 50))
                                    
woodenCrate = pygame.transform.scale(pygame.image.load("RegularCrate.png"), (50, 50))
cratebreak1 = pygame.transform.scale(pygame.image.load("cratebreak1.png"), (60, 60))
cratebreak2 = pygame.transform.scale(pygame.image.load("cratebreak2.png"), (60, 60))
cratebreak3 = pygame.transform.scale(pygame.image.load("cratebreak3.png"), (70, 60))
cratebreak4 = pygame.transform.scale(pygame.image.load("cratebreak4.png"), (70, 60))
cratebreak5 = pygame.transform.scale(pygame.image.load("cratebreak5.png"), (70, 60))
cratebreak6 = pygame.transform.scale(pygame.image.load("cratebreak6.png"), (70, 60))




# This is a list of every sprite. All blocks and the player block as well.
sprite_list = pygame.sprite.Group()
box_list = pygame.sprite.Group()
all_boxes = pygame.sprite.Group()
#moving_left_sprite_list = pygame.sprite.Group()

# Player picture
player = Crash(playerX, playerY)

# Metal Box varible
i = 0
metalPosY = 525
metalPosX = 0
while i < 20:
    box = Crate(metalPosX, metalPosY, metalCrate)
    metalPosX += 50
    all_boxes.add(box)
    #box_list.add(box)
    sprite_list.add(box)
    i += 1

# Wooden Box
j = 0
woodenPosX = 500
woodenPosY = 475
woodenBox = Crate(woodenPosX, woodenPosY, woodenCrate)
box_list.add(woodenBox)
all_boxes.add(woodenBox)
#sprite_list.add(woodenBox)


sprite_list.add(player)

left = right = spin = jump = False

done = False

while done == False:
    clock.tick(frameRate)    

    for event in pygame.event.get():
        # When the user hits red x
        if event.type == pygame.QUIT:
            done = True

        if event.type == pygame.KEYDOWN and event.key == pygame.K_RETURN:
            startGame = True

        if event.type == KEYDOWN and event.key == K_UP:
            jump = True
        #if event.type == KEYDOWN and event.key == K_DOWN:
         #   down = True
        if event.type == KEYDOWN and event.key == K_SPACE:
            spin = True
        if event.type == KEYDOWN and event.key == K_LEFT:
            left = True
        if event.type == KEYDOWN and event.key == K_RIGHT:
            right = True

            

        #if event.type == KEYUP and event.key == K_UP:
            #jump = False
        #if event.type == KEYUP and event.key == K_DOWN:
         #   down = False
        if event.type == KEYUP and event.key == K_SPACE:
            spin = False
        if event.type == KEYUP and event.key == K_LEFT:
            left = False
        if event.type == KEYUP and event.key == K_RIGHT:
            right = False

                
        # When the Game hasn't been started    
    if startGame == False:
        screen.blit(welcome_background_image, background_position)
        myfont = pygame.font.SysFont("Comic Sans", 45)
        label = myfont.render("PRESS ENTER TO START GAME", 1, white)
        screen.blit(label, (300, 500))
        pygame.display.flip()
    if startGame == True:
        
        screen.blit(background_image, background_position)
        player.update(jump, left, right, spin)
        box_list.draw(screen)
        sprite_list.draw(screen)
        pygame.display.flip()
        jump = False
pygame.quit ()
