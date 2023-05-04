<p align="center">
<img src="docs/img/kabot-logo.png" alt= “” width="100">
</p>


# Kabot ESP32-S3 firmware repository

<p align="center">
<img src="docs/img/kabot-esp32-s3.jpg" alt= “” width="500">
</p>

## What is this repo?

This is a scratchpad repo of new release of [Kabot](https://github.com/kabot-io/POC) firmware for ESP32-S3 board. Key features:
- as simple setup as possible - [just VSCode with Dev Containers](https://code.visualstudio.com/docs/devcontainers/containers) plugin
- cross platform - Linux, and hopefully Windows and other *nix systems (other than linux untested)
- ease of development - built using [PlatformIO](https://platformio.org/)

## Running:

Follow those steps to set up development environment:

1. [Install VSCode](https://code.visualstudio.com/) and [Docker](https://www.docker.com/) - we'll be using [Dev Containers](https://code.visualstudio.com/docs/devcontainers/containers) plugin, so follow instructions there.

2. Clone the repository: 
```bash
git clone https://github.com/kabot-io/kabot-s3-firmware.git
```
3. Open workspace in VSCode:
```bash
code ./kabot-s3-firmware/kabot-s3.code-workspace
```

Say **say yes to opening workspace in Dev Container.**:

![Say yes](docs/img/dev-containers-reopen.png)

First build of the container may take quite a few minutes, depending on your Internet connection.


7. Type `F1` -> `PlatformIO: Build` or `Ctrl + Alt + B` - first build may take a while - PlatformIO needs to download all its dependancies; toolchain, libraries, tools etc.

![Build](docs/img/platformio-build.png)

8. Connect Kabot to USB using USB-C cable.

9. Type `F1` -> `PlatformIO: Upload` or `Ctrl + Alt + U` to upload firmware to board.

![Build](docs/img/platformio-upload.png)

10. You are all set! Happy tinkering. You may start by looking into [micro-ROS documentation](https://micro.ros.org/).