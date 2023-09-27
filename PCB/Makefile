all: placeleds stl

placeleds: placeleds.c PCBCase/pcb.c PCBCase/pcb.h
	gcc -IPCBCase -O -o $@ $< PCBCase/pcb.c -lpopt -lm -g

leds:	placeleds
	#./placeleds 5x7/5x7.kicad_pcb --cols=5 --rows=7 --width-join=0.5 --width-end=0.2 --width-power=0.3 --fill=VCC --power-vias=0.8 --vias=0.8
	./placeleds Gate/Gate.kicad_pcb -x100 -y100 -d120 --diode=1 --count=27 --group=3 --spacing=3 --vias=0.8 --power-vias=0.8 --width-power=0.2 --width-end=0.2 --width-join=0.2 --angle=10

stl:    LED/LED.stl

PCBCase/case: PCBCase/case.c
	make -C PCBCase

%.stl: %.scad
	echo "Making $@"
	/Applications/OpenSCAD.app/Contents/MacOS/OpenSCAD $< -o $@
	echo "Made $@"

LED/LED.scad: LED/LED.kicad_pcb PCBCase/case Makefile
	PCBCase/case -o $@ $< --edge=2 --base=5 --top=4 --pcb=2
