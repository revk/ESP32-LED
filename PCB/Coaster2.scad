$fn=180;
h=12;    // Height (and edge wall)
d=pcbwidth();  // PCB diameter
b=3;     // Base
e=10;     // Edge
c=38;	 // Centre diameter
f=8;     // Foot diameter
l=6;     // Lug
dip=2;  // Dip in top
pcbt=pcbthickness();	// PCB thickness
pcbmin=2;	// PCB component height (LEDs)
pcbmax=4;	// PCB component height (center) ** 4.5 **

module outside()
{

    hull()rotate_extrude()translate([d/2,h/2])circle(d=h);
}

module baseplate(t=0)
{
    translate([0,0,-f-1])cylinder(d=d,h=b+1+f+0.01+t);
    for(a=[60:60:359])rotate(a)translate([d/2,0,0])rotate(360/6/2)cylinder(d=l,h=b,$fn=6);
}
