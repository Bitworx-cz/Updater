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

- Replace **`yourTokenHere`** with the token you generated  
- Replace **`yourSwName.ino`** with your firmware name  

---

### 4. Upload & Run
Upload your sketch to the Arduino board.  
Your device will now **check for new firmware and update automatically**.

---

## ✅ That’s it!
Your microcontrollers are now self-updating, secure, and always on the latest version.

---

## 📖 More
- Website: [updater.bitworx.cz](https://updater.bitworx.cz)  
- Token generator: [updater.bitworx.cz/token](https://updater.bitworx.cz/token)  
