import os
import ssl
import urllib.request
import json


url = os.environ["POST_URL"]
cert_file = os.environ["CERT_FILE"]
key_file = os.environ["KEY_FILE"]


def post(data):
    context = ssl.create_default_context()
    context.load_cert_chain(cert_file, key_file)

    opener = urllib.request.build_opener(urllib.request.HTTPSHandler(context=context))

    headers = {
        "Content-Type": "application/json",
    }
    req = urllib.request.Request(
        url, method="POST", headers=headers, data=json.dumps(data).encode()
    )

    try:
        with opener.open(req, timeout=5) as res:
            pass
    except urllib.error.URLError as err:
        print(f"HTTP request error: {err.reason}")
