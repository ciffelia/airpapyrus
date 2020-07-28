# -*- coding: utf-8 -*-

from datetime import datetime
from time import sleep
import ble
import display
import epaper
import storage


def main():
    while True:
        _, measurementValue = ble.scan(5.0)

        image = display.generate_image(measurementValue)
        epaper.draw(image)

        if measurementValue is not None:
            storage.post(measurementValue._asdict())

        sleep_for_sec = max(0, 55 - datetime.now().second)
        sleep(sleep_for_sec)


if __name__ == "__main__":
    main()
