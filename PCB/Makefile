all: placeleds stl

placeleds: placeleds.c PCBCase/pcb.c PCBCase/pcb.h
	gcc -IPCBCase -O -o $@ $< PCBCase/pcb.c -lpopt -lm -g

leds:	placeleds
	./placeleds 5x7/5x7.kicad_pcb --cols=5 --rows=7 --width-join=0.5 --width-end=0.2 --width-power=0.3 --fill=VCC --power-vias=0.8 --vias=0.8
	./placeleds Gate/Gate.kicad_pcb --diameter=100 --count=117 --width-join=0.2 --width-end=0.2 --width-power=0.3 --fill=VCC --power-vias=0.8 --vias=0.8
	./placeleds Gate/Gate.kicad_pcb --diameter=120 --diode=118 --cap=118 --count=39 --width-join=0.2 --width-end=0.2 --width-power=0.3 --fill=VCC --power-vias=0.8 --vias=0.8
	./placeleds Gate/Gate.kicad_pcb --diameter=105 --diode=157 --cap=157 --count=9 --width-join=0.2 --width-end=0.2 --width-power=0.3 --fill=VCC --pair=8 --power-vias=0.8 --vias=0.8
	./placeleds Gate/Gate.kicad_pcb --diameter=110 --diode=175 --cap=175 --count=9 --width-join=0.2 --width-end=0.2 --width-power=0.3 --fill=VCC --pair=10 --power-vias=0.8 --vias=0.8
	./placeleds Gate/Gate.kicad_pcb --diameter=115 --diode=193 --cap=193 --count=9 --width-join=0.2 --width-end=0.2 --width-power=0.3 --fill=VCC --pair=12 --power-vias=0.8 --vias=0.8

stl:    LED/LED.stl

PCBCase/case: PCBCase/case.c
	make -C PCBCase

%.stl: %.scad
	echo "Making $@"
	/Applications/OpenSCAD.app/Contents/MacOS/OpenSCAD $< -o $@
	echo "Made $@"

LED/LED.scad: LED/LED.kicad_pcb PCBCase/case Makefile
	PCBCase/case -o $@ $< --edge=2 --base=5 --top=4 --pcb=2
