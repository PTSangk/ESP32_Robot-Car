
import datetime

#timestamp 
timestamp = datetime.datetime.now().strftime("%d-%m-%Y %H:%M:%S")

for i  in range(100):

        print(f"{timestamp} >> no: {i}")

