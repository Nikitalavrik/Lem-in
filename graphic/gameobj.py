# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    gameobj.py                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/09 12:21:30 by nlavrine          #+#    #+#              #
#    Updated: 2019/08/15 13:25:14 by nlavrine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import pygame
from pygame.rect import Rect


class GameObject:
    def __init__(self, x, y, image_name, speed=[0,0], name=0):
        self.image = pygame.image.load(image_name).convert_alpha()
        self.bounds = self.image.get_rect()
        self.bounds.center = (x, y)
        self.speed = speed
        self.x = x
        self.y = y
        self.name = name

    def draw(self, surface):
        surface.blit(self.image, self.bounds)
        if self.name:
            font = pygame.font.SysFont('Calibri', 35)
            surface.blit(font.render(self.name, True, (255, 255, 0)), self.bounds)
        
    def move(self, dx, dy):
        self.bounds = self.bounds.move(dx, dy)

    def update(self):
        if self.speed == [0, 0] or (self.bounds.center == (self.x, self.y)):
            return
        self.move(*self.speed)
