from taks1.Models.Map import *
from taks1.Models.Drone import *
from random import randint
from taks1.Service import *
import time

class UserInterface:
    def __init__(self):
        self.m = Map()
        self.m.loadMap("Assets/test1.map")

        self.startX = randint(0, 19)
        self.startY = randint(0, 19)
        self.d = Drone(self.startX, self.startY)

    def displayWithPath(self, image, path):
        mark = pygame.Surface((20, 20))
        mark.fill(GREEN)
        for move in path:
            image.blit(mark, (move[1] * 20, move[0] * 20))

        return image

    def showMenu(self):
        print("a. Greedy")
        print("b. A*")
        opt = input("> ")
        if opt == "a":
            self.main(searchAStar)
        else:
            self.main(searchGreedy)

    def main(self, pathFunc):
        # initialize the pygame module
        pygame.init()
        pygame.font.init()
        # load and set the logo
        logo = pygame.image.load("Assets/logo32x32.png")
        pygame.display.set_icon(logo)
        pygame.display.set_caption("Path in simple environment")
        font = pygame.font.SysFont('Comic Sans MS', 24)

        # we position the drone somewhere in the area


        while True:
            fx = randint(0, 19)
            fy = randint(0, 19)
            if self.m.surface[fx][fy] == 0:
                break

        # create a surface on screen that has the size of 400 x 480
        screen = pygame.display.set_mode((400, 400))
        screen.fill(WHITE)

        # define a variable to control the main loop
        running = True

        # main loop
        while running:
            # event handling, gets all event from the event queue
            for event in pygame.event.get():
                # only do something if the event is of type QUIT
                if event.type == pygame.QUIT:
                    # change the value to False, to exit the main loop
                    running = False

                # if event.type == KEYDOWN:
                #     d.move(m)  # this call will be erased

            screen.blit(self.d.mapWithDrone(self.m.image()), (0, 0))
            pygame.display.flip()

        path = pathFunc(self.m, self.startX, self.startY, fx, fy)

        screen.blit(self.displayWithPath(self.m.image(), path), (0, 0))

        pygame.display.flip()
        time.sleep(5)
        pygame.quit()
