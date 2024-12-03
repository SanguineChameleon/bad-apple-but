from PIL import Image
import sys

with open("grid.txt", "r") as sys.stdin:
	img = Image.new("RGB", (480, 360), (255, 0, 0))
	for y in range(0, 360, 36):
		for x in range(0, 480, 48):
			best = input()
			piece = Image.open("scaled/frame%s.png" % best)
			img.paste(piece, (x, y))
	img.save("matched/frame%s.png" % sys.argv[1])