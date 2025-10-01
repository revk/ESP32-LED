$fn=180;
h=11;    // Height (and edge wall)
d=pcbwidth()+2;  // PCB diameter
b=2;     // Base
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

    rotate_extrude()translate([d/2,h/2])circle(d=h);
    cylinder(d=d,h=h-dip/2);
}

module baseplate(t=0)
{
    translate([0,0,-f-1])cylinder(d=d,h=b+1+f+0.01+t);
    for(a=[30:60:359])rotate(a)translate([d/2,0,0])rotate(360/6/2)cylinder(d1=l-0.5,d2=l,h=b,$fn=6);
}
