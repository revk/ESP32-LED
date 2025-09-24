use <Coaster2/Coaster.scad>
include <Coaster2.scad>

translate([0,0,h])rotate([180,0,0])
difference()
{
    outside();
    baseplate(pcbt);
    hull()
    {
        translate([0,0,-1])cylinder(d=d-e*2+pcbmin*2,h=b+1+pcbt);
        translate([0,0,-1])cylinder(d=d-e*2,h=b+1+pcbt+pcbmin);
    }
    hull()
    {
        translate([0,0,-1])cylinder(d=c+pcbmax*2,h=b+1+pcbt);
        translate([0,0,-1])cylinder(d=c,h=b+1+pcbt+pcbmax);
    }
    if(dip)
       hull()rotate_extrude()translate([d/2-sqrt(h*h-(h-dip)*(h-dip)),h*3/2-dip])circle(d=h);
    translate([0,0,b])J3() // USB
    {
    w=10;h=9;
      translate([-w/2,-2.3-h/2,0])cube([w,h,3.5]);
      translate([0,-2.3-4,2.5/2])rotate([90,0,0])
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
