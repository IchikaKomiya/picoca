import board
import pwmio
import time
import digitalio

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

board_led = digitalio.DigitalInOut(board.GP25)
board_led.direction = digitalio.Direction.OUTPUT
board_led.value = True  # Turn on Board LED

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
    # Drive motors
    drive_A(150)
    drive_B(150)
    time.sleep(1)

    drive_A(-150)
    drive_B(-150)
    time.sleep(1)
