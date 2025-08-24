// Generated case design for LEDR/LED.kicad_pcb
// By https://github.com/revk/PCBCase
// Generated 2025-08-24 14:05:45
// title:	PCB-LEDR
// rev:	1
// company:	Adrian Kennard, Andrews & Arnold Ltd
//

// Globals
margin=0.250000;
lip=3.000000;
lipa=0;
lipt=2;
casebottom=2.000000;
casetop=7.000000;
casewall=3.000000;
fit=0.000000;
snap=0.150000;
edge=2.000000;
pcbthickness=1.200000;
nohull=false;
hullcap=1.000000;
hulledge=1.000000;
useredge=false;
spacing=61.950000;
pcbwidth=45.950000;
pcblength=25.500000;
originx=100.025000;
originy=95.250000;

module outline(h=pcbthickness,r=0){linear_extrude(height=h)offset(r=r)polygon(points=[[-22.475000,12.750000],[-9.524999,12.750000],[-9.266180,12.715925],[-9.025000,12.616025],[-8.817893,12.457106],[-8.658974,12.249999],[-8.559074,12.008819],[-8.524999,11.750000],[-8.525000,8.750000],[-8.448879,8.367316],[-8.232107,8.042892],[-7.907684,7.826119],[-7.525000,7.750000],[7.475000,7.750000],[7.857684,7.826120],[8.182107,8.042893],[8.398880,8.367316],[8.475000,8.750000],[8.475000,11.750000],[8.509074,12.008819],[8.608974,12.250000],[8.767893,12.457107],[8.975000,12.616026],[9.216181,12.715926],[9.475000,12.750000],[22.475000,12.750000],[22.666341,12.711938],[22.828553,12.603552],[22.936940,12.441341],[22.975000,12.250000],[22.975000,-12.250000],[22.936939,-12.441342],[22.828553,-12.603553],[22.666342,-12.711939],[22.475000,-12.750000],[-22.475000,-12.750000],[-22.666342,-12.711939],[-22.828553,-12.603553],[-22.936939,-12.441342],[-22.975000,-12.250000],[-22.975000,12.250000],[-22.936939,12.441342],[-22.828553,12.603553],[-22.666342,12.711939]],paths=[[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43]]);}

