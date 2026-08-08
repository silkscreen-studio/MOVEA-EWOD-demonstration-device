# MOVEA, an EWOD demonstration device

A minimal 4x4 EWOD array, with the complete driver board based around an ESP32-C3, a DC DC boost converter module (168V OUT) as well as the HV509 driver IC. All inside a fully enclosed 3D printed device.



> [!CAUTION]
> **HIGH VOLTAGE**
>
> This project generates high voltage (~168V DC) from the USB C to correctly drive the EWOD electrodes.
> While I tried my best to provide a fully enclosed design with the HV part being detachable from the MCU circuitry, the high voltage side remains **not galvanically isolated** from the MCU side. Treat the whole board as live whenever `HV OUT` is enabled, not just HV traces.
>
> The USB isn't galvanically isolated either, so it's recommended to fully disconnect the 2 FPC ribbon cables when programming the device to prevent any USB port damage in case of a failure. Controlling the device (droplet actuation) shall then be done over WIFI.


> [!WARNING]
>
> **A few safety notes:**
> 
> Although I tried to design a fully enclosed device, the acrylic cover does not latch. Whenever high voltage is enabled, it is the user's responsibility to keep the acrylic door shut.
>
> While the firmware demo already enforces this (could not be the case if a custom firmware is flashed). It is important to only enable the high voltage when actively actuating the droplets, and the `HV OUT` rail capacitors should be discharged in firmware after the HV module is disabled, to ensure `HV OUT` collapses instead of staying at 168V (the electrodes barely sink any current on their own). Collapsing `HV OUT` should obviously be done before switching the device off (because otherwise the N channel mosfet in charge of sinking `HV OUT` to ground won't conduct).

> [!WARNING]
> **No warranty, use at your own risk**: This project is provided as-is, without any guarantee of safety, correctness, or fitness for any purpose. If you do build, reproduce, adapt or take inspiration from this project, it's entirely at your own risk.
>
> I disclaim all responsibility for any damage, injury or other consequences arising from the use, reproduction, or modification of this design.


> [!NOTE]
> **Educational / demo purpose only** This project is intended for educational / demo purpose only, with no intent of being  used in actual lab experiments.

<br><br>
<img width="45%" alt="image" src="https://github.com/user-attachments/assets/36d8d75a-2011-4945-b53d-c5eaee0d2d56" />
<br><br>
<br><br>

<img lt="3D layout" src="ASSETS/EWOD_LAYOUT_3D.png" />



# Key features:

 - ESP32-C3 MCU
 - HV509 16 CH push pull HV driver
 - 3.3V-12V IN 168V OUT DC DC High voltage converter module
 - VIN enabled `HV OUT` rail (AO3415A P channel Mosfet)
 - 2x110k serie resistor directly on the HV boost output: should limit the current to a safe 750µA (in case of a downstream short circuit)
 - same 2x110k acting as bleeding resistors, sinking `HV OUT` to GND until the MCU disables it.
 - 2 FPC ribbon cables to be able to disconnect all HV related circuitry from the ESP32 devboard
 - detachable EWOD cartridge, that connects thanks to 2x20P 2.54mm Dupont Header pins.
 - 3D printed enclosure with acrylic cover to see the water droplet through the window.

# Schematic:

<img width="1000" alt="bottom layout" src="ASSETS/EWOD_MOVEA_V1.0_Schematic_07_08_26.png" />

# Layout:

<p align="center">
<img width="50.45%" alt="Top layout" src="ASSETS/EWOD_LAYOUT_TOP.png" />
<img width="49%" alt="bottom layout" src="ASSETS/EWOD_LAYOUT_BOTTOM.png" />
</p>


# Firmware:

A minimal demo code in C++ (Arduino IDE) is available to interface the HV509 as well as controlling the different power mosfets.

# Enclosure Assembly:

After 3D printing the different parts, cutting a 78.5mm long Φ 6mm steel rod and creating the acrylic window (2mm rectangle cut from an acrylic sheet, then bent with a hot air gun), the device can be assembled:
After connecting the 2 FPC ribbon cables, the PCB can be securely mounted to the enclosure thanks to threaded inserts added beforehand, and the HV cover can be glued in place (held in place with the 2 side rails). for the window, it's recommended to create a 'chain' with all the hinges placed on the enclosure with the rod in the middle, before glueing the acrylic window to the 3 hinge parts.

<br><br>


<img lt="3D Enclosure IMG 1" src="ASSETS/Enclosure 1.png" />
<img lt="3D Enclosure IMG 2" src="ASSETS/Enclosure 2.png" />
<img lt="3D Enclosure IMG 3" src="ASSETS/Enclosure 3.png" />



# Render:

<img lt="3D Render IMG TOP view" src="ASSETS/Render TOP.png" />
<img lt="3D Render IMG ISO 1" src="ASSETS/Render ISO.png" />
<img lt="3D Render IMG ISO 2" src="ASSETS/Render ISO 2.png" />
<img lt="3D Render IMG Hinge" src="ASSETS/Render Hinge.PNG" />



