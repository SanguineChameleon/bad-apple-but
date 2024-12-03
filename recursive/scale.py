from PIL import Image
import sys

def dist(c1, c2):
	return (c1[0] - c2[0]) ** 2 + (c1[1] - c2[1]) ** 2 + (c1[2] - c2[2]) ** 2

FRAME_COUNT = 6572

with open("scaled.txt", "w") as sys.stdout:
	for i in range(1, FRAME_COUNT + 1):
		img = Image.open("frames/frame%d.png" % i)
		img.thumbnail((48, 36), Image.Resampling.LANCZOS)
		#img.save("scaled/frame%d.png" % i)
		pix = img.load()
		for y in range(36):
			for x in range(48):
				S = pix[x, y][0] + pix[x, y][1] + pix[x, y][2]
				print(round(S / 3))
		print()