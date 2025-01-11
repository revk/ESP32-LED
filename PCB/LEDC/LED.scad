// Generated case design for LEDC/LED.kicad_pcb
// By https://github.com/revk/PCBCase
// Generated 2025-01-11 12:20:13
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

module outline(h=pcbthickness,r=0){linear_extrude(height=h)offset(r=r)polygon(points=[[0.000089,2.977084],[0.000000,13.090000],[0.031948,13.355609],[0.125969,13.606066],[0.276699,13.827084],[0.475541,14.006056],[0.711151,14.132771],[0.970089,14.200000],[14.250089,16.000000],[43.000089,16.000000],[43.390270,15.961571],[43.765456,15.847759],[44.111230,15.662940],[44.414303,15.414214],[44.663029,15.111141],[44.847848,14.765367],[44.961660,14.390181],[45.000089,14.000000],[45.000089,2.000000],[44.961660,1.609819],[44.847848,1.234633],[44.663029,0.888859],[44.414303,0.585786],[44.111230,0.337060],[43.765456,0.152241],[43.390270,0.038429],[43.000089,0.000000],[14.250089,0.000000],[1.033663,1.794444],[0.757780,1.866072],[0.506751,2.001080],[0.294897,2.191764],[0.134303,2.427246],[0.034130,2.694093]],paths=[[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33]]);}

