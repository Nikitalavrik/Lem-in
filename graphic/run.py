# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.py                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/09 12:21:24 by nlavrine          #+#    #+#              #
#    Updated: 2019/08/28 20:12:37 by nlavrine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import pygame, sys
from game import Game
from gameobj import GameObject
from parse import parse_all, find_node

resolution = [1280, 852]
node_image = "graphic/images/node.png"
ant_image = "graphic/images/ant.png"
image_back = "graphic/images/background.png"
koef = resolution[0] / resolution[1]
fps = 30

def create_game(graph, start, end):

	run_game = Game("LE MYRAXA", resolution[0], resolution[1],
								image_back, fps, graph, start, end)
	return (run_game)

def create_node(game, graph):
	max_x = 0
	max_y = 0
	for g in graph:
		if g.x > max_x:
				max_x = g.x
		if g.y > max_y:
				max_y = g.y
	
	koef = [int((resolution[0] - 80) / (max_x + 2)), int((resolution[1] - 52) / (max_y + 1))]
	koef[0] = 1 if koef[0] < 1 else koef[0]
	koef[1] = 1 if koef[1] < 1 else koef[1]
	for g in graph:
		g.x = g.x * koef[0] + 160 - max_x * 2
		g.y = g.y * koef[1] + 80 - max_y * 2
		obj = GameObject(g.x, g.y, node_image, name=g.name)
		game.objects.append(obj)

def create_ants(game, start, num_of_ants):
	ants = []
	for _ in range(num_of_ants):
		obj = GameObject(start.x, start.y, ant_image)
		ants.append(obj)
		game.objects.append(obj)
	return (ants)

if (len(sys.argv) == 3 and sys.argv[1] == "-f"):
	try:
		start, num_of_ants, ants_moves, graph = parse_all(sys.argv[2], 0)
	except:
		print("Bad file name")
		exit(0)
elif (len(sys.argv) == 1):
	try:
		start, num_of_ants, ants_moves, graph = parse_all("", 1)
	except:
		print("Bad file name")
		exit(0)
else:
	print("Enter filename")	
	# start, num_of_ants, ants_moves, graph = parse_all(sys.argv[1])

end = find_node(graph, ants_moves[-1][-1].move)
if len(graph) > 10:
	print("BIG GRAPH")
	exit()

game = create_game(graph, start, end)
create_node(game, graph)
ants = create_ants(game, start, num_of_ants)
game.ants_moves = ants_moves
game.ants = ants
game.run()
