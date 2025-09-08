use <Coaster2/Coaster.scad>
include <Coaster2.scad>


translate([0,0,b])rotate([180,0,0])
{
    intersection()
    {
        outside();
        difference()
        {
            baseplate();
            translate([0,0,-0.01-pcbt])U1()translate([0.785,0,0])cylinder(d1=4,d2=2,h=b+0.03);
        }
    }
    
    intersection()
    {
        baseplate();
        union()
        {
            for(a=[0:120:359])rotate(a+60)translate([d/2-f/2-1,0,0])sphere(d=f);
            for(a=[0:120:359])rotate(a)translate([d/2-f/2-1,0,0])sphere(d=f-1);
        }
    }   
}