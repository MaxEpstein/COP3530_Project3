import pandas as pd
import csv
import string

data = pd.read_csv('Test.csv', usecols = [1, 2, 9, 14, 16, 17])

print(len(data))
matrix = data.to_numpy()
print(matrix[18][5])

file = open('NewTest.csv', 'w', newline='')

writer = csv.writer(file)
writer.writerow(["Month", "Day", "FlightNum", "ArrDelay", "Origin", "Dest"])
for i in range(len(data)):
   if (i < 200000):
        writer.writerow([matrix[i,0], matrix[i,1], matrix[i,2], matrix[i,3], matrix[i,4], matrix[i,5]])
