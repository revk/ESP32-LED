use <Coaster2/Coaster.scad>
include <Coaster2.scad>

translate([0,0,h])rotate([180,0,0])
difference()
{
    outside();
    baseplate(pcbt);
    translate([0,0,-1])cylinder(d=d-e*2,h=b+1+pcbt+pcbmin);
    translate([0,0,-1])cylinder(d=c,h=b+1+pcbt+pcbmax);
    translate([0,0,b])J3() // USB
    {
      translate([-5,1.51-8,0])cube([10,8.5,4]);
      translate([0,1.51-8,2.5/2])rotate([90,0,0])
      {
        translate([0,0,-2])hull()
        {
            w=8.5;h=2.5;
            translate([-w/2+h/2,0,0])cylinder(d=h,h=100);
            translate([w/2-h/2,0,0])cylinder(d=h,h=100);
        }
        translate([0,0,1.1])hull()
        {
            w=12.5;h=7.5;
            translate([-w/2+h/2,0,0])cylinder(d=h,h=100);
            translate([w/2-h/2,0,0])cylinder(d=h,h=100);
        }
      }
    }
}
