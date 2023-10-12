all: placeleds stl

placeleds: placeleds.c PCBCase/pcb.c PCBCase/pcb.h
	gcc -IPCBCase -O -o $@ $< PCBCase/pcb.c -lpopt -lm -g

leds:	placeleds
	#./placeleds 5x7/5x7.kicad_pcb --cols=5 --rows=7 --fill=VCC --power-vias=0.8 --vias=0.8 --tracks
	#./placeleds 5x9/5x9.kicad_pcb --cols=5 --rows=9 --fill=VCC --power-vias=0.8 --vias=0.8 --tracks
	#./placeleds Gate/Gate.kicad_pcb -x100 -y100  -d98.5 --zone-in=1.75 --zone-out=1.25   --diode=1 --count=117 --vias=0.8 --power-vias=0.8 --angle=181.5384615 --fill=VCC --tracks
	#./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d103.5 --zone-in=1.75 --zone-out=1.25 --diode=118 --count=117 --vias=0.8 --power-vias=0.8 --angle=181.5384615 --fill=VCC --tracks
	#./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d108.5 --zone-in=1.25 --zone-out=1.25 --diode=235 --count=39 --vias=0.8 --power-vias=0.8 --angle=184.6153846 --fill=VCC --tracks
	#./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d113.5 --zone-in=1.25 --zone-out=1.25 --diode=274 --count=18 --group=2 --spacing=4.485 --vias=0.8 --power-vias=0.8 --angle=200 --fill=VCC --tracks
	#./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d118.5 --zone-in=1.25 --zone-out=1.25 --diode=292 --count=117 --vias=0.8 --power-vias=0.8 --angle=181.5384615 --fill=VCC --tracks
	#./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d123.5 --zone-in=1.25 --zone-out=1.25 --diode=409 --count=27 --group=3 --spacing=4.12125 --vias=0.8 --power-vias=0.8 --angle=200 --fill=VCC --tracks
	#./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d128.5 --zone-in=1.25 --zone-out=1.25 --diode=436 --count=18 --group=2 --spacing=10.12125 --vias=0.8 --power-vias=0.8 --angle=200 --fill=VCC --tracks
	#./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d133.5 --zone-in=1.25 --zone-out=1.25 --diode=454 --count=45 --group=5 --spacing=6 --vias=0.8 --power-vias=0.8 --angle=200 --fill=VCC --tracks

stl:    LED/LED.stl

PCBCase/case: PCBCase/case.c
	make -C PCBCase

%.stl: %.scad
	echo "Making $@"
	/Applications/OpenSCAD.app/Contents/MacOS/OpenSCAD $< -o $@
	echo "Made $@"

LED/LED.scad: LED/LED.kicad_pcb PCBCase/case Makefile
	PCBCase/case -o $@ $< --edge=2 --base=5 --top=4 --pcb=2
