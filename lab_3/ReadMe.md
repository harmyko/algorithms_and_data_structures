# Aerouosto modeliavimas

## Užduoties sąlyga

3. Aerouostas (ADT: prioritetinė eilė, ilgas sveikas skaičius). Aerouostas turi 1 pakilimo/nusileidimo taką, besileidžiantys lėktuvai turi prioritetą, t.y. jei takas laisvas, tai pirmiausia priimamas besileidžiantis lėktuvas, bet jei kažkuris lėktuvas pradėjo pakilimą, tai visi kiti, tame tarpe ir norintys nusileisti, lėktuvai turi laukti; lėktuvas, norintis nusileisti, negali laukti labai ilgai, nes jam baigsis degalai. Tikslas: patyrinėti prie kokio apkrovimo aerouostui pakanka vieno tako. Pradiniai duomenys: nusileidimo laikas (trukmė), pakilimo laikas (trukmė), laikas, kurį norintis leistis lėktuvas, dar gali išbūti ore, lėktuvo panorusio kilti/leistis einamuoju momentu tikimybė (galima realizacija: generuojamas atsitiktinis skaičius ir tikrinama, ar jis tenkina tam tikrą sąlygą), besileidžiantys ir kylantys lėktuvai pasirodo su vienoda tikimybe. Rezultatai: nukritęs lėktuvas (modeliavimas iš karto baigiamas), maksimalus ir vidutinis norinčio nusileisti lėktuvo laukimo laikas, maksimalus ir vidutinis norinčio pakilti lėktuvo laukimo laikas.

## Įvesties formatas
Vienoje eilutėje x parametrai, atskirti tarpais:

## Programos veikimo pavyzdys

### Įvestis


### Išvestis

Simulation parameters:

Simulation Results:

## Projekto struktūra
- **priorityQueue.h** - prioritetinės eilės antraštinis failas. *(Autorius: ugva1377)*
- **priorityQueue.c** - prioritetinės eilės implementacija. *(Autorius: ugva1377)*
- **BigInteger.h** - didelių sveikų skaičių antraštinis failas. *(Autorius: emsa0885)*
- **BigInteger.c** - didelių sveikų skaičių implementacija. *(Autorius: emsa0885)*
- **airport_sim.h** - aerouosto simuliacijos antraštinis failas.
- **airport_sim.c** - pagrindinė aerouosto simuliacijos logika.
- **main.c** - programos paleidimo ir valdymo logika.
- **Makefile** - kompiliavimo instrukcijos.
- **Go.cmd** - automatizavimo skriptas Windows sistemai.


## Testavimo scenarijai:
Programoje įdiegti 5 testų scenarijai:
1. 
2. 
3. 
4. 
5. 

## Testų paleidimas:

``
airport_sim.exe -test
``