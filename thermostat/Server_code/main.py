import serial
import matplotlib.pyplot as plt
import csv
from datetime import datetime


temp_x = []
temp_y = []
hum_x = []
hum_y = []

pattern = '^Humidity: ([0-9.]+) per.  Temperature: ([0-9.]+) C Heat index: ([0-9.]+) C$'

ser = serial.Serial('COM6', 9600)
i = 2400
j = 0

csv_header = [["time", "temp", "humidity"]]

csvFile = open('serialReader/temp_data.csv', 'w')

writer = csv.writer(csvFile)
writer.writerows(csv_header)

while i>0:
    data = ser.readline().decode()
    print(f"{data} | iter {i}")

    current_time = datetime.now().time().isoformat()[:-7]
    temperature = data[35:40]
    humidity = data[10:15]

    writer.writerows([[current_time, temperature, humidity]])

    if j == 0:
        temp_x.append(current_time)
        temp_y.append(temperature)

    j = j + 1 if j<240 else 0


    i -= 1

csvFile.close()

fig = plt.figure()
ax = plt.subplot(111)
ax.plot(temp_x, temp_y, label='y = temperature\nx = time')
plt.gca().invert_yaxis()
plt.gcf().autofmt_xdate()
plt.title('Залежність зміни температури від часу при охолодженні')
ax.legend()
fig.savefig('serialReader/plot.png')

plt.show()

