stl:    LED/LED.stl LED2/LED.stl

PCBCase/case: PCBCase/case.c
	make -C PCBCase

%.stl: %.scad
	echo "Making $@"
	/Applications/OpenSCAD.app/Contents/MacOS/OpenSCAD $< -o $@
	echo "Made $@"

LED/LED.scad: LED/LED.kicad_pcb PCBCase/case Makefile
	PCBCase/case -o $@ $< --edge=2 --base=5 --top=4 --pcb=2

LED2/LED.scad: LED2/LED.kicad_pcb PCBCase/case Makefile
	PCBCase/case -o $@ $< --edge=2 --base=5 --top=4 --pcb=2

