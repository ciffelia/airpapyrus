import serial
import re

ser = serial.Serial("/dev/ttyUSB0", baudrate=115200)

pattern = re.compile(
    r"^\[airpapyrus_report\]([\d\.]+),([\d\.]+),([\d\.]+),([\d\.]+),([\d\.]+)\r\n",
    re.MULTILINE,
)


def read_from_serial():
    bytesToRead = ser.in_waiting
    return ser.read(bytesToRead).decode("utf-8")


def read():
    text = read_from_serial()

    try:
        *_, last_match = pattern.finditer(text)
    except ValueError:
        # No match
        return None

    temperature, humidity, pressure, co2, tvoc = last_match.groups()

    return {
        "temperature": float(temperature),
        "humidity": float(humidity),
        "pressure": float(pressure),
        "co2": int(co2),
        "tvoc": int(tvoc),
    }
