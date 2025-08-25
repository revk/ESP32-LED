all: png stl */README.md

placeleds: placeleds.c PCBCase/pcb.c PCBCase/pcb.h
	gcc -IPCBCase -O -o $@ $< PCBCase/pcb.c -lpopt -lm -g

leds:	placeleds
	#./placeleds 5x7/5x7.kicad_pcb --cols=5 --rows=7 --fill=VCC --power-vias=0.8 --vias=0.8 --tracks
	#./placeleds 5x9/5x9.kicad_pcb --cols=5 --rows=9 --fill=VCC --power-vias=0.8 --vias=0.8 --tracks
	#./placeleds Gate/Gate.kicad_pcb -x100 -y100 -r49.25 --zone-in=1.75 --zone-out=1.25   --diode=1 --count=117 --vias=0.8 --power-vias=0.8 --angle=181.5384615 --fill=VCC --tracks
	#./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d51.75 --zone-in=1.75 --zone-out=1.25 --diode=118 --count=117 --vias=0.8 --power-vias=0.8 --angle=181.5384615 --fill=VCC --tracks
	#./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d54.25 --zone-in=1.25 --zone-out=1.25 --diode=235 --count=39 --vias=0.8 --power-vias=0.8 --angle=184.6153846 --fill=VCC --tracks
	#./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d56.75 --zone-in=1.25 --zone-out=1.25 --diode=274 --count=18 --group=2 --spacing=4.485 --vias=0.8 --power-vias=0.8 --angle=200 --fill=VCC --tracks
	#./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d59.25 --zone-in=1.25 --zone-out=1.25 --diode=292 --count=117 --vias=0.8 --power-vias=0.8 --angle=181.5384615 --fill=VCC --tracks
	#./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d61.75 --zone-in=1.25 --zone-out=1.25 --diode=409 --count=27 --group=3 --spacing=4.12125 --vias=0.8 --power-vias=0.8 --angle=200 --fill=VCC --tracks
	#./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d62.25 --zone-in=1.25 --zone-out=1.25 --diode=436 --count=27 --group=3 --spacing=5.060625 --vias=0.8 --power-vias=0.8 --angle=200 --fill=VCC --tracks
	#./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d66.75 --zone-in=1.25 --zone-out=1.25 --diode=463 --count=45 --group=5 --spacing=6 --vias=0.8 --power-vias=0.8 --angle=200 --fill=VCC --tracks

	#./placeleds Coaster2/Coaster.kicad_pcb -x100 -y100 -d90 --diode=140 --count=60 --fill=VCC --tracks --vias=0.8 --power-vias=0.8  --zone-in=2.5 --zone-out=2.5
	#./placeleds Coaster2/Coaster.kicad_pcb -x100 -y100 -d80 --diode=80 --count=60 --fill=VCC --tracks --vias=0.8 --power-vias=0.8  --zone-in=2.5 --zone-out=2.5
	#./placeleds Coaster2/Coaster.kicad_pcb -x100 -y100 -d70 --diode=68 --count=12 --fill=VCC --tracks --vias=0.8 --power-vias=0.8  --zone-in=2.5 --zone-out=2.5
	#./placeleds Coaster2/Coaster.kicad_pcb -x100 -y100 -d60 --diode=56 --count=12 --fill=VCC --tracks --vias=0.8 --power-vias=0.8  --zone-in=2.5 --zone-out=2.5
	#./placeleds Coaster2/Coaster.kicad_pcb -x100 -y100 -d50 --diode=44 --count=12 --fill=VCC --tracks --vias=0.8 --power-vias=0.8  --zone-in=2.5 --zone-out=2.5
	#./placeleds Coaster2/Coaster.kicad_pcb -x100 -y100 -d40 --diode=32 --count=12 --fill=VCC --tracks --vias=0.8 --power-vias=0.8  --zone-in=2.5 --zone-out=2.5
	#./placeleds Coaster2/Coaster.kicad_pcb -x100 -y100 -d30 --diode=20 --count=12 --fill=VCC --tracks --vias=0.8 --power-vias=0.8  --zone-in=2.5 --zone-out=2.5
	#./placeleds Coaster2/Coaster.kicad_pcb -x100 -y100 -d20 --diode=8 --count=12 --fill=VCC --tracks --vias=0.8 --power-vias=0.8  --zone-in=2.5 --zone-out=2.5
	#./placeleds Coaster2/Coaster.kicad_pcb -x100 -y100 -d10 --diode=2 --count=6 --fill=VCC --tracks --vias=0.8 --power-vias=0.8  --zone-in=2.5 --zone-out=2.5

	#./placeleds Coaster2/Coaster.kicad_pcb -x100 -y100 -d80 --diode=61 --count=64 --fill=VBUS --tracks --vias=0.8 --power-vias=0.8  --zone-in=2 --zone-out=2 
	#./placeleds Coaster2/Coaster.kicad_pcb -x100 -y100 -d72 --diode=29 --count=32 --fill=VBUS --tracks --vias=0.8 --power-vias=0.8  --zone-in=2 --zone-out=2
	#./placeleds Coaster2/Coaster.kicad_pcb -x100 -y100 -d64 --diode=13 --count=16 --fill=VBUS --tracks --vias=0.8 --power-vias=0.8  --zone-in=2 --zone-out=2
	#./placeleds Coaster2/Coaster.kicad_pcb -x100 -y100 -d56 --diode=5 --count=8 --fill=VBUS --tracks --vias=0.8 --power-vias=0.8  --zone-in=2 --zone-out=2
	#./placeleds Coaster2/Coaster.kicad_pcb -x100 -y100 -d48 --diode=1 --count=4 --fill=VBUS --tracks --vias=0.8 --power-vias=0.8  --zone-in=2 --zone-out=2

	#./placeleds LED32/LED.kicad_pcb -x100 -y100 -d6 --diode=1 --count=4 --fill=VCC --tracks --vias=0.8 --power-vias=0.8 --zone-in=1.375 --zone-out=1.375
	#./placeleds LED32/LED.kicad_pcb -x100 -y100 -d11.5 --diode=5 --count=12 --fill=VCC --tracks --vias=0.8 --power-vias=0.8 --zone-in=1.375 --zone-out=1.375
	#./placeleds LED32/LED.kicad_pcb -x100 -y100 -d17 --diode=17 --count=16 --fill=VCC --tracks --vias=0.8 --power-vias=0.8 --zone-in=1.375 --zone-out=1.375
	#./placeleds LED32/LED.kicad_pcb -x100 -y100 -d22.5 --diode=33 --count=24 --fill=VCC --tracks --vias=0.8 --power-vias=0.8 --zone-in=1.375 --zone-out=1.375
	#./placeleds LED32/LED.kicad_pcb -x100 -y100 -d28 --diode=57 --count=32 --fill=VCC --tracks --vias=0.8 --power-vias=0.8 --zone-in=1.375 --zone-out=1.375

