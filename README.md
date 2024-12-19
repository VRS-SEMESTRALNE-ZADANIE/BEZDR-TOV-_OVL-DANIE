# TX (Transmitter) RFM cez SPI

## Teoretický základ
TX RFM (vysielač) je zariadenie, ktoré prenáša dáta z hlavnej jednotky (STM32) do prijímača (RX). Využíva SPI (Serial Peripheral Interface) na komunikáciu s mikrokontrolérom a následne bezdrôtovo vysiela dáta vo forme šifrovaných paketov.

## Proces fungovania

1. **Príprava dát na vysielanie:**
   - STM32 generuje dáta, napríklad informácie o pohybe joysticku alebo stave tlačidiel.
   - Dáta sú spracované a štruktúrované do paketov, ktoré obsahujú:
     - Adresu prijímača.
     - Typ správy (pohyb, stav, atď.).
     - Šifrovaný obsah správy.

2. **Prenos dát cez SPI:**
   - STM32 odosiela pripravené pakety do TX RFM cez SPI protokol:
     - **MOSI (Master Out Slave In):** Dáta sú posielané zo STM32 do RFM.
     - **SCK (Serial Clock):** Hodinový signál synchronizuje prenos.
     - **SS (Slave Select):** Aktivuje TX RFM modul na príjem dát.

3. **Vysielanie bezdrôtovo:**
   - Po prijatí dát TX RFM modul konvertuje pakety na rádiové signály.
   - Signály sú vysielané na určenú frekvenciu, ktorá je prednastavená pre prijímač.

4. **Potvrdenie prenosu:**
   - Ak protokol podporuje potvrdenie (ACK), TX očakáva odpoveď od RX a informuje STM32 o stave prenosu.

## Prínosy TX RFM cez SPI
- Rýchly a spoľahlivý prenos dát.
- Jednoduchá konfigurácia s STM32.
- Šifrovanie zaisťuje bezpečnosť prenášaných dát.
