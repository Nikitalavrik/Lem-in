# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    game.py                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/09 11:30:34 by nlavrine          #+#    #+#              #
#    Updated: 2019/08/15 13:59:38 by nlavrine         ###   ########.fr        #
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
                 graph,
                 start,
                 end):
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
        self.mouse_handlers = []
        self.graph = graph
        self.ants_moves = []
        self.ants = []
        self.start = start
        self.end = end
        self.end_index = 0
        for g in self.graph:
            if g == self.end:
                break
            self.end_index += 1


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
    def close(self):
        x, y, w, h = 1198, 20, 60, 20
        pygame.draw.rect(self.surface, (153 , 77, 0), (x, y, w, h))
        font = pygame.font.SysFont('Calibri', 30)
        mouse = pygame.mouse.get_pos()
        click = pygame.mouse.get_pressed()
        if (x + w > mouse[0] and y + h > mouse[1]):
            font = self.surface.blit(font.render("Close", True, (0, 48, 143)), (x + 2, y, w + 40, h * 2))
            if click[0] == 1:
                pygame.quit()
                sys.exit()
        else:
            font = self.surface.blit(font.render("Close", True, (255, 255, 0)), (x + 2, y, w + 40, h * 2))
    def draw_text(self):
        font = pygame.font.SysFont('Calibri', 30)
        self.surface.blit(font.render("Start - " + self.start.name, True, (255, 255, 0)), (10,10))
        font = pygame.font.SysFont('Calibri', 30)
        self.surface.blit(font.render("End - " + self.end.name, True, (255, 255, 0)), (10,50))
        font = pygame.font.SysFont('Calibri', 30)
        self.surface.blit(font.render("Space - Step", True, (255, 255, 0)), (10,90))

    def check_end(self):
        font = pygame.font.SysFont('Calibri', 35)
        self.surface.blit(font.render(str(self.end.num_of_ants), True, (49, 0, 179)),
        (self.objects[self.end_index].bounds[0] + 60, self.objects[self.end_index].bounds[1] + 116))

    def handle_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                if event.key in self.keydown_handlers.keys():
                    self.keydown_handlers[event.key]()
    
    def handle_space(self):
        if (self.ants_moves):
            move = self.ants_moves.pop(0)
            for ant in move:
                where_to_move = find_node(self.graph, ant.move)
                obj_ant = self.ants[ant.id - 1]
                if (obj_ant.x, obj_ant.y) != obj_ant.bounds.center:
                    self.ants_moves.insert(0, move)
                    break
                dx = where_to_move.x - obj_ant.x
                dy = where_to_move.y - obj_ant.y
                dx = dx - dx % 10
                dy = dy - dy % 10
                obj_ant.x += dx
                obj_ant.y += dy
                if ant.move == self.end.name:
                    self.end.num_of_ants += 1
                obj_ant.speed = [dx / 10, dy / 10]

    def run(self):
        while not self.game_over:
            self.surface.blit(self.background_image, (0, 0))
            self.create_lines()
            self.update()
            self.draw()
            self.draw_text()
            self.check_end()
            self.close()
            self.handle_events()
            pygame.display.update()
            self.clock.tick(self.frame_rate)