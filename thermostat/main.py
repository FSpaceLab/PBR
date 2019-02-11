import serial
import matplotlib.pyplot as plt
import numpy as np
from datetime import datetime
import re

temp_x = []
temp_y = []
hum_x = []
hum_y = []


HUMIDITY = 1
TEMPERATURE = 2
HEAT_INDEX = 3

pattern = '^Humidity: ([0-9.]+) per.  Temperature: ([0-9.]+) C Heat index: ([0-9.]+) C$'

ser = serial.Serial('COM6', 9600)
i = 600
j = 0
while i>0:
    data = ser.readline().decode()
    print(f"{data} | iter {i}")
    if j == 0:
        temp_y.append(data[35:40])
        temp_x.append(datetime.now().time().isoformat()[:-7])

        hum_y.append(data[10:15])
        hum_x.append(datetime.now().time().isoformat()[:-7])

    j = j + 1 if j<60 else 0


    i -= 1

fig = plt.figure()
ax = plt.subplot(111)
ax.plot(temp_x, temp_y, label='y = temperature\nx = time')
plt.title('Залежність зміни температури від часу при охолодженні')
plt.gcf().autofmt_xdate()
ax.legend()
fig.savefig('plot1.png')

plt.show()

