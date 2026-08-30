import serial
import time
from pynput import keyboard

ser = serial.Serial('COM9', 115200, timeout=0.1)
time.sleep(2)

def on_press(key):
    try:
        if key.char in ['w', 'a', 's', 'd']:
            print(key.char)
            ser.write(key.char.encode('utf-8'))
    except AttributeError:
        pass
def on_release(key):
    try:
        if key.char in ['w', 'a', 's', 'd']:#make wasd to }gyj
            ser.write(chr(ord(key.char.encode())+6).encode('utf-8'))
            print(chr(ord(key.char.encode())+6).encode('utf-8'))
    except AttributeError:
        pass


with keyboard.Listener(on_press=on_press, on_release=on_release) as listener:
    listener.join()
