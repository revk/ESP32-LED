all: grid stl

grid: grid.c PCBCase/pcb.c PCBCase/pcb.h
	gcc -IPCBCase -O -o $@ $< PCBCase/pcb.c -lpopt -lm -g

leds:	grid
	./grid 5x7/5x7.kicad_pcb --cols=5 --rows=7 --sides
	./grid 150x7/150x7.kicad_pcb --cols=150 --rows=7

stl:    LED/LED.stl

PCBCase/case: PCBCase/case.c
	make -C PCBCase

%.stl: %.scad
	echo "Making $@"
	/Applications/OpenSCAD.app/Contents/MacOS/OpenSCAD $< -o $@
	echo "Made $@"

LED/LED.scad: LED/LED.kicad_pcb PCBCase/case Makefile
	PCBCase/case -o $@ $< --edge=2 --base=5 --top=4 --pcb=2
