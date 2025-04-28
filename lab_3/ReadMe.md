# Aerouosto modeliavimas

## Užduoties sąlyga

3. Aerouostas (ADT: prioritetinė eilė, ilgas sveikas skaičius). Aerouostas turi 1 pakilimo/nusileidimo taką, besileidžiantys lėktuvai turi prioritetą, t.y. jei takas laisvas, tai pirmiausia priimamas besileidžiantis lėktuvas, bet jei kažkuris lėktuvas pradėjo pakilimą, tai visi kiti, tame tarpe ir norintys nusileisti, lėktuvai turi laukti; lėktuvas, norintis nusileisti, negali laukti labai ilgai, nes jam baigsis degalai. Tikslas: patyrinėti prie kokio apkrovimo aerouostui pakanka vieno tako. Pradiniai duomenys: nusileidimo laikas (trukmė), pakilimo laikas (trukmė), laikas, kurį norintis leistis lėktuvas, dar gali išbūti ore, lėktuvo panorusio kilti/leistis einamuoju momentu tikimybė (galima realizacija: generuojamas atsitiktinis skaičius ir tikrinama, ar jis tenkina tam tikrą sąlygą), besileidžiantys ir kylantys lėktuvai pasirodo su vienoda tikimybe. Rezultatai: nukritęs lėktuvas (modeliavimas iš karto baigiamas), maksimalus ir vidutinis norinčio nusileisti lėktuvo laukimo laikas, maksimalus ir vidutinis norinčio pakilti lėktuvo laukimo laikas.

## Projekto struktūra
- **priorityQueue.h** - prioritetinės eilės antraštinis failas. *(Autorius: ugva1377)*
- **priorityQueue.c** - prioritetinės eilės implementacija. *(Autorius: ugva1377)*
- **BigInteger.h** - didelių sveikų skaičių antraštinis failas. *(Autorius: emsa0885)*
- **BigInteger.c** - didelių sveikų skaičių implementacija. *(Autorius: emsa0885)*
- **airport_sim.h** - aerouosto simuliacijos antraštinis failas.
- **airport_sim.c** - pagrindinė aerouosto simuliacijos logika.
- **main.c** - programos paleidimo ir valdymo logika.
- **tests.txt** - tekstinis failas su testų parametrais.
- **Makefile** - kompiliavimo instrukcijos.
- **Go.cmd** - automatizavimo skriptas Windows sistemai.

## Įvesties formatas
Vienoje eilutėje 5 parametrai, atskirti tarpais:
<landing_duration> <takeoff_duration> <max_air_time> <arrival_probability> <max_steps>

## Programos veikimo pavyzdys

### Įvestis

``
airport_sim.exe 3 2 5 0.7 1000
``

### Išvestis

``
Simulation Parameters:
Landing duration: 3
Takeoff duration: 2
Max air time: 5
Arrival probability: 0.70
Max steps: 100

Simulation Results:
Landing planes:
- Max wait time: 3
- Average wait time: 1.600000
Takeoff planes:
- Max wait time: 9
- Average wait time: 2.700000
``

## Testavimo scenarijai:
Programoje įdiegti 5 testų scenarijai:
1. 3 2 5 0.7 1000
2. 4 3 6 0.5 800
3. 2 2 4 0.8 1200
4. 5 4 7 0.6 900
5. 3 3 5 0.65 1100

## Testų paleidimas:

``
./airport_sim.exe -test
``