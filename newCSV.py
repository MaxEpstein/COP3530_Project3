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
        writer.writerow([str(matrix[i,0]), str(matrix[i,1]), str(matrix[i,2]), str(matrix[i,3]), str(matrix[i,4]), str(matrix[i,5])])
