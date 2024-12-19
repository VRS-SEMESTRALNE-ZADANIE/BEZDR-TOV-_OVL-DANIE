# OVLÁDANIE AUTÍČKA

Tento projekt umožňuje ovládanie modelu autíčka pomocou joysticku, ktorý je napojený na mikrokontrolér STM32. Pôvodná implementácia predpokladala použitie RFM modulov a SPI protokolu na bezdrôtovú komunikáciu medzi joystickom a autíčkom. Neskôr bol tento koncept zjednodušený na priame káblové prepojenie.

## Pôvodné riešenie: RFM a SPI komunikácia

### Popis riešenia

V pôvodnom návrhu sa využívali dva RFM moduly (RFM12B) na bezdrôtový prenos dát medzi joystickom a autíčkom. RFM modul na strane joysticku bol pripojený k STM32 cez SPI protokol, ktorý zabezpečoval šifrovaný a rýchly prenos dát o pohybe joysticku. Na strane prijímača, druhý RFM modul prijímal signály, dekódoval ich a odosielal do STM32, ktorý zabezpečoval ovládanie motorov.

### Detaily komunikácie

1. **Joystick:**
   - Pohyb joysticku generoval analógové hodnoty na osiach X a Y.
   - ADC v STM32 konvertoval tieto hodnoty na digitálne signály.
   - STM32 spracoval signály a cez SPI odoslal príkazy do RFM modulu.

2. **Prenos cez RFM:**
   - RFM modul na strane joysticku vysielal dáta vo forme paketov.
   - Prenos obsahoval informácie o smere a rýchlosti pohybu, ako aj o stave tlačidiel.

3. **Prijímač:**
   - RFM modul na strane autíčka prijal pakety a odoslal ich cez SPI do STM32.
   - STM32 dekódoval dáta a odoslal príkazy do dosky MD25 na riadenie motorov.

### Nevýhody RFM riešenia

- Zvýšená zložitosť implementácie SPI protokolu.
- Možné interferencie a strata signálu pri bezdrôtovom prenose.
- Potreba synchronizácie medzi vysielačom a prijímačom.

## Aktuálne riešenie: Priame káblové prepojenie

### Popis zapojenia

Joystick bol napojený priamo na STM32 cez analógové vstupy, kde bol jeho signál spracovaný cez prevodník ADC (Analog-to-Digital Converter). Signál z joysticku špecifikuje dve osy:

- **X-osa**: Rýchlosť a smer pohybu autíčka dopredu alebo dozadu.
- **Y-osa**: Otáčanie autíčka doľava alebo doprava.

Prevodník ADC konvertuje analógové hodnoty z joysticku na digitálne signály, ktoré sa následne posielajú do druhého STM32 mikrokontroléra nachádzajúceho sa na autíčku. Tento STM32 prijíma tieto hodnoty cez káblové prepojenie a cez protokol USART odosiela príkazy do riadiacej dosky MD25.

Riadiaca doska MD25 je priamo pripojená na motory autíčka a interpretuje príkazy od mikrokontroléra. Na základe prijatých hodnôt nastavuje:

- **Rýchlosť motorov**: Pohyb dopredu alebo dozadu.
- **Diferenciálne riadenie**: Otáčanie autíčka podľa rozdielnej rýchlosti ľavého a pravého motora.

Okrem ovládania joystickom sme implementovali aj ovládanie cez štyri tlačidlá, ktoré boli napojené na STM32 cez digitálne vstupy. Každé tlačidlo vykonáva jednu zo špecifických funkcií:

- **Tlačidlá 1 a 2**: Rýchlosť pohybu dopredu a dozadu.
- **Tlačidlá 3 a 4**: Otáčanie doľava alebo doprava.

### Detailný priebeh spracovania signálov

1. **Joystick a ADC spracovanie:**
   - Pri pohybe joysticku sa mení jeho napätie na osiach X a Y.
   - ADC v STM32 tieto analógové signály konvertuje na digitálne hodnoty (0 – 4095).
   - Tieto hodnoty určujú smer a intenzitu pohybu.

2. **Prenos signálov do STM na autíčku:**
   - Digitálne hodnoty sa cez káble posielajú do STM32 na autíčku.
   - Mikrokontrolér ich interpretuje a cez USART protokol odosiela príkazy do dosky MD25.

3. **MD25 a motory:**
   - MD25 riadi rýchlosť a smery motorov na základe prijatých príkazov.
   - Motory sa pohybujú synchronizovane alebo diferencovane v závislosti od hodnôt príkazov.

4. **Pohyb autíčka:**
   - Rýchlosť pohybu je riadená zmenou PWM signálu na doske MD25.
   - Diferenciálne ovládanie zabezpečuje otáčanie podľa rozdielu medzi rýchlosťou ľavého a pravého motora.

## Rozdelenie práce

- **Konfigurácia pinov a prehľadávanie registrov:** Žolo (Zoltán Sármány)
- **Logika pohybu:** Matúš (Matúš Tetliak)
- **Prenos signálov cez USART a správa s Gitom:** Džihi (Samuel Mihálik)
- **Zapájanie hardvéru a vyhľadávanie informácií:** Kubo (Jakub Tinák)

## Záver

Projekt poskytol dve alternatívne riešenia na ovládanie autíčka – pôvodný bezdrôtový prenos cez RFM moduly a SPI protokol a jednoduchšie káblové prepojenie joysticku so STM32. Napriek vyššej zložitosti pôvodného riešenia boli získané dôležité poznatky o bezdrôtovej komunikácii. Aktuálne káblové riešenie ponúka stabilnejší a jednoduchší systém na presné ovládanie modelu autíčka.
