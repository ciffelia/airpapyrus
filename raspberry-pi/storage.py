import os
import requests


url = os.environ["POST_URL"]
access_client_id = os.environ["ACCESS_CLIENT_ID"]
access_client_secret = os.environ["ACCESS_CLIENT_SECRET"]


def post(data):
    headers = {
        "CF-Access-Client-Id": access_client_id,
        "CF-Access-Client-Secret": access_client_secret,
    }

    try:
        requests.post(url, headers=headers, data=data, timeout=5.0)
    except requests.exceptions.RequestException as err:
        print(f"HTTP request error: {err}")
