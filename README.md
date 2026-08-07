# MOVEA, an EWOD demonstration device

A minimal 4x4 EWOD array, with the complete driver board based around an ESP32-C3, a DC DC boost converter module (168V OUT) as well as the HV509 driver IC. All inside a fully enclosed 3D printed device. 

> [!CAUTION]
> **HIGH VOLTAGE**
>
> This project generates high voltage (~168V DC) from the USB C to correctly drive the EWOD electrodes.
> While I tried my best to provide a fully enclosed design with the HV part being detachable from the MCU circuitry, the high voltage side remains **not galvanically isolated** from the MCU side. Treat the whole board as live whenever VPP is enabled, not just HV traces.
>
> The USB isn't galvanically isolated either, so it's recommended to fully disconnect the 2 FPC ribbon cables when programming the device. Controlling the device (droplet actuation) shall then be done over WIFI.

> [!WARNING]
> **No warranty, use at your own risk**: This project is provided as-is, without any guarantee of safety, correctness, or fitness for any purpose. If you do build, reproduce, adapt or take inspiration from this project, it's entirely at your own risk.
>
> I disclaim all responsibility for any damage, injury or other consequences arising from the use, reproduction, or modification of this design.


> [!NOTE]
> **Educational / demo purpose only** This project is intended for educational / demo purpose only, with no intent of being  used in actual lab experiments.

> [!IMPORTANT]
>
> A few safety notes:
> Although I tried to design a fully enclosed device, the acrylic cover does not latch. Whenever high voltage is enabled, it is the user's responsibility to never open the acrylic cover.
>
> While the firmware demo already enforces this (could not be the case if a custom firmware is coded). It is important to only enable the high voltage when actively driving the device, and the VPP rail capacitors should be discharged in firmware after the HV module is disabled, to ensure VPP collapses instead of staying at 168V (the electrodes barely sink any current on their own). Collapsing VPP should obviously be done before switching the device off.
