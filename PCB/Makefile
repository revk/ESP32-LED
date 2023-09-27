all: placeleds stl

placeleds: placeleds.c PCBCase/pcb.c PCBCase/pcb.h
	gcc -IPCBCase -O -o $@ $< PCBCase/pcb.c -lpopt -lm -g

leds:	placeleds
	#./placeleds 5x7/5x7.kicad_pcb --cols=5 --rows=7 --width-join=0.5 --width-end=0.2 --width-power=0.3 --fill=VCC --power-vias=0.8 --vias=0.8
	./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d103.5 --diode=1 --count=117 --vias=0.8 --power-vias=0.8 --width-power=0.3 --width-end=0.2 --width-join=0.2 --angle=181.5384615 --fill=VCC
	./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d109.5 --diode=118 --count=39 --vias=0.8 --power-vias=0.8 --width-power=0.3 --width-end=0.2 --width-join=0.2 --angle=184.6153846 --fill=VCC
	./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d114.5 --diode=157 --count=18 --group=2 --spacing=4 --vias=0.8 --power-vias=0.8 --width-power=0.3 --width-end=0.2 --width-join=0.2 --angle=200 --fill=VCC
	./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d119.5 --diode=175 --count=117 --vias=0.8 --power-vias=0.8 --width-power=0.3 --width-end=0.2 --width-join=0.2 --angle=181.5384615 --fill=VCC
	./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d124.5 --diode=292 --count=18 --group=2 --spacing=8 --vias=0.8 --power-vias=0.8 --width-power=0.3 --width-end=0.2 --width-join=0.2 --angle=200 --fill=VCC
	./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d129.5 --diode=310 --count=18 --group=2 --spacing=10 --vias=0.8 --power-vias=0.8 --width-power=0.3 --width-end=0.2 --width-join=0.2 --angle=200 --fill=VCC
	./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d134.5 --diode=328 --count=45 --group=5 --spacing=6 --vias=0.8 --power-vias=0.8 --width-power=0.3 --width-end=0.2 --width-join=0.2 --angle=200 --fill=VCC

stl:    LED/LED.stl

PCBCase/case: PCBCase/case.c
	make -C PCBCase

%.stl: %.scad
	echo "Making $@"
	/Applications/OpenSCAD.app/Contents/MacOS/OpenSCAD $< -o $@
	echo "Made $@"

LED/LED.scad: LED/LED.kicad_pcb PCBCase/case Makefile
	PCBCase/case -o $@ $< --edge=2 --base=5 --top=4 --pcb=2
