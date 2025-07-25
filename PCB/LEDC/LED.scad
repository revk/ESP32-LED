// Generated case design for LEDC/LED.kicad_pcb
// By https://github.com/revk/PCBCase
// Generated 2025-07-19 13:16:50
// title:	PCB-LEDC
// rev:	1
// company:	Adrian Kennard, Andrews & Arnold Ltd
//

// Globals
margin=0.200000;
lip=2.000000;
casebottom=2.000000;
casetop=7.000000;
casewall=3.000000;
fit=0.000000;
edge=2.000000;
pcbthickness=1.200000;
nohull=false;
hullcap=1.000000;
hulledge=1.000000;
useredge=false;
spacing=62.000089;
pcbwidth=46.000089;
pcblength=16.000000;
originx=98.499955;
originy=100.000000;

module outline(h=pcbthickness,r=0){linear_extrude(height=h)offset(r=r)polygon(points=[[-22.999955,-5.022916],[-23.000045,5.090000],[-22.968100,5.355609],[-22.874079,5.606067],[-22.723348,5.827085],[-22.524505,6.006056],[-22.288894,6.132770],[-22.029955,6.200000],[-8.749955,8.000000],[21.000045,8.000000],[21.390225,7.961571],[21.765412,7.847759],[22.111185,7.662940],[22.414259,7.414214],[22.662984,7.111141],[22.847804,6.765367],[22.961615,6.390181],[23.000045,6.000000],[23.000045,-6.000000],[22.961615,-6.390181],[22.847804,-6.765367],[22.662984,-7.111141],[22.414259,-7.414214],[22.111185,-7.662940],[21.765412,-7.847759],[21.390225,-7.961571],[21.000045,-8.000000],[-8.749955,-8.000000],[-21.966381,-6.205556],[-22.242263,-6.133922],[-22.493290,-5.998914],[-22.705143,-5.808231],[-22.865738,-5.572751],[-22.965914,-5.305905]],paths=[[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33]]);}

