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

def find_node(graph, name):
	
	for node in graph:
		if node.name == name:
			return (node)

def parse_graph(path):

	f = open(path, 'r')
	ants = 0
	graph = []
	prev_line = ""
	for line in f.readlines():
		if (line[0] == '\n'):
			break 
		if (ants == 0):
			ants = int(line)
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
				node1 = find_node(graph, splited[0])
				node2 = find_node(graph, splited[1][:-1])
				node1.add_link(node2)
		prev_line = line

	f.close()
	return (start, ants, graph)