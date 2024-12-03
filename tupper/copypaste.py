import time
import pyautogui
import pyperclip

time.sleep(20)

FRAME_COUNT = 6572

presets = open("presets.txt", "r").read().split("\n")

for i in range(1, FRAME_COUNT + 1):
	pyperclip.copy("loadBase62Preset(\"%s\")" % presets[i - 1])
	pyautogui.hotkey("ctrl", "v")
	pyautogui.press("enter")
	pyautogui.screenshot().save("shots/frame%d.png" % i)