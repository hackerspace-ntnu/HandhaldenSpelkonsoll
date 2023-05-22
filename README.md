# Handhalden Spelkonsoll
  
Dette er et prosjekt med mål om å utvikle en håndholdt spillkonsoll basert på ESP32 og skjermkontrolleren ILI9488.  
Spillkonsollen kommer med et egetutviklet snake-spill.
  
# Features som er planlagt og i utvikling:  
#### Hardware:  
* mikrokontroller: ESP32 dev board
* skjerm: ILI9488 480*320, 3.5"  
* input: Dpad + 4 knapper
* kretskort: [custom KiCad modell](hardware/kretskort/)  
* kabinett: 3d printet, [cad filer](hardware/design/) følger og det er åpent for tilpassing som i valg av farger

#### Software:  
* Spill: snake  
* Grafikk: [LVGL](https://github.com/lvgl/lvgl)
* ~~Kommunikasjonsprotokoll: [ESP-NOW](https://github.com/espressif/esp-now)~~
