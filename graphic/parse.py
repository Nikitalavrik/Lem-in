# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    parse.py                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/09 15:36:23 by nlavrine          #+#    #+#              #
#    Updated: 2019/08/09 18:10:56 by nlavrine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os

class Node:
	def __init__(self, name, x, y):
		self.name = name
		self.x = x
		self.y = y
		self.links = []
	
	def add_link(self, node):
		self.links.append(node)

	def __str__(self):
		return self.name
	
	def __repr__(self):
		return self.name

class Move:
	def __init__(self, id, move):
		self.id = id
		self.move = move
	
	def __repr__(self):
		return self.move

def find_node(graph, name):
	
	for node in graph:
		if node.name == name:
			return (node)

def	parse_graph(line, prev_line, graph, start):
	if (line[0] != '#'):
		splited = line.split(' ')
		if (len(splited) == 3):
			node = Node(splited[0], int(splited[1]), int(splited[2]))
			graph.append(node)
			if (prev_line == "##start\n"):
				start = node
	if ('-' in line):
		splited = line.split('-')
		if (len(splited) == 2):
			node = find_node(graph, splited[0])
			node.add_link(find_node(graph, splited[1][:-1]))
	return (start)

def	parse_moves(line):
	one_move = []
	for word in line.split(' '):
		if word:
			splited = word.split('-')
			one_move.append(Move(int(splited[0][1:]), splited[1]))
	return (one_move)

def parse_all(path):
	graph = []
	prev_line = ""
	start = 0
	ant_moves = []
	with open(path, 'r') as f:
		ants = int(f.readline())
		while True:
			line = f.readline()
			if (line[0] == '\n' or not line):
				break 
			start = parse_graph(line, prev_line, graph, start)
			prev_line = line

		while line:
			line = f.readline()[:-1]
			one_move = parse_moves(line)
			if one_move:
				ant_moves.append(one_move)
	return (start, ants, ant_moves, graph)