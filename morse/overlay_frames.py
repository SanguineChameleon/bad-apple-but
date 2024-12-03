from PIL import Image

overlay_img = Image.open("overlay.png")

FRAME_COUNT = 6572

cnt = 0

for FRAME_ID in range(1, FRAME_COUNT + 1):
	frame_img = Image.open("shots/shot%d.png" % FRAME_ID)
	frame_img.paste(overlay_img, (0, 0), overlay_img)
	frame_pix = frame_img.load()
	if frame_pix[547, 169] == (250, 250, 250):
		for x in range(547, 1143):
			for y in range(169, 487):
				if frame_pix[x, y] == (250, 250, 250):
					frame_pix[x, y] = (255, 255, 255)
		cnt += 1
	frame_img.save("overlaid/frame%d.png" % FRAME_ID)

print(cnt)