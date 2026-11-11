---
id: 20261022171858
title: Absolute Beginner Deep-Dive Tutorial
author: Karl Schmitt
date: 2026-10-22
---

# Raspberry Pi Pico 2 WH — Absolute Beginner Deep-Dive Tutorial

![Raspberry Pi Pico 2 WH – Elektor](https://images.openai.com/static-rsc-4/YSXAnd7zH66YDInBpqw4E_EWluIMknTn2wsMeLPUB-M2rGLEd5IgM053P8TkXPBHQDh_W6mqrCYMwvDXRO6AcG2k_CSAPgzV5YbLKRTfWdWNufqvhvNzmg5g48ulW7mq1DAclfsQG2_S6Q4mM7-vlkxNUHXsam9w3_VKupxugYc?purpose=inline)

![Raspberry Pi Pico 2 W RP2350 Pico2W ARM Cortex-M33 And RISC-V Hazard3 Wi-Fi4 Bluetooth5.2 CYW43439](https://images.openai.com/static-rsc-4/PjbtMLY0tQpyw92kssznOQKwSGlYq7stsFfpT6AAG86dt4bb8pveqiT3q-61t8P2xUMrR9YiX62AURbnK-HRA25VY4LecCYJH5MQeGVb96-7JNPLGViWwji3VRNagSdn0R1yfrvRGULx6bPW4CWCu65EcSi8iJ8gdCa7Kk-gzrk?purpose=inline)

![Electronic Circuit — SunFounder Pico 2 W Starter Kit for Raspberry Pi Pico 2 W  documentation](https://images.openai.com/static-rsc-4/lURC31pgi8kdOVbRa57bx3IviSLFDr01ydpG_Qi71ciLsXHJH4vzzWPQT0TrkHl8Tz_YGN0XGqiYdv5LMbTDGldNQYoinTaizGXULm_H4o_W_JSDFVFZqwUfFWbpOMldVrvGBJwLwD9P2o7O629sDPzXlDpPZIhARnT419cExZ8?purpose=inline)

8

Welcome to your Raspberry Pi Pico 2 WH journey! 😊 We will start from zero, explain what the hardware actually does, write our first programs, connect electronic components, and gradually build real projects.

This tutorial is designed around Windows 11, Visual Studio Code, and PowerShell, with practical exercises rather than simply copying code. The explanations and code examples are organized so that you can also turn them into Markdown notes in your Zettelkasten.

## 1. What exactly is a Raspberry Pi Pico 2 WH?

The Raspberry Pi Pico 2 WH is a small microcontroller development board. You can program it to read sensors, control LEDs, operate buttons, communicate with other devices, and perform many other physical-world tasks.

It is not the same kind of computer as your Windows PC or a Raspberry Pi 5.

![Raspberry Pi Pico 2 WH – Elektor](https://images.openai.com/static-rsc-4/YSXAnd7zH66YDInBpqw4E_EWluIMknTn2wsMeLPUB-M2rGLEd5IgM053P8TkXPBHQDh_W6mqrCYMwvDXRO6AcG2k_CSAPgzV5YbLKRTfWdWNufqvhvNzmg5g48ulW7mq1DAclfsQG2_S6Q4mM7-vlkxNUHXsam9w3_VKupxugYc?purpose=inline)

The Pico 2 WH

The physical device

A tiny programmable board with a processor, memory, GPIO pins, USB connectivity and wireless capability.

![Raspberry Pi Pico 2 WH / SC1634](https://images.openai.com/static-rsc-4/umEt_L5XgFHk-4Oe0G_s4FhSfERRWl61-mvwJ8rsYysZAakUETpMsUKnoLpmQR_yYjlwVXbZuSXFe7mRKGi4cbcsvUmsZGGEBBKDM0G4hVo45dotBcblMO5XK3bsGQNTWgPfgZjZZoiI7GxXAQ82m1-gpAoaJk4RHWv9YD3273A?purpose=inline)

Your Windows 11 PC

The development computer

You edit your code, transfer it to the board, inspect results and debug problems.

![電子工作の必需品！使ってみよう、ブレッドボード - 初歩からのエレクトリックDIYライフ](https://images.openai.com/static-rsc-4/rOmCd5G5QM23LrHyEgr8Ml1M3mohuiq2MkxW7fW_cMkyfcjQwTXjjc0EX59Ptgb3ffPv6Ga8qA2eOh7bUcd0x1m1hqbuKHH-I3cXXIVc8wLrYux7QboqbYmCgwKTJm8LphjkB7sw4MXYa-qP3Nqj_hKUTRJeAma22RH1WA2mXYU?purpose=inline)

The electronic circuit

The physical world

LEDs, buttons, sensors and other components let your program interact with its environment.

### The basic mental model

Think of the Pico as a tiny computer that can interact directly with the physical world.

Windows PC

Write and edit the program

USB cable — program transfer, serial communication and power

Pico 2 WH

Executes your program

Electronic components

LEDs, buttons, sensors, motors via suitable drivers

Your PC does not need to remain connected for most programs to run. Once a program has been transferred to the Pico and saved in its onboard flash storage, the board can generally run it independently when powered.

## 2. Understand the Pico 2 WH hardware

The following are the important specifications and what they mean for a beginner.

| Feature       | What it means                                                                      |
| ------------- | ---------------------------------------------------------------------------------- |
| Processor     | RP2350, a dual-core microcontroller                                                |
| CPU options   | Dual Arm Cortex-M33 cores or dual Hazard3 RISC-V cores, depending on configuration |
| Clock speed   | Up to 150 MHz                                                                      |
| SRAM          | 520 KB of on-chip RAM                                                              |
| Flash storage | Typically 4 MB onboard                                                             |
| GPIO          | 26 multifunction GPIO pins                                                         |
| Wireless      | 2.4 GHz Wi-Fi and Bluetooth 5.2 via the wireless subsystem                         |
| USB           | USB 1.1 device functionality                                                       |
| Power         | 5 V USB input; 3.3 V logic for GPIO                                                |
| Headers       | The `H` variant has pre-soldered headers                                           |

The exact wireless implementation, supported modes and software APIs depend on the firmware and libraries you use.

Two important safety rules:

* GPIO pins use 3.3 V logic. Do not connect 5 V signals directly to GPIO pins.

* GPIO pins cannot safely power arbitrary motors, relays or other high-current loads. Use suitable driver circuits and external power when necessary.

The letter `W` indicates wireless capability, while `H` indicates the version with headers already soldered to the board. Those headers make breadboard experiments much easier.

## 3. What you need before starting

## Beginner equipment checklist

0 of 7

Raspberry Pi Pico 2 W with headers

Your Pico 2 WH board

USB data cable

A cable that supports data, not just charging

Windows 11 PC

For editing, flashing and testing programs

Thonny IDE

The easiest starting point for MicroPython

Breadboard and jumper wires

For connecting components without soldering

LEDs and 220–330 Ω resistors

For the first external electronics experiments

Push button and optional sensor

For later input and measurement exercises

You can begin with just the board, USB cable and PC. You do not need to buy every component immediately.

## 4. Choose your programming language

The Pico 2 WH can be programmed in different languages. The two main paths are MicroPython and C/C++.

![Introduction to MicroPython](https://images.openai.com/static-rsc-4/nJi0oM0RGtCq-W1HyBsixknvW1eJA9lcBT_Ykua-M1Xp4A3rBQWJAkQDfY523_O_6CqH5jZixQAcSzk_OQAiyEpWg4UutseWhXpPFtgB07gaI9mRWDE3ClO33v7-gtTL1UDPg-eg4i6m8G1I599HNZIyTulbZY_QEZnKpbjoVCk?purpose=inline)

Path A — MicroPython (recommended first)

Start here

Write readable Python code, interactively test instructions and experiment with hardware without compiling a complete application. This is the quickest way to understand microcontrollers.

![$12.99 - Raspberry Pi Pico 2 RP2350 with Headers Pre-Soldered Assembled - Tinkersphere](https://images.openai.com/static-rsc-4/bNWX1hjkPTcv-AnMRhgh9auVmTvawip_4MuAdIxktGKfDsE1qC2Qs1ZIgSbXhnc1fvn93vAJ1AAIKwD9prgu1TLtMZyL0gcuhEuWggZq3oeNAEt1kMrBkUj_IJ3Imr0kcdGilJmLeYWciU4uMneh4BAZG_Hd0o8fS017N-QJpbM?purpose=inline)

Path B — C/C++ SDK

Use the Raspberry Pi Pico SDK, CMake and a C/C++ compiler. This is an excellent later step if you want more control over performance, low-level hardware and embedded software architecture.

I recommend starting with MicroPython, then doing a second learning phase in C/C++. The concepts you learn about GPIO, voltage, timing, sensors and communication transfer to both paths.

## 5. Set up the software on Windows 11

### Step 1 — Download the correct firmware

Firmware is the software that allows the Pico to execute MicroPython programs.

Open the official MicroPython download page:

[Download MicroPython firmware for Pico 2 W (official site)](https://micropython.org/download/RPI_PICO2_W/?utm_source=chatgpt.com).

![](https://www.google.com/s2/favicons?domain=https://micropython.org\&sz=32)

Python for microcontrollers

+1

Important: use the firmware for Pico 2 W, not the original Pico, original Pico W, or non-wireless Pico 2.

### Step 2 — Put the Pico into bootloader mode

![The microcomputer 'Raspberry Pi Pico 2 W' that can use Wi-Fi and Bluetooth has arrived, so we'll do a quick photo review - GIGAZINE](https://images.openai.com/static-rsc-4/rOl8QqID5vZY_hjm4hj_1hQsqmYLBcUBVOO5cW1ME40uyU3Ps9wprl_pin42a7CpwNepXTrfNuSPl9_wwOu1BTHk8Sb_MH8FeOyWw8SR5PXqmLhASacTN7mS3tgYZPwS-Lf4s3JRNvrAJ1AwR0JH3rrmHW3miXb9OVyY6zDB8S0?purpose=inline)

![get-started-robo-pico-circuitpyhton-setting-up-robo-pico](https://images.openai.com/static-rsc-4/RcGa0ejC3Kts7_boK7U8k7VRgkAM7Ujs3pE1SPEA33UpdvVjcwr1MrpnP94YQBN7PwzMzLIIg_tlfRfFTFd2iitn4RtR3Zot7Og_1lzzcLNoG7tN9YO9I1LTkdIZVYYS86JvpcM_fWW9GEAhBBjghnr3pF4hMjw1irSaUnzQ7TE?purpose=inline)

Follow these steps:

1. Disconnect the Pico from USB.

2. Find the small button marked `BOOTSEL`.

3. Press and hold `BOOTSEL`.

4. While holding it, connect the USB cable to your PC.

5. Release the button after connecting.

6. Open File Explorer.

Windows should show a removable drive, commonly named `RPI-RP2`.

This is the board's bootloader mode. It lets you install firmware without having to run a program already stored on the board.

### Step 3 — Install MicroPython

1. Download the stable `.uf2` firmware file from the official page.

2. Open the `RPI-RP2` drive in File Explorer.

3. Copy the downloaded `.uf2` file onto that drive.

4. Wait for the board to restart.

The removable drive should disappear when the Pico reboots. That is normal.

The firmware is now installed. You normally do not have to repeat this procedure each time you connect the board.

![](https://www.google.com/s2/favicons?domain=https://micropython.org\&sz=32)

Python for microcontrollers

+1

### Step 4 — Install Thonny

Visit [Thonny's official website](https://thonny.org/?utm_source=chatgpt.com) and install the Windows version.

Thonny provides three useful things:

* An editor for writing Python code.

* A way to execute code on the Pico.

* A Shell or REPL where you can enter individual instructions and see their results.

Although you can use Visual Studio Code for editing, Thonny is a convenient first tool because it handles the connection to the microcontroller for you.

### Step 5 — Connect Thonny to the Pico

1. Open Thonny.

2. Find the interpreter selection, usually in the bottom-right corner.

3. Select a MicroPython interpreter for the Raspberry Pi Pico.

4. Choose the USB serial port belonging to your board if prompted.

5. Open the Shell panel.

If the board does not appear, disconnect and reconnect it, check that you used a data-capable USB cable, and verify that Windows recognizes its serial interface.

## 6. Your first program: Hello, Pico!

Before controlling a physical component, let's confirm that your program executes.

Enter this in Thonny's Shell:

```
print("Hello, Pico 2 WH!")
```

Press Enter.

Expected output:

```
Hello, Pico 2 WH!
```

Congratulations! You have executed your first Python instruction on the microcontroller.

### What did you just do?

* `print()` is a Python function that displays information.

* `"Hello, Pico 2 WH!"` is a string, meaning a sequence of text characters.

* The parentheses tell Python what value to pass to the function.

Try changing the text:

```python
print("I am learning embedded systems.")
print(2 + 3)
print("The answer is:", 42)
```

Expected output:

```
I am learning embedded systems.
5
The answer is: 42
```

Exercise: Print your own message and calculate `150 + 75`. Then try `150 / 75`.

This is a small exercise, but it establishes an important principle: the Pico runs instructions, calculates values and produces output.

## 7. Understand the REPL

REPL stands for Read–Evaluate–Print Loop.

It lets you enter one instruction at a time and immediately see the result.

Read

You enter `2 + 3`.

Evaluate

MicroPython calculates the expression.

Print

The Shell displays `5`.

The REPL is ideal for experimenting with a new function before putting it into a complete program.

For example:

```python
temperature = 21
print(temperature)
print(temperature + 5)
```

The first line stores the value `21` in a variable called `temperature`. The next lines display the stored value and calculate a new value.

## 8. Make the onboard LED blink

Now we move from software into physical computing.

The Pico 2 W has a wireless-capable board design and a programmable onboard LED. The MicroPython firmware for this board provides access to the LED through the `Pin` API.

![Raspberry Pi Pico 2 W Microcontroller Board, Based on Official RP2350 Chip, Dual-core & Dual-architecture Design, Supports WIFI and Bluetooth](https://images.openai.com/static-rsc-4/t1MKW8rb135GR0HUx5OmOuikhxYF4XN0yzZU6H1tLzekkuin_8i07vOt-hQ6Pt_otLeGziScGN20WSZ8v4g-spxeo1zwggw7UGnfTofEjfpgFY51p5cH2i2DbCEDmah_PFi3PKdH3Yqa9yxOP6Q5FG1XtUwx6T0TqCrwGM3lbLI?purpose=inline)

[waveshare.com](https://www.waveshare.com/raspberry-pi-pico-2-w.htm?utm_source=chatgpt.com)

### Step 1 — Understand the program

Here is the complete example:

```python
from machine import Pin
from time import sleep

led = Pin("LED", Pin.OUT)

while True:    
    led.on()    
    sleep(1)    
    led.off()    
    sleep(1)
```

Save this as `main.py` on the Pico if you want it to run automatically whenever the board starts.

### Step 2 — Explain every line

| Code                      | Meaning                                             |
| ------------------------- | --------------------------------------------------- |
| `from machine import Pin` | Imports the pin-control functionality.              |
| `from time import sleep`  | Imports a function that pauses the program.         |
| `Pin("LED", Pin.OUT)`     | Configures the onboard LED connection as an output. |
| `while True:`             | Starts a loop that repeats indefinitely.            |
| `led.on()`                | Turns the LED on.                                   |
| `sleep(1)`                | Pauses for approximately one second.                |
| `led.off()`               | Turns the LED off.                                  |

The colon after `while True:` begins a code block. The indented lines belong to that block and are repeated.

### Step 3 — Follow the program's execution

Start the program

LED ON

Wait 1 second

LED OFF

Wait 1 second

Repeat from LED ON

### Step 4 — Experiment

Change both `sleep(1)` calls to `sleep(0.2)`. The LED should blink much faster.

Then try:

```
sleep(2)
```

The LED stays in its current state for about two seconds before the program continues.

Important: `while True` never ends on its own. In Thonny, use the Stop button or interrupt execution if you need to stop the program. A program saved as `main.py` also starts again when the Pico restarts.

If the LED does not blink, first check that the correct firmware was installed and that the Pico is selected as the interpreter. Do not assume that the GPIO pin used for an external LED is the same as the board's onboard LED interface.

## 9. Learn the GPIO pins

GPIO means General-Purpose Input/Output.

These pins allow the Pico to communicate with external electronics. A pin can often be configured as an input or an output, and some pins support additional functions such as PWM, ADC, I²C, SPI and UART.

![Raspberry Pi Pico 2 W RP2350 Pico2W ARM Cortex-M33 And RISC-V Hazard3 Wi-Fi4 Bluetooth5.2 CYW43439](https://images.openai.com/static-rsc-4/PjbtMLY0tQpyw92kssznOQKwSGlYq7stsFfpT6AAG86dt4bb8pveqiT3q-61t8P2xUMrR9YiX62AURbnK-HRA25VY4LecCYJH5MQeGVb96-7JNPLGViWwji3VRNagSdn0R1yfrvRGULx6bPW4CWCu65EcSi8iJ8gdCa7Kk-gzrk?purpose=inline)

[spotpear.com](https://spotpear.com/shop/Raspberry-Pi-Pico-2W-RP2350A-WIFI4-Bluetooth5-CYW43439.html?utm_source=chatgpt.com)

Use the official pinout reference when wiring circuits: [Raspberry Pi Pico-series documentation](https://www.raspberrypi.com/documentation/microcontrollers/pico-series.html?utm_source=chatgpt.com).

![](https://www.google.com/s2/favicons?domain=https://github.com\&sz=32)

GitHub

+1

### The two most important GPIO modes

Output

The Pico sends a digital signal to another component.

Example: turn an LED on or off.

Input

The Pico reads a digital signal from another component.

Example: detect a button press.

A digital GPIO signal is commonly represented by two logical states:

* `0` — LOW

* `1` — HIGH

For the Pico's GPIO logic, LOW is near 0 V and HIGH is near 3.3 V. These are logic levels, not a promise that a pin can supply unlimited current.

### A simple digital output

For an external LED, we might configure GPIO 15 as an output:

```
from machine import Pinled = Pin(15, Pin.OUT)led.value(1)  # HIGHled.value(0)  # LOW
```

This code controls GPIO 15, not the onboard LED. Connect an external LED circuit before running it if you want to observe a physical result.

## 10. Your first external circuit: an LED

Now you can make your own circuit rather than relying on the onboard LED.

![2.1 こんにちは、LED！ — SunFounder Pico 2 W Starter Kit for Raspberry Pi Pico 2 W  ドキュメント](https://images.openai.com/static-rsc-4/1COaogPXai7PkxliwsDij0aQTItqoOb1zUmYvP7Ui1FM5qL89vZpSJLP7gwtoagbcGdHdN2dElEsSLomp5dumYLy_zWO2OAKz5t8Y-JyobAAaCDjD3ZCZWt-HB87lkfE28HSwHMbrh733AK1pWIBDTliBN-oRvc_KCV84ZoHKus?purpose=inline)

[docs.sunfounder.com](https://docs.sunfounder.com/projects/pico-2w-kit/ja/latest/pyproject/py_led.html?utm_source=chatgpt.com)

### Components

* One red LED

* One 220–330 Ω resistor

* A breadboard

* Jumper wires

* Your Pico 2 WH

### Wiring diagram

Conceptual circuit: GPIO 15 supplies the signal through a series resistor and LED to ground. The breadboard placement and exact header positions are not shown to scale.

The LED has polarity:

* The anode is the positive side.

* The cathode is the negative side.

A resistor limits current. Without it, excessive current can damage the LED or GPIO pin.

For a red LED with an approximate forward voltage of 2 V, a 330 Ω resistor gives an approximate current of:

\\\[ I=\frac{3.3-2.0}{330}\approx 0.00394\text{ A} \\]

That is approximately 3.9 mA, a reasonable starting point for this simple demonstration.

### Test program

```
from machine import Pinfrom time import sleepled = Pin(15, Pin.OUT)while True:    led.toggle()    sleep(0.5)
```

`toggle()` switches the output from its current logical state to the opposite state. The LED should alternate between on and off.

Exercise: Change `sleep(0.5)` to `sleep(0.1)`, then `sleep(2)`. Observe the difference.

## 11. Read a push button

An LED teaches us about output. A button teaches us about input.

The idea is simple: when the button is pressed, the Pico detects a change in the electrical signal.

For this exercise, connect a normally open push button between GPIO 14 and GND. We will use the Pico's internal pull-up resistor.

Internal pull-up

Keeps the input HIGH when the button is not pressed

Button released

GPIO 14 reads 1 (HIGH)

Button pressed

GPIO 14 connects to GND and reads 0 (LOW)

### Program

```
from machine import Pinfrom time import sleepbutton = Pin(14, Pin.IN, Pin.PULL_UP)while True:    if button.value() == 0:        print("Button pressed!")        sleep(0.2)
```

The `if` statement checks whether the condition is true. When the button is pressed, the program prints a message.

The `sleep(0.2)` introduces a small delay. This helps prevent excessive repeated messages, but it is not a complete solution to switch bounce. Later, you can learn proper debouncing.

### Make the button control an LED

Wire an LED and resistor to GPIO 15 as in the previous exercise. Then combine input and output:

```
from machine import Pinfrom time import sleepbutton = Pin(14, Pin.IN, Pin.PULL_UP)led = Pin(15, Pin.OUT)while True:    if button.value() == 0:        led.on()    else:        led.off()    sleep(0.01)
```

When you press the button, the LED turns on. When you release it, the LED turns off.

This is a major milestone: your program now responds to a physical action.

## 12. Variables, conditions and loops

You already know the basic building blocks of Python. Let's connect them to embedded programming.

### Variables

A variable stores a value.

```
counter = 0counter = counter + 1print(counter)
```

Output:

```
1
```

This pattern is useful for counting button presses, measuring events and tracking application state.

### Conditions

Conditions allow a program to make decisions.

```
temperature = 28if temperature > 25:    print("It is warm.")else:    print("It is not warm.")
```

Later, a temperature sensor can supply the value instead of a hard-coded number.

### Loops

A loop repeats instructions.

```
from time import sleepfor number in range(5):    print(number)    sleep(1)
```

Output:

```
0
1
2
3
4
```

This loop runs five times. It is useful for bounded experiments. For continuously operating embedded applications, you will often use a `while` loop.

### Functions

Functions organize code into reusable pieces.

```
def greet_device(name):    print("Hello,", name)greet_device("Pico 2 WH")greet_device("Sensor")
```

As your projects grow, functions keep the code understandable and make it easier to test individual pieces.

## 13. Make an LED gradually brighter with PWM

PWM stands for Pulse-Width Modulation.

Instead of continuously supplying a lower voltage, the Pico rapidly switches a digital output on and off. The proportion of time it stays on is called the duty cycle.

### Visualize the duty cycle

Duty cycle

25%

Duty cycle

50%

Duty cycle

75%

The bars represent the proportion of time the output is HIGH, not the electrical voltage at any instant.

For an LED, a higher duty cycle generally makes it appear brighter.

### Program

Use the external LED circuit on GPIO 15.

```
from machine import Pin, PWMfrom time import sleepled = PWM(Pin(15))led.freq(1000)while True:    for duty in range(0, 65536, 2048):        led.duty_u16(duty)        sleep(0.03)    for duty in range(65535, -1, -2048):        led.duty_u16(duty)        sleep(0.03)
```

Here:

* `PWM(Pin(15))` configures the pin for PWM.

* `freq(1000)` sets a PWM frequency of 1,000 Hz.

* `duty_u16()` accepts values from 0 to 65,535.

* `0` means continuously LOW; `65535` means effectively continuously HIGH.

* The loops gradually increase and decrease the duty cycle.

The LED should fade up and down. If it doesn't, check the wiring and the board's MicroPython version.

This is your introduction to controlling output beyond a simple on/off signal.

## 14. Read an analog sensor with the ADC

So far, we have worked with digital signals: HIGH or LOW.

But many sensors produce a range of voltages. A potentiometer, for example, can be used as a simple adjustable voltage source.

The Pico has an ADC (Analog-to-Digital Converter) that can measure an input voltage and convert it into a number.

### Understand the conversion

Potentiometer

Produces an adjustable voltage

ADC input

GPIO 26 / ADC0

Digital measurement

A number between 0 and 65,535 in MicroPython's 16-bit-scaled reading

### Example code

```
from machine import ADCfrom time import sleepsensor = ADC(26)while True:    reading = sensor.read_u16()    print(reading)    sleep(0.5)
```

This code reads the voltage on ADC0, which is available on GPIO 26.

The reading will vary with the input voltage. MicroPython returns a 16-bit-scaled result; this does not mean the ADC has 16 bits of physical resolution.

Safety: Never allow the ADC input to exceed its permitted voltage range. For a beginner experiment, use a properly wired potentiometer powered from 3V3 and GND, with its wiper connected to GPIO 26. Do not connect a 5 V sensor output directly to the ADC.

## 15. Communicate with sensors using I²C

I²C is a serial communication protocol used by many electronic sensors, displays and peripheral devices.

It usually uses two signal wires:

* SDA — Serial Data

* SCL — Serial Clock

The Pico acts as the controller and communicates with a device connected to the bus.

Pico 2 WH

SDA and SCL pins

SDA

Data

SCL

Clock

I²C sensor

For example, a temperature or humidity sensor

Here is a basic example using GPIO 4 as SDA and GPIO 5 as SCL. This pair supports I²C0 on the Pico 2.

```
from machine import Pin, I2Ci2c = I2C(    0,    sda=Pin(4),    scl=Pin(5),    freq=100000)print(i2c.scan())
```

If an I²C device is correctly connected, powered and compatible with the selected pins, `i2c.scan()` should return a list of detected device addresses, for example:

```
[104]
```

The number `104` is decimal address `0x68`, a common address for certain real-time clocks and inertial sensors.

An empty list (`[]`) means no I²C devices were detected. It does not necessarily mean your code is wrong; check the wiring, power, pin configuration and device address.

I²C is useful because several compatible devices can share the same SDA and SCL wires, provided they have distinct addresses and the bus is wired correctly.

## 16. Use the built-in Wi-Fi

Your wireless Pico 2 WH can connect to a 2.4 GHz Wi-Fi network. This opens up projects involving web servers, sensor telemetry and networked automation.

The wireless hardware is part of the Pico 2 W design, but your Python program must configure and connect to a network before it can communicate over Wi-Fi.

![](https://www.google.com/s2/favicons?domain=https://micropython.org\&sz=32)

Python for microcontrollers

+1

### Example: connect to Wi-Fi

Use a trusted network and replace the example values with your own credentials.

```
import networkimport timessid = "YOUR_WIFI_NAME"password = "YOUR_WIFI_PASSWORD"wlan = network.WLAN(network.STA_IF)wlan.active(True)wlan.connect(ssid, password)for attempt in range(20):    if wlan.isconnected():        break    print("Connecting...")    time.sleep(1)if wlan.isconnected():    print("Connected!")    print(wlan.ifconfig())else:    print("Connection failed.")
```

This example:

1. Imports the wireless networking module.

2. Enables station mode, which lets the Pico join an existing Wi-Fi network.

3. Starts the connection process.

4. Waits up to approximately 20 seconds for a connection.

5. Prints network configuration information when connected.

The example assumes your firmware supports the wireless API and that the network settings are compatible. For real projects, add better error handling and a sensible retry strategy.

Security note: Do not publish your Wi-Fi password in a public repository or share screenshots containing your credentials. For more robust projects, store credentials separately from source code.

### What can you build with Wi-Fi?

* A small web server that serves a status page.

* A temperature monitor that sends measurements to a computer.

* A device that reports button presses over a network.

* A sensor node that communicates with a backend application.

A Pico web server can later be a useful companion to a Java or Spring Boot backend, although a microcontroller and a full server have very different resource constraints.

## 17. Save a program so it starts automatically

Typing into the Shell is excellent for experiments, but a useful device needs a program that runs whenever it starts.

In Thonny:

1. Choose File → New.

2. Enter your program.

3. Choose File → Save as.

4. Select the Raspberry Pi Pico as the destination.

5. Save the file as `main.py`.

6. Restart the Pico or disconnect and reconnect its power.

MicroPython typically executes `boot.py` first, followed by `main.py` when those files are present.

![](https://www.google.com/s2/favicons?domain=https://micropython.com\&sz=32)

MicroPython

For example, a standalone LED program could be:

```
from machine import Pinfrom time import sleepled = Pin("LED", Pin.OUT)while True:    led.toggle()    sleep(1)
```

Once saved as `main.py`, it should begin blinking when the board boots.

Be careful with programs that enter an endless loop or immediately connect to an unavailable network. They can make it harder to interact with the board normally. You can interrupt execution or use BOOTSEL mode to recover and replace the firmware if needed.

## 18. MicroPython or C/C++? The deeper learning path

Since embedded programming can lead in several directions, it is worth understanding how the two main approaches differ.

| Topic              | MicroPython                            | C/C++ with Pico SDK                            |
| ------------------ | -------------------------------------- | ---------------------------------------------- |
| Getting started    | Very quick                             | More setup                                     |
| Typical workflow   | Edit and run Python                    | Configure, compile and flash                   |
| Debugging          | Interactive Shell, exceptions          | Compiler diagnostics, debugger and logs        |
| Hardware control   | Friendly APIs                          | Low-level SDK APIs                             |
| Build system       | Usually unnecessary for basic scripts  | Commonly CMake                                 |
| Best beginner goal | Understand electronics and programming | Understand embedded software and native builds |

You do not have to choose one language forever. The same LED project can be implemented in MicroPython and then rewritten in C. Comparing the two versions is a very effective way to understand how a high-level API maps to lower-level hardware operations.

For the C/C++ phase, use the official documentation:

[Raspberry Pi Pico C/C++ SDK documentation](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html?utm_source=chatgpt.com).

## 19. Your 30-day Pico 2 WH learning roadmap

Here is a gradual plan that takes you from your first program to a useful embedded project.

## 30-day checklist

0/20 tasks

### Week 1: Foundations

Identify the board and its pins

Install MicroPython and connect Thonny

Learn variables, functions, loops and conditions

Blink the onboard LED

Save and run main.py

### Week 2: Electronics and GPIO

Build an external LED circuit

Understand resistors and voltage

Read a push button

Combine input and output

Build a simple reaction timer

### Week 3: Sensors and communication

Use PWM to control LED brightness

Read analog input with the ADC

Scan an I²C bus

Read a compatible sensor

Connect to Wi-Fi

### Week 4: Build a real project

Design a sensor monitor

Display readings in the Shell

Add Wi-Fi connectivity

Handle errors and reconnects

Document and test the finished project

You can spread the exercises across 30 days at your own pace. The goal is not to memorize every function. It is to understand what the program does, observe the physical result and learn to diagnose mistakes.

## 20. Final project: Wi-Fi sensor monitor

Your first substantial project will be a sensor monitor.

![Video Loop With Raspberry Pi at Robert Lindsay blog](https://images.openai.com/static-rsc-4/cUGdzWVshnQ33ZA07KFH3-K2ssR2bWlxu-f_L7RoWyMwZUNClqYHHOzpNZM6Met2cfb5MDbVRx-ZLyR30NRGNRA9nXbJ1IM-MTlchjIdZZckh9WcSpcqkiK2XlYTMEF1spKLix0MFzlJlI1G5PeV5iH3UQsSn6TXwQcLK62cnX4?purpose=inline)

[storage.googleapis.com](https://storage.googleapis.com/dggzollhzfcaye/video-loop-with-raspberry-pi.html?utm_source=chatgpt.com)

The finished project will:

1. Read a temperature or temperature-and-humidity sensor.

2. Process the readings using MicroPython.

3. Display the measurements in the Shell or on an optional display.

4. Connect to Wi-Fi.

5. Make the readings available to another device over a local network.

6. Handle missing sensors or network failures without silently crashing.

You can extend it later with an OLED display, data logging, a small web interface or communication with a Java/Spring Boot backend.

### Suggested project architecture

Sensor

Measures the environment

Pico 2 WH

Reads, validates and processes data

Wi-Fi

Transfers readings over the local network

Computer or backend

Displays or stores measurements

This project combines programming, electronics, communication protocols and basic software architecture. Build it in stages rather than attempting everything at once.

## 21. Troubleshooting guide

| Problem                                      | What to check                                                             |
| -------------------------------------------- | ------------------------------------------------------------------------- |
| Pico does not appear as a USB drive          | Hold BOOTSEL while connecting; check the USB cable.                       |
| Pico does not appear in Thonny               | Select the correct interpreter and serial port.                           |
| `ImportError` or missing module              | Check the installed firmware and whether the module is supported.         |
| Onboard LED does not blink                   | Confirm Pico 2 W firmware and check the LED API.                          |
| External LED does not light                  | Check polarity, resistor, GPIO number, ground and breadboard connections. |
| Button reads the wrong state                 | Check the pull-up configuration and wiring to GND.                        |
| I²C scan returns `[]`                        | Check device power, SDA/SCL connections, pin mapping and address.         |
| Wi-Fi connection fails                       | Check the network, password, signal and firmware support.                 |
| Program keeps restarting or stops responding | Inspect errors in the Shell and interrupt the running program.            |

A good debugging habit is to change just one thing at a time. Record the expected result, the actual result and what you changed. This makes troubleshooting a repeatable engineering process rather than guesswork.

## 22. Your reference library

These official resources are useful companions to this tutorial.

![Raspberry Pi Pico 2 WH - RP2350 ARM Cortex M33 + CYW43439 - WiFi/Bluetooth - ze złączami Sklep Botland](https://images.openai.com/static-rsc-4/-BHZUV78DjWJurEuqH16kaMhH4CHaNDeQTHQ3n0VWCa9UdRFHwzEGMTZFN9lmF9Ydgb-OitnBrI_lQ4YxE94wfu4NGMol9eEpXsbV5gToUo_CP6C0ZDYd8hAKlyeTV_7smd5M_1Xnv5Fqjyib7Ac3ksdkGMQ8bpLw6JxllroG9Y?purpose=inline)

1\. Hardware and pinout

Learn about the RP2350, GPIO, power, peripherals and board variants.

[Pico-series documentation](https://www.raspberrypi.com/documentation/microcontrollers/pico-series.html?utm_source=chatgpt.com)

![Getting Started with Seeed Studio XIAO RP2350(MicroPython) | Seeed Studio Wiki](https://images.openai.com/static-rsc-4/a8REq3TeQ2n_PPqvwJix2pftQ_GtOLW9pM51t5_4xjIj6ivUJ0PCYm1WJs_4jtFcl9zsZvetNi592lY5mSPKN44IMEG1qChY8SHgkFgPCgAXOCkdVfzK8Cllu18jxvsiPchY-76Z_s3MtL1UpBHwSEcsyKVoIZ1iTHAt_i5_j5U?purpose=inline)

2\. MicroPython firmware

Download firmware specifically for the wireless Pico 2 W.

[Pico 2 W firmware](https://micropython.org/download/RPI_PICO2_W/?utm_source=chatgpt.com)

![Download Thonny 5.0.0 for Windows - Filehippo.com](https://images.openai.com/static-rsc-4/4IvYz3x4Fa370iJ50IyEHan8tmu4CZGztkzQeaHyaLi1nAss8eBxAe-9GDEGexqQaj3ZoZYpIsZMFCaqEx0VWskWGb8Y2FxG4-SDmqaSj7yVRzrrQ4CFaGiPE6qSXdiKdgtnVK0XEbD72pRWALSqNdnQah2i0jyf5aEm-tTZDaM?purpose=inline)

3\. Beginner development environment

Install the editor and interactive Python environment.

[Thonny IDE](https://thonny.org/?utm_source=chatgpt.com)

![Raspberry Pi PicoでLチカやってみた（MicroPython版） - uepon日々の備忘録](https://images.openai.com/static-rsc-4/P2HwuhBlUU0McrQ0RMqt-80NALH_eYQ88IQfqRQsT_U-r4yjdOas1w07RX2GDForTgo3ntUf34jE7Rry8c9IQgJ7-k06BtXE8s_Lf98hrWi2umsFh_XsiXQwWohYYTScRREiolKtUVTfECCI6IPZIdTMR9k750opZEfQQRg_tCM?purpose=inline)

4\. Official beginner exercises

Follow a practical introduction to programming a Pico and controlling an LED.

[Getting started with Raspberry Pi Pico](https://projects.raspberrypi.org/en/projects/getting-started-with-the-pico?utm_source=chatgpt.com)

## Your first milestone

For now, don't worry about Wi-Fi, sensors, PWM or C++. Start with just three tasks:

* Install the correct MicroPython firmware.
* Execute `print("Hello, Pico 2 WH!")`.
* Make the onboard LED blink.

Once those three tasks work, you have a functioning development environment and have completed your first embedded programming exercise.

One last clarification: Raspberry Pi officially names the wireless second-generation model Pico 2 W with headers. Some sellers may use “Pico 2 WH” informally; the important thing is that your board is the wireless RP2350 model with pre-soldered headers.

![](https://www.google.com/s2/favicons?domain=https://github.com\&sz=32)

GitHub

+1

You can treat this tutorial as your master note in Zettlr and create separate notes for GPIO, MicroPython, PWM, ADC, I²C, Wi-Fi and each project as you learn.
