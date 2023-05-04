FROM mcr.microsoft.com/devcontainers/base:focal

RUN apt-get update \
    && apt-get -qqy install \
    bc \
    sudo \
    build-essential \
    ca-certificates \
    clang \
    curl \
    gcc \
    git \
    python3 \
    python3-dev \
    python3-distutils \
    python3-pip \
    python3-setuptools \
    srecord \
    udev \
    xz-utils \
    usbutils \
    vim \
    && apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*



RUN curl -fLo /etc/udev/rules.d/99-platformio-udev.rules --create-dirs https://raw.githubusercontent.com/platformio/platformio-core/develop/platformio/assets/system/99-platformio-udev.rules
RUN echo 'SUBSYSTEMS=="usb", ATTRS{idVendor}=="303a", ATTRS{idProduct}=="1001", MODE:="0666"' > /etc/udev/rules.d/99-kabot.rules

USER $USERNAME
