// Stargate
// Origin is centre of ring at face, i.e. base of glyphs
// Ring faces up

doglyphs=true;          // Include glyphs
doramp=true;            // Include ramp
top=false;              // Top only for PCB
bottom=false;            // Bottom only for PCB

radiusi=50;             // Inner radius (i.e. hole in gate)
radiusr=radiusi*62/50;  // Edge of glyphys
radiuso=radiusi*70/50;  // Outer radius (before adding chevrons
depth=radiusi*8/50;    // Gate thickness (before chevrons/glyphs
rampw=radiuso*0.8;      // Ramp width
rampw2=radiuso;         // Ramp width at bottom
raised=1;               // Raised glyphs, etc
raisedr=raised/3;       // Radius of raised base
edge=1;                 // Glyph edge
thickness=0.5;          // line thickness

radiuspcbo=70.25;        // PCB radius (outer)
radiuspcbi=49.75;        // PCB radius (inner)
thicknesspcb=2.5;       // PCB and parts thickness
frontpcb=1;             // Gate thickness in front of PCB

$fn=39*3;

module cone(r,h,c=6)
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
        cone(r=raisedr,h=raised);
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
w=10;
    // PCB
    translate([0,0,-frontpcb-thicknesspcb])
    washer(ri=radiuspcbi,ro=radiuspcbo,h=thicknesspcb,center=false);
    translate([-w,-radiuso*2,-frontpcb-thicknesspcb-5])
    cube([w,radiuso*2-(radiuspcbo+radiuspcbi)/2,6]);
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

module washer2(a,b,c,d,h,center=false)
{
    render()
    difference()
    {
        cylinder(r1=a,r2=b,h=h,center=center);
        cylinder(r1=d,r2=c,h=h,center=center);
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
    washer(ri=radiusi,ro=radiuso+0.01,h=depth);
}

module gate()
{ // Draw the gate
    ring();
    if(doglyphs)
        glyphs();
    if(doramp)
        ramp();
    // raised rings
    washer2(radiuso,radiuso-raisedr,radiuso-raisedr-thickness,radiuso-raisedr-thickness-raisedr,raised);
    washer2(radiusr+thickness/2+raisedr,radiusr+thickness/2,radiusr-thickness/2,radiusr-thickness/2-raisedr,raised);
    washer2(radiusi+raisedr+thickness+raisedr,radiusi+raisedr+thickness,radiusi+raisedr,radiusi,raised);
    // Glyph dividers
    for(a=[0:1:38])
        rotate([0,0,360*(a+0.5)/39])
            translate([-thickness/2,radiusi+raisedr+thickness/2,0])
            hull()
            {
                translate([-raisedr,0,-1])
                cube([thickness+raisedr*2,radiusr-radiusi-thickness,1]);
                cube([thickness,radiusr-radiusi-thickness,raised]);
            }
    // Edge bands
    for(a=[0:1:233])
        rotate([0,0,360*a/234])
            translate([-thickness/2,radiusr,0])
            {
                translate([-raisedr,0,-1])
                cube([thickness+raisedr*2,radiuso-radiusr-thickness,1]);
                cube([thickness,radiuso-radiusr-thickness,raised]);
            }
    // back of gate
    rotate([180,0,0])
        translate([0,0,depth])
            washer2(radiuso,radiuso-raisedr,radiusi+raisedr,radiusi,raised);
    chevrons();
}

module cut()
{ // Cut line for top/bottom
    translate([0,0,-frontpcb])
        cylinder(r1=radiuspcbo,r2=radiuso*2,h=radiuso);
}

difference()
{
    gate();
    if(top||bottom)pcb();
    if(top)difference(){translate([0,0,-depth*2])cylinder(r=radiuso*3,h=depth*4);cut();}
    else if(bottom)cut();
 }
