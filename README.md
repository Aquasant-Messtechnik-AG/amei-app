# 📱 AMEI-App Menüsystem

Dieses Repository enthält das Menüsystem der **AMEI-App**, das mit der **LVGL-Bibliothek (Version 8.3)** entwickelt wurde. Die grafische Benutzeroberfläche wurde zunächst im offiziellen **LVGL-Simulator für Visual Studio** umgesetzt, um eine hardwareunabhängige Entwicklung und ein einfaches Debugging zu ermöglichen.

## 🎯 Projektziel

Ziel des Projekts ist es, ein flexibles und erweiterbares Menüsystem zu entwickeln, das später auf einem **STM32L4R5ZIT6** Mikrocontroller mit einem **TFT-LCD (320x240 Pixel)** über **SPI** betrieben werden soll. Durch die klare Trennung von Logik, Darstellung und Hardwarezugriff wird eine einfache Portierung auf die Zielhardware ermöglicht.

## 🛠️ Verwendete Technologien

- 🔧 **[LVGL 8.3](https://github.com/lvgl/lvgl)** – Open-Source-GUI-Bibliothek für eingebettete Systeme  
- 🖥️ **[LVGL Visual Studio Simulator](https://github.com/lvgl/lv_port_pc_visual_studio)** – Offizieller Simulator für Windows zur Entwicklung und zum Testen von GUIs  
- 💻 **Visual Studio** – Entwicklungsumgebung zur Ausführung des LVGL-Simulators  
- 🧠 **STM32L4R5ZIT6** – Ziel-Mikrocontroller für die finale Implementierung  
- 📺 **TFT-LCD 320x240** – Display zur Darstellung des Menüs  
- 🔌 **SPI** – Kommunikationsschnittstelle zwischen Mikrocontroller und Display

## 🧩 Entwicklungsschritte

1. 🧪 **Simulation**: Entwicklung und Test des Menüs im LVGL-Simulator unter Windows  
2. 🧱 **Modularisierung**: Trennung von GUI-Logik und Hardwarezugriff zur besseren Wartbarkeit  
3. 🔄 **Portierung**: Anpassung der Hardware-spezifischen Schichten für den STM32L4R5ZIT6  
4. 🎮 **Integration**: Einbindung von Eingabemethoden (z. B. Tastensteuerung) zur Navigation im Menü

## 🔜 Nächste Schritte

- ⚙️ Implementierung der Hardwareabstraktionsschicht (HAL) für STM32  
- 🖧 Anbindung des SPI-Displays  
- 🎚️ Integration der physischen Tasten zur Menüsteuerung  
- 🚀 Optimierung der Speicher- und Performanceanforderungen für Embedded-Einsatz
