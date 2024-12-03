import keyboard
import time
import pyautogui
cur = 0
while True:
	if keyboard.is_pressed("space"):
		pyautogui.screenshot().save("letter_shots/letter_%s.png" % (chr(ord('a') + cur)))
		time.sleep(0.1)
		cur += 1
		if cur == 26:
			break