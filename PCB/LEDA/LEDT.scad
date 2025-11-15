// Generated case design for LEDA/LED.kicad_pcb
// By https://github.com/revk/PCBCase
// Generated 2025-11-15 09:59:46
// title:	PCB-USBA
// rev:	1
// comment:	www.me.uk
// comment:	@TheRealRevK
//

// Globals
margin=0.200000;
lip=3.000000;
lipa=0;
lipt=2;
casewall=3.000000;
casebottom=7.000000;
casetop=7.000000;
bottomthickness=0.000000;
topthickness=0.000000;
fit=0.000000;
snap=0.150000;
edge=2.000000;
pcbthickness=1.200000;
function pcbthickness()=1.200000;
nohull=false;
hullcap=1.000000;
hulledge=1.000000;
useredge=true;
datex=-7.000000;
datey=0.000000;
datet=0.500000;
dateh=2.500000;
datea=30;
date="2025-11-15";
datef="OCRB";
logox=-7.000000;
logoy=0.000000;
logot=0.500000;
logoh=10.000000;
logoa=0;
logo="A";
logof="AJK";
spacing=49.125000;
pcbwidth=33.125000;
function pcbwidth()=33.125000;
pcblength=15.400000;
function pcblength()=15.400000;
originx=104.437500;
originy=100.000000;

module outline(h=pcbthickness,r=0){linear_extrude(height=h)offset(r=r)polygon(points=[[-16.562500,-7.700000],[-16.562500,7.700000],[2.034072,7.700000],[2.034072,-7.700000]],paths=[[0,1,2,3]]);}

