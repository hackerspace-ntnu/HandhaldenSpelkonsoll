# HandheldtSpelkonsoll
  
Dette er ett prosjekt i startfasen under utvikling med mål om å utvikle en håndholdt spillkonsoll basert på ESP32 og skjermkontrolleren ILI9341/ILI9488.  
Målet er å lage et multiplayer snake spill til den håndholdte spillkonsollen så alle som har en konsoll kan spille mot hverandre.  
  
  
# Features som er planlagt og i utvikling:  
Hardware:  
microcontroller: ESP32 dev board.  
skjerm: ILI9488 controller 480*320 oppløsning 3.5"  
input: Joystick/dpad + 6 knapper.  
kabinett: 3d printet, cad filer følger og det er åpent for tilpassing som i valg av farger.

Software:  
Spill  
Startet arbeid på ett snake inspirert spill Ormkamp.  
Flere skjermdriver-bibliotek er under vurdering. TFT_eSPI har skrevet til skjermene.  


### TODO:
* Lage logikk for å kjøre et faktisk snake spill i c, deretter implementer multiplayer.
* Få spillet til å kjøres på skjermen (Vise grafikk)
* Lag system for å ta inn input (Knappetrykk påvirker spillet)
* Sette opp trådløs kommunikasjon mellom kontroller (Nødvendig for multiplayer WIFI/BLE)
* Implementere meny-system (instillinger start pause eventuelt mulig for flere minigames)
