import board
import digitalio
import time
import pulseio
import pwmio

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

# Set up pins for motors and LEDs
pwm_A = pwmio.PWMOut(board.GP0, frequency=5000, duty_cycle=0)
pwm_B = pwmio.PWMOut(board.GP6, frequency=5000, duty_cycle=0)

a1 = digitalio.DigitalInOut(board.GP1)
a1.direction = digitalio.Direction.OUTPUT

a2 = digitalio.DigitalInOut(board.GP2)
a2.direction = digitalio.Direction.OUTPUT

b1 = digitalio.DigitalInOut(board.GP7)
b1.direction = digitalio.Direction.OUTPUT

b2 = digitalio.DigitalInOut(board.GP8)
b2.direction = digitalio.Direction.OUTPUT


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

def drive_A(v):
    if v > 0:
        v = min(v, 255)
        a1.value = True
        a2.value = False
    else:
        v = max(v, -255)
        a1.value = False
        a2.value = True
    pwm_A.duty_cycle = int(abs(v) * 65535 / 255)  # Convert 8-bit value to 16-bit

def drive_B(v):
    if v > 0:
        v = min(v, 255)
        b1.value = True
        b2.value = False
    else:
        v = max(v, -255)
        b1.value = False
        b2.value = True
    pwm_B.duty_cycle = int(abs(v) * 65535 / 255)  # Convert 8-bit value to 16-bit


while True:
    depth = getDepth()
    print(f"{depth} cm")

    if depth < 20 and depth >= 0:
        LeftLED.value = True
        RightLED.value = True
        BoardLED.value = True
        drive_A(150)
        drive_B(150)
    else:
        LeftLED.value = False
        RightLED.value = False
        BoardLED.value = False
        drive_A(-150)
        drive_B(-150)
    time.sleep(0.5)

