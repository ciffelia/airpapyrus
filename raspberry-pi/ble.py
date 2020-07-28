# -*- coding: utf-8 -*-

import struct
from collections import namedtuple
from bluepy.btle import Scanner


# Test company ID
myCompanyId = "ffff"

AdvertisePayload = struct.Struct("<fffHH")

MeasurementValue = namedtuple(
    "MeasurementValue", "temperature humidity pressure co2 tvoc"
)


def scan(timeout):
    scanner = Scanner()
    devices = scanner.scan(timeout)

    for device in devices:
        # Ad Type 0x09: Complete Local Name
        deviceName = device.getValueText(0x09)
        if deviceName != "airpapyrus":
            continue

        # Ad Type 0xFF: Manufacturer Specific Data
        adData = device.getValueText(0xFF)
        if adData is None:
            continue

        companyId = adData[0:4]
        if companyId != myCompanyId:
            continue

        return parseAirpapyrusAdvertise(adData)

    return None, None


def parseAirpapyrusAdvertise(advertise):
    seq = advertise[4:6]
    payload = bytes.fromhex(advertise[6:])

    measurementValue = MeasurementValue._make(AdvertisePayload.unpack(payload))

    return seq, measurementValue
