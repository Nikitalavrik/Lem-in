# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    gameobj.py                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/09 12:21:30 by nlavrine          #+#    #+#              #
#    Updated: 2019/08/09 17:21:31 by nlavrine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import pygame
from pygame.rect import Rect


class GameObject:
    def __init__(self, x, y, w, h, image_name, speed=(0,0)):
        self.image = pygame.image.load(image_name).convert_alpha()
        self.bounds = self.image.get_rect()
        self.bounds.center = (x, y)
        self.speed = speed

    @property
    def left(self):
        return self.bounds.left

    @property
    def right(self):
        return self.bounds.right

    @property
    def top(self):
        return self.bounds.top

    @property
    def bottom(self):
        return self.bounds.bottom

    @property
    def width(self):
        return self.bounds.width

    @property
    def height(self):
        return self.bounds.height

    @property
    def center(self):
        return self.bounds.center

    @property
    def centerx(self):
        return self.bounds.centerx

    @property
    def centery(self):
        return self.bounds.centery

    def draw(self, surface):
        surface.blit(self.image, self.bounds)

    def move(self):
        self.bounds = self.bounds.move(*self.speed)

    def update(self):
        if self.speed == [0, 0]:
            return

        # self.move(*self.speed)
