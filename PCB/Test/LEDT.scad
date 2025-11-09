// Generated case design for Test/LED.kicad_pcb
// By https://github.com/revk/PCBCase
// Generated 2025-11-09 11:02:40
// title:	Test
// rev:	1
// company:	Adrian Kennard, Andrews & Arnold Ltd
//

// Globals
margin=0.200000;
lip=3.000000;
lipa=0;
lipt=2;
casewall=3.000000;
casebottom=2.000000;
casetop=5.000000;
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
useredge=false;
datex=0.000000;
datey=0.000000;
datet=0.500000;
dateh=3.000000;
datea=0;
date="2025-10-16";
datef="OCRB";
logox=0.000000;
logoy=0.000000;
logot=0.500000;
logoh=10.000000;
logoa=0;
logo="A";
logof="AJK";
spacing=41.000000;
pcbwidth=25.000000;
function pcbwidth()=25.000000;
pcblength=45.000000;
function pcblength()=45.000000;
originx=100.000000;
originy=100.000000;

module outline(h=pcbthickness,r=0){linear_extrude(height=h)offset(r=r)polygon(points=[[12.500000,22.500000],[-12.500000,22.500000],[-12.500000,-22.500000],[12.500000,-22.500000]],paths=[[0,1,2,3]]);}

