# -*- coding: utf-8 -*-

from enum import IntEnum
from PIL import Image, ImageDraw, ImageFont
from datetime import datetime


WIDTH = 264
HEIGHT = 176


class Color(IntEnum):
    WHITE = 0xFF
    LIGHT_GRAY = 0xC0
    DARK_GRAY = 0x80
    BLACK = 0x00


dummy_image = Image.new("L", (0, 0))
dummy_draw = ImageDraw.Draw(dummy_image)

font_20 = ImageFont.truetype("fonts/x14y20pxScoreDozer.ttf", 20)
font_40 = ImageFont.truetype("fonts/x14y20pxScoreDozer.ttf", 40)


def text_to_image(text, font, color=Color.BLACK):
    width, height = dummy_draw.textsize(text, font)

    image = Image.new("LA", (width, height))
    draw = ImageDraw.Draw(image)

    draw.text((0, 0), text, (color, 255), font)

    return image


def generate_label(value, unit, line_spacing=0):
    value_image = text_to_image(value, font_40)
    unit_image = text_to_image(unit, font_20)

    if len(unit) == 1:
        # Single line
        width = value_image.width + unit_image.width
        height = value_image.height
    else:
        # Two lines
        width = value_image.width
        height = value_image.height + line_spacing + unit_image.height

    image = Image.new("LA", (width, height))

    # Upper left
    image.paste(value_image)

    # Bottom right
    image.paste(
        unit_image,
        box=(image.width - unit_image.width, image.height - unit_image.height),
    )

    return image


def paste_center(image1, image2, xy):
    x = xy[0] - image2.width // 2
    y = xy[1] - image2.height // 2

    alpha_band = image2.split()[-1]

    image1.paste(image2, mask=alpha_band, box=(x, y))


def draw_measurement_value(image, value):
    temperature_text = str(round(value["temperature"], 1))
    humidity_text = str(round(value["humidity"], 1))
    pressure_text = str(round(value["pressure"] / 100))  # Pa to hPa
    co2_text = str(round(value["co2"]))

    temperature_image = generate_label(temperature_text, "℃")
    humidity_image = generate_label(humidity_text, "%")
    pressure_image = generate_label(pressure_text, "hPa")
    co2_image = generate_label(co2_text, "ppm")

    x1 = WIDTH // 4
    x2 = x1 * 3
    y1 = (HEIGHT - 36) // 4
    y2 = y1 * 3

    paste_center(image, temperature_image, (x1, y1))
    paste_center(image, humidity_image, (x2, y1))
    paste_center(image, pressure_image, (x1, y2))
    paste_center(image, co2_image, (x2, y2))


def draw_no_data(image):
    no_data_image = text_to_image("No data", font_40)

    x = WIDTH // 2
    y = (HEIGHT - 36) // 2

    paste_center(image, no_data_image, (x, y))


def draw_datetime(image, dt):
    dt_text = dt.strftime("%Y/%m/%d (%a) %H:%M")
    dt_image = text_to_image(dt_text, font_20, Color.WHITE)

    paste_center(image, dt_image, (WIDTH // 2, HEIGHT - 18))


def generate_image(value):
    image = Image.open(f"assets/background.png")

    if value is None:
        draw_no_data(image)
    else:
        draw_measurement_value(image, value)

    draw_datetime(image, datetime.now())

    return image
