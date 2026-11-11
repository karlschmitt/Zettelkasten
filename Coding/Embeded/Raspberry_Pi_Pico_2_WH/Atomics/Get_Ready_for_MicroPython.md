---
id: 20261022174224
title: Get ready for MicroPython
author: Karl Schmitt
date: 2026-10-22
---

# Get ready for MicroPython

Getting your **Raspberry Pi Pico 2 WH** (or Pico 2 W) ready for MicroPython _involves a simple drag-and-drop firmware installation_. Because it is powered by the newer **RP2350** chip, it requires specific firmware separate from the older RP2040-based Pico W. \[[1](https://raspberry.tips/en/raspberrypi-einsteiger/raspberry-pi-pico-getting-started-micropython), [2](https://www.youtube.com/watch?v=YM39P4dUpnM\&t=2), [3](https://www.youtube.com/watch?v=F82MrOkheSE\&t=117), [4](https://randomnerdtutorials.com/getting-started-raspberry-pi-pico-2-w/)]

Here is the step-by-step process to get it ready:

### Step 1: Download the MicroPython Firmware

![Micropython Logo](../../Images/Micropython-logo.png)

1. Head to the official MicroPython download page for the Pico 2 W / WH Firmware.
2. Scroll down to the **Firmware / Releases** section.
3. Download the latest stable **`.uf2`** file (avoid the "preview" builds unless you need experimental features). \[[1](https://micropython.org/download/RPI_PICO2_W/), [2](https://www.elektronik-kompendium.de/sites/raspberry-pi/2611081.htm), [3](https://raspberry.tips/en/raspberrypi-einsteiger/raspberry-pi-pico-getting-started-micropython)]

### Step 2: Boot the Pico 2 WH into BOOTSEL Mode

1. Grab a Micro-USB cable that supports **data transfer** (some cables only provide power).
2. **If your board is brand new:** Simply plug it into your computer. A completely empty board will enter bootloader mode automatically.
3. **If it has been used before:** Press and hold the small white **BOOTSEL** button on the Pico, plug the USB cable into your computer, and then release the button.
4. Your computer will detect the board as a removable USB storage drive named **`RP2350`**. \[[1](https://www.raspberrypi.com/documentation/microcontrollers/micropython.html), [2](https://raspberry.tips/en/raspberrypi-einsteiger/raspberry-pi-pico-getting-started-micropython)]

### Step 3: Flash the Firmware

1. Open the `RP2350` volume in your computer's file explorer.
2. **Drag and drop** (or copy) the downloaded `.uf2` file directly onto the root of the drive.
3. The file will transfer, the drive will automatically unmount, and the Pico 2 WH will reboot into MicroPython mode. \[[1](https://www.youtube.com/watch?v=2d21MBF4i6Q), [2](https://raspberry.tips/en/raspberrypi-einsteiger/raspberry-pi-pico-getting-started-micropython), [3](https://www.youtube.com/watch?v=AxyUdMSyes0\&t=140), [4](https://www.elecrow.com/blog/getting-started-with-raspberry-pi-pico-2-on-all-in-one-starter-kit.html?srsltid=AYCX9vLvBN2NHY3v64TMiWtlxkxCGVxWUJwx4t853ndd-c2h2CUdW4z8)]

***

### Step 4: Program with an IDE

To start writing Python code, you need an editor that can talk to the Pico's serial connection. \[[1](https://www.raspberrypi.com/documentation/microcontrollers/micropython.html), [2](https://raspberry.tips/en/raspberrypi-einsteiger/raspberry-pi-pico-getting-started-micropython)]

Option A: Using Thonny IDE (Easiest)

1. Download and install [Thonny IDE](https://thonny.org/).
2. Open Thonny, look at the **bottom right corner** of the window, and click on the current interpreter text.
3. Select **`MicroPython (Raspberry Pi Pico)`** from the list.
4. The terminal (Shell) at the bottom will display the MicroPython prompt (`>>>`), confirming it is successfully connected to your RP2350 board. \[[1](https://www.youtube.com/watch?v=I7p-vmC8XfU\&t=406), [2](https://www.youtube.com/watch?v=2d21MBF4i6Q), [3](https://raspberry.tips/en/raspberrypi-einsteiger/raspberry-pi-pico-getting-started-micropython)]

Option B: Using Visual Studio Code

1. Install [VS Code](https://code.visualstudio.com/).
2. Search for and install the **`MicroPico`** extension.
3. Connect your Pico, configure the extension to map to your device's serial port, and use the integrated terminal to run your commands. \[[1](https://www.youtube.com/watch?v=F82MrOkheSE\&t=117)]

Quick Verification Code

To ensure everything works, type the following into the interpreter shell and hit Enter: \[[1](https://www.youtube.com/watch?v=3qTxBXVQ4yo\&t=7), [2](https://www.youtube.com/watch?v=I7p-vmC8XfU\&t=406)]
```python
print("Hello from Pico 2 WH!")
```

Use code with caution.

If it prints the message back to you, your setup is complete and ready for your first project! \[[1](https://www.youtube.com/watch?v=I7p-vmC8XfU\&t=406)]

Would you like to write a **basic script to blink the onboard LED** to start testing, or are you looking to immediately connect the device to **Wi-Fi** or **Bluetooth**?
