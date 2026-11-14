import serial
import time

# Open UART connection.
ser = serial.Serial(
    "/dev/serial0",
    115200,
    timeout=1
)

time.sleep(2)

test_messages = [
    '{"v":1,"type":"drive","seq_num":1,"motors":[80,80,75,80,80,80]}',
    '{"v":1,"type":"stop","seq_num":2}',
    '{"v":1,"type":"drive","seq_num":3,"motors":[150,80,75,80,80,80]}'
]

for message in test_messages:
    print(f"Sending: {message}")

    ser.write((message + "\n").encode("utf-8"))

    time.sleep(0.2)

ser.close()