# Aerouosto modeliavimas

## Užduoties sąlyga

2. Duotas lėktuvų skrydžių sąrašas: miestas, miestas, išskridimo laikas, skrydžio trukmė. Rasti greičiausio skrydžio iš vieno duoto miesto į kitą duotą miestą maršrutą ir jo laiką (pradinis išskridimo laikas yra nesvarbus). Numatyti atvejį, kad toks maršrutas neegzistuoja. (grafo realizacija paremta kaimynystės sąrašais)

## Projekto struktūra
- **flight_graph.h** - trumpiausio maršruto laiko atžvilgiu paieškos antraštinis failas.
- **priorityQueue.c** - trumpiausio maršruto laiko atžvilgiu paieškos implementacija.
- **main.c** - programos paleidimo ir valdymo logika.
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