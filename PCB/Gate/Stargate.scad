// Stargate
// Origin is centre of ring at face, i.e. base of glyphs
// Ring faces up

doglyphs=true;          // Include glyphs
doramp=true;            // Include ramp
dopcb=true;             // Include cut out for PCB
top=false;              // Top only
bottom=false;           // Bottom only

radiusi=50;             // Inner radius (i.e. hole in gate)
radiusr=radiusi*62/50;  // Edge of glyphys
radiuso=radiusi*70/50;  // Outer radius (before adding chevrons
depth=radiusi*15/50;    // Gate thickness (before chevrons/glyphs
rampw=radiuso*0.8;      // Ramp width
rampw2=radiuso;         // Ramp width at bottom
raised=1;               // Raised glyphs, etc
edge=1;                 // Glyph edge
thickness=0.5;          // line thickness

radiuspcbo=70.5;        // PCB radius (outer)
radiuspcbi=49.5;        // PCB radius (inner)
thicknesspcb=1;         // PCB thickness
radiuspartso=69.0;      // PCB parts radius (outer)
radiuspartsi=50.5;      // PCB parts radius (inner)
thicknessparts=1.5;     // PCB thickness with parts
frontpcb=1;             // Gate thickness in front of PCB
lip=2;                  // Top/Bottom overlap lip

$fn=39*3;

module cone(r,h,c=8)
{
    polyhedron(points=[[0,0,h],for(i=[0:1:c-1])[r*sin(360*i/c),r*cos(360*i/c),0]],faces=[[for(i=[c:-1:1])i],for(i=[1:1:c])[0,i,1+(i%c)]]);
}

module glyphs()
{
    render()
    scale(radiusi/50)
    translate([-130/2,-130/2,-1])
    minkowski()
    {
        cone(r=raised/2,h=raised);
            linear_extrude(height=1)
            import("Glyphs.dxf");
    }
}

module ramp(t=0)
{
    h=radiuso-sqrt(radiusi*radiusi-rampw*rampw/4);
    b=raised*3;
    hull()
    {
        translate([-rampw/2+t,-radiuso-b-t,-depth-t-raised*4])
        cube([rampw-t*2,h+b,depth+raised*4]);
        translate([-rampw2/2+t,-radiuso-b-t,h*2-t/10])
        cube([rampw2-t*2,raised,1]);
    }
}

module pcb()
{
    difference()
    { // PCB
        h=bottom?thicknesspcb:depth*2;
        translate([0,0,-frontpcb-h])
        {
            cylinder(r=radiuspcbo,h=h);
            translate([0,0,thicknesspcb-thicknessparts])
            washer(ri=radiuspartsi,ro=radiuspartso,h=thicknessparts);
        }
        cylinder(r=radiuspcbi,h=depth*5,center=true);
    }
    // Hole in base
    if(doramp)ramp(5);
}

module ringouter(h=0)
{
    hull()
    {
        cylinder(r=radiuso+edge*2,h=depth+raised*2,center=true);
        cylinder(r=radiuso+edge,h=depth+raised*4+h,center=true);
    }
}

module ringouterstripe()
{
    difference()
    {
        ringouter();
        d=(radiuso-radiusr)/14;
        translate([0,0,depth/2+raised*2])
        {
            washer(ri=radiuso-d,ro=radiuso,h=raised*3);
            for(i=[1:1:6])
                washer(ri=radiuso-i*d*2-d,ro=radiuso-i*d*2,h=raised);
        }
    }
}

module washer(ro,ri,h,center=true)
{
    render()
    difference()
    {
        cylinder(r=ro,h=h,center=center);
        cylinder(r=ri,h=h+1,center=center);
    }
}

module chevron()
{
    ci=radiusr/10;
    cl=radiuso/2;
    render()
    translate([0,0,-depth/2])   // centre on middle of ring
    {
        difference()
        {
            union()
            {
                intersection()
                {
                    difference()
                    {
                        ringouter();
                        cylinder(r=radiuso,h=depth+raised*4+2,center=true);
                    }
                    hull()
                    {
                        cylinder(d=1,h=depth*2,center=true);
                        translate([-cl/2,radiuso+edge+1,-depth])
                        cube([cl,1,depth*2]);
                    }
                }
                intersection()
                {
                    ringouterstripe();
                    hull()
                    {
                        translate([-ci/2,radiusr*.95,-depth])
                        cube([ci,1,depth*2]);
                        translate([-ci*1.5,radiuso+edge+1,-depth])
                        cube([ci*3,1,depth*2]);
                    }
                }
            }
            intersection()
            {
                ringouter(raised);
                hull()
                {
                    translate([-ci/2+raised,radiusr*.95+raised,-depth])
                    cube([ci-raised*2,1,depth*2]);
                    translate([-ci+raised,radiuso+edge+1,-depth])
                    cube([ci*2-raised*2,1,depth*2]);
                }
            }
        }
        intersection()
        {
            ringouter(raised*2);
            hull()
            {
                translate([-ci/2+raised*2,radiusr*.95+raised*2,-depth/2-raised*2])
                cube([ci-raised*4,1,depth+raised*4]);
                translate([-ci+raised*2,radiuso+edge+1,-depth])
                cube([ci*2-raised*4,1,depth*2]);
            }
        }
    }
}

module chevrons()
{
    for(c=[0:1:8])
        rotate([0,0,c*360/9])
        chevron();
}

module ring()
{    
    translate([0,0,-depth/2])
    washer(ri=radiusi,ro=radiuso,h=depth);
}

module gate()
{ // Draw the gate
    ring();
    if(doglyphs)
        glyphs();
    if(doramp)
        ramp();
    minkowski()
    {
        cone(r=raised/2,h=raised);
        translate([0,0,0-1])
        union()
        {
            // raised rings
            washer(ri=radiusi-thickness/2+raised/2,ro=radiusi+thickness/2+raised/2,h=2);
            washer(ri=radiusr-thickness/2,ro=radiusr+thickness/2,h=2);
            washer(ri=radiuso-thickness/2-raised/2,ro=radiuso+thickness/2-raised/2,h=2);
            // dividers
            for(a=[0:1:38])
                rotate([0,0,360*(a+0.5)/39])
                    translate([-thickness/2,radiusi+raised/2,0])
                    cube([thickness,radiusr-radiusi-raised/2,1]);
            // Edge bands
            for(a=[0:1:233])
                rotate([0,0,360*a/234])
                    translate([-thickness/2,radiusr,0])
                    cube([thickness,radiuso-radiusr-raised/2,1]);
        }
    }
    chevrons();
}

module cut()
{ // Cut line for top/bottom
    translate([0,0,-frontpcb])
    union()
    {
        difference()
        {
            cylinder(r1=radiuspcbo,r2=radiuso+edge*2,h=lip);
            cylinder(r1=radiuspcbi,r2=radiuspcbi-edge*2,h=lip);
        }
        translate([0,0,lip])
        cylinder(r=radiuso*2,h=depth*10);
    }
}

difference()
{
    gate();
    if(dopcb)pcb();
    if(top)difference(){translate([0,0,-depth*2])cylinder(r=radiuso*3,h=depth*4);cut();}
    if(bottom)translate([0,0,-frontpcb])cut();
 }
