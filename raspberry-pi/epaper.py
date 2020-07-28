# -*- coding: utf-8 -*-

from PIL import ImageOps
from waveshare_epd import epd2in7

epd = epd2in7.EPD()


def draw(image):
    # なぜか左右反転して表示されるので
    mirror_image = ImageOps.mirror(image)

    buffer = epd.getbuffer_4Gray(mirror_image)

    try:
        epd.Init_4Gray()
        epd.display_4Gray(buffer)

    except KeyboardInterrupt:
        print("Shutting down e-Paper...")
        epd.sleep()
        exit()

    epd.sleep()
