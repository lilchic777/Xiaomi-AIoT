# Xiaomi-AIoT

Code of Xiaomi AIoT Development Platform. Using U1P GD32F470ZKT6 or U2P Horizon X3M as computing unit.

## 01：Basic Knowledge of Electronic Technology

### 01.1 Number LED

Digital display experiment, press the sw5 button. E1 will continuously display 0-50.

### 01.2 Digital Password Lock

The core of a digital combination lock is a digital logic circuit, which determines whether the password entered by the user is correct and controls the lock's switch status. The password for the combination lock is 127369. Enter any numbers, but once you enter 1, the system will begin to verify the password. If the last 5 digits are 27369, the password is correct and the light will turn on.

### 01.3 8 Broad Button

Eight-lane quiz machine. When someone rushes to answer, whoever presses the button will cause a red light to flash for three seconds and display the button number, then turn off and reset to zero.

## 02: Embedded System

### 02.1 I2C

Press the SW1 button, and if the first digit on the E1 digital tube lights up, it means that we have successfully triggered the I2C event.

### 02.2 I2C LED

Press the SW1 button, and the LED light on E1 will turn on, then switch LED colors approximately once every 1 second.  When you press the SW2 button, the LED on E1 will turn off.

### 02.3 Timer

The routine sets two timers. When mode=1, it is a normal timer, and the LED turns on/off once every 1.5 seconds. When mode=2, it is a watchdog timer, and the LED remains off.

### 02.4 USART

Use the serial port debugging assistant to send data. If the data received by the U1P sub-board in Uart0_RecvBuffer[0] is equal to 0x39 (decimal 9), set the buffer to 1 and execute the LED_ON() function to turn on the LED light;

If the received data Uart0_RecvBuffer[0] equals 0x61 (decimal value ‘a’), set the buffer to 2 and execute the LED_OFF() function to turn off the LED;

If the received data Uart0_RecvBuffer[0] equals 0x41 (decimal value ‘A’), set the buffer to 3 and execute the LED_BLINK() function to make the LED light blink, with a delay of 250 milliseconds.  

## 03: Resistive Sensor

### 03.1 Gryo

The four positions of the digital tube correspond to left, front, rear, and right, respectively. When the gyroscope sensor detects forward tilting, the number 1 is displayed in the second position.

### 03.2 Old Fallen

The four positions of the digital tube correspond to left, front, right, and rear. At this point, a gyroscope sensor is used to simulate an elderly person. When the gyroscope sensor detects forward tilting (i.e., simulates detecting an elderly person falling forward), the number 1 is displayed in the second position.

## 04: Inductive Sensor

### 04.1 NFC

After starting the program, if there is no NFC card on the S5 sub-board, the card search will fail, and the program will remain in the card search state, with “----” displayed on the E1 digital tube.

After placing an NFC card on the S5 sub-board, the program will enter the authentication, card writing, and card reading states in sequence, with the card data displayed on the E1 digital tube.

When another NFC card is placed on the S5 sub-board, the data read from that card will be displayed on the E1.

### 04.2 Dorm Locker

In this experiment, E3 replaces the dormitory door lock. When unoccupied (i.e., when there is no NFC card on the S5 sub-board), the door lock is in the closed state (i.e., E3 is on the far right in the diagram), the E1 digital display shows “----”, and the LED is off. At this point, the program is in card-searching mode.

When a card is swiped, the E1 digital display quickly shows the read card ID. If the authentication password is correct, the display shows “OPEN,” and the door lock opens. After the door lock opens, the red light on E1 stays on for about 5 seconds, simulating someone entering the room. After about 5 seconds, the red light turns off, and the door lock automatically closes.

If the NFC card does not match the authentication password in the program, authentication fails, and the door lock remains closed. At this point, the program remains in the card search-anti-collision-card selection-authentication state and cannot enter the card writing or card reading state.

## 05: Capacitive Sensor

### 05.1 Microphone

After power-on initialization, recording begins, and once completed, playback starts, repeating in a loop (recording time is approximately 10 seconds).

### 05.2 Fan by Voice

When the microphone sub-board detects sound, it triggers the fan sub-board, and the fan starts spinning.

## 06: Thermocouple Sensor

### 06.1 TH Sensor

After the program starts, the E1 sub-board first displays “----” to indicate that the system is initializing. Approximately 2 seconds later, the system enters the default display mode, and the E1 sub-board displays “0000”.

Pressing the SW1 button causes the system to detect the rising edge of the button press, switching to temperature display mode, with the E1 subboard displaying the detected temperature. Pressing the SW2 button switches the system to humidity display mode, such as “53.4H” indicating the current environmental humidity is 53.4%. Pressing the SW1 button again switches back to temperature display mode.

### 06.2 Auto Curtain

After starting the program, the E1 sub-board displays “----”, and the E3 curtain remains stationary.

