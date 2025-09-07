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
      translate([-5,1.51-8,0])cube([10,8.5,4]);
      translate([0,1.51-8,0])rotate([90,0,0])
      {
        translate([0,0,-2])hull()
        {
            translate([-8.5/2+2.5/2,0,0])cylinder(d=2.5,h=100);
            translate([8.5/2-2.5/2,0,0])cylinder(d=2.5,h=100);
        }
        translate([0,0,1])hull()
        {
            translate([-11.5/2+7.5/2,0,0])cylinder(d=7.5,h=100);
            translate([11.5/2-7.5/2,0,0])cylinder(d=7.5,h=100);
        }
      }
    }
    for(a=[0:120:360])rotate(a+60)translate([d/2-1,-2.5,-1])cube([e+2,5,b+1]);
}
