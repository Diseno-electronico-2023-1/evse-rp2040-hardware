## Código fuente de microprocesador para RP2040
# Guía inicial

Para el desarrollo del sistema se ha usado Zephyr. Es necesaria su instalación para el uso de este programa: https://docs.zephyrproject.org/latest/develop/getting_started/index.html

Para la instalación en Windows se debe instalar chocolatey: https://chocolatey.org/install

Luego ejecutar los siguientes comandos para instalar las dependencias

```
choco feature enable -n allowGlobalConfirmation
choco install cmake --installargs 'ADD_CMAKE_TO_PATH=System'
choco install ninja gperf python git dtc-msys2 wget unzip
```
