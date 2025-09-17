# Updater – Automatic Arduino Firmware Updates

[![CI](https://github.com/Bitworx-cz/Updater/actions/workflows/ci4main.yml/badge.svg)](https://github.com/Bitworx-cz/Updater/actions/workflows/ci4main.yml)
[![Get Token](https://img.shields.io/badge/Get%20Token-updater.bitworx.cz-blue?style=for-the-badge)](https://updater.bitworx.cz/token)
[![Website](https://img.shields.io/badge/Website-updater.bitworx.cz-brightgreen?style=for-the-badge)](https://updater.bitworx.cz)

Keep your Arduino-based devices up to date effortlessly.
This library allows your boards to **periodically check for new firmware and install updates automatically**.

---

## 🚀 Quick Start

### 1. Get an Access Token

Before your device can update, you need a token.
👉 [Generate your token here](https://updater.bitworx.cz/token)

---

### 2. Install the Library

1. Open the **Arduino IDE**
2. Go to **Sketch → Include Library → Manage Libraries…**
3. Search for **Updater**
4. Click **Install**

---

### 3. Add Update Logic

In your sketch, include the library and add update checks to your loop:

```cpp
#include <Updater.h>

void loop() {
    // Your normal logic here...

    // Example: check for updates every few hours
    updater.TryUpdate("yourTokenHere", "yourSwName.ino");
}
```

* Replace **`yourTokenHere`** with the token you generated
* Replace **`yourSwName.ino`** with your firmware name

---

### 4. Upload & Run

Upload your sketch to the Arduino board.
Your device will now **check for new firmware and update automatically**.

---

## 🛠 CI/CD Example (GitHub Actions)

You can automate building and uploading your firmware using GitHub Actions.
Replace `YOUR_TOKEN_HERE` with a token generated on [updater.bitworx.cz/token](https://updater.bitworx.cz/token).

```yaml
name: Build & Upload ESP32-C3 Sketch Example

on:
  push:
    branches:
      - main

jobs:
  build-and-upload:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout repository
        uses: actions/checkout@v4

      - name: Set up Arduino CLI
        uses: arduino/setup-arduino-cli@v2
        with:
          version: 1.3.1

      - name: Install ESP32 core
        run: |
          arduino-cli core update-index
          arduino-cli core install esp32:esp32@2.0.17

      - name: Compile sketch
        run: |
          FILE=$(find . -name "*.ino" | head -n 1)
          NAME=$(basename "$FILE" .ino)
          rm -rf ./build
          arduino-cli compile \
            --fqbn esp32:esp32:esp32c3:PartitionScheme=default \
            --output-dir ./build \
            --export-binaries \
            --clean \
            "$FILE"
          BIN="./build/${NAME}.ino.bin"
          OTA_BIN="./build/${NAME}.ino.esp32c3.bin"
          cp "$BIN" "$OTA_BIN"
          echo "Prepared OTA binary: $OTA_BIN"

      - name: Upload OTA binary
        run: |
          curl -X POST http://espupdater.runasp.net/upload \
            -F "filename=$(basename $OTA_BIN)" \
            -F "token=YOUR_TOKEN_HERE" \
            -F "platform=ESP32-C3" \
            -F "file=@$OTA_BIN"
```

---

## ✅ That’s it!

Your microcontrollers are now self-updating, secure, and always on the latest version.

---

## 📖 More

* Website: [updater.bitworx.cz](https://updater.bitworx.cz)
* Token generator: [updater.bitworx.cz/token](https://updater.bitworx.cz/token)
