from PIL import Image
import sys

FRAME_COUNT = 6572

with open("data.txt", "w") as sys.stdout:
	pix = Image.open("frames/frame%s.png" % sys.argv[1]).load()
	for y in range(360):
		for x in range(480):
			S = pix[x, y][0] + pix[x, y][1] + pix[x, y][2]
			print(round(S / 3))
	print()