from PIL import Image, ImageOps
import sys
import matplotlib.pyplot as plt
from matplotlib.patches import RegularPolygon
import math

GRID_HEIGHT = 23
GRID_WIDTH = 35
SIDE_LENGTH = 3
EDGE_COLOR = "black"
LINE_WIDTH = 0.5
ZERO_COLOR = "#8bc8f9"
ONE_COLOR = "#1d429b"
FONT_NAME = "Latin Modern Roman 10 Bold"

colors = [[None for j in range(GRID_WIDTH)] for i in range(GRID_HEIGHT)]

all_colors = []

with open("grid_colors.txt", "r") as sys.stdin:
	for i in range(GRID_HEIGHT):
		row = list(input().split())
		for j in range(GRID_WIDTH):
			colors[i][j] = row[j]
			all_colors.append(colors[i][j])

fig, ax = plt.subplots(1)
ax.set_aspect("equal")

center_x = []
center_y = []

cnt = 0

for i in range(GRID_HEIGHT):
	for j in range(GRID_WIDTH):
		if j % 2 == 1 and i == GRID_HEIGHT - 1:
			continue
		cnt += 1
		x = SIDE_LENGTH * 1.5 * j
		y = SIDE_LENGTH * math.sqrt(3) * (GRID_HEIGHT - 1 - i - (j % 2) / 2)
		center_x.append(x)
		center_y.append(y)
		hexagon = RegularPolygon((x, y), numVertices = 6, orientation = math.radians(30), radius = SIDE_LENGTH, edgecolor = EDGE_COLOR, linewidth = LINE_WIDTH, facecolor = colors[i][j])
		ax.add_patch(hexagon)
		#ax.text(x, y - 0.1, "788", ha = "center", va = "center", size = 5, fontname = FONT_NAME)

ax.scatter(center_x, center_y, alpha = 0)

plt.axis("off")
fig.savefig("uncropped.png", dpi = 350, bbox_inches = "tight", pad_inches = 0)

img1 = Image.open("uncropped.png").convert("RGB")
img1 = ImageOps.invert(img1)
bbox = img1.getbbox()
img1 = img1.crop(bbox)
img1 = ImageOps.invert(img1)
img2 = Image.new("RGB", (1600, 1200), (255, 255, 255))
img2.paste(img1, ((img2.size[0] - img1.size[0]) // 2, (img2.size[1] - img1.size[1]) // 2))
img2.save("cropped.png")