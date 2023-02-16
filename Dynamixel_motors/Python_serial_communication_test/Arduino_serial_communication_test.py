import serial
import time

ser = serial.Serial('/dev/ttyACM0', 57600, timeout=1)

time.sleep(1)
ser.read(100)
# ser.write(b'1')

for i in range(0, 2):
    # time.sleep(0.1)
    ser.write(b'2')
    time.sleep(0.1)
    x = ser.read(15)
    print(x)

ser.close()
pd.Series(kirigami_area_arr), pd.Series(kirigami_perimeter_arr), pd.Series(kirigami_width_arr), pd.Series(kirigami_height_arr), pd.Series(kirigami_aspect_ratio_arr), pd.Series(hole_area_arr), pd.Series(hole_perimeter_arr), pd.Series(hole_width_arr), pd.Series(hole_height_arr), pd.Series(hole_aspect_ratio_arr)