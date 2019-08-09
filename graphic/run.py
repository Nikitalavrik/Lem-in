# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.py                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/09 12:21:24 by nlavrine          #+#    #+#              #
#    Updated: 2019/08/09 18:09:44 by nlavrine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import pygame
from game import Game
from gameobj import GameObject
from parse import parse_graph

resolution = [1280, 852]
node_image = "images/node.png"
ant_image = "images/ant.png"

def create_game(graph):

	run_game = Game("lem-in", resolution[0], resolution[1],
								"images/background.png", 30, graph)
	return (run_game)

def create_node(game, graph):
	for g in graph:
		g.x = g.x * 100 + 400
		g.y = g.y * 100 + 120
		obj = GameObject(g.x, g.y, 80, 80, node_image)
		game.objects.append(obj)

def create_ants(game, start, num_of_ants):
	ants = []
	for _ in range(num_of_ants):
		obj = GameObject(start.x, start.y, 80, 80, ant_image)
		ants.append(obj)
		game.objects.append(obj)
	return (ants)

start, num_of_ants, graph = parse_graph("../test/tst4")

game = create_game(graph)

create_node(game, graph)
ants = create_ants(game, start, num_of_ants)

game.run()