module pcb(h=pcbthickness,r=0){linear_extrude(height=h)offset(r=r)polygon(points=[[-16.562500,7.700000],[2.034072,7.700000],[2.292892,7.665927],[2.534075,7.566029],[2.741179,7.407107],[2.741179,7.407134],[3.855393,6.292894],[4.562500,6.000001],[4.562500,6.000000],[16.562500,6.000000],[16.562500,-6.000000],[4.562500,-6.000000],[3.855393,-6.292893],[2.741179,-7.407107],[2.741179,-7.407108],[2.534072,-7.566025],[2.292892,-7.665923],[2.034074,-7.699996],[2.034072,-7.700000],[-16.562500,-7.700000]],paths=[[0,1,2,3,4],[5,6,7],[8,9,10,11,12,13],[14,15,16,17],[18,19,0]]);}
module J1(){translate([16.562500,0.000000,1.200000])rotate([0,0,90.000000])children();}
module part_J1(part=true,hole=false,block=false)
{
};
module C6(){translate([-0.337500,2.200000,1.200000])rotate([0,0,90.000000])children();}
module part_C6(part=true,hole=false,block=false)
{
translate([-0.337500,2.200000,1.200000])rotate([0,0,90.000000])m0(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
};
module U5(){translate([2.162500,3.500000,1.200000])children();}
module part_U5(part=true,hole=false,block=false)
{
translate([2.162500,3.500000,1.200000])m1(part,hole,block,casetop); // RevK:SOT-23-6-MD8942 SOT-23-6 (back)
};
module C8(){translate([2.162500,1.500000,1.200000])children();}
module part_C8(part=true,hole=false,block=false)
{
translate([2.162500,1.500000,1.200000])m0(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
};
module C3(){translate([5.062500,-2.200000,1.200000])rotate([0,0,90.000000])children();}
module part_C3(part=true,hole=false,block=false)
{
translate([5.062500,-2.200000,1.200000])rotate([0,0,90.000000])m2(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D1(){translate([4.562500,-4.900000,1.200000])rotate([0,0,90.000000])children();}
module part_D1(part=true,hole=false,block=false)
{
translate([4.562500,-4.900000,1.200000])rotate([0,0,90.000000])m3(part,hole,block,casetop); // D1
};
module R9(){translate([2.162500,5.400000,1.200000])children();}
module part_R9(part=true,hole=false,block=false)
{
translate([2.162500,5.400000,1.200000])m4(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
};
module R11(){translate([0.362500,5.400000,1.200000])children();}
module part_R11(part=true,hole=false,block=false)
{
translate([0.362500,5.400000,1.200000])m4(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
};
module U1(){translate([0.862500,-5.800000,1.200000])children();}
module part_U1(part=true,hole=false,block=false)
{
translate([0.862500,-5.800000,1.200000])m5(part,hole,block,casetop); // U1
};
module C1(){translate([2.062500,-3.500000,1.200000])rotate([0,0,180.000000])children();}
module part_C1(part=true,hole=false,block=false)
{
translate([2.062500,-3.500000,1.200000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C7(){translate([4.662500,2.200000,1.200000])rotate([0,0,-90.000000])children();}
module part_C7(part=true,hole=false,block=false)
{
translate([4.662500,2.200000,1.200000])rotate([0,0,-90.000000])m0(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
};
module PCB1(){translate([-4.437500,0.000000,1.200000])children();}
module part_PCB1(part=true,hole=false,block=false)
{
};
module L2(){translate([2.162500,-1.100000,1.200000])children();}
module part_L2(part=true,hole=false,block=false)
{
translate([2.162500,-1.100000,1.200000])scale([1.000000,1.000000,1.400000])rotate([0.000000,0.000000,-90.000000])m6(part,hole,block,casetop); // RevK:L_4x4_ TYA4020 (back)
};
module R1(){translate([3.932500,-3.524663,1.200000])children();}
module part_R1(part=true,hole=false,block=false)
{
translate([3.932500,-3.524663,1.200000])m4(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
};
module U2(){translate([-8.837500,0.000000,1.200000])rotate([0,0,90.000000])children();}
module part_U2(part=true,hole=false,block=false)
{
translate([-8.837500,0.000000,1.200000])rotate([0,0,90.000000])m7(part,hole,block,casetop); // U2
};
module R10(){translate([3.962500,5.400000,1.200000])children();}
module part_R10(part=true,hole=false,block=false)
{
translate([3.962500,5.400000,1.200000])m4(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
};
module C2(){translate([0.262500,-3.500000,1.200000])rotate([0,0,180.000000])children();}
module part_C2(part=true,hole=false,block=false)
{
translate([0.262500,-3.500000,1.200000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
// Parts to go on PCB (top)
module parts_top(part=false,hole=false,block=false){
part_J1(part,hole,block);
part_C6(part,hole,block);
part_U5(part,hole,block);
part_C8(part,hole,block);
part_C3(part,hole,block);
part_D1(part,hole,block);
part_R9(part,hole,block);
part_R11(part,hole,block);
part_U1(part,hole,block);
part_C1(part,hole,block);
part_C7(part,hole,block);
part_PCB1(part,hole,block);
part_L2(part,hole,block);
part_R1(part,hole,block);
part_U2(part,hole,block);
part_R10(part,hole,block);
part_C2(part,hole,block);
}

parts_top=3;
module D2(){translate([0.562500,1.925000,0.000000])rotate([0,0,-90.000000])rotate([180,0,0])children();}
module part_D2(part=true,hole=false,block=false)
{
translate([0.562500,1.925000,0.000000])rotate([0,0,-90.000000])rotate([180,0,0])m8(part,hole,block,casebottom); // D2 (back)
};
module V2(){translate([-4.437500,-7.700000,0.000000])rotate([180,0,0])children();}
module part_V2(part=true,hole=false,block=false)
{
};
module J2(){translate([-6.187500,0.000000,0.000000])rotate([180,0,0])children();}
module part_J2(part=true,hole=false,block=false)
{
translate([-6.187500,0.000000,0.000000])rotate([180,0,0])m9(part,hole,block,casebottom,453); // J2 (back)
};
module R2(){translate([-1.837500,6.600000,0.000000])rotate([0,0,180.000000])rotate([180,0,0])children();}
module part_R2(part=true,hole=false,block=false)
{
translate([-1.837500,6.600000,0.000000])rotate([0,0,180.000000])rotate([180,0,0])m4(part,hole,block,casebottom); // RevK:R_0402_ R_0402_1005Metric
};
module V1(){translate([-4.437500,7.700000,0.000000])rotate([0,0,180.000000])rotate([180,0,0])children();}
module part_V1(part=true,hole=false,block=false)
{
};
module R3(){translate([-3.637500,6.600000,0.000000])rotate([0,0,180.000000])rotate([180,0,0])children();}
module part_R3(part=true,hole=false,block=false)
{
translate([-3.637500,6.600000,0.000000])rotate([0,0,180.000000])rotate([180,0,0])m4(part,hole,block,casebottom); // RevK:R_0402_ R_0402_1005Metric
};
module J3(){translate([14.662500,-2.540000,0.000000])rotate([0,0,-90.000000])rotate([180,0,0])children();}
module part_J3(part=true,hole=false,block=false)
{
};
module C4(){translate([1.562500,6.700000,0.000000])rotate([0,0,180.000000])rotate([180,0,0])children();}
module part_C4(part=true,hole=false,block=false)
{
translate([1.562500,6.700000,0.000000])rotate([0,0,180.000000])rotate([180,0,0])m0(part,hole,block,casebottom); // RevK:C_0603_ C_0603_1608Metric
};
// Parts to go on PCB (bottom)
module parts_bottom(part=false,hole=false,block=false){
part_D2(part,hole,block);
part_V2(part,hole,block);
part_J2(part,hole,block);
part_R2(part,hole,block);
part_V1(part,hole,block);
part_R3(part,hole,block);
part_J3(part,hole,block);
part_C4(part,hole,block);
}

parts_bottom=2;
module b(cx,cy,z,w,l,h){translate([cx-w/2,cy-l/2,z])cube([w,l,h]);}
module m0(part=false,hole=false,block=false,height)
{ // RevK:C_0603_ C_0603_1608Metric
// 0603 Capacitor
if(part)
{
	b(0,0,0,1.6,0.8,1); // Chip
	b(0,0,0,1.6,0.95,0.2); // Pad size
}
}

module m1(part=false,hole=false,block=false,height)
{ // RevK:SOT-23-6-MD8942 SOT-23-6
// SOT-23-6
if(part)
{
	b(0,0,0,1.726,3.026,1.2); // Part
	b(0,0,0,3.6,2.5,0.5); // Pins
}
}

module m2(part=false,hole=false,block=false,height)
{ // RevK:C_0402 C_0402_1005Metric
// 0402 Capacitor
if(part)
{
	b(0,0,0,1.0,0.5,1); // Chip
	b(0,0,0,1.5,0.65,0.2); // Pad size
}
}

module m3(part=false,hole=false,block=false,height)
{ // D1
// 1.6x1.5mm LED
if(part)
{

        b(0,0,0,1.5,1.6,0.28);
        b(0,0,0,1.5,1,0.6);
}
if(hole)
{
        hull()
        {
                b(0,0,0.1,1.5,1.6,0.1);
                translate([0,0,height])cylinder(d=1.001,h=0.001,$fn=17);
        }
}
if(block)
{
        hull()
        {
                b(0,0,0.1,3.5,3.6,0.1);
                translate([0,0,height])cylinder(d=2,h=1,$fn=17);
        }
}
}

module m4(part=false,hole=false,block=false,height)
{ // RevK:R_0402_ R_0402_1005Metric
// 0402 Resistor
if(part)
{
	b(0,0,0,1.5,0.65,0.2); // Pad size
	b(0,0,0,1.0,0.5,0.5); // Chip
}
}

module m5(part=false,hole=false,block=false,height)
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

module m6(part=false,hole=false,block=false,height)
{ // RevK:L_4x4_ TYA4020
// 4x4 Inductor
if(part)
{
	b(0,0,0,4,4,3);
}
}

module m7(part=false,hole=false,block=false,height)
{ // U2
// ESP32-S3-MINI-1
translate([-15.4/2,-15.45/2,0])
{
	if(part)
	{
		cube([15.4,20.5,0.8]);
		translate([0.7,0.5,0])cube([14,13.55,2.4]);
		cube([15.4,20.5,0.8]);
	}
}
}

module m8(part=false,hole=false,block=false,height)
{ // D2
// DFN1006-2L
if(part)
{
	b(0,0,0,1.0,0.6,0.45); // Chip
}
}

module m9(part=false,hole=false,block=false,height,N=0)
{ // J2
// WAGO-2060-45x-998-404
n=N%10; // 45x
if(part)
{
	translate([-0.9,0,0])hull()
	{
		b(0,0,0,12.7,n*4-0.1,1);
		translate([0.8,0,0])b(0,0,0,11.1,n*4-0.1,4.5);
	}
	for(p=[0:n-1])hull()
    {
        translate([-6,-4*(n-1)/2+p*4,2])sphere(d=3,$fn=12);
        translate([-11.510,0,2])sphere(d=4,$fn=12);
    }
}
if(hole)
{
    hull()
    {
        translate([-11.510,0,2])sphere(d=5,$fn=12);
        translate([-50,0,2])sphere(d=5,$fn=12);
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

module top_half(fit=0)
{
	difference()
	{
		translate([-casebottom-100,-casewall-100,pcbthickness+0.01]) cube([pcbwidth+casewall*2+200,pcblength+casewall*2+200,height]);
		translate([0,0,pcbthickness])
        	{
			snape=lip/5;
			snaph=(lip-snape*2)/3;
			if(lipt==1)rotate(lipa)hull()
			{
				translate([0,-pcblength,lip/2])cube([0.001,pcblength*2,0.001]);
				translate([-lip/2,-pcblength,0])cube([lip,pcblength*2,0.001]);
			} else if(lipt==2)for(a=[0,90,180,270])rotate(a+lipa)hull()
			{
				translate([0,-pcblength-pcbwidth,lip/2])cube([0.001,pcblength*2+pcbwidth*2,0.001]);
				translate([-lip/2,-pcblength-pcbwidth,0])cube([lip,pcblength*2+pcbwidth*2,0.001]);
			}
            		difference()
            		{
                		pcb_hulled(lip,casewall);
				if(snap)
                        	{
					hull()
					{
						pcb_hulled(0.1,casewall/2-snap/2+fit);
						translate([0,0,snape])pcb_hulled(snaph,casewall/2+snap/2+fit);
						translate([0,0,lip-snape-snaph])pcb_hulled(0.1,casewall/2-snap/2+fit);
					}
					translate([0,0,lip-snape-snaph])pcb_hulled(snaph,casewall/2-snap/2+fit);
					hull()
					{
						translate([0,0,lip-snape])pcb_hulled(0.1,casewall/2-snap/2+fit);
						translate([0,0,lip])pcb_hulled(0.1,casewall/2+snap/2+fit);
					}
                        	}
				else pcb_hulled(lip,casewall/2+fit);
				if(lipt==0)translate([-pcbwidth,-pcblength,0])cube([pcbwidth*2,pcblength*2,lip]);
				else if(lipt==1) rotate(lipa)translate([0,-pcblength,0])hull()
				{
					translate([lip/2,0,0])cube([pcbwidth,pcblength*2,lip]);
					translate([-lip/2,0,lip])cube([pcbwidth,pcblength*2,lip]);
				}
				else if(lipt==2)for(a=[0,180])rotate(a+lipa)hull()
                		{
                            		translate([lip/2,lip/2,0])cube([pcbwidth+pcblength,pcbwidth+pcblength,lip]);
                            		translate([-lip/2,-lip/2,lip])cube([pcbwidth+pcblength,pcbwidth+pcblength,lip]);
                		}
            		}
            		difference()
            		{
				if(snap)
                        	{
					hull()
					{
						translate([0,0,-0.1])pcb_hulled(0.1,casewall/2+snap/2-fit);
						translate([0,0,snape-0.1])pcb_hulled(0.1,casewall/2-snap/2-fit);
					}
					translate([0,0,snape])pcb_hulled(snaph,casewall/2-snap/2-fit);
					hull()
					{
						translate([0,0,snape+snaph])pcb_hulled(0.1,casewall/2-snap/2-fit);
						translate([0,0,lip-snape-snaph])pcb_hulled(snaph,casewall/2+snap/2-fit);
						translate([0,0,lip-0.1])pcb_hulled(0.1,casewall/2-snap/2-fit);
					}
                        	}
				else pcb_hulled(lip,casewall/2-fit);
				if(lipt==1)rotate(lipa+180)translate([0,-pcblength,0])hull()
				{
					translate([lip/2,0,0])cube([pcbwidth,pcblength*2,lip+0.1]);
					translate([-lip/2,0,lip])cube([pcbwidth,pcblength*2,lip+0.1]);
				}
				else if(lipt==2)for(a=[90,270])rotate(a+lipa)hull()
                		{
                            		translate([lip/2,lip/2,0])cube([pcbwidth+pcblength,pcbwidth+pcblength,lip]);
                            		translate([-lip/2,-lip/2,lip])cube([pcbwidth+pcblength,pcbwidth+pcblength,lip]);
                		}
			}
            	}
		minkowski()
                {
                	union()
                	{
                		parts_top(part=true,hole=true);
                		parts_bottom(part=true,hole=true);
                	}
                	translate([-0.01,-0.01,-height])cube([0.02,0.02,height]);
                }
        }
	minkowski()
        {
        	union()
                {
                	parts_top(part=true,hole=true);
                	parts_bottom(part=true,hole=true);
                }
                translate([-0.01,-0.01,0])cube([0.02,0.02,height]);
        }
}

module case_wall()
{
	difference()
	{
		solid_case();
		translate([0,0,-height])pcb_hulled(height*2,0.02);
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
		translate([0,0,-casebottom])pcb_hulled(height,casewall);
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

module top_cut(fit=0)
{
	difference()
	{
		top_half(fit);
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
		 top_cut(-fit);
	}
}

module top_body()
{
	difference()
	{
		intersection()
		{
			solid_case();
			pcb_hulled(casetop+pcbthickness,0.03);
		}
		if(parts_top||topthickness)minkowski()
		{
			union()
			{
				if(nohull)parts_top(part=true);
				else hull(){parts_top(part=true);pcb_hulled();}
				if(topthickness)pcb_hulled(casetop+pcbthickness-topthickness,0);
			}
			translate([0,0,margin-height])cylinder(r=margin,h=height,$fn=8);
		}
	}
	intersection()
	{
		pcb_hulled(casetop+pcbthickness,0.03);
		union()
		{
			parts_top(block=true);
			parts_bottom(block=true);
		}
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
	translate([0,0,pcbthickness+casetop])rotate([180,0,0])children();
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
			translate([0,0,-casebottom])pcb_hulled(casebottom+pcbthickness,0.03);
		}
		if(parts_bottom||bottomthickness)minkowski()
		{
			union()
			{
				if(nohull)parts_bottom(part=true);
				else hull()parts_bottom(part=true);
				if(bottomthickness)translate([0,0,bottomthickness-casebottom])pcb_hulled(casebottom+pcbthickness-bottomthickness,0);
			}
			translate([0,0,-margin])cylinder(r=margin,h=height,$fn=8);
		}
	}
	intersection()
	{
		translate([0,0,-casebottom])pcb_hulled(casebottom+pcbthickness,0.03);
		union()
		{
			parts_top(block=true);
			parts_bottom(block=true);
		}
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
	translate([0,0,casebottom])children();
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

module datecode()
{
	minkowski()
	{
		translate([datex,datey,-1])rotate(datea)scale([-1,1])linear_extrude(1)text(date,size=dateh,halign="center",valign="center",font=datef);
		cylinder(d1=datet,d2=0,h=datet,$fn=6);
	}
}

module logocode()
{
	minkowski()
	{
		translate([logox,logoy,-1])rotate(logoa)scale([-1,1])linear_extrude(1)text(logo,size=logoh,halign="center",valign="center",font=logof);
		cylinder(d1=logot,d2=0,h=logot,$fn=6);
	}
}
difference(){top();logocode();}