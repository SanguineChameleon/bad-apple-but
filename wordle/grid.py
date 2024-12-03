from PIL import Image
import sys

ROW_COUNT = 3
COL_COUNT = 5
GRID_GAP = 30
SQUARE_GAP = 5
COL_POS = [0] * 5
ROW_POS = [0] * 6
for i in range(1, 5):
	COL_POS[i] = COL_POS[i - 1] + SQUARE_GAP + 65
for i in range(1, 6):
	ROW_POS[i] = ROW_POS[i - 1] + SQUARE_GAP + 65
GRID_WIDTH = COL_POS[-1] + 65
GRID_HEIGHT = ROW_POS[-1] + 65

img = Image.new("RGB", (480 * 4, 360 * 4), (18, 18, 19))
ROW_OFFSET = (360 * 4 - GRID_HEIGHT * ROW_COUNT - GRID_GAP * (ROW_COUNT + 1)) // 2
COL_OFFSET = (480 * 4 - GRID_WIDTH * COL_COUNT - GRID_GAP * (COL_COUNT + 1)) // 2

with open("grid.txt", "r") as sys.stdin:
	for i in range(ROW_COUNT):
		for j in range(COL_COUNT):
			for x in range(6):
				for y in range(5):
					file_name = input()
					pos_x = i * (GRID_HEIGHT + GRID_GAP) + ROW_POS[x] + GRID_GAP + ROW_OFFSET
					pos_y = j * (GRID_WIDTH + GRID_GAP) + COL_POS[y] + GRID_GAP + COL_OFFSET
					img.paste(Image.open("letters/letter_%s.png" % file_name), (pos_y, pos_x))
				input()

img.save("wordle/frame%s.png" % sys.argv[1])