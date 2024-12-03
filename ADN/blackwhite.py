from PIL import Image
import os
import win32
import time
os.system("")

def dist(c1, c2):
	return (c1[0] - c2[0]) ** 2 + (c1[1] - c2[1]) ** 2 + (c1[2] - c2[2]) ** 2

FRAME_COUNT = 6572

row_count = 0

for i in range(1, FRAME_COUNT + 1):
	print("\033[?25l")
	print("\033[1;1H",end="")
	img = Image.open("frames/frame%d.png" % i)
	pix = img.load()
	row_count = 0
	for y in range(0, 360, 1):
		row_count += 1
		for x in range(0, 480, 1):
			if dist(pix[x, y], (0, 0, 0)) <= dist(pix[x, y], (255, 255, 255)):
				print(1, end = "")
			else:
				print(0, end = "")
		print()