from PIL import Image
import sys

GRID_HEIGHT = 23
GRID_WIDTH = 35

IMG_HEIGHT = 1200
IMG_WIDTH = 1600

FRAME_COUNT = 6572

color_id = dict()

with open("region_colors.txt", "r") as sys.stdin:
	for i in range(GRID_HEIGHT):
		row = input().split()
		for j in range(GRID_WIDTH):
			if j % 2 == 1 and i == GRID_HEIGHT - 1:
				continue
			r = int(row[j][1:3], 16)
			g = int(row[j][3:5], 16)
			b = int(row[j][5:7], 16)
			color_id[(r, g, b)] = (i, j)

pix = Image.open("region_colors.png").load()

reg_id = [[None for j in range(IMG_WIDTH)] for i in range(IMG_HEIGHT)]

reg_cnt = [[0 for j in range(GRID_WIDTH)] for i in range(GRID_HEIGHT)]

for y in range(IMG_HEIGHT):
	for x in range(IMG_WIDTH):
		reg_id[y][x] = color_id.get(pix[x, y], None)
		if reg_id[y][x]:
			reg_cnt[reg_id[y][x][0]][reg_id[y][x][1]] += 1


for frame_id in range(1, FRAME_COUNT + 1):
	reg_sum = [[0 for j in range(GRID_WIDTH)] for i in range(GRID_HEIGHT)]
	img = Image.open("../frames/frame%s.png" % frame_id)
	img = img.resize((IMG_WIDTH, IMG_HEIGHT), Image.Resampling.LANCZOS)
	pix = img.load()
	for y in range(IMG_HEIGHT):
		for x in range(IMG_WIDTH):
			if reg_id[y][x]:
				s = pix[x, y][0] + pix[x, y][1] + pix[x, y][2]
				reg_sum[reg_id[y][x][0]][reg_id[y][x][1]] += s / 3
	with open("grids/grid%d.txt" % frame_id, "w") as sys.stdout:
		for i in range(GRID_HEIGHT):
			for j in range(GRID_WIDTH):
				if reg_cnt[i][j] == 0:
					print(0, end = " ")
					continue
				avg = reg_sum[i][j] / reg_cnt[i][j]
				if avg <= 255 / 2:
					print(1, end = " ")
				else:
					print(0, end = " ")
			print()