stl:    LEDC/LEDT.stl LEDR/LEDT.stl LEDC12/LEDT.stl LEDC/LEDB.stl LEDR/LEDB.stl LEDC12/LEDB.stl

png:	$(patsubst %.kicad_pcb,%.png,$(wildcard */*.kicad_pcb))

PCBCase/case: PCBCase/case.c
	make -C PCBCase

PCBCase/clean: PCBCase/clean.c
	make -C PCBCase

%.stl: %.scad
	echo "Making $@"
	/Applications/OpenSCAD.app/Contents/MacOS/OpenSCAD $< -o $@
	echo "Made $@"

LEDC/LEDT.scad: LEDC/LED.kicad_pcb PCBCase/case
	PCBCase/case -o $@ $< --edge=2 --bottom=2 --top=7 --pcb=2 --two-file

LEDC12/LEDT.scad: LEDC12/LED.kicad_pcb PCBCase/case
	PCBCase/case -o $@ $< --edge=2 --bottom=2 --top=7 --pcb=2 --two-file

LEDR/LEDT.scad: LEDR/LED.kicad_pcb PCBCase/case
	PCBCase/case -o $@ $< --edge=2 --bottom=2 --top=7 --pcb=2 --two-file

%.png:	%.kicad_pcb PCBCase/clean PCBCase/render
	PCBCase/render $<

%/README.md: %/*.kicad_pcb %/*.stl PCBCase/readme
	PCBCase/readme $@
