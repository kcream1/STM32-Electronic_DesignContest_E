# Blob Detection Example
#
# This example shows off how to use the find_blobs function to find color
# blobs in the image. This example in particular looks for dark green objects.

import sensor, image, time,pyb
#import car
from pyb import Servo
import time
from pyb import Pin

p_in_6 = Pin('P6', Pin.IN, Pin.PULL_UP)
p_in_5 = Pin('P5', Pin.IN, Pin.PULL_UP)
p_out_2 = Pin('P2', Pin.OUT_PP)
p_out_3 = Pin('P3', Pin.OUT_PP)
p_out_3.low()
p_out_2.low()


s1 = Servo(1)#对应p7引脚
s2 = Servo(2)#对应p8引脚
# You may need to tweak the above settings for tracking green things...
# Select an area in the Framebuffer to copy the color settings.

sensor.reset() # Initialize the camera sensor.
sensor.set_pixformat(sensor.RGB565) # use RGB565.
sensor.set_framesize(sensor.VGA) # use QQVGA for speed.
sensor.skip_frames(10) # Let new settings take affect.
sensor.set_auto_whitebal(False) # turn this off.
sensor.set_auto_exposure(False, 18000)
clock = time.clock() # Tracks FPS.
led = pyb.LED(3)
uart = pyb.UART(3, 115200, timeout_char = 1000)     #定义串口3变量timeout_char是超时时间，超时1秒跳出
led.on()

h3=0
x3=0
red_threshold   =  (13, 49, 18, 61, 6, 47)
size_threshold = 2000



def find_max(blobs):#寻找最大的小球
    max_size=0
    for blob in blobs:
        if blob[2]*blob[3] > max_size:
            max_blob=blob
            max_size = blob[2]*blob[3]
    return max_blob

def pidx(a):#x方向上的pid控制
    global x3
    kpx=0.17
    kix=0.07
    x2=a-0
    x3+=x2
    x4=x2*kpx+x3*kix
    if x4>80:
        x4=80
    if x4<-80:
        x4=-80
    return x4

def pidh(b):#h方向上的pid控制
    global h3
    kph=0.18
    kih=0.08
    h2=b-0
    h3+=h2
    h4=h2*kph+kih*h3
    if h4>80:
        h4=80
    if h4<-80:
        h4=-60
    return -h4

green_thresholds = (30, 70, -64, -8, -32, 32)

while(True):
    clock.tick() # Track elapsed milliseconds between snapshots().
    img = sensor.snapshot() # Take a picture and return the image.
    green_blobs = img.find_blobs([green_thresholds])
    # 2. 抠出绿光区域为黑色
    for b in green_blobs:
      img.draw_rectangle(b.rect(), color = (0,0,0))
    blobs = img.find_blobs([red_threshold])
    if blobs:
        max_blob = find_max(blobs)
        x = (-max_blob[5]+320)/4#x轴的坐标
        h_error = max_blob[6]
        h=(h_error-240)/4
        img.draw_rectangle(max_blob[0:4]) # rect
        img.draw_cross(max_blob[5], max_blob[6]) # cx, c
        x1=pidx(x)
        h1=pidh(h)
        print(h)
        print("h error: ", h1)
        #uart.write('hello')
        if p_in_6.value() == 0:
           p_out_2.low()
           p_out_3.low()
        else:
           s1.angle(h1) # move to 45 degrees
           s2.angle(x1)
           if abs(h)<1:
              p_out_2.high()
              p_out_3.high()
           else:
              p_out_2.low()
              p_out_3.low()
