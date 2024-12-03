from PIL import Image
import sys

img = Image.open("chars.png")
pix = img.load()

def dist(c1, c2):
	return (c1[0] - c2[0]) ** 2 + (c1[1] - c2[1]) ** 2 + (c1[2] - c2[2]) ** 2


for x in range(32, 127):
	with open("chars/char%d.txt" % x, "w") as sys.stdout:
		for y in range(20):
			for z in range(9):
				col = pix[(x - 32) * 9 + z, y]
				if dist(col, (0, 0, 0)) <= dist(col, (255, 255, 255)):
					print(1, end = "")
				else:
					print(0, end = "")
			print()