module pcb(h=pcbthickness,r=0){linear_extrude(height=h)offset(r=r)polygon(points=[[-22.475000,12.750000],[-9.524999,12.750000],[-9.266180,12.715925],[-9.025000,12.616025],[-8.817893,12.457106],[-8.658974,12.249999],[-8.559074,12.008819],[-8.524999,11.750000],[-8.525000,8.750000],[-8.448879,8.367316],[-8.232107,8.042892],[-7.907684,7.826119],[-7.525000,7.750000],[7.475000,7.750000],[7.857684,7.826120],[8.182107,8.042893],[8.398880,8.367316],[8.475000,8.750000],[8.475000,11.750000],[8.509074,12.008819],[8.608974,12.250000],[8.767893,12.457107],[8.975000,12.616026],[9.216181,12.715926],[9.475000,12.750000],[22.475000,12.750000],[22.666341,12.711938],[22.828553,12.603552],[22.936940,12.441341],[22.975000,12.250000],[22.975000,-12.250000],[22.936939,-12.441342],[22.828553,-12.603553],[22.666342,-12.711939],[22.475000,-12.750000],[-22.475000,-12.750000],[-22.666342,-12.711939],[-22.828553,-12.603553],[-22.936939,-12.441342],[-22.975000,-12.250000],[-22.975000,12.250000],[-22.936939,12.441342],[-22.828553,12.603553],[-22.666342,12.711939]],paths=[[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43]]);}
module part_L2(part=true,hole=false,block=false)
{
translate([10.925000,-3.835000,1.200000])rotate([-0.000000,-0.000000,-90.000000])m0(part,hole,block,casetop); // RevK:L_4x4_ TYA4020 (back)
};
module part_U3(part=true,hole=false,block=false)
{
translate([-18.975000,-2.000000,1.200000])rotate([0,0,90.000000])m1(part,hole,block,casetop); // U3 (back)
};
module part_D2(part=true,hole=false,block=false)
{
translate([-13.525000,-0.450000,1.200000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // D2 (back)
};
module part_R3(part=true,hole=false,block=false)
{
translate([-4.525000,-9.000000,1.200000])m3(part,hole,block,casetop); // RevK:R_0402 R_0402_1005Metric (back)
};
module part_R15(part=true,hole=false,block=false)
{
translate([9.125000,2.665000,1.200000])m3(part,hole,block,casetop); // RevK:R_0402 R_0402_1005Metric (back)
};
module part_C12(part=true,hole=false,block=false)
{
translate([10.925000,-1.235000,1.200000])m4(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
};
module part_C5(part=true,hole=false,block=false)
{
translate([13.725000,-6.750000,1.200000])rotate([0,0,180.000000])m4(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
};
module part_C4(part=true,hole=false,block=false)
{
translate([6.775000,-9.250000,1.200000])rotate([0,0,-90.000000])m5(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module part_V1(part=true,hole=false,block=false)
{
};
module part_R2(part=true,hole=false,block=false)
{
translate([-10.025000,-0.450000,1.200000])rotate([0,0,180.000000])m3(part,hole,block,casetop); // RevK:R_0402 R_0402_1005Metric (back)
};
module part_C1(part=true,hole=false,block=false)
{
translate([17.637500,-11.012500,1.200000])rotate([0,0,180.000000])m6(part,hole,block,casetop); // C1 (back)
};
module part_R14(part=true,hole=false,block=false)
{
translate([12.725001,2.665000,1.200000])m3(part,hole,block,casetop); // RevK:R_0402 R_0402_1005Metric (back)
};
module part_U5(part=true,hole=false,block=false)
{
translate([11.275000,-9.850000,1.200000])rotate([0,0,180.000000])m7(part,hole,block,casetop); // U5 (back)
};
module part_J5(part=true,hole=false,block=false)
{
translate([17.135000,-4.750000,1.200000])rotate([0,0,90.000000])translate([0.000000,-2.400000,0.000000])rotate([90.000000,-0.000000,-0.000000])m8(part,hole,block,casetop); // RevK:USB-C-Socket-H CSP-USC16-TR (back)
};
module part_R4(part=true,hole=false,block=false)
{
translate([10.925000,2.665000,1.200000])m3(part,hole,block,casetop); // RevK:R_0402 R_0402_1005Metric (back)
};
module part_D1(part=true,hole=false,block=false)
{
translate([-13.025000,-3.050000,1.200000])rotate([0,0,45.000000])m9(part,hole,block,casetop); // D1 (back)
};
module part_R9(part=true,hole=false,block=false)
{
translate([8.175000,-9.850000,1.200000])m3(part,hole,block,casetop); // RevK:R_0402 R_0402_1005Metric (back)
};
module part_C9(part=true,hole=false,block=false)
{
translate([-11.825000,-0.450000,1.200000])rotate([0,0,180.000000])m5(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module part_V2(part=true,hole=false,block=false)
{
};
module part_R1(part=true,hole=false,block=false)
{
translate([-6.275000,-9.000000,1.200000])m3(part,hole,block,casetop); // RevK:R_0402 R_0402_1005Metric (back)
};
module part_PCB1(part=true,hole=false,block=false)
{
};
module part_U7(part=true,hole=false,block=false)
{
translate([10.925000,0.765000,1.200000])m10(part,hole,block,casetop); // RevK:SOT-23-6-MD8942 SOT-23-6 (back)
};
module part_C3(part=true,hole=false,block=false)
{
translate([9.175000,-6.650000,1.200000])rotate([0,0,180.000000])m4(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
};
module part_R5(part=true,hole=false,block=false)
{
translate([20.775000,-10.650000,1.200000])rotate([0,0,90.000000])m3(part,hole,block,casetop); // RevK:R_0402 R_0402_1005Metric (back)
};
module part_U1(part=true,hole=false,block=false)
{
translate([20.690000,1.500000,1.200000])m11(part,hole,block,casetop); // U1 (back)
};
module part_C10(part=true,hole=false,block=false)
{
translate([8.425000,-0.535000,1.200000])rotate([0,0,90.000000])m4(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
};
module part_C2(part=true,hole=false,block=false)
{
translate([11.421745,-6.729436,1.200000])m5(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module part_R6(part=true,hole=false,block=false)
{
translate([21.675000,-10.650000,1.200000])rotate([0,0,-90.000000])m3(part,hole,block,casetop); // RevK:R_0402 R_0402_1005Metric (back)
};
module part_C7(part=true,hole=false,block=false)
{
translate([-8.675000,-0.950000,1.200000])rotate([0,0,-90.000000])m5(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module part_C8(part=true,hole=false,block=false)
{
translate([9.975000,3.650000,1.200000])rotate([0,0,180.000000])m5(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module part_C11(part=true,hole=false,block=false)
{
translate([13.425000,-0.535000,1.200000])rotate([0,0,90.000000])m4(part,hole,block,casetop); // RevK:C_0603_ C_0603_1608Metric (back)
};
module part_R7(part=true,hole=false,block=false)
{
translate([-15.725000,-2.200000,1.200000])m3(part,hole,block,casetop); // RevK:R_0402 R_0402_1005Metric (back)
};
module part_D3(part=true,hole=false,block=false)
{
translate([-14.325000,-1.350000,1.200000])m2(part,hole,block,casetop); // D2 (back)
};
module part_J6(part=true,hole=false,block=false)
{
translate([-14.975000,-8.250000,1.200000])m12(part,hole,block,casetop,452); // J6 (back)
};
module part_U6(part=true,hole=false,block=false)
{
translate([-0.025000,-0.250000,1.200000])m13(part,hole,block,casetop); // U6 (back)
};
module part_J2(part=true,hole=false,block=false)
{
translate([-14.975000,6.250000,1.200000])m12(part,hole,block,casetop,453); // J6 (back)
};
// Parts to go on PCB (top)
module parts_top(part=false,hole=false,block=false){
part_L2(part,hole,block);
part_U3(part,hole,block);
part_D2(part,hole,block);
part_R3(part,hole,block);
part_R15(part,hole,block);
part_C12(part,hole,block);
part_C5(part,hole,block);
part_C4(part,hole,block);
part_V1(part,hole,block);
part_R2(part,hole,block);
part_C1(part,hole,block);
part_R14(part,hole,block);
part_U5(part,hole,block);
part_J5(part,hole,block);
part_R4(part,hole,block);
part_D1(part,hole,block);
part_R9(part,hole,block);
part_C9(part,hole,block);
part_V2(part,hole,block);
part_R1(part,hole,block);
part_PCB1(part,hole,block);
part_U7(part,hole,block);
part_C3(part,hole,block);
part_R5(part,hole,block);
part_U1(part,hole,block);
part_C10(part,hole,block);
part_C2(part,hole,block);
part_R6(part,hole,block);
part_C7(part,hole,block);
part_C8(part,hole,block);
part_C11(part,hole,block);
part_R7(part,hole,block);
part_D3(part,hole,block);
part_J6(part,hole,block);
part_U6(part,hole,block);
part_J2(part,hole,block);
}

parts_top=10;
module part_SW1(part=true,hole=false,block=false)
{
};
module part_JP1(part=true,hole=false,block=false)
{
};
module part_J1(part=true,hole=false,block=false)
{
};
module part_J3(part=true,hole=false,block=false)
{
};
// Parts to go on PCB (bottom)
module parts_bottom(part=false,hole=false,block=false){
part_SW1(part,hole,block);
part_JP1(part,hole,block);
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
{ // RevK:C_0402 C_0402_1005Metric
// 0402 Capacitor
if(part)
{
	b(0,0,0,1.0,0.5,1); // Chip
	b(0,0,0,1.5,0.65,0.2); // Pad size
}
}

module m6(part=false,hole=false,block=false,height)
{ // C1
if(part)
{
	b(0,0,0,3.5,2.8,1.9);
}
}

module m7(part=false,hole=false,block=false,height)
{ // U5
if(part)
{
	b(0,0,0,4,5,4);
}
if(hole)
{
	translate([0,0.50,0])cylinder(d1=5,d2=7,h=height+1,$fn=6);
}
if(block)
{
	translate([0,0.5,0])cylinder(d1=7,d2=9,h=height+1,$fn=6);
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
                b(0,0,.8,2.8,2.8,1);
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

module m12(part=false,hole=false,block=false,height,N=0)
{ // J6
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

module m13(part=false,hole=false,block=false,height)
{ // U6
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
                		parts_top(part=true);
                		parts_bottom(part=true);
                	}
                	translate([-0.01,-0.01,-height])cube([0.02,0.02,height]);
                }
        }
	minkowski()
        {
        	union()
                {
                	parts_top(part=true);
                	parts_bottom(part=true);
                }
                translate([-0.01,-0.01,0])cube([0.02,0.02,height]);
        }
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
			pcb_hulled(height);
		}
		if(parts_top)minkowski()
		{
			if(nohull)parts_top(part=true);
			else hull(){parts_top(part=true);pcb_hulled();}
			translate([0,0,margin-height])cylinder(r=margin*2,h=height,$fn=8);
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
			translate([0,0,-height])pcb_hulled(height+pcbthickness);
		}
		if(parts_bottom)minkowski()
		{
			if(nohull)parts_bottom(part=true);
			else hull()parts_bottom(part=true);
			translate([0,0,-margin])cylinder(r=margin*2,h=height,$fn=8);
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
top();
