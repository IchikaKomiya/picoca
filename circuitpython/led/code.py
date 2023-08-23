import board
import digitalio
import time

LeftLED = digitalio.DigitalInOut(board.GP11)
LeftLED.direction = digitalio.Direction.OUTPUT

RightLED = digitalio.DigitalInOut(board.GP10)
RightLED.direction = digitalio.Direction.OUTPUT

BoardLED = digitalio.DigitalInOut(board.GP25)
BoardLED.direction = digitalio.Direction.OUTPUT


while True:
    for i in range(5):
        LeftLED.value = True
        RightLED.value = True
        BoardLED.value = True
        time.sleep(0.5)
        LeftLED.value = False
        RightLED.value = False
        BoardLED.value = False
        time.sleep(0.5)
    time.sleep(1)
