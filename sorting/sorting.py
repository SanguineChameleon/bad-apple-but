from PIL import Image
import sys

FRAME_COUNT = 6572

def draw(frame_id, A, x, y):
	orig_img = Image.open("frames/frame%d.png" % (510))#frame_id)
	orig_img = orig_img.resize((1440, 1080), Image.Resampling.LANCZOS)
	red_img = orig_img
	pix = red_img.load()
	for x in range(400, 410):
		for y in range(1080):
			avg = round(255 / 2 + (pix[x, y][0] + pix[x, y][1] + pix[x, y][2]) / 6)
			pix[x, y] = (avg, 0, 0)
	red_img.save("sorting_frames/frame%d.png" % frame_id)
	raise SystemExit

	new_img = Image.new("RGB", (1440, 1080), (255, 0, 0))
	for i in range(1440):
		region = orig_img.crop((A[i], 0, A[i] + 1, 1080))
		new_img.paste(region, (i, 0, i + 1, 1080))
	new_img.save("sorting_frames/frame%d.png" % frame_id)
	raise SystemExit


with open("swaps.txt", "r") as sys.stdin:
	A = list(map(int, input().split()))
	for i in range(1, FRAME_COUNT):
		x, y = map(int, input().split())
		draw(i, A, x, y)
		A[x], A[y] = A[y], A[x]
	draw(FRAME_COUNT, A, -1, -1)