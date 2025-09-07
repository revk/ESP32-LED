use <Coaster2/Coaster.scad>
include <Coaster2.scad>

difference()
{
    cylinder(d=d,h=b); 
    rotate([180,0,0])translate([0,0,-pcbt-b-0.01])U1()translate([0.785,0,0])cylinder(d1=4,d2=2,h=b+0.02);
}

intersection()
{
    translate([0,0,b-h])minkowski()
    {
        translate([0,0,h/2])cylinder(d=d,h=0.001);
        sphere(d=h);
    }
    for(a=[0:120:360])rotate(a+60)translate([d/2-1,-2.5,0])cube([e+2,5,b]);
}
intersection()
{
    cylinder(d=d,h=f);
    union()
    {
        for(a=[0:120:360])rotate(a)translate([d/2-f/2-2,0,b])sphere(d=f);
        for(a=[0:120:360])rotate(a+60)translate([d/2-(f-1)/2-2,0,b])sphere(d=f-1);
    }
}