# -*- coding: utf-8 -*-

from datetime import datetime
from time import sleep
import usbserial
import display
import epaper
import storage


def main():
    while True:
        value = usbserial.read()

        image = display.generate_image(value)
        epaper.draw(image)

        if value is not None:
            storage.post(value)

        sleep(60 - datetime.now().second)


if __name__ == "__main__":
    main()