module pcb(h=pcbthickness,r=0){linear_extrude(height=h)offset(r=r)polygon(points=[[12.500000,22.500000],[-12.500000,22.500000],[-12.500000,-22.500000],[12.500000,-22.500000]],paths=[[0,1,2,3]]);}
module D29(){translate([4.100000,7.500000,1.200000])rotate([0,0,180.000000])children();}
module part_D29(part=true,hole=false,block=false)
{
translate([4.100000,7.500000,1.200000])rotate([0,0,180.000000])m0(part,hole,block,casetop); // D29
};
module D22(){translate([4.100000,-10.000000,1.200000])rotate([0,0,180.000000])children();}
module part_D22(part=true,hole=false,block=false)
{
translate([4.100000,-10.000000,1.200000])rotate([0,0,180.000000])m0(part,hole,block,casetop); // D29
};
module TP2(){translate([-2.500000,-17.500000,1.200000])rotate([0,0,90.000000])children();}
module part_TP2(part=true,hole=false,block=false)
{
};
module TP8(){translate([1.400000,10.900000,1.200000])children();}
module part_TP8(part=true,hole=false,block=false)
{
};
module D18(){translate([-2.200000,-7.900000,1.200000])children();}
module part_D18(part=true,hole=false,block=false)
{
translate([-2.200000,-7.900000,1.200000])m1(part,hole,block,casetop); // D18
};
module D39(){translate([9.100000,5.100000,1.200000])rotate([0,0,180.000000])children();}
module part_D39(part=true,hole=false,block=false)
{
translate([9.100000,5.100000,1.200000])rotate([0,0,180.000000])m0(part,hole,block,casetop); // D29
};
module D24(){translate([4.100000,-5.000000,1.200000])rotate([0,0,180.000000])children();}
module part_D24(part=true,hole=false,block=false)
{
translate([4.100000,-5.000000,1.200000])rotate([0,0,180.000000])m0(part,hole,block,casetop); // D29
};
module D26(){translate([4.100000,0.000000,1.200000])rotate([0,0,180.000000])children();}
module part_D26(part=true,hole=false,block=false)
{
translate([4.100000,0.000000,1.200000])rotate([0,0,180.000000])m0(part,hole,block,casetop); // D29
};
module TP9(){translate([7.700000,10.900000,1.200000])children();}
module part_TP9(part=true,hole=false,block=false)
{
};
module D5(){translate([-9.600000,-4.500000,1.200000])rotate([0,0,-90.000000])children();}
module part_D5(part=true,hole=false,block=false)
{
translate([-9.600000,-4.500000,1.200000])rotate([0,0,-90.000000])m2(part,hole,block,casetop); // D5
};
module TP5(){translate([0.000000,-20.500000,1.200000])rotate([0,0,90.000000])children();}
module part_TP5(part=true,hole=false,block=false)
{
};
module D3(){translate([-9.600000,-8.500000,1.200000])rotate([0,0,-90.000000])children();}
module part_D3(part=true,hole=false,block=false)
{
translate([-9.600000,-8.500000,1.200000])rotate([0,0,-90.000000])m2(part,hole,block,casetop); // D5
};
module D10(){translate([-9.600000,5.500000,1.200000])rotate([0,0,-90.000000])children();}
module part_D10(part=true,hole=false,block=false)
{
translate([-9.600000,5.500000,1.200000])rotate([0,0,-90.000000])m2(part,hole,block,casetop); // D5
};
module D31(){translate([9.100000,-12.500000,1.200000])rotate([0,0,180.000000])children();}
module part_D31(part=true,hole=false,block=false)
{
translate([9.100000,-12.500000,1.200000])rotate([0,0,180.000000])m0(part,hole,block,casetop); // D29
};
module D43(){translate([-0.200000,-5.900000,1.200000])children();}
module part_D43(part=true,hole=false,block=false)
{
translate([-0.200000,-5.900000,1.200000])m1(part,hole,block,casetop); // D18
};
module D9(){translate([-9.600000,3.500000,1.200000])rotate([0,0,-90.000000])children();}
module part_D9(part=true,hole=false,block=false)
{
translate([-9.600000,3.500000,1.200000])rotate([0,0,-90.000000])m2(part,hole,block,casetop); // D5
};
module D12(){translate([-2.200000,-11.900000,1.200000])children();}
module part_D12(part=true,hole=false,block=false)
{
translate([-2.200000,-11.900000,1.200000])m1(part,hole,block,casetop); // D18
};
module D14(){translate([-0.200000,-11.900000,1.200000])children();}
module part_D14(part=true,hole=false,block=false)
{
translate([-0.200000,-11.900000,1.200000])m1(part,hole,block,casetop); // D18
};
module D38(){translate([9.100000,2.900000,1.200000])rotate([0,0,90.000000])children();}
module part_D38(part=true,hole=false,block=false)
{
translate([9.100000,2.900000,1.200000])rotate([0,0,90.000000])m0(part,hole,block,casetop); // D29
};
module D6(){translate([-9.600000,-2.500000,1.200000])rotate([0,0,-90.000000])children();}
module part_D6(part=true,hole=false,block=false)
{
translate([-9.600000,-2.500000,1.200000])rotate([0,0,-90.000000])m2(part,hole,block,casetop); // D5
};
module D20(){translate([-0.200000,-7.900000,1.200000])children();}
module part_D20(part=true,hole=false,block=false)
{
translate([-0.200000,-7.900000,1.200000])m1(part,hole,block,casetop); // D18
};
module D21(){translate([4.100000,-12.500000,1.200000])rotate([0,0,180.000000])children();}
module part_D21(part=true,hole=false,block=false)
{
translate([4.100000,-12.500000,1.200000])rotate([0,0,180.000000])m0(part,hole,block,casetop); // D29
};
module D41(){translate([-2.200000,2.300000,1.200000])children();}
module part_D41(part=true,hole=false,block=false)
{
translate([-2.200000,2.300000,1.200000])m1(part,hole,block,casetop); // D18
};
module D28(){translate([4.100000,5.000000,1.200000])rotate([0,0,180.000000])children();}
module part_D28(part=true,hole=false,block=false)
{
translate([4.100000,5.000000,1.200000])rotate([0,0,180.000000])m0(part,hole,block,casetop); // D29
};
module D30(){translate([4.100000,10.000000,1.200000])rotate([0,0,180.000000])children();}
module part_D30(part=true,hole=false,block=false)
{
translate([4.100000,10.000000,1.200000])rotate([0,0,180.000000])m0(part,hole,block,casetop); // D29
};
module D35(){translate([9.100000,-3.700000,1.200000])rotate([0,0,180.000000])children();}
module part_D35(part=true,hole=false,block=false)
{
translate([9.100000,-3.700000,1.200000])rotate([0,0,180.000000])m0(part,hole,block,casetop); // D29
};
module D33(){translate([9.100000,-8.100000,1.200000])rotate([0,0,180.000000])children();}
module part_D33(part=true,hole=false,block=false)
{
translate([9.100000,-8.100000,1.200000])rotate([0,0,180.000000])m0(part,hole,block,casetop); // D29
};
module D15(){translate([-2.200000,0.500000,1.200000])children();}
module part_D15(part=true,hole=false,block=false)
{
translate([-2.200000,0.500000,1.200000])m1(part,hole,block,casetop); // D18
};
module D34(){translate([9.100000,-5.900000,1.200000])rotate([0,0,90.000000])children();}
module part_D34(part=true,hole=false,block=false)
{
translate([9.100000,-5.900000,1.200000])rotate([0,0,90.000000])m0(part,hole,block,casetop); // D29
};
module D2(){translate([-9.600000,-10.500000,1.200000])rotate([0,0,-90.000000])children();}
module part_D2(part=true,hole=false,block=false)
{
translate([-9.600000,-10.500000,1.200000])rotate([0,0,-90.000000])m2(part,hole,block,casetop); // D5
};
module D48(){translate([-2.200000,7.700000,1.200000])children();}
module part_D48(part=true,hole=false,block=false)
{
translate([-2.200000,7.700000,1.200000])m1(part,hole,block,casetop); // D18
};
module D23(){translate([4.100000,-7.500000,1.200000])rotate([0,0,180.000000])children();}
module part_D23(part=true,hole=false,block=false)
{
translate([4.100000,-7.500000,1.200000])rotate([0,0,180.000000])m0(part,hole,block,casetop); // D29
};
module D16(){translate([-4.200000,-7.900000,1.200000])children();}
module part_D16(part=true,hole=false,block=false)
{
translate([-4.200000,-7.900000,1.200000])m1(part,hole,block,casetop); // D18
};
module D8(){translate([-9.600000,1.500000,1.200000])rotate([0,0,-90.000000])children();}
module part_D8(part=true,hole=false,block=false)
{
translate([-9.600000,1.500000,1.200000])rotate([0,0,-90.000000])m2(part,hole,block,casetop); // D5
};
module D40(){translate([9.100000,7.300000,1.200000])rotate([0,0,90.000000])children();}
module part_D40(part=true,hole=false,block=false)
{
translate([9.100000,7.300000,1.200000])rotate([0,0,90.000000])m0(part,hole,block,casetop); // D29
};
module TP3(){translate([4.100000,-17.500000,1.200000])rotate([0,0,90.000000])children();}
module part_TP3(part=true,hole=false,block=false)
{
};
module D19(){translate([-4.200000,-5.900000,1.200000])children();}
module part_D19(part=true,hole=false,block=false)
{
translate([-4.200000,-5.900000,1.200000])m1(part,hole,block,casetop); // D18
};
module D44(){translate([-2.200000,-3.900000,1.200000])children();}
module part_D44(part=true,hole=false,block=false)
{
translate([-2.200000,-3.900000,1.200000])m1(part,hole,block,casetop); // D18
};
module TP10(){translate([9.100000,-20.500000,1.200000])children();}
module part_TP10(part=true,hole=false,block=false)
{
};
module D36(){translate([9.100000,-1.500000,1.200000])rotate([0,0,90.000000])children();}
module part_D36(part=true,hole=false,block=false)
{
translate([9.100000,-1.500000,1.200000])rotate([0,0,90.000000])m0(part,hole,block,casetop); // D29
};
module D25(){translate([4.100000,-2.500000,1.200000])rotate([0,0,180.000000])children();}
module part_D25(part=true,hole=false,block=false)
{
translate([4.100000,-2.500000,1.200000])rotate([0,0,180.000000])m0(part,hole,block,casetop); // D29
};
module TP4(){translate([9.100000,-17.500000,1.200000])rotate([0,0,90.000000])children();}
module part_TP4(part=true,hole=false,block=false)
{
};
module D37(){translate([9.100000,0.700000,1.200000])rotate([0,0,180.000000])children();}
module part_D37(part=true,hole=false,block=false)
{
translate([9.100000,0.700000,1.200000])rotate([0,0,180.000000])m0(part,hole,block,casetop); // D29
};
module D7(){translate([-9.600000,-0.500000,1.200000])rotate([0,0,-90.000000])children();}
module part_D7(part=true,hole=false,block=false)
{
translate([-9.600000,-0.500000,1.200000])rotate([0,0,-90.000000])m2(part,hole,block,casetop); // D5
};
module D45(){translate([-0.200000,-3.900000,1.200000])children();}
module part_D45(part=true,hole=false,block=false)
{
translate([-0.200000,-3.900000,1.200000])m1(part,hole,block,casetop); // D18
};
module D1(){translate([-9.600000,-12.500000,1.200000])rotate([0,0,-90.000000])children();}
module part_D1(part=true,hole=false,block=false)
{
translate([-9.600000,-12.500000,1.200000])rotate([0,0,-90.000000])m2(part,hole,block,casetop); // D5
};
module TP6(){translate([-10.600000,8.300000,1.200000])children();}
module part_TP6(part=true,hole=false,block=false)
{
};
module D27(){translate([4.100000,2.500000,1.200000])rotate([0,0,180.000000])children();}
module part_D27(part=true,hole=false,block=false)
{
translate([4.100000,2.500000,1.200000])rotate([0,0,180.000000])m0(part,hole,block,casetop); // D29
};
module TP7(){translate([-5.000000,8.200000,1.200000])children();}
module part_TP7(part=true,hole=false,block=false)
{
};
module D42(){translate([-4.200000,-3.900000,1.200000])children();}
module part_D42(part=true,hole=false,block=false)
{
translate([-4.200000,-3.900000,1.200000])m1(part,hole,block,casetop); // D18
};
module TP1(){translate([-9.600000,-17.500000,1.200000])rotate([0,0,90.000000])children();}
module part_TP1(part=true,hole=false,block=false)
{
};
module D17(){translate([-0.200000,-9.900000,1.200000])children();}
module part_D17(part=true,hole=false,block=false)
{
translate([-0.200000,-9.900000,1.200000])m1(part,hole,block,casetop); // D18
};
module D11(){translate([-4.200000,-11.900000,1.200000])children();}
module part_D11(part=true,hole=false,block=false)
{
translate([-4.200000,-11.900000,1.200000])m1(part,hole,block,casetop); // D18
};
module D32(){translate([9.100000,-10.300000,1.200000])rotate([0,0,90.000000])children();}
module part_D32(part=true,hole=false,block=false)
{
translate([9.100000,-10.300000,1.200000])rotate([0,0,90.000000])m0(part,hole,block,casetop); // D29
};
module D46(){translate([-2.200000,4.100000,1.200000])children();}
module part_D46(part=true,hole=false,block=false)
{
translate([-2.200000,4.100000,1.200000])m1(part,hole,block,casetop); // D18
};
module D4(){translate([-9.600000,-6.500000,1.200000])rotate([0,0,-90.000000])children();}
module part_D4(part=true,hole=false,block=false)
{
translate([-9.600000,-6.500000,1.200000])rotate([0,0,-90.000000])m2(part,hole,block,casetop); // D5
};
module D13(){translate([-4.200000,-9.900000,1.200000])children();}
module part_D13(part=true,hole=false,block=false)
{
translate([-4.200000,-9.900000,1.200000])m1(part,hole,block,casetop); // D18
};
module D47(){translate([-2.200000,5.900000,1.200000])children();}
module part_D47(part=true,hole=false,block=false)
{
translate([-2.200000,5.900000,1.200000])m1(part,hole,block,casetop); // D18
};
// Parts to go on PCB (top)
module parts_top(part=false,hole=false,block=false){
part_D29(part,hole,block);
part_D22(part,hole,block);
part_TP2(part,hole,block);
part_TP8(part,hole,block);
part_D18(part,hole,block);
part_D39(part,hole,block);
part_D24(part,hole,block);
part_D26(part,hole,block);
part_TP9(part,hole,block);
part_D5(part,hole,block);
part_TP5(part,hole,block);
part_D3(part,hole,block);
part_D10(part,hole,block);
part_D31(part,hole,block);
part_D43(part,hole,block);
part_D9(part,hole,block);
part_D12(part,hole,block);
part_D14(part,hole,block);
part_D38(part,hole,block);
part_D6(part,hole,block);
part_D20(part,hole,block);
part_D21(part,hole,block);
part_D41(part,hole,block);
part_D28(part,hole,block);
part_D30(part,hole,block);
part_D35(part,hole,block);
part_D33(part,hole,block);
part_D15(part,hole,block);
part_D34(part,hole,block);
part_D2(part,hole,block);
part_D48(part,hole,block);
part_D23(part,hole,block);
part_D16(part,hole,block);
part_D8(part,hole,block);
part_D40(part,hole,block);
part_TP3(part,hole,block);
part_D19(part,hole,block);
part_D44(part,hole,block);
part_TP10(part,hole,block);
part_D36(part,hole,block);
part_D25(part,hole,block);
part_TP4(part,hole,block);
part_D37(part,hole,block);
part_D7(part,hole,block);
part_D45(part,hole,block);
part_D1(part,hole,block);
part_TP6(part,hole,block);
part_D27(part,hole,block);
part_TP7(part,hole,block);
part_D42(part,hole,block);
part_TP1(part,hole,block);
part_D17(part,hole,block);
part_D11(part,hole,block);
part_D32(part,hole,block);
part_D46(part,hole,block);
part_D4(part,hole,block);
part_D13(part,hole,block);
part_D47(part,hole,block);
}