When sw1 is pressed, the curtain moves to the far left. The first digit of the E1 digital display is 0, indicating the curtain is stationary, while the last three digits are 100, indicating the curtain is at the far left. Pressing sw2 moves the curtain to the center. Pressing sw3 moves the curtain to the far right.

Pressing any other buttons (SW4 to SW12) causes the curtain to move back and forth between the left and right sides, with the curtain's movement status and position dynamically displayed on the E1 digital display. Specifically, the first digit of the digital display shows 1, indicating the curtain is in motion; when it moves to the far left or right, it displays 0. The last three digits indicate the current position of the curtain.

## 07: Photoelectric Sensor

### 07.1 Camera

> [!NOTE]
>
> This experiment is based on the U2 Horizon X3M computing sub-board. Please refer to the user manual for environment configuration, login, and other operations.

After running the Python program, a window opens on the display showing the live feed from the camera.

### 07.2 Vision for Old Fallen

This experiment uses YOLO-V5 and selects photos of elderly people falling to train the model. After starting the Python program, photos can be placed in front of the camera to simulate an elderly person falling. Once the camera detects an “elderly person falling,” the annotation is displayed in real time in the window.

## 08: Radiation and Wave Sensors

### 08.1 Ir Sensor

When the S7 human infrared sensor is equipped with a protective cover, the S7 green indicator light turns off, and the E1 RGB indicator light turns off.

When the S7 protective cover is removed and the sensor is approached, the S7 detects a human presence, the S7 green indicator light turns on, and approximately 2 seconds later, the E1 red RGB indicator light turns on.

Finally, when the protective cover is replaced, the S7 green light turns off, and approximately 2 seconds later, the E1 red light turns off.

### 08.2 Ultra Sensor

When the S6 ultrasonic sensor is equipped with a protective cover, the E1 sub-board displays a default distance of 250. The sensor in the center of the S6 can be removed and positioned at a certain angle for convenient measurement of the distance ahead. When the S6 protective cover is removed, the E1 digital tube will display the distance to the obstacle in front of the S6 sensor.

### 08.3 Smart Faucet

When the S7 is equipped with a protective cover, the system cannot detect human presence. At this point, the S7's green light turns off, and “----” is displayed on the E1.

When someone washes their hands, the S7 green light turns on, followed by the E1 green light, indicating that the faucet is open and a 30-second countdown begins. After the 30-second countdown, even if a human presence is still detected (S7 green light is on), the faucet will close (E1 LED turns off). 

When no human presence is detected, the faucet will close regardless of whether the countdown has ended, and the system returns to the S7 with protective cover mode. When human presence is detected again, the 30-second countdown will restart.

> [!NOTE]
>
> Since the S7 human infrared sensor is based on the pyroelectric effect, it will maintain the “human present” effect for a certain period after detecting that a person has left. After the person leaves the detection range, the sensor's output signal returns to a high level, but at this point, the capacitance of the pyroelectric sensor must slowly discharge or charge through a resistor until the voltage drops below the threshold before the output is turned off. This RC delay circuit typically lasts approximately 10 seconds.

### 08.4 Car Goback Radar

When the “vehicle distance” is greater than 1000, E1 lights up green, indicating that the vehicle distance is safe; when the vehicle distance is between 500 and 1000, E1 lights up yellow, indicating that caution should be exercised; when the vehicle distance is less than 500, E1 lights up red, indicating that the vehicle should stop immediately.

## 09: Bluetooth Communication

### 09.1 Bluetooth

After sending the uppercase letter ‘A’ via mobile phone Bluetooth, the LED on the U1 sub-board lights up, as shown in Figure 4. After sending the letter ‘B’ via mobile phone Bluetooth, the LED on the U1 sub-board turns off.

> [!TIP]
>
> For mobile phone Bluetooth control, you can use the nRF Connect Bluetooth debugger. After connecting, click the up arrow next to Descriptors in CLIENT-Unknown Service, and finally send information to the C3 sub-board via Write Value.

## 10: Smart Greenhouse

### 10.1 Smart Greenhouse

Through Zigbee communication, the temperature, humidity, and light intensity of the simulated smart greenhouse can be monitored in real time. The U1 terminal sub-board collects temperature, humidity, and light intensity data from the S2 sensor and sends the data to the U1 coordinator sub-board via Zigbee broadcast. After receiving the data, the U1 coordinator sub-board parses it, checks that the identifier “THL” is correct, and displays the data on the E1 digital tube.

The first two digits on the E1 digital display show the temperature in degrees Celsius, and the last two digits show the humidity in percent. After approximately 1.5 seconds, the E1 switches to display light intensity, and after approximately 1 second, it switches back to displaying temperature and humidity.

> [!NOTE]
>
> The code burned into the U1 terminal subboard and coordinator subboard is different. In the UserInit() function, the terminal subboard is Zigbee_Set(TERMINAL), while the coordinator subboard is Zigbee_Set(COORDINATOR).