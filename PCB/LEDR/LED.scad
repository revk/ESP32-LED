// Generated case design for LEDR/LED.kicad_pcb
// By https://github.com/revk/PCBCase
// Generated 2025-01-11 12:21:00
// title:	PCB-LED
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

module outline(h=pcbthickness,r=0){linear_extrude(height=h)offset(r=r)polygon(points=[[0.500000,25.500000],[13.450001,25.500000],[13.708820,25.465925],[13.950000,25.366025],[14.157107,25.207106],[14.316026,24.999999],[14.415926,24.758819],[14.450001,24.500000],[14.450000,21.500000],[14.526121,21.117316],[14.742893,20.792892],[15.067316,20.576119],[15.450000,20.500000],[30.450000,20.500000],[30.832684,20.576120],[31.157107,20.792893],[31.373880,21.117316],[31.450000,21.500000],[31.450000,24.500000],[31.484074,24.758819],[31.583974,25.000000],[31.742893,25.207107],[31.950000,25.366026],[32.191181,25.465926],[32.450000,25.500000],[45.450000,25.500000],[45.641341,25.461938],[45.803553,25.353552],[45.911940,25.191341],[45.950000,25.000000],[45.950000,0.500000],[45.911939,0.308658],[45.803553,0.146447],[45.641342,0.038061],[45.450000,0.000000],[0.500000,0.000000],[0.308658,0.038061],[0.146447,0.146447],[0.038061,0.308658],[0.000000,0.500000],[0.000000,25.000000],[0.038061,25.191342],[0.146447,25.353553],[0.308658,25.461939]],paths=[[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43]]);}

