import pyautogui
import sys
import time
screenshot = pyautogui.screenshot()
screenshot.save("shots/shot%s.png" % sys.argv[1])