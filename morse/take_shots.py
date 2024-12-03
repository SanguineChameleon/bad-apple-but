import time
import pyautogui
import pyperclip

pyautogui.PAUSE = 0.01

FRAME_COUNT = 6572

time.sleep(20)


# max_len = 0

for FRAME_ID in range(1, FRAME_COUNT + 1):
	string = open("strings/string%d.txt" % FRAME_ID, "r").read().strip()
	pyautogui.moveTo(981, 422)
	pyautogui.click()
	pyautogui.hotkey("ctrl", "a")
	pyperclip.copy(string)
	pyautogui.hotkey("ctrl", "v")
	pyautogui.moveTo(1226, 443)
	pyautogui.click()
	pyautogui.screenshot().save("shots/shot%d.png" % FRAME_ID)

# print(max_len)