import pygame
import random

class Enemy():
    # Constructor function
    def __init__(self, x, y, speed, size):
        self.x = x
        self.y = y
        self.image = pygame.image.load("../assets/Fish02_A.png")
        self.speed = speed
        self.size = size
        # Create the self.hitbox rectangle in the Enemy class
        self.hitbox = pygame.Rect(self.x, self.y, int(self.size*1.25), self.size)

        # Create the self.hitbox rectangle in the Enemy class
        self.hitbox

        self.image = pygame.transform.scale(self.image, (int(self.size * 1.25), self.size))

        if self.speed < 0:
            self.image = pygame.transform.flip(self.image, True, False)


    def update(self, screen):
        self.x += self.speed
        # Make the self.hitbox move just like the Enemy’s x
        self.hitbox.x += self.speed
        # Draw Enemy’s hitbox onscreen
        # pygame.draw.rect(screen, (255, 0, 255), self.hitbox)
        screen.blit(self.image, (self.x, self.y))

# Start the game
pygame.init()
game_width = 1000
game_height = 650
screen = pygame.display.set_mode((game_width, game_height))
clock = pygame.time.Clock()
running = True

# Add background image
background_image = pygame.image.load("../assets/Scene_A.png")
background_image_2  = pygame.image.load("../assets/Scene_B.png")

# Load player image
player_image = pygame.image.load("../assets/Fish01_A.png")
player_image_2 = pygame.image.load("../assets/Fish01_B.png")
player_eating_image = pygame.image.load("../assets/Fish01_open.png")

# Make some variables for the background animation
bg_animation_timer_max = 25
bg_animation_timer = bg_animation_timer_max
# Make the background animation frame variable
bg_animation_frame = 0

# Create some variables
# Make the player_starting_x variable
player_starting_x = 480
# Make the player_starting_y variable
player_starting_y = 310
# Make the player_starting_size variable
player_starting_size = 30
# Make player_x start as player_starting_x
player_x = player_starting_x
# Make player_y start as player_starting_y
player_y = player_starting_y
# Changed variables of player
player_speed = 20
# Make player_size start as player_starting_size
player_size = player_starting_size
player_inc_size = 10
player_facing_left = False
player_facing_right = True
# Create player's hitbox
player_hitbox = pygame.Rect(player_x, player_y, int(player_size*1.25), player_size)
# Make the player_alive boolean
# Make player_alive start as False
player_alive = False

# Make the player eating timer max variable
player_eating_timer_max = 10
player_eating_timer = 0
# Add the swimming timer max variable
player_swimming_timer_max = 8
# Add the swimming timer variable
player_swimming_timer = player_swimming_timer_max
# Add the swimming frame variable
player_swimming_frame = 0

# Make the score variable
score = -1
# Load a font for the score text
score_font = pygame.font.SysFont("default", 30)
# Make the score_text variable
score_text = score_font.render("Score: " + str(score), 1, (255, 255, 255))
# Load a picture for the play button
play_button_pic = pygame.image.load("../assets/BtnPlayIcon.png")
# Make the play_button_x variable
play_button_x = game_width/2 - play_button_pic.get_width()/2
# Make the play_button_y variable
play_button_y = game_height/2 - play_button_pic.get_height()/2


play_button_y = game_height/2

enemy_timer_max = 50
enemy_timer = enemy_timer_max

enemies = []
# Make the enemies_to_remove array
enemies_to_remove = []

