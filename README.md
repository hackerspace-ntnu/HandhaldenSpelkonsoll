# HandhaldenSpelkonsoll
  
Dette er et prosjekt med mål om å utvikle en håndholdt spillkonsoll basert på ESP32 og skjermkontrolleren ILI9488.  
Spillkonsollen kommer med et egetutviklet multiplayer snake-spill slik at opptil 2(!) stykker kan spille med hverandre. 
  
# Features som er planlagt og i utvikling:  
#### Hardware:  
* microcontroller: ESP32 dev board
* skjerm: ILI9488 480*320, 3.5"  
* input: Dpad + 4 knapper
* pcb: custom KiCad modell  
* kabinett: 3d printet, cad filer følger og det er åpent for tilpassing som i valg av farger

#### Software:  
* Spill: snake  
* Grafikk: [LVGL](https://github.com/lvgl/lvgl)
* Kommunikasjonsprotokoll: [ESP-NOW](https://github.com/espressif/esp-now) 


### TODO:
* Implementere GUI
* Sette sammen grafikk og trådløs kommunikasjon mellom enheter
* Rense opp i minnebruk, har bare 384 kiB (bare gå gjennom koden og free mallocer som det har blitt glemt å frigjøres)
* TO MØTER MED PIZZA (eller annen mat)!!