module pcb(h=pcbthickness,r=0){linear_extrude(height=h)offset(r=r)polygon(points=[[0.500000,25.500000],[13.450001,25.500000],[13.708820,25.465925],[13.950000,25.366025],[14.157107,25.207106],[14.316026,24.999999],[14.415926,24.758819],[14.450001,24.500000],[14.450000,21.500000],[14.526121,21.117316],[14.742893,20.792892],[15.067316,20.576119],[15.450000,20.500000],[30.450000,20.500000],[30.832684,20.576120],[31.157107,20.792893],[31.373880,21.117316],[31.450000,21.500000],[31.450000,24.500000],[31.484074,24.758819],[31.583974,25.000000],[31.742893,25.207107],[31.950000,25.366026],[32.191181,25.465926],[32.450000,25.500000],[45.450000,25.500000],[45.641341,25.461938],[45.803553,25.353552],[45.911940,25.191341],[45.950000,25.000000],[45.950000,0.500000],[45.911939,0.308658],[45.803553,0.146447],[45.641342,0.038061],[45.450000,0.000000],[0.500000,0.000000],[0.308658,0.038061],[0.146447,0.146447],[0.038061,0.308658],[0.000000,0.500000],[0.000000,25.000000],[0.038061,25.191342],[0.146447,25.353553],[0.308658,25.461939]],paths=[[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43]]);}
spacing=61.950000;
pcbwidth=45.950000;
pcblength=25.500000;
// Parts to go on PCB (top)
module parts_top(part=false,hole=false,block=false){
translate([33.900000,8.915000,1.200000])rotate([-0.000000,-0.000000,-90.000000])m0(part,hole,block,casetop); // RevK:L_4x4_ TYA4020 (back)
translate([4.000000,10.750000,1.200000])rotate([0,0,90.000000])m1(part,hole,block,casetop); // U3 (back)
translate([9.450000,12.300000,1.200000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // D2 (back)
translate([18.450000,3.750000,1.200000])m3(part,hole,block,casetop); // RevK:R_0402 R_0402_1005Metric (back)
translate([32.100000,15.415000,1.200000])m3(part,hole,block,casetop); // RevK:R_0402 R_0402_1005Metric (back)
translate([33.900000,11.515000,1.200000])m4(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
translate([36.700000,6.000000,1.200000])rotate([0,0,180.000000])m4(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
translate([38.150000,21.000000,1.200000])rotate([0,0,180.000000])m5(part,hole,block,casetop); // J4 (back)
translate([29.750000,3.500000,1.200000])rotate([0,0,-90.000000])m6(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
// Missing model U2.1 WLP-1.437-1.347
translate([12.950000,12.300000,1.200000])rotate([0,0,180.000000])m3(part,hole,block,casetop); // RevK:R_0402 R_0402_1005Metric (back)
translate([40.612500,1.737500,1.200000])rotate([0,0,180.000000])m7(part,hole,block,casetop); // C1 (back)
translate([35.700001,15.415000,1.200000])m3(part,hole,block,casetop); // RevK:R_0402 R_0402_1005Metric (back)
// Missing model U5.1 SMD-4P-4x5
translate([40.110000,8.000000,1.200000])rotate([0,0,90.000000])translate([0.000000,-2.400000,0.000000])rotate([90.000000,-0.000000,-0.000000])m8(part,hole,block,casetop); // RevK:USB-C-Socket-H CSP-USC16-TR (back)
translate([33.900000,15.415000,1.200000])m3(part,hole,block,casetop); // RevK:R_0402 R_0402_1005Metric (back)
translate([9.950000,9.700000,1.200000])rotate([0,0,45.000000])m9(part,hole,block,casetop); // D1 (back)
translate([31.150000,2.900000,1.200000])m3(part,hole,block,casetop); // RevK:R_0402 R_0402_1005Metric (back)
translate([41.050000,14.250000,1.200000])rotate([0,0,-90.000000])m6(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
translate([11.150000,12.300000,1.200000])rotate([0,0,180.000000])m6(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
translate([16.700000,3.750000,1.200000])m3(part,hole,block,casetop); // RevK:R_0402 R_0402_1005Metric (back)
translate([33.900000,13.515000,1.200000])m10(part,hole,block,casetop); // RevK:SOT-23-6-MD8942 SOT-23-6 (back)
translate([32.150000,6.100000,1.200000])rotate([0,0,180.000000])m4(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
translate([43.750000,2.100000,1.200000])rotate([0,0,90.000000])m3(part,hole,block,casetop); // RevK:R_0402 R_0402_1005Metric (back)
// Missing model U8.1 VEML3235SL
translate([43.665000,14.250000,1.200000])m11(part,hole,block,casetop); // U1 (back)
translate([39.650000,14.250000,1.200000])rotate([0,0,-90.000000])m6(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
translate([31.400000,12.215000,1.200000])rotate([0,0,90.000000])m4(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
translate([34.396745,6.020564,1.200000])m6(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
translate([44.650000,2.100000,1.200000])rotate([0,0,-90.000000])m3(part,hole,block,casetop); // RevK:R_0402 R_0402_1005Metric (back)
translate([14.300000,11.800000,1.200000])rotate([0,0,-90.000000])m6(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
translate([42.750000,16.000000,1.200000])m3(part,hole,block,casetop); // RevK:R_0402 R_0402_1005Metric (back)
translate([32.950000,16.400000,1.200000])rotate([0,0,180.000000])m6(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
translate([36.400000,12.215000,1.200000])rotate([0,0,90.000000])m4(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
translate([7.250000,10.550000,1.200000])m3(part,hole,block,casetop); // RevK:R_0402 R_0402_1005Metric (back)
translate([8.650000,11.400000,1.200000])m2(part,hole,block,casetop); // D2 (back)
translate([8.000000,4.500000,1.200000])m5(part,hole,block,casetop); // J4 (back)
translate([22.950000,12.500000,1.200000])m12(part,hole,block,casetop); // U6 (back)
translate([8.000000,19.000000,1.200000])m13(part,hole,block,casetop); // J2 (back)
}

parts_top=10;
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
{ // U3
// SO-4_4.4x4.3mm_P2.54mm 
if(part)
{
	b(0,0,0,4.5,4.6,2.2); // Part
	b(0,0,0,3.34,6.8,1.5); // Pins
}
}

module m2(part=false,hole=false,block=false,height)
{ // D2
// DFN1006-2L
if(part)
{
	b(0,0,0,1.0,0.6,0.45); // Chip
}
}

module m3(part=false,hole=false,block=false,height)
{ // RevK:R_0402 R_0402_1005Metric
// 0402 Resistor
if(part)
{
	b(0,0,0,1.5,0.65,0.2); // Pad size
	b(0,0,0,1.0,0.5,0.5); // Chip
}
}

module m4(part=false,hole=false,block=false,height)
{ // RevK:C_0603_ C_0603_1608Metric
// 0603 Capacitor
if(part)
{
	b(0,0,0,1.6,0.8,1); // Chip
	b(0,0,0,1.6,0.95,0.2); // Pad size
}
}

module m5(part=false,hole=false,block=false,height)
{ // J4
// WAGO-2060-452-998-404
N=2;
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

module m6(part=false,hole=false,block=false,height)
{ // RevK:C_0402 C_0402_1005Metric
// 0402 Capacitor
if(part)
{
	b(0,0,0,1.0,0.5,1); // Chip
	b(0,0,0,1.5,0.65,0.2); // Pad size
}
}

module m7(part=false,hole=false,block=false,height)
{ // C1
if(part)
{
	b(0,0,0,3.5,2.8,1.9);
}
}

module m8(part=false,hole=false,block=false,height)
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

module m9(part=false,hole=false,block=false,height)
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

module m10(part=false,hole=false,block=false,height)
{ // RevK:SOT-23-6-MD8942 SOT-23-6
// SOT-23-6
if(part)
{
	b(0,0,0,1.726,3.026,1.2); // Part
	b(0,0,0,3.6,2.5,0.5); // Pins
}
}

module m11(part=false,hole=false,block=false,height)
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