module pcb(h=pcbthickness,r=0){linear_extrude(height=h)offset(r=r)polygon(points=[[0.000089,2.977084],[0.000000,13.090000],[0.031948,13.355609],[0.125969,13.606066],[0.276699,13.827084],[0.475541,14.006056],[0.711151,14.132771],[0.970089,14.200000],[14.250089,16.000000],[43.000089,16.000000],[43.390270,15.961571],[43.765456,15.847759],[44.111230,15.662940],[44.414303,15.414214],[44.663029,15.111141],[44.847848,14.765367],[44.961660,14.390181],[45.000089,14.000000],[45.000089,2.000000],[44.961660,1.609819],[44.847848,1.234633],[44.663029,0.888859],[44.414303,0.585786],[44.111230,0.337060],[43.765456,0.152241],[43.390270,0.038429],[43.000089,0.000000],[14.250089,0.000000],[1.033663,1.794444],[0.757780,1.866072],[0.506751,2.001080],[0.294897,2.191764],[0.134303,2.427246],[0.034130,2.694093]],paths=[[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33]]);}
spacing=61.000089;
pcbwidth=45.000089;
pcblength=16.000000;
// Parts to go on PCB (top)
module parts_top(part=false,hole=false,block=false){
translate([32.900089,13.825000,1.200000])rotate([0,0,180.000000])rotate([-0.000000,-0.000000,-90.000000])m0(part,hole,block,casetop); // RevK:L_4x4_ TYA4020 (back)
translate([13.300089,10.000000,1.200000])rotate([0,0,-90.000000])m1(part,hole,block,casetop); // D2 (back)
translate([34.700089,7.325000,1.200000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
translate([10.900089,1.100000,1.200000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
translate([9.100089,1.300000,1.200000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
translate([32.900089,11.225000,1.200000])rotate([0,0,180.000000])m3(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
translate([35.696308,6.032242,1.200000])m3(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
translate([37.300089,1.600000,1.200000])rotate([0,0,90.000000])m4(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
translate([38.200089,2.000000,1.200000])rotate([0,0,90.000000])m4(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
translate([10.900089,14.900000,1.200000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
translate([32.740089,3.100000,1.200000])rotate([0,0,90.000000])m5(part,hole,block,casetop); // C1 (back)
translate([41.000089,14.500000,1.200000])rotate([0,0,90.000000])m4(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
translate([31.100088,7.325000,1.200000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
translate([13.000089,1.000000,1.200000])m3(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
translate([39.110089,8.000000,1.200000])rotate([0,0,90.000000])translate([0.000000,-2.400000,0.000000])rotate([90.000000,-0.000000,-0.000000])m6(part,hole,block,casetop); // RevK:USB-C-Socket-H CSP-USC16-TR (back)
translate([32.900089,7.325000,1.200000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
translate([43.200089,14.398959,1.200000])rotate([0,0,-135.000000])m7(part,hole,block,casetop); // D1 (back)
translate([9.100089,14.700000,1.200000])rotate([0,0,180.000000])m4(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
translate([32.900089,9.225000,1.200000])rotate([0,0,180.000000])m8(part,hole,block,casetop); // RevK:SOT-23-6-MD8942 SOT-23-6 (back)
translate([31.150089,6.100000,1.200000])rotate([0,0,180.000000])m3(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
translate([40.000089,14.500000,1.200000])rotate([0,0,90.000000])m2(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
translate([41.500089,1.700000,1.200000])m9(part,hole,block,casetop); // U1 (back)
translate([35.400089,10.525000,1.200000])rotate([0,0,-90.000000])m3(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
translate([33.396834,6.020564,1.200000])m4(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
translate([39.100089,14.500000,1.200000])rotate([0,0,-90.000000])m2(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
translate([13.000089,15.000000,1.200000])m3(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
translate([30.400089,10.525000,1.200000])rotate([0,0,-90.000000])m3(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
translate([36.600089,10.500000,1.200000])rotate([0,0,90.000000])m3(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
translate([21.950089,8.000000,1.200000])m10(part,hole,block,casetop); // U6 (back)
translate([7.000089,8.000000,1.200000])m11(part,hole,block,casetop); // J2 (back)
}

parts_top=6;
// Parts to go on PCB (bottom)
module parts_bottom(part=false,hole=false,block=false){
// Missing model SW1.1 SW_PUSH_6mm_H4.3mm (back)
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
{ // RevK:C_0402 C_0402_1005Metric
// 0402 Capacitor
if(part)
{
	b(0,0,0,1.0,0.5,1); // Chip
	b(0,0,0,1.5,0.65,0.2); // Pad size
}
}

module m5(part=false,hole=false,block=false,height)
{ // C1
if(part)
{
	b(0,0,0,3.5,2.8,1.9);
}
}

module m6(part=false,hole=false,block=false,height)
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
	{
		// Plug
		translate([1.63,-20,1.63])
		rotate([-90,0,0])
		hull()
		{
			cylinder(d=2.5,h=21,$fn=24);
			translate([5.68,0,0])
			cylinder(d=2.5,h=21,$fn=24);
		}
		translate([1.63,-22.5,1.63])
		rotate([-90,0,0])
		hull()
		{
			cylinder(d=7,h=21,$fn=24);
			translate([5.68,0,0])
			cylinder(d=7,h=21,$fn=24);
		}
	}
}
}

module m7(part=false,hole=false,block=false,height)
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

module m8(part=false,hole=false,block=false,height)
{ // RevK:SOT-23-6-MD8942 SOT-23-6
// SOT-23-6
if(part)
{
	b(0,0,0,1.726,3.026,1.2); // Part
	b(0,0,0,3.6,2.5,0.5); // Pins
}
}

module m9(part=false,hole=false,block=false,height)
{ // U1
if(part)
{
	b(0,0,0,3.5,2.65,0.23);
	b(0,0,0,3.2,2.35,0.98);
}
if(hole)
{
	h=(casetop>casebottom?casetop:casebottom)+pcbthickness+1;
	translate([0.71,0,-h])cylinder(d=1,h=h+0.01);
}
}

module m10(part=false,hole=false,block=false,height)
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

module m11(part=false,hole=false,block=false,height)
{ // J2
// WAGO-2060-453-998-404
N=3;
if(part)
{
	translate([-0.9,0,0])hull()
	{
		b(0,0,0,12.7,N*4-0.1,1);
		translate([0.8,0,0])b(0,0,0,11.1,N*4-0.1,4.5);
	}
}
if(hole)
	for(p=[0:N-1])translate([0,-4*(N-1)/2+p*4,2])rotate([90,0,-90])cylinder(d=3,h=20);
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
	intersection()
	{
		parts_top(hole=true);
		case_wall();
	}
}

module bottom_side_hole()
{
	intersection()
	{
		parts_bottom(hole=true);
		case_wall();
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

module top()
{
	translate([casewall,casewall+pcblength,pcbthickness+casetop])rotate([180,0,0])difference()
	{
		union()
		{
			top_body();
			top_edge();
		}
		parts_space();
		translate([0,0,pcbthickness-height])pcb(height,r=margin);
	}
}

module bottom_body()
{
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

module bottom()
{
	translate([casewall,casewall,casebottom])difference()
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
