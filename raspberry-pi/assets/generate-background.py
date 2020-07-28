# -*- coding: utf-8 -*-

from enum import IntEnum
from PIL import Image, ImageDraw


WIDTH = 264
HEIGHT = 176


class Color(IntEnum):
    WHITE = 0xFF
    LIGHT_GRAY = 0xC0
    DARK_GRAY = 0x80
    BLACK = 0x00


def generate_icon(icon_name, size):
    image = Image.open(f"{icon_name}.png").convert("RGBA")
    resized_image = image.resize(size, Image.NEAREST)

    pixdata = resized_image.load()

    for x in range(size[0]):
        for y in range(size[1]):
            if pixdata[x, y][3] >= 128:
                pixdata[x, y] = (
                    Color.LIGHT_GRAY,
                    Color.LIGHT_GRAY,
                    Color.LIGHT_GRAY,
                    255,
                )
            else:
                pixdata[x, y] = (0, 0, 0, 0)

    return resized_image


def generate_background():
    image = Image.new("L", (WIDTH, HEIGHT), Color.WHITE)
    draw = ImageDraw.Draw(image)

    temp_icon = generate_icon("temperature", (70, 70))
    image.paste(temp_icon, mask=temp_icon, box=(0, 0))

    humidity_icon = generate_icon("humidity", (70, 70))
    image.paste(humidity_icon, mask=humidity_icon, box=(WIDTH // 2, 0))

    pressure_icon = generate_icon("pressure", (60, 60))
    image.paste(pressure_icon, mask=pressure_icon, box=(5, (HEIGHT - 36) // 2 + 5))

    co2_icon = generate_icon("co2", (70, 70))
    image.paste(co2_icon, mask=co2_icon, box=(WIDTH // 2 + 5, (HEIGHT - 36) // 2))

    # 縦の区切り線
    draw.line([(WIDTH / 2, 0), (WIDTH / 2, HEIGHT)], width=2, fill=Color.DARK_GRAY)

    # 横の区切り線
    draw.line(
        [(0, (HEIGHT - 36) / 2), (WIDTH, (HEIGHT - 36) / 2)],
        width=2,
        fill=Color.DARK_GRAY,
    )

    # 下部の日時表示の背景
    draw.rectangle([(0, HEIGHT - 36), (WIDTH, HEIGHT)], fill=Color.BLACK)

    return image


def main():
    image = generate_background()
    image.save("background.png")


if __name__ == "__main__":
    main()
