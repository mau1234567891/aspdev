import pygame
import serial
import time

ser = serial.Serial("COMX", 115200)  # CAMBIA COM3
time.sleep(2)

pygame.init()
pygame.joystick.init()

j = pygame.joystick.Joystick(0)
j.init()

while True:
    pygame.event.pump()
    x = j.get_axis(0)
    y = j.get_axis(1)

    if y < -0.5: ser.write(b'U')
    elif y > 0.5: ser.write(b'D')
    elif x < -0.5: ser.write(b'L')
    elif x > 0.5: ser.write(b'R')

    time.sleep(0.1)
