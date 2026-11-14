import serial
import time


# Open the UART connection to ESP32.
uart = serial.Serial(
    port="/dev/serial0",
    baudrate=115200,
    timeout=2
)

time.sleep(1)

try:
    # Send a test message.
    message = "Hello from Raspberry Pi!"
    uart.write((message + "\n").encode("utf-8"))

    print(f"Sent: {message}")

    # Read the response from ESP32.
    response = uart.readline().decode("utf-8").strip()

    if response:
        print(f"Received: {response}")
    else:
        print("No response received.")

finally:
    uart.close()