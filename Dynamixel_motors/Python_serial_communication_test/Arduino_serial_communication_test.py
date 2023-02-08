import serial
import time

ser = serial.Serial('/dev/ttyACM0', 57600, timeout=1)

time.sleep(1)
ser.read(100)
ser.write(b'1')

for i in range(0, 100):
    # time.sleep(0.1)
    ser.write(b'2')
    x = ser.read(13)
    print(x)

ser.close()
