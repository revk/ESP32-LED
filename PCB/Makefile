all: placeleds stl

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
	./placeleds Roulette/Roulette.kicad_pcb -x100 -y100 -r50 --zone-in=1.25 --zone-out=1.25 --diode=1 --count=74 --vias=0.8 --power-vias=0.8 --angle=0 --fill=VLED --tracks
	./placeleds Roulette/Roulette.kicad_pcb -x90 -y69 --rows=7 --cols=11 --diode=75 --cap=75 --vias=0.8 --power-vias=0.8 --angle=0 --fill=VLED --tracks

stl:    LED/LED.stl

PCBCase/case: PCBCase/case.c
	make -C PCBCase

%.stl: %.scad
	echo "Making $@"
	/Applications/OpenSCAD.app/Contents/MacOS/OpenSCAD $< -o $@
	echo "Made $@"

LED/LED.scad: LED/LED.kicad_pcb PCBCase/case Makefile
	PCBCase/case -o $@ $< --edge=2 --base=5 --top=4 --pcb=2