module pcb(h=pcbthickness,r=0){linear_extrude(height=h)offset(r=r)polygon(points=[[-22.999955,-5.022916],[-23.000045,5.090000],[-22.968100,5.355609],[-22.874079,5.606067],[-22.723348,5.827085],[-22.524505,6.006056],[-22.288894,6.132770],[-22.029955,6.200000],[-8.749955,8.000000],[21.000045,8.000000],[21.390225,7.961571],[21.765412,7.847759],[22.111185,7.662940],[22.414259,7.414214],[22.662984,7.111141],[22.847804,6.765367],[22.961615,6.390181],[23.000045,6.000000],[23.000045,-6.000000],[22.961615,-6.390181],[22.847804,-6.765367],[22.662984,-7.111141],[22.414259,-7.414214],[22.111185,-7.662940],[21.765412,-7.847759],[21.390225,-7.961571],[21.000045,-8.000000],[-8.749955,-8.000000],[-21.966381,-6.205556],[-22.242263,-6.133922],[-22.493290,-5.998914],[-22.705143,-5.808231],[-22.865738,-5.572751],[-22.965914,-5.305905]],paths=[[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33]]);}
module part_L2(part=true,hole=false,block=false)
{
translate([10.900045,5.825000,1.200000])rotate([0,0,180.000000])scale([1.000000,1.000000,1.400000])rotate([0.000000,0.000000,-90.000000])m0(part,hole,block,casetop); // RevK:L_4x4_ TYA4020 (back)
};
module part_D2(part=true,hole=false,block=false)
{
translate([-8.599955,2.000000,1.200000])rotate([0,0,-90.000000])m1(part,hole,block,casetop); // D2 (back)
};
module part_R15(part=true,hole=false,block=false)
{
translate([12.700045,-0.675000,1.200000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
};
module part_R1(part=true,hole=false,block=false)
{
translate([-11.499955,-6.900000,1.200000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
};
module part_R3(part=true,hole=false,block=false)
{
translate([-13.099955,-6.700000,1.200000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
};
module part_C12(part=true,hole=false,block=false)
{
translate([10.900045,3.225000,1.200000])rotate([0,0,180.000000])m3(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
};
module part_C5(part=true,hole=false,block=false)
{
translate([13.600044,-2.000000,1.200000])rotate([0,0,180.000000])m4(part,hole,block,casetop); // RevK:C_0805 C_0805_2012Metric (back)
};
module part_C13(part=true,hole=false,block=false)
{
translate([17.200045,-5.700000,1.200000])rotate([0,0,-90.000000])m5(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module part_R13(part=true,hole=false,block=false)
{
translate([-8.599955,-2.000000,1.200000])rotate([0,0,90.000000])m2(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
};
module part_V1(part=true,hole=false,block=false)
{
};
module part_C8(part=true,hole=false,block=false)
{
translate([16.300044,-5.700000,1.200000])rotate([0,0,-90.000000])m5(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module part_R2(part=true,hole=false,block=false)
{
translate([-11.499955,6.900000,1.200000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
};
module part_C1(part=true,hole=false,block=false)
{
translate([16.300044,6.800000,1.200000])rotate([0,0,180.000000])m6(part,hole,block,casetop); // RevK:C_1206 C_1206_3216Metric (back)
};
module part_C4(part=true,hole=false,block=false)
{
translate([19.700045,5.300000,1.200000])rotate([0,0,180.000000])m5(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module part_R14(part=true,hole=false,block=false)
{
translate([9.100043,-0.675000,1.200000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
};
module part_C6(part=true,hole=false,block=false)
{
translate([-9.099955,-6.900000,1.200000])m4(part,hole,block,casetop); // RevK:C_0805 C_0805_2012Metric (back)
};
module part_J5(part=true,hole=false,block=false)
{
translate([17.110045,0.000000,1.200000])rotate([0,0,90.000000])translate([0.000000,-2.400000,0.000000])rotate([90.000000,-0.000000,-0.000000])m7(part,hole,block,casetop); // RevK:USB-C-Socket-H CSP-USC16-TR (back)
};
module part_R4(part=true,hole=false,block=false)
{
translate([10.900045,-0.675000,1.200000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
};
module part_D1(part=true,hole=false,block=false)
{
translate([21.200045,6.398959,1.200000])rotate([0,0,-135.000000])m8(part,hole,block,casetop); // D1 (back)
};
module part_C9(part=true,hole=false,block=false)
{
translate([-13.099955,6.700000,1.200000])rotate([0,0,180.000000])m5(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module part_V2(part=true,hole=false,block=false)
{
};
module part_PCB1(part=true,hole=false,block=false)
{
};
module part_U7(part=true,hole=false,block=false)
{
translate([10.900045,1.225000,1.200000])rotate([0,0,180.000000])m9(part,hole,block,casetop); // RevK:SOT-23-6-MD8942 SOT-23-6 (back)
};
module part_C3(part=true,hole=false,block=false)
{
translate([9.150045,-1.900000,1.200000])rotate([0,0,180.000000])m3(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
};
module part_R7(part=true,hole=false,block=false)
{
translate([14.300044,-6.900000,1.200000])rotate([0,0,90.000000])m2(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
};
module part_R5(part=true,hole=false,block=false)
{
translate([17.900045,5.300000,1.200000])m2(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
};
module part_U1(part=true,hole=false,block=false)
{
translate([20.300044,-6.100000,1.200000])m10(part,hole,block,casetop); // U1 (back)
};
module part_C10(part=true,hole=false,block=false)
{
translate([13.400045,2.525000,1.200000])rotate([0,0,-90.000000])m3(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
};
module part_C2(part=true,hole=false,block=false)
{
translate([11.300044,-1.900000,1.200000])m5(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module part_R6(part=true,hole=false,block=false)
{
translate([15.100044,5.300000,1.200000])m2(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
};
module part_C7(part=true,hole=false,block=false)
{
translate([-9.099955,6.900000,1.200000])m4(part,hole,block,casetop); // RevK:C_0805 C_0805_2012Metric (back)
};
module part_C14(part=true,hole=false,block=false)
{
translate([15.300044,-6.500000,1.200000])rotate([0,0,90.000000])m3(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
};
module part_C11(part=true,hole=false,block=false)
{
translate([8.400045,2.525000,1.200000])rotate([0,0,-90.000000])m3(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
};
module part_U2(part=true,hole=false,block=false)
{
translate([11.037544,-5.200000,1.200000])m11(part,hole,block,casetop); // RevK:IR-SMD-4P,3.35x3.9mm IR-3.35x3.9 (back)
};
module part_U6(part=true,hole=false,block=false)
{
translate([-0.049955,0.000000,1.200000])m12(part,hole,block,casetop); // U6 (back)
};
module part_J2(part=true,hole=false,block=false)
{
translate([-14.999955,0.000000,1.200000])m13(part,hole,block,casetop); // J2 (back)
};
// Parts to go on PCB (top)
module parts_top(part=false,hole=false,block=false){
part_L2(part,hole,block);
part_D2(part,hole,block);
part_R15(part,hole,block);
part_R1(part,hole,block);
part_R3(part,hole,block);
part_C12(part,hole,block);
part_C5(part,hole,block);
part_C13(part,hole,block);
part_R13(part,hole,block);
part_V1(part,hole,block);
part_C8(part,hole,block);
part_R2(part,hole,block);
part_C1(part,hole,block);
part_C4(part,hole,block);
part_R14(part,hole,block);
part_C6(part,hole,block);
part_J5(part,hole,block);
part_R4(part,hole,block);
part_D1(part,hole,block);
part_C9(part,hole,block);
part_V2(part,hole,block);
part_PCB1(part,hole,block);
part_U7(part,hole,block);
part_C3(part,hole,block);
part_R7(part,hole,block);
part_R5(part,hole,block);
part_U1(part,hole,block);
part_C10(part,hole,block);
part_C2(part,hole,block);
part_R6(part,hole,block);
part_C7(part,hole,block);
part_C14(part,hole,block);
part_C11(part,hole,block);
part_U2(part,hole,block);
part_U6(part,hole,block);
part_J2(part,hole,block);
}

parts_top=5;
module part_J1(part=true,hole=false,block=false)
{
};
module part_J3(part=true,hole=false,block=false)
{
};
// Parts to go on PCB (bottom)
module parts_bottom(part=false,hole=false,block=false){
part_J1(part,hole,block);
part_J3(part,hole,block);
}

parts_bottom=0;
module b(cx,cy,z,w,l,h){translate([cx-w/2,cy-l/2,z])cube([w,l,h]);}
module m0(part=false,hole=false,block=false,height)
{ // RevK:L_4x4_ TYA4020
// 4x4 Inductor
if(part)
{
	b(0,0,0,4,4,3);
}
}

module m1(part=false,hole=false,block=false,height)
{ // D2
// DFN1006-2L
if(part)
{
	b(0,0,0,1.0,0.6,0.45); // Chip
}
}

module m2(part=false,hole=false,block=false,height)
{ // RevK:R_0402_ R_0402_1005Metric
// 0402 Resistor
if(part)
{
	b(0,0,0,1.5,0.65,0.2); // Pad size
	b(0,0,0,1.0,0.5,0.5); // Chip
}
}

module m3(part=false,hole=false,block=false,height)
{ // RevK:C_0603_ C_0603_1608Metric
// 0603 Capacitor
if(part)
{
	b(0,0,0,1.6,0.8,1); // Chip
	b(0,0,0,1.6,0.95,0.2); // Pad size
}
}

module m4(part=false,hole=false,block=false,height)
{ // RevK:C_0805 C_0805_2012Metric
// 0805 Capacitor
if(part)
{
	b(0,0,0,2,1.2,1); // Chip
	b(0,0,0,2,1.45,0.2); // Pad size
}
}

module m5(part=false,hole=false,block=false,height)
{ // RevK:C_0402 C_0402_1005Metric
// 0402 Capacitor
if(part)
{
	b(0,0,0,1.0,0.5,1); // Chip
	b(0,0,0,1.5,0.65,0.2); // Pad size
}
}

module m6(part=false,hole=false,block=false,height)
{ // RevK:C_1206 C_1206_3216Metric
// 1206 Capacitor
if(part)
{
	b(0,0,0,3.2,1.6,1.5); // Part
	b(0,0,0,4.1,1.8,0.2); // Pads
}
}

module m7(part=false,hole=false,block=false,height)
{ // RevK:USB-C-Socket-H CSP-USC16-TR
// USB connector
rotate([-90,0,0])translate([-4.47,-3.84,0])
{
	if(part)
	{
		b(4.47,7,0,7,2,0.2);	// Pads
		translate([1.63,-0.2,1.63])
		rotate([-90,0,0])
		hull()
		{
			cylinder(d=3.26,h=7.55,$fn=24);
			translate([5.68,0,0])
			cylinder(d=3.26,h=7.55,$fn=24);
		}
		translate([0,6.2501,0])cube([8.94,1.1,1.6301]);
		translate([0,1.7,0])cube([8.94,1.6,1.6301]);
	}
	if(hole)
		translate([1.63,-20,1.63])
		rotate([-90,0,0])
	{
		// Plug
		hull()
		{
			cylinder(d=2.5,h=21,$fn=24);
			translate([5.68,0,0])
			cylinder(d=2.5,h=21,$fn=24);
		}
		hull()
		{
			cylinder(d=7,h=21,$fn=24);
			translate([5.68,0,0])
			cylinder(d=7,h=21,$fn=24);
		}
		translate([2.84,0,-100])
			cylinder(d=5,h=100,$fn=24);
	}
}
}

module m8(part=false,hole=false,block=false,height)
{ // D1
// 1x1mm LED
if(part)
{
        b(0,0,0,1.2,1.2,.8);
}
if(hole)
{
        hull()
        {
                b(0,0,.8,1.2,1.2,1);
                translate([0,0,height])cylinder(d=2,h=1,$fn=16);
        }
}
if(block)
{
        hull()
        {
                b(0,0,0,2.4,2.4,1);
                translate([0,0,height])cylinder(d=4,h=1,$fn=16);
        }
}
}

module m9(part=false,hole=false,block=false,height)
{ // RevK:SOT-23-6-MD8942 SOT-23-6
// SOT-23-6
if(part)
{
	b(0,0,0,1.726,3.026,1.2); // Part
	b(0,0,0,3.6,2.5,0.5); // Pins
}
}

module m10(part=false,hole=false,block=false,height)
{ // U1
if(part)
{
	b(0,0,0,3.5,2.65,0.23);
	b(0,0,0,3.2,2.35,0.98);
}
if(hole)
{
	translate([0.71,0,-pcbthickness-0.01])
		hull()
		{
			cylinder(d=1,h=pcbthickness+0.02);
			translate([0.75+casewall+1,0,0])cylinder(d=1,h=pcbthickness+0.02);
		}
}
}

module m11(part=false,hole=false,block=false,height)
{ // RevK:IR-SMD-4P,3.35x3.9mm IR-3.35x3.9
if(part)
{
	b(0,0,0,3.35,3.9,1.6);
	translate([0,0.45,1.6])sphere(r=1.4);
}
if(hole)
{
	translate([0,0.45,0])cylinder(d1=4,d2=6,h=height+1,$fn=6);
}
if(block)
{
	translate([0,0.45,0])cylinder(d1=6,d2=8,h=height+1,$fn=6);
}
}

module m12(part=false,hole=false,block=false,height)
{ // U6
// ESP32-S3-MINI-1
translate([-15.4/2,-15.45/2,0])
{
	if(part)
	{
		cube([15.4,20.5,0.8]);
		translate([0.7,0.5,0])cube([14,13.55,2.4]);
	}
	if(hole)
	{
		cube([15.4,20.5,0.8]);
	}
}
}

module m13(part=false,hole=false,block=false,height)
{ // J2
// WAGO-2060-45x-998-404
N=3;
if(part)
{
	translate([-0.9,0,0])hull()
	{
		b(0,0,0,12.7,N*4-0.1,1);
		translate([0.8,0,0])b(0,0,0,11.1,N*4-0.1,4.5);
	}
	for(p=[0:N-1])hull()
    {
        translate([-6,-4*(N-1)/2+p*4,2])sphere(d=3,$fn=12);
        translate([-11.510,0,2])sphere(d=4,$fn=12);
    }
}
if(hole)
{
    hull()
    {
        translate([-11.510,0,2])sphere(d=4,$fn=12);
        translate([-11.510,0,-height])sphere(d=4,$fn=12);
    }
    hull()
    {
        translate([-11.510,0,2])sphere(d=4,$fn=12);
        translate([-50,0,2])sphere(d=4,$fn=12);
    }
}
}

// Generate PCB casework

height=casebottom+pcbthickness+casetop;
$fn=48;

module pyramid()
{ // A pyramid
 polyhedron(points=[[0,0,0],[-height,-height,height],[-height,height,height],[height,height,height],[height,-height,height]],faces=[[0,1,2],[0,2,3],[0,3,4],[0,4,1],[4,3,2,1]]);
}


module pcb_hulled(h=pcbthickness,r=0)
{ // PCB shape for case
	if(useredge)outline(h,r);
	else hull()outline(h,r);
}

module solid_case(d=0)
{ // The case wall
	hull()
        {
                translate([0,0,-casebottom])pcb_hulled(height,casewall-edge);
                translate([0,0,edge-casebottom])pcb_hulled(height-edge*2,casewall);
        }
}

module preview()
{
	pcb();
	color("#0f0")parts_top(part=true);
	color("#0f0")parts_bottom(part=true);
	color("#f00")parts_top(hole=true);
	color("#f00")parts_bottom(hole=true);
	color("#00f8")parts_top(block=true);
	color("#00f8")parts_bottom(block=true);
}

module top_half(step=false)
{
	difference()
	{
		translate([-casebottom-100,-casewall-100,pcbthickness-lip/2+0.01]) cube([pcbwidth+casewall*2+200,pcblength+casewall*2+200,height]);
		if(step)translate([0,0,pcbthickness-lip/2-0.01])pcb_hulled(lip,casewall/2+fit);
	}
}

module bottom_half(step=false)
{
	translate([-casebottom-100,-casewall-100,pcbthickness+lip/2-height-0.01]) cube([pcbwidth+casewall*2+200,pcblength+casewall*2+200,height]);
	if(step)translate([0,0,pcbthickness-lip/2])pcb_hulled(lip,casewall/2-fit);
}

module case_wall()
{
	difference()
	{
		solid_case();
		translate([0,0,-height])pcb_hulled(height*2);
	}
}

module top_side_hole()
{
	difference()
	{
		intersection()
		{
			parts_top(hole=true);
			case_wall();
		}
		translate([0,0,-casebottom])pcb_hulled(height,casewall-edge);
	}
}

module bottom_side_hole()
{
	difference()
	{
		intersection()
		{
			parts_bottom(hole=true);
			case_wall();
		}
		translate([0,0,edge-casebottom])pcb_hulled(height-edge*2,casewall);
	}
}

module parts_space()
{
	minkowski()
	{
		union()
		{
			parts_top(part=true,hole=true);
			parts_bottom(part=true,hole=true);
		}
		sphere(r=margin,$fn=6);
	}
}

module top_cut()
{
	difference()
	{
		top_half(true);
		if(parts_top)difference()
		{
			minkowski()
			{ // Penetrating side holes
				top_side_hole();
				rotate([180,0,0])
				pyramid();
			}
			minkowski()
			{
				top_side_hole();
				rotate([0,0,45])cylinder(r=margin,h=height,$fn=4);
			}
		}
	}
	if(parts_bottom)difference()
	{
		minkowski()
		{ // Penetrating side holes
			bottom_side_hole();
			pyramid();
		}
			minkowski()
			{
				bottom_side_hole();
				rotate([0,0,45])translate([0,0,-height])cylinder(r=margin,h=height,$fn=4);
			}
	}
}

module bottom_cut()
{
	difference()
	{
		 translate([-casebottom-50,-casewall-50,-height]) cube([pcbwidth+casewall*2+100,pcblength+casewall*2+100,height*2]);
		 top_cut();
	}
}

module top_body()
{
	difference()
	{
		intersection()
		{
			solid_case();
			pcb_hulled(height);
			top_half();
		}
		if(parts_top)minkowski()
		{
			if(nohull)parts_top(part=true);
			else hull()parts_top(part=true);
			translate([0,0,margin-height])cylinder(r=margin,h=height,$fn=8);
		}
	}
	intersection()
	{
		solid_case();
		parts_top(block=true);
	}
}

module top_edge()
{
	intersection()
	{
		case_wall();
		top_cut();
	}
}

module top_pos()
{ // Position for plotting bottom
	translate([casewall,casewall,pcbthickness+casetop])rotate([180,0,0])children();
}

module pcb_pos()
{	// Position PCB relative to base 
		translate([0,0,pcbthickness-height])children();
}

module top()
{
	top_pos()difference()
	{
		union()
		{
			top_body();
			top_edge();
		}
		parts_space();
		pcb_pos()pcb(height,r=margin);
	}
}

module bottom_body()
{ // Position for plotting top
	difference()
	{
		intersection()
		{
			solid_case();
			translate([0,0,-height])pcb_hulled(height);
			bottom_half();
		}
		if(parts_bottom)minkowski()
		{
			if(nohull)parts_bottom(part=true);
			else hull()parts_bottom(part=true);
			translate([0,0,-margin])cylinder(r=margin,h=height,$fn=8);
		}
	}
	intersection()
	{
		solid_case();
		parts_bottom(block=true);
	}
}

module bottom_edge()
{
	intersection()
	{
		case_wall();
		bottom_cut();
	}
}

module bottom_pos()
{
	translate([casewall,casewall,casebottom])children();
}

module bottom()
{
	bottom_pos()difference()
	{
		union()
		{
        		bottom_body();
        		bottom_edge();
		}
		parts_space();
		pcb(height,r=margin);
	}
}
bottom(); translate([spacing,0,0])top();