parts_top=48;
// Parts to go on PCB (bottom)
module parts_bottom(part=false,hole=false,block=false){
}

parts_bottom=0;
module b(cx,cy,z,w,l,h){translate([cx-w/2,cy-l/2,z])cube([w,l,h]);}
module m0(part=false,hole=false,block=false,height)
{ // D29
// 2x2mm LED
if(part)
{
        b(0,0,0,2.0+0.2,2.0+0.2,0.65+0.2);
}
if(hole)
{
        hull()
        {
                b(0,0,.6+0.2,2.0+0.2,2.0+0.2,1);
                translate([0,0,height])cylinder(d=1.001,h=0.001,$fn=16);
        }
}
if(block)
{
        hull()
        {
                b(0,0,.65+0.2,2.8,2.8,1);
                translate([0,0,height])cylinder(d=2,h=1,$fn=16);
        }
}
}

module m1(part=false,hole=false,block=false,height)
{ // D18
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

module m2(part=false,hole=false,block=false,height)
{ // D5
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
                translate([0,0,height])cylinder(d=1.001,h=0.001,$fn=16);
        }
}
if(block)
{
        hull()
        {
                b(0,0,.8,2.8,2.8,1);
                translate([0,0,height])cylinder(d=2,h=1,$fn=16);
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