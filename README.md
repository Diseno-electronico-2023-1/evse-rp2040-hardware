# Código fuente de microprocesador para RP2040
## Guía inicial

Para el desarrollo del sistema se ha usado [Zephyr](https://docs.zephyrproject.org/latest/develop/getting_started/index.html). Es necesaria su instalación para ejecutar la aplicación.

Para la instalación en Windows se debe instalar [chocolatey](https://chocolatey.org/install)

Luego ejecutar los siguientes comandos en cmd.exe como **Administrador** para instalar las dependencias

```
choco feature enable -n allowGlobalConfirmation
choco install cmake --installargs 'ADD_CMAKE_TO_PATH=System'
choco install ninja gperf python git dtc-msys2 wget unzip
```

Ahora se creara un ambiente virtual con Python, para ello ejecute los siguientes comandos en cmd.exe (no Administrador)

```
cd %HOMEPATH%
python -m venv zephyrproject\.venv
zephyrproject\.venv\Scripts\activate.bat
```

En el ambiente virtual instale west (se debe iniciar el ambiente virtual cada vez que se requiera trabajar)

```
pip install west
```

Luego obtenga el código fuente de Zephyr:

```
west init zephyrproject
cd zephyrproject
west update
```

Exporte el CMake de Zephyr e instale las dependencias adicionales de Python

```
west zephyr-exportwest update
pip install -r %HOMEPATH%\zephyrproject\zephyr\scripts\requirements.txt
```

Después clone este repositorio en la carpeta zephyrproject (Ejemplo con http)

```
cd %HOMEPATH%\zephyrproject
git init
git clone https://github.com/Diseno-electronico-2023-1/evse-rp2040-hardware.git
```

Su jerarquía de carpetas debe quedar asi


![image](https://user-images.githubusercontent.com/76027960/225695480-95798ff3-9ca3-42b7-b33f-a52da15752df.png)

EL código fuente de la aplicación con Zephyr esta listo, pero para compilarlo deberá instalar los SDK.

### Intalando los SDK

En cmd.exe (fuera del ambiente virtual creado previamente) ejecute los siguientes comandos:

```
cd %HOMEPATH%
wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.15.2/zephyr-sdk-0.15.2_windows-x86_64.zip
unzip zephyr-sdk-0.15.2_windows-x86_64.zip
cd zephyr-sdk-0.15.2
setup.cmd
```

### Ejecutar la aplicación
Una vez instalado el entorno de trabajo de Zephyr, la aplicación se ejecuta haciendo la Build y luego el Flash a la tarjeta.

#### Compilar la aplicación
Para compilar la aplicación en una RP2040 ingrese a la carpeta de la aplicación que desea compilar (Ejemplo para ingresar a App)

```
cd %HOMEPATH%\zephyrproject\evse-rp2040-hardware\app
```

Luego ejecute el siguiente comando

```
west build -p always -b rpi_pico
```

Se creará automaticamente una carpeta llamada *build*
#### Flashear la tarjeta
Conecte la RP2040 via USB mientras mantiene oprimido el botón de **boot**. Windows lo reconocerá como un disco externo. Ingrese a la carpeta *build* previamente creada y luego a *zephyr* (*build/zephyr*). Copie el archivo *zephyr.uf2* y peguelo dentro el disco duro externo que representa la memoria de la tarjeta RP2040 conectada.
Pruebe desde la ruta "\zephyrproject\evse-rp2040-hardware\app" el siguiente comando para Windows (El disco externo reconocido para la placa debe ser E:\ si es otro reemplácelo, por ejemplo D:\):
```
copy .\build\zephyr\zephyr.uf2 E:\
```


