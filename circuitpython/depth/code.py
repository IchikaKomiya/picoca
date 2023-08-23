import board
import digitalio
import time
import pulseio

LeftLED = digitalio.DigitalInOut(board.GP11)
LeftLED.direction = digitalio.Direction.OUTPUT

RightLED = digitalio.DigitalInOut(board.GP10)
RightLED.direction = digitalio.Direction.OUTPUT

BoardLED = digitalio.DigitalInOut(board.GP25)
BoardLED.direction = digitalio.Direction.OUTPUT

# Set up the ultrasonic sensor pins
trigPin = digitalio.DigitalInOut(board.GP14)
trigPin.direction = digitalio.Direction.OUTPUT

echoPin = pulseio.PulseIn(board.GP15)
echoPin.pause()

# Speed of sound
V = 340  # in m/s

def sendTrigger():
    trigPin.value = True
    time.sleep(0.00001)
    trigPin.value = False

def getDepth():
    sendTrigger()
    echoPin.clear()
    echoPin.resume()
    while not echoPin:
        pass
    echoPin.pause()
    print(echoPin[0])
    t = echoPin[0] * 1e-6  # Convert microseconds to seconds
    return V * t * 100 / 2  # Convert to cm

while True:
    depth = getDepth()
    print(f"{depth} cm")

    if depth < 20 and depth >= 0:
        LeftLED.value = True
        RightLED.value = True
        BoardLED.value = True
    else:
        LeftLED.value = False
        RightLED.value = False
        BoardLED.value = False

    time.sleep(0.5)
