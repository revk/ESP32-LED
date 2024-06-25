// Generated case design for LED/LED.kicad_pcb
// By https://github.com/revk/PCBCase
// Generated 2024-06-25 09:23:34
// title:	PCB-LED
// rev:	1
// company:	Adrian Kennard, Andrews & Arnold Ltd
//

// Globals
margin=0.200000;
lip=2.000000;
casebottom=5.000000;
casetop=4.000000;
casewall=3.000000;
fit=0.000000;
edge=2.000000;
pcbthickness=1.000000;
nohull=false;
hullcap=1.000000;
hulledge=1.000000;
useredge=false;

module outline(h=pcbthickness,r=0){linear_extrude(height=h)offset(r=r)polygon(points=[[32.500000,0.000000],[0.000000,0.000000],[0.000000,16.000000],[32.500000,16.000000],[17.600000,0.650000],[17.600000,16.650000]],paths=[[0,1],[2,3,0],[4,5]]);}

module pcb(h=pcbthickness,r=0){linear_extrude(height=h)offset(r=r)polygon(points=[[32.500000,0.000000],[0.000000,0.000000],[0.000000,16.000000],[32.500000,16.000000],[17.600000,0.650000],[17.600000,16.650000]],paths=[[0,1],[2,3,0],[4,5]]);}
spacing=48.500000;
pcbwidth=32.500000;
pcblength=16.650000;
// Parts to go on PCB (top)
module parts_top(part=false,hole=false,block=false){
translate([21.250000,13.700000,1.000000])rotate([0,0,180.000000])rotate([-0.000000,-0.000000,-90.000000])m0(part,hole,block,casetop); // RevK:L_4x4_ TYA4020 (back)
translate([23.050000,7.200000,1.000000])rotate([0,0,180.000000])m1(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
translate([21.250000,11.100000,1.000000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
translate([27.950000,14.600000,1.000000])rotate([0,0,180.000000])m1(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
// Missing model (null).1 CP_EIA-3528-21_Kemet-B
translate([19.449999,7.200000,1.000000])rotate([0,0,180.000000])m1(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
translate([26.610000,8.000000,1.000000])rotate([0,0,90.000000])translate([0.000000,-2.400000,0.000000])rotate([90.000000,-0.000000,-0.000000])m3(part,hole,block,casetop); // RevK:USB-C-Socket-H CSP-USC16-TR (back)
translate([21.250000,7.200000,1.000000])rotate([0,0,180.000000])m1(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
translate([30.297638,1.600000,1.000000])rotate([0,0,-135.000000])m4(part,hole,block,casetop); // (null) (null) (back)
translate([28.000000,13.500000,1.000000])rotate([0,0,180.000000])m5(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
translate([21.250000,9.100000,1.000000])rotate([0,0,180.000000])m6(part,hole,block,casetop); // RevK:SOT-23-6-MD8942 SOT-23-6 (back)
translate([19.650000,6.100000,1.000000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
translate([26.000000,2.500000,1.000000])m1(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
translate([23.750000,10.400000,1.000000])rotate([0,0,-90.000000])m2(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
translate([21.896745,6.020564,1.000000])m5(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
translate([26.000000,13.500000,1.000000])rotate([0,0,180.000000])m1(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
translate([18.750000,10.400000,1.000000])rotate([0,0,-90.000000])m2(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
translate([10.450000,8.000000,1.000000])m7(part,hole,block,casetop); // (null) (null) (back)
// Missing model (null).1 MP011985
}

parts_top=2;
// Parts to go on PCB (bottom)
module parts_bottom(part=false,hole=false,block=false){
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
{ // RevK:R_0402_ R_0402_1005Metric
// 0402 Resistor
if(part)
{
	b(0,0,0,1.5,0.65,0.2); // Pad size
	b(0,0,0,1.0,0.5,0.5); // Chip
}
}

module m2(part=false,hole=false,block=false,height)
{ // RevK:C_0603_ C_0603_1608Metric
// 0603 Capacitor
if(part)
{
	b(0,0,0,1.6,0.8,1); // Chip
	b(0,0,0,1.6,0.95,0.2); // Pad size
}
}

module m3(part=false,hole=false,block=false,height)
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
		translate([0,6.25,0])cube([8.94,1.1,1.63]);
		translate([0,1.7,0])cube([8.94,1.6,1.63]);
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

module m4(part=false,hole=false,block=false,height)
{ // (null) (null)
// 1x1mm LED
if(part)
{
        b(0,0,0,1,1,.8);
}
if(hole)
{
        hull()
        {
                b(0,0,.8,1,1,1);
                translate([0,0,height])cylinder(d=2,h=1,$fn=16);
        }
}
if(block)
{
        hull()
        {
                b(0,0,0,2,2,1);
                translate([0,0,height])cylinder(d=4,h=1,$fn=16);
        }
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
{ // RevK:SOT-23-6-MD8942 SOT-23-6
// SOT-23-6
if(part)
{
	b(0,0,0,1.726,3.026,1.2); // Part
	b(0,0,0,3.6,2.5,0.5); // Pins
}
}

module m7(part=false,hole=false,block=false,height)
{ // (null) (null)
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
