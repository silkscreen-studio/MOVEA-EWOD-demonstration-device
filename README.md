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

