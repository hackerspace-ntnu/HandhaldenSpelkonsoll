# HandhaldenSpelkonsoll
  
Dette er et prosjekt med mål om å utvikle en håndholdt spillkonsoll basert på ESP32 og skjermkontrolleren ILI9488.  
Spillkonsollen kommer med et egetutviklet multiplayer snake-spill slik at opptil 4 stykker kan spille med hverandre. 
  
# Features som er planlagt og i utvikling:  
#### Hardware:  
* microcontroller: ESP32 dev board
* skjerm: ILI9488 480*320, 3.5"  
* input: Dpad + 4 knapper
* pcb: custom KiCad modell  
* kabinett: 3d printet, cad filer følger og det er åpent for tilpassing som i valg av farger

#### Software:  
* Spill: snake  
* Foreløpig brukes biblioteket [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) for å skrive til skjermene. 
* Kommunikasjonsprotokoll: [ESP-NOW](https://github.com/espressif/esp-now) 


### TODO:
* ~~Lage logikk for å kjøre et faktisk snake spill i c~~, deretter implementer multiplayer. (coming soon)
* Få spillet til å kjøres på skjermen (Vise grafikk) "det er trivielt" -Joakim ([påbegynt](https://github.com/hackerspace-ntnu/HandhaldenSpelkonsoll/pull/12))
* Lag system for å ta inn input (Knappetrykk påvirker spillet) "det er trivielt" -Joakim
* Sette opp trådløs kommunikasjon mellom kontroller (Nødvendig for multiplayer) ([påbegynt](https://github.com/hackerspace-ntnu/HandhaldenSpelkonsoll/pull/14))
* Implementere meny-system (instillinger start pause eventuelt mulig for flere minigames)
* Rense opp i minnebruk, har bare 384 kiB (bare gå gjennom koden og free mallocer som det har blitt glemt å frigjøres)
* Lag revidert utgave av kretskort, aka fiks det som må fikses ([påbegynt](https://github.com/hackerspace-ntnu/HandhaldenSpelkonsoll/tree/circuit-board-design))
* TO MØTER MED PIZZA (eller annen mat)!!
* ~~Test spillet litt mer og se etter bugs (Nåværende, mest oppdaterte branch er an-attempt-at-game, hvor en del bugs allerede er blitt fikset)~~
