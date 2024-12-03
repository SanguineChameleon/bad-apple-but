from PIL import Image
import sys

FRAME_COUNT = 6572
GRID_WIDTH = 63
GRID_HEIGHT = 22
CELL_WIDTH = 14
CELL_HEIGHT = 30

chars = ".- /"

char_names = ["dot", "dash", "space", "slash"]

char_pix = [Image.open("chars/%s.png" % name).load() for name in char_names]

for frame_id in range(1, FRAME_COUNT + 1):
	with open("costs/costs%d.txt" % frame_id, "w") as sys.stdout:
		frame_img = Image.open("../frames/frame%d.png" % frame_id)
		frame_img = frame_img.resize((GRID_WIDTH * CELL_WIDTH, GRID_HEIGHT * CELL_HEIGHT))
		frame_pix = frame_img.load()
		for row in range(GRID_HEIGHT):
			for col in range(GRID_WIDTH):
				costs = [0] * len(char_names)
				for char_id in range(len(char_names)):
					for y in range(CELL_HEIGHT):
						for x in range(CELL_WIDTH):
							fx = col * CELL_WIDTH + x
							fy = row * CELL_HEIGHT + y
							frame_val = round((frame_pix[fx, fy][0] + frame_pix[fx, fy][1] + frame_pix[fx, fy][2]) / 3)
							char_val = char_pix[char_id][x, y][0]
							costs[char_id] += abs(frame_val - char_val)
				print(" ".join(map(str, costs)))