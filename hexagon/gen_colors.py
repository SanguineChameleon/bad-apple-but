import random
import sys
random.seed(69420)

colors = []

for i in range(23 * 35):
	s = "#"
	for j in range(6):
		s += random.choice("0123456789abcdef")
	if s not in colors:
		colors.append(s)

with open("grid_colors.txt", "w") as sys.stdout:
	for i in range(23):
		for j in range(35):
			print(colors[i * 35 + j], end = " ")
		print()