# ***************** Loop Land Below *****************
# Everything under 'while running' will be repeated over and over again
while running:
    # Makes the game stop if the player clicks the X or presses esc
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
            running = False

    keys = pygame.key.get_pressed()

    if keys[pygame.K_RIGHT]:
        player_facing_left = False
        player_facing_right = True
        player_x += player_speed

    if keys[pygame.K_LEFT]:
        player_facing_left = True
        player_facing_right = False
        player_x -= player_speed

    if keys[pygame.K_UP]:
        player_y -= player_speed

    if keys[pygame.K_DOWN]:
        player_y += player_speed

    if keys[pygame.K_SPACE]:
        player_size += player_inc_size

    # Background animation timer
    # Make the timer countdown
    bg_animation_timer -= 1
    # Check to see when the timer reaches 0
    if bg_animation_timer <= 0:
        # When the timer reaches 0, add 1 to the frame
        bg_animation_frame += 1
        # Check to see when the frame goes over 1
        if bg_animation_frame > 1:
            # If the frame goes over 1, reset the frame back to 0
            bg_animation_frame = 0
        # When the timer hits 0, reset it to the timer max
        bg_animation_timer = bg_animation_timer_max

    if bg_animation_frame == 0:
        screen.blit(background_image, (0,0))
    else:
        screen.blit(background_image_2, (0,0))

    enemy_timer -= 1
    if enemy_timer <= 0:
        new_enemy_y = random.randint(0, game_height)
        new_enemy_speed = random.randint(2, 5)
        new_enemy_size = random.randint(player_size/2, player_size*2)
        if random.randint(0,1) == 0:
            enemies.append(Enemy(-new_enemy_size * 2, new_enemy_y, new_enemy_speed, new_enemy_size))
        else:
            enemies.append(Enemy(game_width, new_enemy_y, -new_enemy_speed, new_enemy_size))
        enemy_timer = enemy_timer_max
    
    for enemy in enemies_to_remove:
        enemies.remove(enemy)
    enemies_to_remove = []

    # Update all enemies
    for enemy in enemies:
        enemy.update(screen)

    # In the game loop, check to see if player_alive is True
    if player_alive:
        # Make player_hitbox’s x the same as player_x
        player_hitbox.x = player_x
        # Make player_hitbox’s y the same as player_y
        player_hitbox.y = player_y
        # Make player_hitbox’s width the same as player’s width
        player_hitbox.width = int(player_size) * 1.25
        # Make player_hitbox’s height the same as player’s height
        player_hitbox.height = player_size
        # Draw the player_hitbox
        # pygame.draw.rect(screen, (255, 255, 255), player_hitbox)

        # Check to see if the player_hitbox collides with an enemy
        for enemy in enemies:
            if player_hitbox.colliderect(enemy.hitbox):
                # Check to see if the player is bigger than the enemy
                if player_size >= enemy.size:
                    # Increase score when player eats an enemy
                    score += 1
                    player_size += 2
                    # If the player is bigger, take the enemy off the enemies array
                    enemies.remove(enemy)
                    # Start the eating timer when the player eats an enemy
                    player_eating_timer = player_eating_timer_max
                # Add an else for when the player should get eaten
                else:
                    player_alive = False

        # Make the timer countdown
        player_swimming_timer -= 1
        # Check to see when the timer hits 0
        if player_swimming_timer <= 0:
            # When the timer hits 0, reset the timer
            player_swimming_timer = player_swimming_timer_max
            # When the timer hits 0, move to the next frame
            player_swimming_frame += 1
            # Check to see if the frame is higher than 1
            if player_swimming_frame > 1:
                # If the frame is higher than 1, reset it back to 0
                player_swimming_frame = 0

        # Check to see if the eating timer is above 0
        if player_eating_timer > 0:
            # Make player pic small out of player eating pic if the timer is above 0
            player_image_small = pygame.transform.scale(player_eating_image, (int(player_size * 1.25), player_size))
            # Make the timer count down if it's above 0
            player_eating_timer -= 1

        # Add an else for when the eating timer is not above 0
        else:
            # Check to see if the frame is 0
            if player_swimming_frame == 0:                
                # Scale player_image
                player_image_small = pygame.transform.scale(player_image, (player_size, player_size))

            # Add an else for when the frame is 1
            else:
                # Scale player_image
                player_image_small = pygame.transform.scale(player_image_2, (player_size, player_size))


        if player_facing_right != True:
            player_image_small = pygame.transform.flip(player_image_small, True, False)

        # Display the player
        # CHANGE IMAGE TO SMALLER VERSION
        screen.blit(player_image_small, (player_x, player_y))

    # Check to see if the player is alive
    if player_alive:
        # Put the line that updates the score text
        # inside the new if statement    
        # In the loop, update the score_text
        score_text = score_font.render("Score: " + str(score), 1, (255, 255, 255))
    # Add an else for when the player is not alive
    else:
        # Make the text say something different
        # if the player is not alive
        score_text = score_font.render("Final Score: " + str(score), 1, (255, 255, 255))
    if score >= 0:                
        # In the loop, draw the score text
        screen.blit(score_text, (30,30))

    # If the player is not alive, draw the play button
    if not player_alive:
        screen.blit(play_button_pic, (play_button_x, play_button_y))
        # Get the mouse position
        mouse_x, mouse_y = pygame.mouse.get_pos()
        # Check to see if the left mouse button is being pressed
        if pygame.mouse.get_pressed()[0]:
            # Check to see if the x of the mouse is over the button
            if mouse_x > play_button_x and mouse_x < play_button_x + play_button_pic.get_width():
                # Check to see if the y of the mouse is over the button
                if mouse_y > play_button_y and mouse_y < play_button_y + play_button_pic.get_height():
                    player_alive = True
                    score = 0
                    player_x = player_starting_x
                    player_y = player_starting_y
                    player_size = player_starting_size
                    # Make a for loop to go through the enemies array
                    for enemy in enemies:
                        enemies_to_remove.append(enemy)
                                

    # Tell pygame to update the screen
    pygame.display.flip()
    clock.tick(50)
    pygame.display.set_caption("MY GAME fps: " + str(clock.get_fps()))

# Quit screen
pygame.quit()    
