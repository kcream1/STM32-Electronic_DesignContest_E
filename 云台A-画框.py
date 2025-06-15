from machine import Pin
import sensor, image, time
import  pyb
from pyb import UART
import math

# 初始化摄像头
red_threshold  = (13, 49, 18, 61, 6, 47)
sensor.reset()
sensor.set_pixformat(sensor.RGB565) # 设置图像色彩格式为RGB565格式
sensor.set_framesize(sensor.HQVGA)  # 设置图像大小为160*120
sensor.set_auto_whitebal(False)      # 设置自动白平衡
sensor.set_brightness(1000)         # 设置亮度为3000
sensor.skip_frames(time = 20)       # 跳过帧
sensor.set_auto_exposure(False, 35000)
clock = time.clock()
img = sensor.snapshot().gamma_corr(gamma = 0.5, contrast = 1.0, brightness = 0.0)



num = 0
uart = UART(3,115200)
def fill(string, width):
    if len(string) == width:
        if string > str(sensor.width()):
            return str(sensor.width())
        else:
            return string
    else:
        padding = "0" * (width - len(string))
        return padding + string
def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob[2]*blob[3] > max_size:
            max_blob=blob
            max_size = blob[2]*blob[3]
    return max_blob





def recive_data():
    global tmp_data
    if uart.any():        #等待接收
      t = uart.read();	  #读入数据
      tmp_data=int(t)
      print(tmp_data)

      if(tmp_data == 1):
        output_str1=sorted_coordinates[0][0]
        output_str2=sorted_coordinates[0][1]

        output_str3=sorted_coordinates[1][0]
        output_str4=sorted_coordinates[1][1]

        output_str5=sorted_coordinates[2][0]
        output_str6=sorted_coordinates[2][1]

        output_str7=sorted_coordinates[3][0]
        output_str8=sorted_coordinates[3][1]


        x_err_1 = output_str1 - num1
        y_err_2 = output_str2 - num2

        x_err_3 = output_str3 - output_str1
        y_err_4 = output_str4 - output_str2

        x_err_5 = output_str5 - output_str3
        y_err_6 = output_str6 - output_str4

        x_err_7 = output_str7 - output_str5
        y_err_8 = output_str8 - output_str6

        x_errr = output_str1 - output_str7
        y_errr = output_str2 - output_str8

        xerr_str_1="%d"% (x_err_1)
        yerr_str_2="%d"% (y_err_2)

        xerr_str_3="%d"% (x_err_3)
        yerr_str_4="%d"% (y_err_4)

        xerr_str_5="%d"% (x_err_5)
        yerr_str_6="%d"% (y_err_6)

        xerr_str_7="%d"% (x_err_7)
        yerr_str_8="%d"% (y_err_8)

        xerr_str_rrr="%d"% (x_errr)
        yerr_str_rrr="%d"% (y_errr)


        uart.write(xerr_str_1+'\r\n')
        time.sleep_ms(120)
        uart.write(yerr_str_2+'\r\n')
        time.sleep_ms(120)

        uart.write(xerr_str_3+'\r\n')
        time.sleep_ms(120)
        uart.write(yerr_str_4+'\r\n')
        time.sleep_ms(120)

        uart.write(xerr_str_5+'\r\n')
        time.sleep_ms(120)
        uart.write(yerr_str_6+'\r\n')
        time.sleep_ms(120)

        uart.write(xerr_str_7+'\r\n')
        time.sleep_ms(120)
        uart.write(yerr_str_8+'\r\n')
        time.sleep_ms(120)

        uart.write(xerr_str_rrr+'\r\n')
        time.sleep_ms(120)
        uart.write(yerr_str_rrr+'\r\n')
        time.sleep_ms(120)

        print(xerr_str_1)
        print(yerr_str_2)
        print(xerr_str_3)
        print(yerr_str_4)
        print(xerr_str_5)
        print(yerr_str_6)
        print(xerr_str_7)
        print(yerr_str_8)
        print(xerr_str_rrr)
        print(yerr_str_rrr)

threshold=(13,49,18,61,6,47)
filtered_img=img.find_blobs([threshold])

while(True):
    clock.tick()
    img = sensor.snapshot().lens_corr(1.8)
    img = sensor.snapshot() # Take a picture and return the image.

    blobs = img.find_blobs([red_threshold])
    if blobs:
        max_blob = find_max(blobs)
        pan_error = max_blob.cx()-img.width()/2
        tilt_error = max_blob.cy()-img.height()/2
        num1=max_blob.cx()
        num2=max_blob.cy()
        #uart.write(num1)
        #uart.write(num2)

        #print("pan_error: ", pan_error)

        img.draw_rectangle(max_blob.rect()) # rect
        img.draw_cross(max_blob.cx(), max_blob.cy()) # cx, cy

# -----矩形框部分-----
    # 在图像中寻找矩形
    for r in img.find_rects(threshold = 10000):
        # 判断矩形边长是否符合要求
        if r.w() < 130 and r.h() < 130 and r.w()>20 and r.h()>20:
            # 在屏幕上框出矩形
            img.draw_rectangle(r.rect(), color = (255, 0, 0), scale = 4)
            # 获取矩形角点位置
            corner = r.corners()
            # 在屏幕上圈出矩形角点
            img.draw_circle(corner[0][0], corner[0][1], 5, color = (0, 0, 255), thickness = 2, fill = False)
            img.draw_circle(corner[1][0], corner[1][1], 5, color = (0, 0, 255), thickness = 2, fill = False)
            img.draw_circle(corner[2][0], corner[2][1], 5, color = (0, 0, 255), thickness = 2, fill = False)
            img.draw_circle(corner[3][0], corner[3][1], 5, color = (0, 0, 255), thickness = 2, fill = False)
            x_values = [corner[0][0],corner[1][0], corner[2][0], corner[3][0]]
            y_values = [corner[0][1],corner[1][1],corner[2][1],corner[3][1]]
            center_x = sum(x_values) / len(x_values)
            center_y = sum(y_values) / len(y_values)
            angles = []
            for x, y in zip(x_values, y_values):
                angle = math.atan2(y - center_y, x - center_x)  # 计算角度
                angles.append(angle)

            sorted_coordinates = [coord for _, coord in sorted(zip(angles, zip(x_values, y_values)))]
            #print(sorted_coordinates[0][0])
            #output_str1="%d" % (corner[0][0])
            #output_str2="%d" % (corner[0][1])
            #uart.write(output_str1+'\r\n')
            #time.sleep_ms(100)
            #uart.write(output_str2+'\r\n')
            recive_data()
