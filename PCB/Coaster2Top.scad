use <Coaster2/Coaster.scad>
include <Coaster2.scad>

translate([0,0,h])rotate([180,0,0])
difference()
{
    minkowski()
    {
        translate([0,0,h/2])cylinder(d=d,h=0.001);
        sphere(d=h);
    }
    translate([0,0,-1])cylinder(d=d,h=b+1+pcbt);
    translate([0,0,-1])cylinder(d=d-e*2,h=b+1+pcbt+pcbmin);
    translate([0,0,-1])cylinder(d=c,h=b+1+pcbt+pcbmax);
    translate([0,0,b])J3() // USB
    {
      cube([10,8,4]);
    }
}
