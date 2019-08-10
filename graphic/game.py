# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    game.py                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/09 11:30:34 by nlavrine          #+#    #+#              #
#    Updated: 2019/08/09 17:39:28 by nlavrine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import pygame
import sys

from parse import find_node
from collections import defaultdict


class Game:
    def __init__(self, 
                 caption, 
                 width, 
                 height, 
                 back_image_filename, 
                 frame_rate,
                 graph):
        self.background_image = \
            pygame.image.load(back_image_filename)
        self.frame_rate = frame_rate
        self.game_over = False
        self.objects = []
        pygame.mixer.pre_init(44100, 16, 2, 4096)
        pygame.init()
        pygame.font.init()
        self.surface = pygame.display.set_mode((width, height))
        pygame.display.set_caption(caption)
        self.clock = pygame.time.Clock()
        self.keydown_handlers = defaultdict(list)
        self.keydown_handlers[pygame.K_SPACE] = self.handle_space
        self.keyup_handlers = defaultdict(list)
        self.mouse_handlers = []
        self.graph = graph
        self.ants_moves = []
        self.ants = []

    def update(self):
        for o in self.objects:
            o.update()

    def draw(self):
        for o in self.objects:
            o.draw(self.surface)
    def move(self):
        for o in self.objects:
            o.move(o.move())
    
    def create_lines(self):
        for node in self.graph:
            for link in node.links:
                pygame.draw.line(self.surface, (0, 0, 0),
                                    (node.x, node.y), (link.x, link.y), 3)

    def handle_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                self.keydown_handlers[event.key]()
                   
            elif event.type == pygame.KEYUP:
                for handler in self.keyup_handlers[event.key]:
                    handler(event.key)
            elif event.type in (pygame.MOUSEBUTTONDOWN, 
                                pygame.MOUSEBUTTONUP, 
                                pygame.MOUSEMOTION):
                for handler in self.mouse_handlers:
                    handler(event.type, event.pos)
    
    def handle_space(self):
        if (self.ants_moves):
            move = self.ants_moves.pop(0)
            for ant in move:
                where_to_move = find_node(self.graph, ant.move)
                obj_ant = self.ants[ant.id - 1]
                print(abs(where_to_move.x - obj_ant.x),
                    abs(where_to_move.y - obj_ant.y))
                obj_ant.speed = [abs(where_to_move.x - obj_ant.x),
                        abs(where_to_move.y - obj_ant.y)]
                self.update()
                obj_ant.speed = [0,0]


    def run(self):
        self.surface.blit(self.background_image, (0, 0))
        self.create_lines()
        while not self.game_over:
            
            self.handle_events()
            self.update()
            self.draw()

            pygame.display.update()
            self.clock.tick(self.frame_rate)