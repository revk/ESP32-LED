$fn=180;
h=10;    // Height (and edge wall)
d=100; //pcbwidth();  // PCB diameter
b=3;    // Base
e=8;    // Edge
c=40;	// Centre diameter
f=8;    // Foot diameter
l=6;    // Lug
pcbt=pcbthickness();	// PCB thickness
pcbmin=2;	// PCB component height (LEDs)
pcbmax=4.5;	// PCB component height (center)

module outside()
{

    hull()rotate_extrude()translate([d/2,h/2])circle(d=h);
}

module baseplate(t=0)
{
    translate([0,0,-f-1])cylinder(d=d,h=b+1+f+0.01+t);
    for(a=[60:60:359])rotate(a)translate([d/2,0,0])rotate(360/6/2)cylinder(d=l,h=b,$fn=6);
}
