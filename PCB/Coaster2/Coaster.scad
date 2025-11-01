// Generated case design for Coaster2/Coaster.kicad_pcb
// By https://github.com/revk/PCBCase
// Generated 2025-11-01 10:15:26
// title:	Coaster
//

// Globals
margin=0.200000;
lip=3.000000;
lipa=0;
lipt=2;
casewall=3.000000;
casebottom=5.000000;
casetop=5.000000;
bottomthickness=0.000000;
topthickness=0.000000;
fit=0.000000;
snap=0.150000;
edge=2.000000;
pcbthickness=1.600000;
function pcbthickness()=1.600000;
nohull=false;
hullcap=1.000000;
hulledge=1.000000;
useredge=false;
datex=0.000000;
datey=0.000000;
datet=0.500000;
dateh=3.000000;
datea=0;
date="2025-09-17";
datef="OCRB";
logox=0.000000;
logoy=0.000000;
logot=0.500000;
logoh=10.000000;
logoa=0;
logo="A";
logof="AJK";
spacing=116.000000;
pcbwidth=100.000000;
function pcbwidth()=100.000000;
pcblength=100.000000;
function pcblength()=100.000000;
originx=100.000000;
originy=100.000000;

module outline(h=pcbthickness,r=0){linear_extrude(height=h)offset(r=r)polygon(points=[[50.000000,0.000000],[49.960470,-1.987826],[49.841942,-3.972508],[49.644604,-5.950910],[49.368767,-7.919901],[49.014868,-9.876370],[48.583467,-11.817222],[48.075245,-13.739389],[47.491007,-15.639830],[46.831675,-17.515542],[46.098293,-19.363559],[45.292020,-21.180957],[44.414131,-22.964864],[43.466014,-24.712459],[42.449168,-26.420979],[41.365202,-28.087721],[40.215828,-29.710051],[39.002865,-31.285404],[37.728231,-32.811287],[36.393941,-34.285290],[35.002104,-35.705080],[33.554921,-37.068413],[32.054682,-38.373133],[30.503757,-39.617178],[28.904600,-40.798580],[27.259739,-41.915470],[25.571774,-42.966084],[23.843375,-43.948760],[22.077275,-44.861943],[20.276266,-45.704191],[18.443196,-46.474170],[16.580964,-47.170665],[14.692514,-47.792573],[12.780832,-48.338911],[10.848940,-48.808816],[8.899895,-49.201543],[6.936777,-49.516473],[4.962690,-49.753108],[2.980756,-49.911072],[0.994109,-49.990116],[-0.994109,-49.990116],[-2.980756,-49.911072],[-4.962690,-49.753108],[-6.936777,-49.516473],[-8.899895,-49.201543],[-10.848940,-48.808816],[-12.780832,-48.338911],[-14.692514,-47.792573],[-16.580964,-47.170665],[-18.443196,-46.474170],[-20.276266,-45.704191],[-22.077275,-44.861943],[-23.843375,-43.948760],[-25.571774,-42.966084],[-27.259739,-41.915470],[-28.904600,-40.798580],[-30.503757,-39.617178],[-32.054682,-38.373133],[-33.554921,-37.068413],[-35.002104,-35.705080],[-36.393941,-34.285290],[-37.728231,-32.811287],[-39.002865,-31.285404],[-40.215828,-29.710051],[-41.365202,-28.087721],[-42.449168,-26.420979],[-43.466014,-24.712459],[-44.414131,-22.964864],[-45.292020,-21.180957],[-46.098293,-19.363559],[-46.831675,-17.515542],[-47.491007,-15.639830],[-48.075245,-13.739389],[-48.583467,-11.817222],[-49.014868,-9.876370],[-49.368767,-7.919901],[-49.644604,-5.950910],[-49.841942,-3.972508],[-49.960470,-1.987826],[-50.000000,0.000000],[-49.960470,1.987826],[-49.841942,3.972508],[-49.644604,5.950910],[-49.368767,7.919901],[-49.014868,9.876370],[-48.583467,11.817222],[-48.075245,13.739389],[-47.491007,15.639830],[-46.831675,17.515542],[-46.098293,19.363559],[-45.292020,21.180957],[-44.414131,22.964864],[-43.466014,24.712459],[-42.449168,26.420979],[-41.365202,28.087721],[-40.215828,29.710051],[-39.002865,31.285404],[-37.728231,32.811287],[-36.393941,34.285290],[-35.002104,35.705080],[-33.554921,37.068413],[-32.054682,38.373133],[-30.503757,39.617178],[-28.904600,40.798580],[-27.259739,41.915470],[-25.571774,42.966084],[-23.843375,43.948760],[-22.077275,44.861943],[-20.276266,45.704191],[-18.443196,46.474170],[-16.580964,47.170665],[-14.692514,47.792573],[-12.780832,48.338911],[-10.848940,48.808816],[-8.899895,49.201543],[-6.936777,49.516473],[-4.962690,49.753108],[-2.980756,49.911072],[-0.994109,49.990116],[0.994109,49.990116],[2.980756,49.911072],[4.962690,49.753108],[6.936777,49.516473],[8.899895,49.201543],[10.848940,48.808816],[12.780832,48.338911],[14.692514,47.792573],[16.580964,47.170665],[18.443196,46.474170],[20.276266,45.704191],[22.077275,44.861943],[23.843375,43.948760],[25.571774,42.966084],[27.259739,41.915470],[28.904600,40.798580],[30.503757,39.617178],[32.054682,38.373133],[33.554921,37.068413],[35.002104,35.705080],[36.393941,34.285290],[37.728231,32.811287],[39.002865,31.285404],[40.215828,29.710051],[41.365202,28.087721],[42.449168,26.420979],[43.466014,24.712459],[44.414131,22.964864],[45.292020,21.180957],[46.098293,19.363559],[46.831675,17.515542],[47.491007,15.639830],[48.075245,13.739389],[48.583467,11.817222],[49.014868,9.876370],[49.368767,7.919901],[49.644604,5.950910],[49.841942,3.972508],[49.960470,1.987826]],paths=[[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157]]);}

module pcb(h=pcbthickness,r=0){linear_extrude(height=h)offset(r=r)polygon(points=[[50.000000,0.000000],[49.960470,-1.987826],[49.841942,-3.972508],[49.644604,-5.950910],[49.368767,-7.919901],[49.014868,-9.876370],[48.583467,-11.817222],[48.075245,-13.739389],[47.491007,-15.639830],[46.831675,-17.515542],[46.098293,-19.363559],[45.292020,-21.180957],[44.414131,-22.964864],[43.466014,-24.712459],[42.449168,-26.420979],[41.365202,-28.087721],[40.215828,-29.710051],[39.002865,-31.285404],[37.728231,-32.811287],[36.393941,-34.285290],[35.002104,-35.705080],[33.554921,-37.068413],[32.054682,-38.373133],[30.503757,-39.617178],[28.904600,-40.798580],[27.259739,-41.915470],[25.571774,-42.966084],[23.843375,-43.948760],[22.077275,-44.861943],[20.276266,-45.704191],[18.443196,-46.474170],[16.580964,-47.170665],[14.692514,-47.792573],[12.780832,-48.338911],[10.848940,-48.808816],[8.899895,-49.201543],[6.936777,-49.516473],[4.962690,-49.753108],[2.980756,-49.911072],[0.994109,-49.990116],[-0.994109,-49.990116],[-2.980756,-49.911072],[-4.962690,-49.753108],[-6.936777,-49.516473],[-8.899895,-49.201543],[-10.848940,-48.808816],[-12.780832,-48.338911],[-14.692514,-47.792573],[-16.580964,-47.170665],[-18.443196,-46.474170],[-20.276266,-45.704191],[-22.077275,-44.861943],[-23.843375,-43.948760],[-25.571774,-42.966084],[-27.259739,-41.915470],[-28.904600,-40.798580],[-30.503757,-39.617178],[-32.054682,-38.373133],[-33.554921,-37.068413],[-35.002104,-35.705080],[-36.393941,-34.285290],[-37.728231,-32.811287],[-39.002865,-31.285404],[-40.215828,-29.710051],[-41.365202,-28.087721],[-42.449168,-26.420979],[-43.466014,-24.712459],[-44.414131,-22.964864],[-45.292020,-21.180957],[-46.098293,-19.363559],[-46.831675,-17.515542],[-47.491007,-15.639830],[-48.075245,-13.739389],[-48.583467,-11.817222],[-49.014868,-9.876370],[-49.368767,-7.919901],[-49.644604,-5.950910],[-49.841942,-3.972508],[-49.960470,-1.987826],[-50.000000,0.000000],[-49.960470,1.987826],[-49.841942,3.972508],[-49.644604,5.950910],[-49.368767,7.919901],[-49.014868,9.876370],[-48.583467,11.817222],[-48.075245,13.739389],[-47.491007,15.639830],[-46.831675,17.515542],[-46.098293,19.363559],[-45.292020,21.180957],[-44.414131,22.964864],[-43.466014,24.712459],[-42.449168,26.420979],[-41.365202,28.087721],[-40.215828,29.710051],[-39.002865,31.285404],[-37.728231,32.811287],[-36.393941,34.285290],[-35.002104,35.705080],[-33.554921,37.068413],[-32.054682,38.373133],[-30.503757,39.617178],[-28.904600,40.798580],[-27.259739,41.915470],[-25.571774,42.966084],[-23.843375,43.948760],[-22.077275,44.861943],[-20.276266,45.704191],[-18.443196,46.474170],[-16.580964,47.170665],[-14.692514,47.792573],[-12.780832,48.338911],[-10.848940,48.808816],[-8.899895,49.201543],[-6.936777,49.516473],[-4.962690,49.753108],[-2.980756,49.911072],[-0.994109,49.990116],[0.994109,49.990116],[2.980756,49.911072],[4.962690,49.753108],[6.936777,49.516473],[8.899895,49.201543],[10.848940,48.808816],[12.780832,48.338911],[14.692514,47.792573],[16.580964,47.170665],[18.443196,46.474170],[20.276266,45.704191],[22.077275,44.861943],[23.843375,43.948760],[25.571774,42.966084],[27.259739,41.915470],[28.904600,40.798580],[30.503757,39.617178],[32.054682,38.373133],[33.554921,37.068413],[35.002104,35.705080],[36.393941,34.285290],[37.728231,32.811287],[39.002865,31.285404],[40.215828,29.710051],[41.365202,28.087721],[42.449168,26.420979],[43.466014,24.712459],[44.414131,22.964864],[45.292020,21.180957],[46.098293,19.363559],[46.831675,17.515542],[47.491007,15.639830],[48.075245,13.739389],[48.583467,11.817222],[49.014868,9.876370],[49.368767,7.919901],[49.644604,5.950910],[49.841942,3.972508],[49.960470,1.987826]],paths=[[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157]]);}
module C54(){translate([-34.449852,10.450248,1.600000])rotate([0,0,163.125000])children();}
module part_C54(part=true,hole=false,block=false)
{
translate([-34.449852,10.450248,1.600000])rotate([0,0,163.125000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module J3(){translate([44.010000,0.000000,1.600000])rotate([0,0,90.000000])children();}
module part_J3(part=true,hole=false,block=false)
{
translate([44.010000,0.000000,1.600000])rotate([0,0,90.000000])translate([0.000000,-1.900000,0.000000])rotate([90.000000,0.000000,0.000000])m1(part,hole,block,casetop); // RevK:USB-C-Socket-H CSP-USC16-TR (back)
};
module C93(){translate([-1.962707,-39.951818,1.600000])rotate([0,0,-92.812500])children();}
module part_C93(part=true,hole=false,block=false)
{
translate([-1.962707,-39.951818,1.600000])rotate([0,0,-92.812500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C78(){translate([39.567060,-5.869219,1.600000])rotate([0,0,-8.437500])children();}
module part_C78(part=true,hole=false,block=false)
{
translate([39.567060,-5.869219,1.600000])rotate([0,0,-8.437500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D108(){translate([-39.807389,-3.920686,1.600000])rotate([0,0,-39.375000])children();}
module part_D108(part=true,hole=false,block=false)
{
translate([-39.807389,-3.920686,1.600000])rotate([0,0,-39.375000])m2(part,hole,block,casetop); // D108
};
module C77(){translate([39.951818,-1.962707,1.600000])rotate([0,0,-2.812500])children();}
module part_C77(part=true,hole=false,block=false)
{
translate([39.951818,-1.962707,1.600000])rotate([0,0,-2.812500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C14(){translate([17.778247,26.607028,1.600000])rotate([0,0,56.250000])children();}
module part_C14(part=true,hole=false,block=false)
{
translate([17.778247,26.607028,1.600000])rotate([0,0,56.250000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C75(){translate([39.567060,5.869219,1.600000])rotate([0,0,8.437500])children();}
module part_C75(part=true,hole=false,block=false)
{
translate([39.567060,5.869219,1.600000])rotate([0,0,8.437500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C65(){translate([17.102204,36.159572,1.600000])rotate([0,0,64.687500])children();}
module part_C65(part=true,hole=false,block=false)
{
translate([17.102204,36.159572,1.600000])rotate([0,0,64.687500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D124(){translate([-3.920686,39.807389,1.600000])rotate([0,0,-129.375000])children();}
module part_D124(part=true,hole=false,block=false)
{
translate([-3.920686,39.807389,1.600000])rotate([0,0,-129.375000])m2(part,hole,block,casetop); // D108
};
module C71(){translate([34.309144,20.564110,1.600000])rotate([0,0,30.937500])children();}
module part_C71(part=true,hole=false,block=false)
{
translate([34.309144,20.564110,1.600000])rotate([0,0,30.937500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D20(){translate([12.245870,-29.564145,1.600000])rotate([0,0,67.500000])children();}
module part_D20(part=true,hole=false,block=false)
{
translate([12.245870,-29.564145,1.600000])rotate([0,0,67.500000])m2(part,hole,block,casetop); // D108
};
module C135(){translate([17.000000,-3.000000,1.600000])children();}
module part_C135(part=true,hole=false,block=false)
{
translate([17.000000,-3.000000,1.600000])m3(part,hole,block,casetop); // RevK:C_0603 C_0603_1608Metric (back)
};
module C60(){translate([-3.528617,35.826650,1.600000])rotate([0,0,95.625000])children();}
module part_C60(part=true,hole=false,block=false)
{
translate([-3.528617,35.826650,1.600000])rotate([0,0,95.625000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C104(){translate([-36.159572,-17.102204,1.600000])rotate([0,0,-154.687500])children();}
module part_C104(part=true,hole=false,block=false)
{
translate([-36.159572,-17.102204,1.600000])rotate([0,0,-154.687500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C85(){translate([26.862358,-29.638045,1.600000])rotate([0,0,-47.812500])children();}
module part_C85(part=true,hole=false,block=false)
{
translate([26.862358,-29.638045,1.600000])rotate([0,0,-47.812500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C55(){translate([-31.749166,16.970283,1.600000])rotate([0,0,151.875000])children();}
module part_C55(part=true,hole=false,block=false)
{
translate([-31.749166,16.970283,1.600000])rotate([0,0,151.875000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C89(){translate([13.475594,-37.661763,1.600000])rotate([0,0,-70.312500])children();}
module part_C89(part=true,hole=false,block=false)
{
translate([13.475594,-37.661763,1.600000])rotate([0,0,-70.312500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D113(){translate([-36.955181,15.307337,1.600000])rotate([0,0,-67.500000])children();}
module part_D113(part=true,hole=false,block=false)
{
translate([-36.955181,15.307337,1.600000])rotate([0,0,-67.500000])m2(part,hole,block,casetop); // D108
};
module C92(){translate([1.962707,-39.951818,1.600000])rotate([0,0,-87.187500])children();}
module part_C92(part=true,hole=false,block=false)
{
translate([1.962707,-39.951818,1.600000])rotate([0,0,-87.187500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C74(){translate([38.801250,9.719207,1.600000])rotate([0,0,14.062500])children();}
module part_C74(part=true,hole=false,block=false)
{
translate([38.801250,9.719207,1.600000])rotate([0,0,14.062500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D33(){translate([25.455844,25.455844,1.600000])rotate([0,0,180.000000])children();}
module part_D33(part=true,hole=false,block=false)
{
translate([25.455844,25.455844,1.600000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // D108
};
module C8(){translate([10.715136,-25.868627,1.600000])rotate([0,0,-67.500000])children();}
module part_C8(part=true,hole=false,block=false)
{
translate([10.715136,-25.868627,1.600000])rotate([0,0,-67.500000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D86(){translate([25.375731,-30.920418,1.600000])rotate([0,0,84.375000])children();}
module part_D86(part=true,hole=false,block=false)
{
translate([25.375731,-30.920418,1.600000])rotate([0,0,84.375000])m2(part,hole,block,casetop); // D108
};
module D103(){translate([-33.258784,-22.222809,1.600000])rotate([0,0,-11.250000])children();}
module part_D103(part=true,hole=false,block=false)
{
translate([-33.258784,-22.222809,1.600000])rotate([0,0,-11.250000])m2(part,hole,block,casetop); // D108
};
module C96(){translate([-13.475594,-37.661763,1.600000])rotate([0,0,-109.687500])children();}
module part_C96(part=true,hole=false,block=false)
{
translate([-13.475594,-37.661763,1.600000])rotate([0,0,-109.687500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D71(){translate([33.258784,22.222809,1.600000])rotate([0,0,168.750000])children();}
module part_D71(part=true,hole=false,block=false)
{
translate([33.258784,22.222809,1.600000])rotate([0,0,168.750000])m2(part,hole,block,casetop); // D108
};
module D76(){translate([39.807389,3.920686,1.600000])rotate([0,0,140.625000])children();}
module part_D76(part=true,hole=false,block=false)
{
translate([39.807389,3.920686,1.600000])rotate([0,0,140.625000])m2(part,hole,block,casetop); // D108
};
module D46(){translate([-7.023252,-35.308270,1.600000])rotate([0,0,33.750000])children();}
module part_D46(part=true,hole=false,block=false)
{
translate([-7.023252,-35.308270,1.600000])rotate([0,0,33.750000])m2(part,hole,block,casetop); // D108
};
module D114(){translate([-35.276851,18.855869,1.600000])rotate([0,0,-73.125000])children();}
module part_D114(part=true,hole=false,block=false)
{
translate([-35.276851,18.855869,1.600000])rotate([0,0,-73.125000])m2(part,hole,block,casetop); // D108
};
module V3(){translate([49.910242,0.000000,1.600000])rotate([0,0,-90.000000])children();}
module part_V3(part=true,hole=false,block=false)
{
};
module C36(){translate([35.826650,3.528617,1.600000])rotate([0,0,5.625000])children();}
module part_C36(part=true,hole=false,block=false)
{
translate([35.826650,3.528617,1.600000])rotate([0,0,5.625000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C139(){translate([-2.000000,-13.500000,1.600000])rotate([0,0,90.000000])children();}
module part_C139(part=true,hole=false,block=false)
{
translate([-2.000000,-13.500000,1.600000])rotate([0,0,90.000000])m3(part,hole,block,casetop); // RevK:C_0603 C_0603_1608Metric (back)
};
module C119(){translate([-20.564110,34.309144,1.600000])rotate([0,0,120.937500])children();}
module part_C119(part=true,hole=false,block=false)
{
translate([-20.564110,34.309144,1.600000])rotate([0,0,120.937500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C103(){translate([-34.309144,-20.564110,1.600000])rotate([0,0,-149.062500])children();}
module part_C103(part=true,hole=false,block=false)
{
translate([-34.309144,-20.564110,1.600000])rotate([0,0,-149.062500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C73(){translate([37.661763,13.475594,1.600000])rotate([0,0,19.687500])children();}
module part_C73(part=true,hole=false,block=false)
{
translate([37.661763,13.475594,1.600000])rotate([0,0,19.687500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C138(){translate([-2.700000,-11.000000,1.600000])rotate([0,0,180.000000])children();}
module part_C138(part=true,hole=false,block=false)
{
translate([-2.700000,-11.000000,1.600000])rotate([0,0,180.000000])m3(part,hole,block,casetop); // RevK:C_0603 C_0603_1608Metric (back)
};
module D42(){translate([20.000528,-29.932906,1.600000])rotate([0,0,78.750000])children();}
module part_D42(part=true,hole=false,block=false)
{
translate([20.000528,-29.932906,1.600000])rotate([0,0,78.750000])m2(part,hole,block,casetop); // D108
};
module C13(){translate([6.242890,31.385129,1.600000])rotate([0,0,78.750000])children();}
module part_C13(part=true,hole=false,block=false)
{
translate([6.242890,31.385129,1.600000])rotate([0,0,78.750000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C22(){translate([-17.778247,-26.607028,1.600000])rotate([0,0,-123.750000])children();}
module part_C22(part=true,hole=false,block=false)
{
translate([-17.778247,-26.607028,1.600000])rotate([0,0,-123.750000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C34(){translate([31.749166,16.970283,1.600000])rotate([0,0,28.125000])children();}
module part_C34(part=true,hole=false,block=false)
{
translate([31.749166,16.970283,1.600000])rotate([0,0,28.125000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C82(){translate([34.309144,-20.564110,1.600000])rotate([0,0,-30.937500])children();}
module part_C82(part=true,hole=false,block=false)
{
translate([34.309144,-20.564110,1.600000])rotate([0,0,-30.937500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D19(){translate([22.627417,-22.627417,1.600000])rotate([0,0,90.000000])children();}
module part_D19(part=true,hole=false,block=false)
{
translate([22.627417,-22.627417,1.600000])rotate([0,0,90.000000])m2(part,hole,block,casetop); // D108
};
module D8(){translate([19.798990,-19.798990,1.600000])rotate([0,0,90.000000])children();}
module part_D8(part=true,hole=false,block=false)
{
translate([19.798990,-19.798990,1.600000])rotate([0,0,90.000000])m2(part,hole,block,casetop); // D108
};
module C99(){translate([-23.827972,-32.128301,1.600000])rotate([0,0,-126.562500])children();}
module part_C99(part=true,hole=false,block=false)
{
translate([-23.827972,-32.128301,1.600000])rotate([0,0,-126.562500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D75(){translate([39.231411,7.803613,1.600000])rotate([0,0,146.250000])children();}
module part_D75(part=true,hole=false,block=false)
{
translate([39.231411,7.803613,1.600000])rotate([0,0,146.250000])m2(part,hole,block,casetop); // D108
};
module C41(){translate([22.838158,-27.828376,1.600000])rotate([0,0,-50.625000])children();}
module part_C41(part=true,hole=false,block=false)
{
translate([22.838158,-27.828376,1.600000])rotate([0,0,-50.625000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C132(){translate([-5.500000,-8.500000,1.600000])children();}
module part_C132(part=true,hole=false,block=false)
{
translate([-5.500000,-8.500000,1.600000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D69(){translate([28.284271,28.284271,1.600000])rotate([0,0,180.000000])children();}
module part_D69(part=true,hole=false,block=false)
{
translate([28.284271,28.284271,1.600000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // D108
};
module C53(){translate([-35.826650,3.528617,1.600000])rotate([0,0,174.375000])children();}
module part_C53(part=true,hole=false,block=false)
{
translate([-35.826650,3.528617,1.600000])rotate([0,0,174.375000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D53(){translate([-36.000000,0.000000,1.600000])rotate([0,0,-45.000000])children();}
module part_D53(part=true,hole=false,block=false)
{
translate([-36.000000,0.000000,1.600000])rotate([0,0,-45.000000])m2(part,hole,block,casetop); // D108
};
module C25(){translate([-31.385129,6.242890,1.600000])rotate([0,0,168.750000])children();}
module part_C25(part=true,hole=false,block=false)
{
translate([-31.385129,6.242890,1.600000])rotate([0,0,168.750000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C44(){translate([3.528617,-35.826650,1.600000])rotate([0,0,-84.375000])children();}
module part_C44(part=true,hole=false,block=false)
{
translate([3.528617,-35.826650,1.600000])rotate([0,0,-84.375000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C11(){translate([-25.868627,10.715136,1.600000])rotate([0,0,157.500000])children();}
module part_C11(part=true,hole=false,block=false)
{
translate([-25.868627,10.715136,1.600000])rotate([0,0,157.500000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D16(){translate([29.564145,12.245870,1.600000])rotate([0,0,157.500000])children();}
module part_D16(part=true,hole=false,block=false)
{
translate([29.564145,12.245870,1.600000])rotate([0,0,157.500000])m2(part,hole,block,casetop); // D108
};
module D58(){translate([-20.000528,29.932906,1.600000])rotate([0,0,-101.250000])children();}
module part_D58(part=true,hole=false,block=false)
{
translate([-20.000528,29.932906,1.600000])rotate([0,0,-101.250000])m2(part,hole,block,casetop); // D108
};
module D109(){translate([-40.000000,0.000000,1.600000])rotate([0,0,-45.000000])children();}
module part_D109(part=true,hole=false,block=false)
{
translate([-40.000000,0.000000,1.600000])rotate([0,0,-45.000000])m2(part,hole,block,casetop); // D108
};
module D119(){translate([-22.222809,33.258784,1.600000])rotate([0,0,-101.250000])children();}
module part_D119(part=true,hole=false,block=false)
{
translate([-22.222809,33.258784,1.600000])rotate([0,0,-101.250000])m2(part,hole,block,casetop); // D108
};
module C68(){translate([26.862358,29.638045,1.600000])rotate([0,0,47.812500])children();}
module part_C68(part=true,hole=false,block=false)
{
translate([26.862358,29.638045,1.600000])rotate([0,0,47.812500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C35(){translate([34.449852,10.450248,1.600000])rotate([0,0,16.875000])children();}
module part_C35(part=true,hole=false,block=false)
{
translate([34.449852,10.450248,1.600000])rotate([0,0,16.875000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C122(){translate([-9.719207,38.801250,1.600000])rotate([0,0,104.062500])children();}
module part_C122(part=true,hole=false,block=false)
{
translate([-9.719207,38.801250,1.600000])rotate([0,0,104.062500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C114(){translate([-34.309144,20.564110,1.600000])rotate([0,0,149.062500])children();}
module part_C114(part=true,hole=false,block=false)
{
translate([-34.309144,20.564110,1.600000])rotate([0,0,149.062500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D63(){translate([7.803613,39.231411,1.600000])rotate([0,0,-146.250000])children();}
module part_D63(part=true,hole=false,block=false)
{
translate([7.803613,39.231411,1.600000])rotate([0,0,-146.250000])m2(part,hole,block,casetop); // D108
};
module C6(){translate([25.868627,10.715136,1.600000])rotate([0,0,22.500000])children();}
module part_C6(part=true,hole=false,block=false)
{
translate([25.868627,10.715136,1.600000])rotate([0,0,22.500000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C116(){translate([-29.638045,26.862358,1.600000])rotate([0,0,137.812500])children();}
module part_C116(part=true,hole=false,block=false)
{
translate([-29.638045,26.862358,1.600000])rotate([0,0,137.812500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D104(){translate([-35.276851,-18.855869,1.600000])rotate([0,0,-16.875000])children();}
module part_D104(part=true,hole=false,block=false)
{
translate([-35.276851,-18.855869,1.600000])rotate([0,0,-16.875000])m2(part,hole,block,casetop); // D108
};
module U3(){translate([-4.000000,-13.500000,1.600000])rotate([0,0,90.000000])children();}
module part_U3(part=true,hole=false,block=false)
{
translate([-4.000000,-13.500000,1.600000])rotate([0,0,90.000000])m4(part,hole,block,casetop); // RevK:SOT-23-6-MD8942 SOT-23-6 (back)
};
module C4(){translate([-16.970563,16.970563,1.600000])rotate([0,0,135.000000])children();}
module part_C4(part=true,hole=false,block=false)
{
translate([-16.970563,16.970563,1.600000])rotate([0,0,135.000000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D91(){translate([7.803613,-39.231411,1.600000])rotate([0,0,56.250000])children();}
module part_D91(part=true,hole=false,block=false)
{
translate([7.803613,-39.231411,1.600000])rotate([0,0,56.250000])m2(part,hole,block,casetop); // D108
};
module C110(){translate([-39.567060,5.869219,1.600000])rotate([0,0,171.562500])children();}
module part_C110(part=true,hole=false,block=false)
{
translate([-39.567060,5.869219,1.600000])rotate([0,0,171.562500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D102(){translate([-30.920418,-25.375731,1.600000])rotate([0,0,-5.625000])children();}
module part_D102(part=true,hole=false,block=false)
{
translate([-30.920418,-25.375731,1.600000])rotate([0,0,-5.625000])m2(part,hole,block,casetop); // D108
};
module D7(){translate([28.000000,0.000000,1.600000])rotate([0,0,135.000000])children();}
module part_D7(part=true,hole=false,block=false)
{
translate([28.000000,0.000000,1.600000])rotate([0,0,135.000000])m2(part,hole,block,casetop); // D108
};
module R4(){translate([-5.900000,-15.300000,1.600000])rotate([0,0,90.000000])children();}
module part_R4(part=true,hole=false,block=false)
{
translate([-5.900000,-15.300000,1.600000])rotate([0,0,90.000000])m5(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
};
module C113(){translate([-36.159572,17.102204,1.600000])rotate([0,0,154.687500])children();}
module part_C113(part=true,hole=false,block=false)
{
translate([-36.159572,17.102204,1.600000])rotate([0,0,154.687500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D17(){translate([32.000000,0.000000,1.600000])rotate([0,0,135.000000])children();}
module part_D17(part=true,hole=false,block=false)
{
translate([32.000000,0.000000,1.600000])rotate([0,0,135.000000])m2(part,hole,block,casetop); // D108
};
module D27(){translate([-22.627417,22.627417,1.600000])rotate([0,0,-90.000000])children();}
module part_D27(part=true,hole=false,block=false)
{
translate([-22.627417,22.627417,1.600000])rotate([0,0,-90.000000])m2(part,hole,block,casetop); // D108
};
module D32(){translate([20.000528,29.932906,1.600000])rotate([0,0,-168.750000])children();}
module part_D32(part=true,hole=false,block=false)
{
translate([20.000528,29.932906,1.600000])rotate([0,0,-168.750000])m2(part,hole,block,casetop); // D108
};
module C84(){translate([29.638045,-26.862358,1.600000])rotate([0,0,-42.187500])children();}
module part_C84(part=true,hole=false,block=false)
{
translate([29.638045,-26.862358,1.600000])rotate([0,0,-42.187500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C107(){translate([-39.567060,-5.869219,1.600000])rotate([0,0,-171.562500])children();}
module part_C107(part=true,hole=false,block=false)
{
translate([-39.567060,-5.869219,1.600000])rotate([0,0,-171.562500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D73(){translate([36.955181,15.307337,1.600000])rotate([0,0,157.500000])children();}
module part_D73(part=true,hole=false,block=false)
{
translate([36.955181,15.307337,1.600000])rotate([0,0,157.500000])m2(part,hole,block,casetop); // D108
};
module C1(){translate([16.970563,16.970563,1.600000])rotate([0,0,45.000000])children();}
module part_C1(part=true,hole=false,block=false)
{
translate([16.970563,16.970563,1.600000])rotate([0,0,45.000000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module U2(){translate([0.000000,0.000000,1.600000])rotate([0,0,90.000000])children();}
module part_U2(part=true,hole=false,block=false)
{
translate([0.000000,0.000000,1.600000])rotate([0,0,90.000000])m6(part,hole,block,casetop); // U2
};
module D100(){translate([-25.375731,-30.920418,1.600000])rotate([0,0,5.625000])children();}
module part_D100(part=true,hole=false,block=false)
{
translate([-25.375731,-30.920418,1.600000])rotate([0,0,5.625000])m2(part,hole,block,casetop); // D108
};
module D4(){translate([-24.000000,0.000000,1.600000])rotate([0,0,-45.000000])children();}
module part_D4(part=true,hole=false,block=false)
{
translate([-24.000000,0.000000,1.600000])rotate([0,0,-45.000000])m2(part,hole,block,casetop); // D108
};
module C115(){translate([-32.128301,23.827972,1.600000])rotate([0,0,143.437500])children();}
module part_C115(part=true,hole=false,block=false)
{
translate([-32.128301,23.827972,1.600000])rotate([0,0,143.437500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module L1(){translate([0.600000,-13.500000,1.600000])rotate([0,0,90.000000])children();}
module part_L1(part=true,hole=false,block=false)
{
translate([0.600000,-13.500000,1.600000])rotate([0,0,90.000000])scale([1.000000,1.000000,1.400000])rotate([0.000000,0.000000,-90.000000])m7(part,hole,block,casetop); // RevK:L_4x4_ TYA4020 (back)
};
module D36(){translate([35.308270,7.023252,1.600000])rotate([0,0,146.250000])children();}
module part_D36(part=true,hole=false,block=false)
{
translate([35.308270,7.023252,1.600000])rotate([0,0,146.250000])m2(part,hole,block,casetop); // D108
};
module D64(){translate([11.611387,38.277613,1.600000])rotate([0,0,-151.875000])children();}
module part_D64(part=true,hole=false,block=false)
{
translate([11.611387,38.277613,1.600000])rotate([0,0,-151.875000])m2(part,hole,block,casetop); // D108
};
module C43(){translate([10.450248,-34.449852,1.600000])rotate([0,0,-73.125000])children();}
module part_C43(part=true,hole=false,block=false)
{
translate([10.450248,-34.449852,1.600000])rotate([0,0,-73.125000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D40(){translate([29.932906,-20.000528,1.600000])rotate([0,0,101.250000])children();}
module part_D40(part=true,hole=false,block=false)
{
translate([29.932906,-20.000528,1.600000])rotate([0,0,101.250000])m2(part,hole,block,casetop); // D108
};
module D80(){translate([38.277613,-11.611387,1.600000])rotate([0,0,118.125000])children();}
module part_D80(part=true,hole=false,block=false)
{
translate([38.277613,-11.611387,1.600000])rotate([0,0,118.125000])m2(part,hole,block,casetop); // D108
};
module C37(){translate([35.826650,-3.528617,1.600000])rotate([0,0,-5.625000])children();}
module part_C37(part=true,hole=false,block=false)
{
translate([35.826650,-3.528617,1.600000])rotate([0,0,-5.625000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D48(){translate([-20.000528,-29.932906,1.600000])rotate([0,0,11.250000])children();}
module part_D48(part=true,hole=false,block=false)
{
translate([-20.000528,-29.932906,1.600000])rotate([0,0,11.250000])m2(part,hole,block,casetop); // D108
};
module C105(){translate([-37.661763,-13.475594,1.600000])rotate([0,0,-160.312500])children();}
module part_C105(part=true,hole=false,block=false)
{
translate([-37.661763,-13.475594,1.600000])rotate([0,0,-160.312500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module R3(){translate([-5.900000,-11.699999,1.600000])rotate([0,0,90.000000])children();}
module part_R3(part=true,hole=false,block=false)
{
translate([-5.900000,-11.699999,1.600000])rotate([0,0,90.000000])m5(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
};
module C2(){translate([16.970563,-16.970563,1.600000])rotate([0,0,-45.000000])children();}
module part_C2(part=true,hole=false,block=false)
{
translate([16.970563,-16.970563,1.600000])rotate([0,0,-45.000000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C130(){translate([7.000000,-13.500000,1.600000])rotate([0,0,-90.000000])children();}
module part_C130(part=true,hole=false,block=false)
{
translate([7.000000,-13.500000,1.600000])rotate([0,0,-90.000000])m3(part,hole,block,casetop); // RevK:C_0603 C_0603_1608Metric (back)
};
module C97(){translate([-17.102204,-36.159572,1.600000])rotate([0,0,-115.312500])children();}
module part_C97(part=true,hole=false,block=false)
{
translate([-17.102204,-36.159572,1.600000])rotate([0,0,-115.312500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D99(){translate([-22.222809,-33.258784,1.600000])rotate([0,0,11.250000])children();}
module part_D99(part=true,hole=false,block=false)
{
translate([-22.222809,-33.258784,1.600000])rotate([0,0,11.250000])m2(part,hole,block,casetop); // D108
};
module D116(){translate([-30.920418,25.375731,1.600000])rotate([0,0,-84.375000])children();}
module part_D116(part=true,hole=false,block=false)
{
translate([-30.920418,25.375731,1.600000])rotate([0,0,-84.375000])m2(part,hole,block,casetop); // D108
};
module PCB1(){translate([2.500000,0.000000,1.600000])children();}
module part_PCB1(part=true,hole=false,block=false)
{
};
module C17(){translate([31.385129,-6.242890,1.600000])rotate([0,0,-11.250000])children();}
module part_C17(part=true,hole=false,block=false)
{
translate([31.385129,-6.242890,1.600000])rotate([0,0,-11.250000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D15(){translate([22.627417,22.627417,1.600000])rotate([0,0,180.000000])children();}
module part_D15(part=true,hole=false,block=false)
{
translate([22.627417,22.627417,1.600000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // D108
};
module C76(){translate([39.951818,1.962707,1.600000])rotate([0,0,2.812500])children();}
module part_C76(part=true,hole=false,block=false)
{
translate([39.951818,1.962707,1.600000])rotate([0,0,2.812500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D98(){translate([-18.855869,-35.276851,1.600000])rotate([0,0,16.875000])children();}
module part_D98(part=true,hole=false,block=false)
{
translate([-18.855869,-35.276851,1.600000])rotate([0,0,16.875000])m2(part,hole,block,casetop); // D108
};
module D84(){translate([30.920418,-25.375731,1.600000])rotate([0,0,95.625000])children();}
module part_D84(part=true,hole=false,block=false)
{
translate([30.920418,-25.375731,1.600000])rotate([0,0,95.625000])m2(part,hole,block,casetop); // D108
};
module D72(){translate([35.276851,18.855869,1.600000])rotate([0,0,163.125000])children();}
module part_D72(part=true,hole=false,block=false)
{
translate([35.276851,18.855869,1.600000])rotate([0,0,163.125000])m2(part,hole,block,casetop); // D108
};
module D38(){translate([35.308270,-7.023252,1.600000])rotate([0,0,123.750000])children();}
module part_D38(part=true,hole=false,block=false)
{
translate([35.308270,-7.023252,1.600000])rotate([0,0,123.750000])m2(part,hole,block,casetop); // D108
};
module D105(){translate([-36.955181,-15.307337,1.600000])rotate([0,0,-22.500000])children();}
module part_D105(part=true,hole=false,block=false)
{
translate([-36.955181,-15.307337,1.600000])rotate([0,0,-22.500000])m2(part,hole,block,casetop); // D108
};
module C111(){translate([-38.801250,9.719207,1.600000])rotate([0,0,165.937500])children();}
module part_C111(part=true,hole=false,block=false)
{
translate([-38.801250,9.719207,1.600000])rotate([0,0,165.937500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D44(){translate([7.023252,-35.308270,1.600000])rotate([0,0,56.250000])children();}
module part_D44(part=true,hole=false,block=false)
{
translate([7.023252,-35.308270,1.600000])rotate([0,0,56.250000])m2(part,hole,block,casetop); // D108
};
module C88(){translate([17.102204,-36.159572,1.600000])rotate([0,0,-64.687500])children();}
module part_C88(part=true,hole=false,block=false)
{
translate([17.102204,-36.159572,1.600000])rotate([0,0,-64.687500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D106(){translate([-38.277613,-11.611387,1.600000])rotate([0,0,-28.125000])children();}
module part_D106(part=true,hole=false,block=false)
{
translate([-38.277613,-11.611387,1.600000])rotate([0,0,-28.125000])m2(part,hole,block,casetop); // D108
};
module D11(){translate([-28.000000,0.000000,1.600000])rotate([0,0,-45.000000])children();}
module part_D11(part=true,hole=false,block=false)
{
translate([-28.000000,0.000000,1.600000])rotate([0,0,-45.000000])m2(part,hole,block,casetop); // D108
};
module C95(){translate([-9.719207,-38.801250,1.600000])rotate([0,0,-104.062500])children();}
module part_C95(part=true,hole=false,block=false)
{
translate([-9.719207,-38.801250,1.600000])rotate([0,0,-104.062500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C86(){translate([23.827972,-32.128301,1.600000])rotate([0,0,-53.437500])children();}
module part_C86(part=true,hole=false,block=false)
{
translate([23.827972,-32.128301,1.600000])rotate([0,0,-53.437500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D77(){translate([40.000000,0.000000,1.600000])rotate([0,0,135.000000])children();}
module part_D77(part=true,hole=false,block=false)
{
translate([40.000000,0.000000,1.600000])rotate([0,0,135.000000])m2(part,hole,block,casetop); // D108
};
module D90(){translate([11.611387,-38.277613,1.600000])rotate([0,0,61.875000])children();}
module part_D90(part=true,hole=false,block=false)
{
translate([11.611387,-38.277613,1.600000])rotate([0,0,61.875000])m2(part,hole,block,casetop); // D108
};
module D112(){translate([-38.277613,11.611387,1.600000])rotate([0,0,-61.875000])children();}
module part_D112(part=true,hole=false,block=false)
{
translate([-38.277613,11.611387,1.600000])rotate([0,0,-61.875000])m2(part,hole,block,casetop); // D108
};
module D107(){translate([-39.231411,-7.803613,1.600000])rotate([0,0,-33.750000])children();}
module part_D107(part=true,hole=false,block=false)
{
translate([-39.231411,-7.803613,1.600000])rotate([0,0,-33.750000])m2(part,hole,block,casetop); // D108
};
module D68(){translate([25.375731,30.920418,1.600000])rotate([0,0,-174.375000])children();}
module part_D68(part=true,hole=false,block=false)
{
translate([25.375731,30.920418,1.600000])rotate([0,0,-174.375000])m2(part,hole,block,casetop); // D108
};
module C121(){translate([-13.475594,37.661763,1.600000])rotate([0,0,109.687500])children();}
module part_C121(part=true,hole=false,block=false)
{
translate([-13.475594,37.661763,1.600000])rotate([0,0,109.687500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C101(){translate([-29.638045,-26.862358,1.600000])rotate([0,0,-137.812500])children();}
module part_C101(part=true,hole=false,block=false)
{
translate([-29.638045,-26.862358,1.600000])rotate([0,0,-137.812500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C112(){translate([-37.661763,13.475594,1.600000])rotate([0,0,160.312500])children();}
module part_C112(part=true,hole=false,block=false)
{
translate([-37.661763,13.475594,1.600000])rotate([0,0,160.312500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C29(){translate([3.528617,35.826650,1.600000])rotate([0,0,84.375000])children();}
module part_C29(part=true,hole=false,block=false)
{
translate([3.528617,35.826650,1.600000])rotate([0,0,84.375000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C56(){translate([-27.828376,22.838158,1.600000])rotate([0,0,140.625000])children();}
module part_C56(part=true,hole=false,block=false)
{
translate([-27.828376,22.838158,1.600000])rotate([0,0,140.625000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C134(){translate([-6.500000,8.500000,1.600000])rotate([0,0,180.000000])children();}
module part_C134(part=true,hole=false,block=false)
{
translate([-6.500000,8.500000,1.600000])rotate([0,0,180.000000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C118(){translate([-23.827972,32.128301,1.600000])rotate([0,0,126.562500])children();}
module part_C118(part=true,hole=false,block=false)
{
translate([-23.827972,32.128301,1.600000])rotate([0,0,126.562500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D49(){translate([-25.455844,-25.455844,1.600000])children();}
module part_D49(part=true,hole=false,block=false)
{
translate([-25.455844,-25.455844,1.600000])m2(part,hole,block,casetop); // D108
};
module C19(){translate([17.778247,-26.607028,1.600000])rotate([0,0,-56.250000])children();}
module part_C19(part=true,hole=false,block=false)
{
translate([17.778247,-26.607028,1.600000])rotate([0,0,-56.250000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C66(){translate([20.564110,34.309144,1.600000])rotate([0,0,59.062500])children();}
module part_C66(part=true,hole=false,block=false)
{
translate([20.564110,34.309144,1.600000])rotate([0,0,59.062500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C38(){translate([34.449852,-10.450248,1.600000])rotate([0,0,-16.875000])children();}
module part_C38(part=true,hole=false,block=false)
{
translate([34.449852,-10.450248,1.600000])rotate([0,0,-16.875000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D78(){translate([39.807389,-3.920686,1.600000])rotate([0,0,129.375000])children();}
module part_D78(part=true,hole=false,block=false)
{
translate([39.807389,-3.920686,1.600000])rotate([0,0,129.375000])m2(part,hole,block,casetop); // D108
};
module C48(){translate([-22.838158,-27.828376,1.600000])rotate([0,0,-129.375000])children();}
module part_C48(part=true,hole=false,block=false)
{
translate([-22.838158,-27.828376,1.600000])rotate([0,0,-129.375000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module R6(){translate([40.900000,6.100000,1.600000])rotate([0,0,-81.699000])children();}
module part_R6(part=true,hole=false,block=false)
{
translate([40.900000,6.100000,1.600000])rotate([0,0,-81.699000])m5(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
};
module C136(){translate([8.250000,-13.500000,1.600000])rotate([0,0,-90.000000])children();}
module part_C136(part=true,hole=false,block=false)
{
translate([8.250000,-13.500000,1.600000])rotate([0,0,-90.000000])m3(part,hole,block,casetop); // RevK:C_0603 C_0603_1608Metric (back)
};
module C61(){translate([1.962707,39.951818,1.600000])rotate([0,0,87.187500])children();}
module part_C61(part=true,hole=false,block=false)
{
translate([1.962707,39.951818,1.600000])rotate([0,0,87.187500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D45(){translate([0.000000,-36.000000,1.600000])rotate([0,0,45.000000])children();}
module part_D45(part=true,hole=false,block=false)
{
translate([0.000000,-36.000000,1.600000])rotate([0,0,45.000000])m2(part,hole,block,casetop); // D108
};
module R1(){translate([-4.500000,8.500000,1.600000])rotate([0,0,180.000000])children();}
module part_R1(part=true,hole=false,block=false)
{
translate([-4.500000,8.500000,1.600000])rotate([0,0,180.000000])m5(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
};
module D47(){translate([-13.776604,-33.259663,1.600000])rotate([0,0,22.500000])children();}
module part_D47(part=true,hole=false,block=false)
{
translate([-13.776604,-33.259663,1.600000])rotate([0,0,22.500000])m2(part,hole,block,casetop); // D108
};
module C30(){translate([10.450248,34.449852,1.600000])rotate([0,0,73.125000])children();}
module part_C30(part=true,hole=false,block=false)
{
translate([10.450248,34.449852,1.600000])rotate([0,0,73.125000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D81(){translate([36.955181,-15.307337,1.600000])rotate([0,0,112.500000])children();}
module part_D81(part=true,hole=false,block=false)
{
translate([36.955181,-15.307337,1.600000])rotate([0,0,112.500000])m2(part,hole,block,casetop); // D108
};
module C31(){translate([16.970283,31.749166,1.600000])rotate([0,0,61.875000])children();}
module part_C31(part=true,hole=false,block=false)
{
translate([16.970283,31.749166,1.600000])rotate([0,0,61.875000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C137(){translate([-2.700000,-16.000000,1.600000])rotate([0,0,180.000000])children();}
module part_C137(part=true,hole=false,block=false)
{
translate([-2.700000,-16.000000,1.600000])rotate([0,0,180.000000])m3(part,hole,block,casetop); // RevK:C_0603 C_0603_1608Metric (back)
};
module D123(){translate([-7.803613,39.231411,1.600000])rotate([0,0,-123.750000])children();}
module part_D123(part=true,hole=false,block=false)
{
translate([-7.803613,39.231411,1.600000])rotate([0,0,-123.750000])m2(part,hole,block,casetop); // D108
};
module C3(){translate([-16.970563,-16.970563,1.600000])rotate([0,0,-135.000000])children();}
module part_C3(part=true,hole=false,block=false)
{
translate([-16.970563,-16.970563,1.600000])rotate([0,0,-135.000000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C69(){translate([29.638045,26.862358,1.600000])rotate([0,0,42.187500])children();}
module part_C69(part=true,hole=false,block=false)
{
translate([29.638045,26.862358,1.600000])rotate([0,0,42.187500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D10(){translate([-19.798990,-19.798990,1.600000])children();}
module part_D10(part=true,hole=false,block=false)
{
translate([-19.798990,-19.798990,1.600000])m2(part,hole,block,casetop); // D108
};
module C131(){translate([4.500000,-13.500000,1.600000])rotate([0,0,90.000000])children();}
module part_C131(part=true,hole=false,block=false)
{
translate([4.500000,-13.500000,1.600000])rotate([0,0,90.000000])m8(part,hole,block,casetop); // C131
};
module C133(){translate([17.000000,3.000000,1.600000])children();}
module part_C133(part=true,hole=false,block=false)
{
translate([17.000000,3.000000,1.600000])m3(part,hole,block,casetop); // RevK:C_0603 C_0603_1608Metric (back)
};
module D13(){translate([0.000000,32.000000,1.600000])rotate([0,0,-135.000000])children();}
module part_D13(part=true,hole=false,block=false)
{
translate([0.000000,32.000000,1.600000])rotate([0,0,-135.000000])m2(part,hole,block,casetop); // D108
};
module D85(){translate([28.284271,-28.284271,1.600000])rotate([0,0,90.000000])children();}
module part_D85(part=true,hole=false,block=false)
{
translate([28.284271,-28.284271,1.600000])rotate([0,0,90.000000])m2(part,hole,block,casetop); // D108
};
module C67(){translate([23.827972,32.128301,1.600000])rotate([0,0,53.437500])children();}
module part_C67(part=true,hole=false,block=false)
{
translate([23.827972,32.128301,1.600000])rotate([0,0,53.437500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D41(){translate([25.455844,-25.455844,1.600000])rotate([0,0,90.000000])children();}
module part_D41(part=true,hole=false,block=false)
{
translate([25.455844,-25.455844,1.600000])rotate([0,0,90.000000])m2(part,hole,block,casetop); // D108
};
module C83(){translate([32.128301,-23.827972,1.600000])rotate([0,0,-36.562500])children();}
module part_C83(part=true,hole=false,block=false)
{
translate([32.128301,-23.827972,1.600000])rotate([0,0,-36.562500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C59(){translate([-10.450248,34.449852,1.600000])rotate([0,0,106.875000])children();}
module part_C59(part=true,hole=false,block=false)
{
translate([-10.450248,34.449852,1.600000])rotate([0,0,106.875000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D23(){translate([-22.627417,-22.627417,1.600000])children();}
module part_D23(part=true,hole=false,block=false)
{
translate([-22.627417,-22.627417,1.600000])m2(part,hole,block,casetop); // D108
};
module C109(){translate([-39.951818,1.962707,1.600000])rotate([0,0,177.187500])children();}
module part_C109(part=true,hole=false,block=false)
{
translate([-39.951818,1.962707,1.600000])rotate([0,0,177.187500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D29(){translate([0.000000,36.000000,1.600000])rotate([0,0,-135.000000])children();}
module part_D29(part=true,hole=false,block=false)
{
translate([0.000000,36.000000,1.600000])rotate([0,0,-135.000000])m2(part,hole,block,casetop); // D108
};
module D24(){translate([-29.564145,-12.245870,1.600000])rotate([0,0,-22.500000])children();}
module part_D24(part=true,hole=false,block=false)
{
translate([-29.564145,-12.245870,1.600000])rotate([0,0,-22.500000])m2(part,hole,block,casetop); // D108
};
module D55(){translate([-33.259663,13.776604,1.600000])rotate([0,0,-67.500000])children();}
module part_D55(part=true,hole=false,block=false)
{
translate([-33.259663,13.776604,1.600000])rotate([0,0,-67.500000])m2(part,hole,block,casetop); // D108
};
module C87(){translate([20.564110,-34.309144,1.600000])rotate([0,0,-59.062500])children();}
module part_C87(part=true,hole=false,block=false)
{
translate([20.564110,-34.309144,1.600000])rotate([0,0,-59.062500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C18(){translate([26.607028,-17.778247,1.600000])rotate([0,0,-33.750000])children();}
module part_C18(part=true,hole=false,block=false)
{
translate([26.607028,-17.778247,1.600000])rotate([0,0,-33.750000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C33(){translate([27.828376,22.838158,1.600000])rotate([0,0,39.375000])children();}
module part_C33(part=true,hole=false,block=false)
{
translate([27.828376,22.838158,1.600000])rotate([0,0,39.375000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C9(){translate([-10.715136,-25.868627,1.600000])rotate([0,0,-112.500000])children();}
module part_C9(part=true,hole=false,block=false)
{
translate([-10.715136,-25.868627,1.600000])rotate([0,0,-112.500000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C58(){translate([-16.970283,31.749166,1.600000])rotate([0,0,118.125000])children();}
module part_C58(part=true,hole=false,block=false)
{
translate([-16.970283,31.749166,1.600000])rotate([0,0,118.125000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C12(){translate([-10.715136,25.868627,1.600000])rotate([0,0,112.500000])children();}
module part_C12(part=true,hole=false,block=false)
{
translate([-10.715136,25.868627,1.600000])rotate([0,0,112.500000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D89(){translate([15.307337,-36.955181,1.600000])rotate([0,0,67.500000])children();}
module part_D89(part=true,hole=false,block=false)
{
translate([15.307337,-36.955181,1.600000])rotate([0,0,67.500000])m2(part,hole,block,casetop); // D108
};
module C27(){translate([-17.778247,26.607028,1.600000])rotate([0,0,123.750000])children();}
module part_C27(part=true,hole=false,block=false)
{
translate([-17.778247,26.607028,1.600000])rotate([0,0,123.750000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D70(){translate([30.920418,25.375731,1.600000])rotate([0,0,174.375000])children();}
module part_D70(part=true,hole=false,block=false)
{
translate([30.920418,25.375731,1.600000])rotate([0,0,174.375000])m2(part,hole,block,casetop); // D108
};
module D121(){translate([-15.307337,36.955181,1.600000])rotate([0,0,-112.500000])children();}
module part_D121(part=true,hole=false,block=false)
{
translate([-15.307337,36.955181,1.600000])rotate([0,0,-112.500000])m2(part,hole,block,casetop); // D108
};
module C106(){translate([-38.801250,-9.719207,1.600000])rotate([0,0,-165.937500])children();}
module part_C106(part=true,hole=false,block=false)
{
translate([-38.801250,-9.719207,1.600000])rotate([0,0,-165.937500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C20(){translate([6.242890,-31.385129,1.600000])rotate([0,0,-78.750000])children();}
module part_C20(part=true,hole=false,block=false)
{
translate([6.242890,-31.385129,1.600000])rotate([0,0,-78.750000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D115(){translate([-33.258784,22.222809,1.600000])rotate([0,0,-78.750000])children();}
module part_D115(part=true,hole=false,block=false)
{
translate([-33.258784,22.222809,1.600000])rotate([0,0,-78.750000])m2(part,hole,block,casetop); // D108
};
module V2(){translate([2.500000,-49.910244,1.600000])rotate([0,0,180.000000])children();}
module part_V2(part=true,hole=false,block=false)
{
};
module D18(){translate([29.564145,-12.245870,1.600000])rotate([0,0,112.500000])children();}
module part_D18(part=true,hole=false,block=false)
{
translate([29.564145,-12.245870,1.600000])rotate([0,0,112.500000])m2(part,hole,block,casetop); // D108
};
module C42(){translate([16.970283,-31.749166,1.600000])rotate([0,0,-61.875000])children();}
module part_C42(part=true,hole=false,block=false)
{
translate([16.970283,-31.749166,1.600000])rotate([0,0,-61.875000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C49(){translate([-27.828376,-22.838158,1.600000])rotate([0,0,-140.625000])children();}
module part_C49(part=true,hole=false,block=false)
{
translate([-27.828376,-22.838158,1.600000])rotate([0,0,-140.625000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D88(){translate([18.855869,-35.276851,1.600000])rotate([0,0,73.125000])children();}
module part_D88(part=true,hole=false,block=false)
{
translate([18.855869,-35.276851,1.600000])rotate([0,0,73.125000])m2(part,hole,block,casetop); // D108
};
module D9(){translate([0.000000,-28.000000,1.600000])rotate([0,0,45.000000])children();}
module part_D9(part=true,hole=false,block=false)
{
translate([0.000000,-28.000000,1.600000])rotate([0,0,45.000000])m2(part,hole,block,casetop); // D108
};
module C108(){translate([-39.951818,-1.962707,1.600000])rotate([0,0,-177.187500])children();}
module part_C108(part=true,hole=false,block=false)
{
translate([-39.951818,-1.962707,1.600000])rotate([0,0,-177.187500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C46(){translate([-10.450248,-34.449852,1.600000])rotate([0,0,-106.875000])children();}
module part_C46(part=true,hole=false,block=false)
{
translate([-10.450248,-34.449852,1.600000])rotate([0,0,-106.875000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C120(){translate([-17.102204,36.159572,1.600000])rotate([0,0,115.312500])children();}
module part_C120(part=true,hole=false,block=false)
{
translate([-17.102204,36.159572,1.600000])rotate([0,0,115.312500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C124(){translate([-1.962707,39.951818,1.600000])rotate([0,0,92.812500])children();}
module part_C124(part=true,hole=false,block=false)
{
translate([-1.962707,39.951818,1.600000])rotate([0,0,92.812500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D67(){translate([22.222809,33.258784,1.600000])rotate([0,0,-168.750000])children();}
module part_D67(part=true,hole=false,block=false)
{
translate([22.222809,33.258784,1.600000])rotate([0,0,-168.750000])m2(part,hole,block,casetop); // D108
};
module D5(){translate([0.000000,28.000000,1.600000])rotate([0,0,-135.000000])children();}
module part_D5(part=true,hole=false,block=false)
{
translate([0.000000,28.000000,1.600000])rotate([0,0,-135.000000])m2(part,hole,block,casetop); // D108
};
module D6(){translate([19.798990,19.798990,1.600000])rotate([0,0,180.000000])children();}
module part_D6(part=true,hole=false,block=false)
{
translate([19.798990,19.798990,1.600000])rotate([0,0,180.000000])m2(part,hole,block,casetop); // D108
};
module C57(){translate([-22.838158,27.828376,1.600000])rotate([0,0,129.375000])children();}
module part_C57(part=true,hole=false,block=false)
{
translate([-22.838158,27.828376,1.600000])rotate([0,0,129.375000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D12(){translate([-19.798990,19.798990,1.600000])rotate([0,0,-90.000000])children();}
module part_D12(part=true,hole=false,block=false)
{
translate([-19.798990,19.798990,1.600000])rotate([0,0,-90.000000])m2(part,hole,block,casetop); // D108
};
module C80(){translate([37.661763,-13.475594,1.600000])rotate([0,0,-19.687500])children();}
module part_C80(part=true,hole=false,block=false)
{
translate([37.661763,-13.475594,1.600000])rotate([0,0,-19.687500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C90(){translate([9.719207,-38.801250,1.600000])rotate([0,0,-75.937500])children();}
module part_C90(part=true,hole=false,block=false)
{
translate([9.719207,-38.801250,1.600000])rotate([0,0,-75.937500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C94(){translate([-5.869219,-39.567060,1.600000])rotate([0,0,-98.437500])children();}
module part_C94(part=true,hole=false,block=false)
{
translate([-5.869219,-39.567060,1.600000])rotate([0,0,-98.437500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D83(){translate([33.258784,-22.222809,1.600000])rotate([0,0,101.250000])children();}
module part_D83(part=true,hole=false,block=false)
{
translate([33.258784,-22.222809,1.600000])rotate([0,0,101.250000])m2(part,hole,block,casetop); // D108
};
module D25(){translate([-32.000000,0.000000,1.600000])rotate([0,0,-45.000000])children();}
module part_D25(part=true,hole=false,block=false)
{
translate([-32.000000,0.000000,1.600000])rotate([0,0,-45.000000])m2(part,hole,block,casetop); // D108
};
module C32(){translate([22.838158,27.828376,1.600000])rotate([0,0,50.625000])children();}
module part_C32(part=true,hole=false,block=false)
{
translate([22.838158,27.828376,1.600000])rotate([0,0,50.625000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D56(){translate([-29.932906,20.000528,1.600000])rotate([0,0,-78.750000])children();}
module part_D56(part=true,hole=false,block=false)
{
translate([-29.932906,20.000528,1.600000])rotate([0,0,-78.750000])m2(part,hole,block,casetop); // D108
};
module D95(){translate([-7.803613,-39.231411,1.600000])rotate([0,0,33.750000])children();}
module part_D95(part=true,hole=false,block=false)
{
translate([-7.803613,-39.231411,1.600000])rotate([0,0,33.750000])m2(part,hole,block,casetop); // D108
};
module D94(){translate([-3.920686,-39.807389,1.600000])rotate([0,0,39.375000])children();}
module part_D94(part=true,hole=false,block=false)
{
translate([-3.920686,-39.807389,1.600000])rotate([0,0,39.375000])m2(part,hole,block,casetop); // D108
};
module C63(){translate([9.719207,38.801250,1.600000])rotate([0,0,75.937500])children();}
module part_C63(part=true,hole=false,block=false)
{
translate([9.719207,38.801250,1.600000])rotate([0,0,75.937500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D22(){translate([-12.245870,-29.564145,1.600000])rotate([0,0,22.500000])children();}
module part_D22(part=true,hole=false,block=false)
{
translate([-12.245870,-29.564145,1.600000])rotate([0,0,22.500000])m2(part,hole,block,casetop); // D108
};
module C100(){translate([-26.862358,-29.638045,1.600000])rotate([0,0,-132.187500])children();}
module part_C100(part=true,hole=false,block=false)
{
translate([-26.862358,-29.638045,1.600000])rotate([0,0,-132.187500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C129(){translate([-3.500000,-8.500000,1.600000])children();}
module part_C129(part=true,hole=false,block=false)
{
translate([-3.500000,-8.500000,1.600000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D101(){translate([-28.284271,-28.284271,1.600000])children();}
module part_D101(part=true,hole=false,block=false)
{
translate([-28.284271,-28.284271,1.600000])m2(part,hole,block,casetop); // D108
};
module C70(){translate([32.128301,23.827972,1.600000])rotate([0,0,36.562500])children();}
module part_C70(part=true,hole=false,block=false)
{
translate([32.128301,23.827972,1.600000])rotate([0,0,36.562500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D120(){translate([-18.855869,35.276851,1.600000])rotate([0,0,-106.875000])children();}
module part_D120(part=true,hole=false,block=false)
{
translate([-18.855869,35.276851,1.600000])rotate([0,0,-106.875000])m2(part,hole,block,casetop); // D108
};
module C24(){translate([-31.385129,-6.242890,1.600000])rotate([0,0,-168.750000])children();}
module part_C24(part=true,hole=false,block=false)
{
translate([-31.385129,-6.242890,1.600000])rotate([0,0,-168.750000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D50(){translate([-29.932906,-20.000528,1.600000])rotate([0,0,-11.250000])children();}
module part_D50(part=true,hole=false,block=false)
{
translate([-29.932906,-20.000528,1.600000])rotate([0,0,-11.250000])m2(part,hole,block,casetop); // D108
};
module D26(){translate([-29.564145,12.245870,1.600000])rotate([0,0,-67.500000])children();}
module part_D26(part=true,hole=false,block=false)
{
translate([-29.564145,12.245870,1.600000])rotate([0,0,-67.500000])m2(part,hole,block,casetop); // D108
};
module D57(){translate([-25.455844,25.455844,1.600000])rotate([0,0,-90.000000])children();}
module part_D57(part=true,hole=false,block=false)
{
translate([-25.455844,25.455844,1.600000])rotate([0,0,-90.000000])m2(part,hole,block,casetop); // D108
};
module C62(){translate([5.869219,39.567060,1.600000])rotate([0,0,81.562500])children();}
module part_C62(part=true,hole=false,block=false)
{
translate([5.869219,39.567060,1.600000])rotate([0,0,81.562500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D79(){translate([39.231411,-7.803613,1.600000])rotate([0,0,123.750000])children();}
module part_D79(part=true,hole=false,block=false)
{
translate([39.231411,-7.803613,1.600000])rotate([0,0,123.750000])m2(part,hole,block,casetop); // D108
};
module D96(){translate([-11.611387,-38.277613,1.600000])rotate([0,0,28.125000])children();}
module part_D96(part=true,hole=false,block=false)
{
translate([-11.611387,-38.277613,1.600000])rotate([0,0,28.125000])m2(part,hole,block,casetop); // D108
};
module C15(){translate([26.607028,17.778247,1.600000])rotate([0,0,33.750000])children();}
module part_C15(part=true,hole=false,block=false)
{
translate([26.607028,17.778247,1.600000])rotate([0,0,33.750000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D92(){translate([3.920686,-39.807389,1.600000])rotate([0,0,50.625000])children();}
module part_D92(part=true,hole=false,block=false)
{
translate([3.920686,-39.807389,1.600000])rotate([0,0,50.625000])m2(part,hole,block,casetop); // D108
};
module D66(){translate([18.855869,35.276851,1.600000])rotate([0,0,-163.125000])children();}
module part_D66(part=true,hole=false,block=false)
{
translate([18.855869,35.276851,1.600000])rotate([0,0,-163.125000])m2(part,hole,block,casetop); // D108
};
module C81(){translate([36.159572,-17.102204,1.600000])rotate([0,0,-25.312500])children();}
module part_C81(part=true,hole=false,block=false)
{
translate([36.159572,-17.102204,1.600000])rotate([0,0,-25.312500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C51(){translate([-34.449852,-10.450248,1.600000])rotate([0,0,-163.125000])children();}
module part_C51(part=true,hole=false,block=false)
{
translate([-34.449852,-10.450248,1.600000])rotate([0,0,-163.125000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module V1(){translate([2.500000,49.910242,1.600000])children();}
module part_V1(part=true,hole=false,block=false)
{
};
module C102(){translate([-32.128301,-23.827972,1.600000])rotate([0,0,-143.437500])children();}
module part_C102(part=true,hole=false,block=false)
{
translate([-32.128301,-23.827972,1.600000])rotate([0,0,-143.437500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C23(){translate([-26.607028,-17.778247,1.600000])rotate([0,0,-146.250000])children();}
module part_C23(part=true,hole=false,block=false)
{
translate([-26.607028,-17.778247,1.600000])rotate([0,0,-146.250000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D117(){translate([-28.284271,28.284271,1.600000])rotate([0,0,-90.000000])children();}
module part_D117(part=true,hole=false,block=false)
{
translate([-28.284271,28.284271,1.600000])rotate([0,0,-90.000000])m2(part,hole,block,casetop); // D108
};
module D2(){translate([24.000000,0.000000,1.600000])rotate([0,0,135.000000])children();}
module part_D2(part=true,hole=false,block=false)
{
translate([24.000000,0.000000,1.600000])rotate([0,0,135.000000])m2(part,hole,block,casetop); // D108
};
module D51(){translate([-33.259663,-13.776604,1.600000])rotate([0,0,-22.500000])children();}
module part_D51(part=true,hole=false,block=false)
{
translate([-33.259663,-13.776604,1.600000])rotate([0,0,-22.500000])m2(part,hole,block,casetop); // D108
};
module D62(){translate([3.920686,39.807389,1.600000])rotate([0,0,-140.625000])children();}
module part_D62(part=true,hole=false,block=false)
{
translate([3.920686,39.807389,1.600000])rotate([0,0,-140.625000])m2(part,hole,block,casetop); // D108
};
module C7(){translate([25.868627,-10.715136,1.600000])rotate([0,0,-22.500000])children();}
module part_C7(part=true,hole=false,block=false)
{
translate([25.868627,-10.715136,1.600000])rotate([0,0,-22.500000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module U1(){translate([0.000000,17.500000,1.600000])rotate([0,0,90.000000])children();}
module part_U1(part=true,hole=false,block=false)
{
translate([0.000000,17.500000,1.600000])rotate([0,0,90.000000])m9(part,hole,block,casetop); // U1
};
module C123(){translate([-5.869219,39.567060,1.600000])rotate([0,0,98.437500])children();}
module part_C123(part=true,hole=false,block=false)
{
translate([-5.869219,39.567060,1.600000])rotate([0,0,98.437500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D74(){translate([38.277613,11.611387,1.600000])rotate([0,0,151.875000])children();}
module part_D74(part=true,hole=false,block=false)
{
translate([38.277613,11.611387,1.600000])rotate([0,0,151.875000])m2(part,hole,block,casetop); // D108
};
module D59(){translate([-13.776604,33.259663,1.600000])rotate([0,0,-112.500000])children();}
module part_D59(part=true,hole=false,block=false)
{
translate([-13.776604,33.259663,1.600000])rotate([0,0,-112.500000])m2(part,hole,block,casetop); // D108
};
module D21(){translate([0.000000,-32.000000,1.600000])rotate([0,0,45.000000])children();}
module part_D21(part=true,hole=false,block=false)
{
translate([0.000000,-32.000000,1.600000])rotate([0,0,45.000000])m2(part,hole,block,casetop); // D108
};
module D14(){translate([12.245870,29.564145,1.600000])rotate([0,0,-157.500000])children();}
module part_D14(part=true,hole=false,block=false)
{
translate([12.245870,29.564145,1.600000])rotate([0,0,-157.500000])m2(part,hole,block,casetop); // D108
};
module D39(){translate([33.259663,-13.776604,1.600000])rotate([0,0,112.500000])children();}
module part_D39(part=true,hole=false,block=false)
{
translate([33.259663,-13.776604,1.600000])rotate([0,0,112.500000])m2(part,hole,block,casetop); // D108
};
module R2(){translate([-5.900000,-13.500000,1.600000])rotate([0,0,90.000000])children();}
module part_R2(part=true,hole=false,block=false)
{
translate([-5.900000,-13.500000,1.600000])rotate([0,0,90.000000])m5(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
};
module C79(){translate([38.801250,-9.719207,1.600000])rotate([0,0,-14.062500])children();}
module part_C79(part=true,hole=false,block=false)
{
translate([38.801250,-9.719207,1.600000])rotate([0,0,-14.062500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C98(){translate([-20.564110,-34.309144,1.600000])rotate([0,0,-120.937500])children();}
module part_C98(part=true,hole=false,block=false)
{
translate([-20.564110,-34.309144,1.600000])rotate([0,0,-120.937500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D118(){translate([-25.375731,30.920418,1.600000])rotate([0,0,-95.625000])children();}
module part_D118(part=true,hole=false,block=false)
{
translate([-25.375731,30.920418,1.600000])rotate([0,0,-95.625000])m2(part,hole,block,casetop); // D108
};
module D87(){translate([22.222809,-33.258784,1.600000])rotate([0,0,78.750000])children();}
module part_D87(part=true,hole=false,block=false)
{
translate([22.222809,-33.258784,1.600000])rotate([0,0,78.750000])m2(part,hole,block,casetop); // D108
};
module C52(){translate([-35.826650,-3.528617,1.600000])rotate([0,0,-174.375000])children();}
module part_C52(part=true,hole=false,block=false)
{
translate([-35.826650,-3.528617,1.600000])rotate([0,0,-174.375000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D61(){translate([0.000000,40.000000,1.600000])rotate([0,0,-135.000000])children();}
module part_D61(part=true,hole=false,block=false)
{
translate([0.000000,40.000000,1.600000])rotate([0,0,-135.000000])m2(part,hole,block,casetop); // D108
};
module C117(){translate([-26.862358,29.638045,1.600000])rotate([0,0,132.187500])children();}
module part_C117(part=true,hole=false,block=false)
{
translate([-26.862358,29.638045,1.600000])rotate([0,0,132.187500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C91(){translate([5.869219,-39.567060,1.600000])rotate([0,0,-81.562500])children();}
module part_C91(part=true,hole=false,block=false)
{
translate([5.869219,-39.567060,1.600000])rotate([0,0,-81.562500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D122(){translate([-11.611387,38.277613,1.600000])rotate([0,0,-118.125000])children();}
module part_D122(part=true,hole=false,block=false)
{
translate([-11.611387,38.277613,1.600000])rotate([0,0,-118.125000])m2(part,hole,block,casetop); // D108
};
module D3(){translate([0.000000,-24.000000,1.600000])rotate([0,0,45.000000])children();}
module part_D3(part=true,hole=false,block=false)
{
translate([0.000000,-24.000000,1.600000])rotate([0,0,45.000000])m2(part,hole,block,casetop); // D108
};
module D110(){translate([-39.807389,3.920686,1.600000])rotate([0,0,-50.625000])children();}
module part_D110(part=true,hole=false,block=false)
{
translate([-39.807389,3.920686,1.600000])rotate([0,0,-50.625000])m2(part,hole,block,casetop); // D108
};
module D30(){translate([7.023252,35.308270,1.600000])rotate([0,0,-146.250000])children();}
module part_D30(part=true,hole=false,block=false)
{
translate([7.023252,35.308270,1.600000])rotate([0,0,-146.250000])m2(part,hole,block,casetop); // D108
};
module C5(){translate([10.715136,25.868627,1.600000])rotate([0,0,67.500000])children();}
module part_C5(part=true,hole=false,block=false)
{
translate([10.715136,25.868627,1.600000])rotate([0,0,67.500000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D65(){translate([15.307337,36.955181,1.600000])rotate([0,0,-157.500000])children();}
module part_D65(part=true,hole=false,block=false)
{
translate([15.307337,36.955181,1.600000])rotate([0,0,-157.500000])m2(part,hole,block,casetop); // D108
};
module C47(){translate([-16.970283,-31.749166,1.600000])rotate([0,0,-118.125000])children();}
module part_C47(part=true,hole=false,block=false)
{
translate([-16.970283,-31.749166,1.600000])rotate([0,0,-118.125000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D82(){translate([35.276851,-18.855869,1.600000])rotate([0,0,106.875000])children();}
module part_D82(part=true,hole=false,block=false)
{
translate([35.276851,-18.855869,1.600000])rotate([0,0,106.875000])m2(part,hole,block,casetop); // D108
};
module C39(){translate([31.749166,-16.970283,1.600000])rotate([0,0,-28.125000])children();}
module part_C39(part=true,hole=false,block=false)
{
translate([31.749166,-16.970283,1.600000])rotate([0,0,-28.125000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C40(){translate([27.828376,-22.838158,1.600000])rotate([0,0,-39.375000])children();}
module part_C40(part=true,hole=false,block=false)
{
translate([27.828376,-22.838158,1.600000])rotate([0,0,-39.375000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module R5(){translate([40.900000,-6.100000,1.600000])rotate([0,0,-98.300000])children();}
module part_R5(part=true,hole=false,block=false)
{
translate([40.900000,-6.100000,1.600000])rotate([0,0,-98.300000])m5(part,hole,block,casetop); // RevK:R_0402_ R_0402_1005Metric (back)
};
module D54(){translate([-35.308270,7.023252,1.600000])rotate([0,0,-56.250000])children();}
module part_D54(part=true,hole=false,block=false)
{
translate([-35.308270,7.023252,1.600000])rotate([0,0,-56.250000])m2(part,hole,block,casetop); // D108
};
module C21(){translate([-6.242890,-31.385129,1.600000])rotate([0,0,-101.250000])children();}
module part_C21(part=true,hole=false,block=false)
{
translate([-6.242890,-31.385129,1.600000])rotate([0,0,-101.250000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D37(){translate([36.000000,0.000000,1.600000])rotate([0,0,135.000000])children();}
module part_D37(part=true,hole=false,block=false)
{
translate([36.000000,0.000000,1.600000])rotate([0,0,135.000000])m2(part,hole,block,casetop); // D108
};
module D28(){translate([-12.245870,29.564145,1.600000])rotate([0,0,-112.500000])children();}
module part_D28(part=true,hole=false,block=false)
{
translate([-12.245870,29.564145,1.600000])rotate([0,0,-112.500000])m2(part,hole,block,casetop); // D108
};
module D43(){translate([13.776604,-33.259663,1.600000])rotate([0,0,67.500000])children();}
module part_D43(part=true,hole=false,block=false)
{
translate([13.776604,-33.259663,1.600000])rotate([0,0,67.500000])m2(part,hole,block,casetop); // D108
};
module D31(){translate([13.776604,33.259663,1.600000])rotate([0,0,-157.500000])children();}
module part_D31(part=true,hole=false,block=false)
{
translate([13.776604,33.259663,1.600000])rotate([0,0,-157.500000])m2(part,hole,block,casetop); // D108
};
module D1(){translate([0.000000,24.000000,1.600000])rotate([0,0,-135.000000])children();}
module part_D1(part=true,hole=false,block=false)
{
translate([0.000000,24.000000,1.600000])rotate([0,0,-135.000000])m2(part,hole,block,casetop); // D108
};
module C26(){translate([-26.607028,17.778247,1.600000])rotate([0,0,146.250000])children();}
module part_C26(part=true,hole=false,block=false)
{
translate([-26.607028,17.778247,1.600000])rotate([0,0,146.250000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D93(){translate([0.000000,-40.000000,1.600000])rotate([0,0,45.000000])children();}
module part_D93(part=true,hole=false,block=false)
{
translate([0.000000,-40.000000,1.600000])rotate([0,0,45.000000])m2(part,hole,block,casetop); // D108
};
module C45(){translate([-3.528617,-35.826650,1.600000])rotate([0,0,-95.625000])children();}
module part_C45(part=true,hole=false,block=false)
{
translate([-3.528617,-35.826650,1.600000])rotate([0,0,-95.625000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D52(){translate([-35.308270,-7.023252,1.600000])rotate([0,0,-33.750000])children();}
module part_D52(part=true,hole=false,block=false)
{
translate([-35.308270,-7.023252,1.600000])rotate([0,0,-33.750000])m2(part,hole,block,casetop); // D108
};
module D35(){translate([33.259663,13.776604,1.600000])rotate([0,0,157.500000])children();}
module part_D35(part=true,hole=false,block=false)
{
translate([33.259663,13.776604,1.600000])rotate([0,0,157.500000])m2(part,hole,block,casetop); // D108
};
module V4(){translate([-49.910243,0.000000,1.600000])rotate([0,0,90.000000])children();}
module part_V4(part=true,hole=false,block=false)
{
};
module C64(){translate([13.475594,37.661763,1.600000])rotate([0,0,70.312500])children();}
module part_C64(part=true,hole=false,block=false)
{
translate([13.475594,37.661763,1.600000])rotate([0,0,70.312500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C16(){translate([31.385129,6.242890,1.600000])rotate([0,0,11.250000])children();}
module part_C16(part=true,hole=false,block=false)
{
translate([31.385129,6.242890,1.600000])rotate([0,0,11.250000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C72(){translate([36.159572,17.102204,1.600000])rotate([0,0,25.312500])children();}
module part_C72(part=true,hole=false,block=false)
{
translate([36.159572,17.102204,1.600000])rotate([0,0,25.312500])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D34(){translate([29.932906,20.000528,1.600000])rotate([0,0,168.750000])children();}
module part_D34(part=true,hole=false,block=false)
{
translate([29.932906,20.000528,1.600000])rotate([0,0,168.750000])m2(part,hole,block,casetop); // D108
};
module C10(){translate([-25.868627,-10.715136,1.600000])rotate([0,0,-157.500000])children();}
module part_C10(part=true,hole=false,block=false)
{
translate([-25.868627,-10.715136,1.600000])rotate([0,0,-157.500000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module C28(){translate([-6.242890,31.385129,1.600000])rotate([0,0,101.250000])children();}
module part_C28(part=true,hole=false,block=false)
{
translate([-6.242890,31.385129,1.600000])rotate([0,0,101.250000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D111(){translate([-39.231411,7.803613,1.600000])rotate([0,0,-56.250000])children();}
module part_D111(part=true,hole=false,block=false)
{
translate([-39.231411,7.803613,1.600000])rotate([0,0,-56.250000])m2(part,hole,block,casetop); // D108
};
module C50(){translate([-31.749166,-16.970283,1.600000])rotate([0,0,-151.875000])children();}
module part_C50(part=true,hole=false,block=false)
{
translate([-31.749166,-16.970283,1.600000])rotate([0,0,-151.875000])m0(part,hole,block,casetop); // RevK:C_0402 C_0402_1005Metric (back)
};
module D97(){translate([-15.307337,-36.955181,1.600000])rotate([0,0,22.500000])children();}
module part_D97(part=true,hole=false,block=false)
{
translate([-15.307337,-36.955181,1.600000])rotate([0,0,22.500000])m2(part,hole,block,casetop); // D108
};
module D60(){translate([-7.023252,35.308270,1.600000])rotate([0,0,-123.750000])children();}
module part_D60(part=true,hole=false,block=false)
{
translate([-7.023252,35.308270,1.600000])rotate([0,0,-123.750000])m2(part,hole,block,casetop); // D108
};
// Parts to go on PCB (top)
module parts_top(part=false,hole=false,block=false){
part_C54(part,hole,block);
part_J3(part,hole,block);
part_C93(part,hole,block);
part_C78(part,hole,block);
part_D108(part,hole,block);
part_C77(part,hole,block);
part_C14(part,hole,block);
part_C75(part,hole,block);
part_C65(part,hole,block);
part_D124(part,hole,block);
part_C71(part,hole,block);
part_D20(part,hole,block);
part_C135(part,hole,block);
part_C60(part,hole,block);
part_C104(part,hole,block);
part_C85(part,hole,block);
part_C55(part,hole,block);
part_C89(part,hole,block);
part_D113(part,hole,block);
part_C92(part,hole,block);
part_C74(part,hole,block);
part_D33(part,hole,block);
part_C8(part,hole,block);
part_D86(part,hole,block);
part_D103(part,hole,block);
part_C96(part,hole,block);
part_D71(part,hole,block);
part_D76(part,hole,block);
part_D46(part,hole,block);
part_D114(part,hole,block);
part_V3(part,hole,block);
part_C36(part,hole,block);
part_C139(part,hole,block);
part_C119(part,hole,block);
part_C103(part,hole,block);
part_C73(part,hole,block);
part_C138(part,hole,block);
part_D42(part,hole,block);
part_C13(part,hole,block);
part_C22(part,hole,block);
part_C34(part,hole,block);
part_C82(part,hole,block);
part_D19(part,hole,block);
part_D8(part,hole,block);
part_C99(part,hole,block);
part_D75(part,hole,block);
part_C41(part,hole,block);
part_C132(part,hole,block);
part_D69(part,hole,block);
part_C53(part,hole,block);
part_D53(part,hole,block);
part_C25(part,hole,block);
part_C44(part,hole,block);
part_C11(part,hole,block);
part_D16(part,hole,block);
part_D58(part,hole,block);
part_D109(part,hole,block);
part_D119(part,hole,block);
part_C68(part,hole,block);
part_C35(part,hole,block);
part_C122(part,hole,block);
part_C114(part,hole,block);
part_D63(part,hole,block);
part_C6(part,hole,block);
part_C116(part,hole,block);
part_D104(part,hole,block);
part_U3(part,hole,block);
part_C4(part,hole,block);
part_D91(part,hole,block);
part_C110(part,hole,block);
part_D102(part,hole,block);
part_D7(part,hole,block);
part_R4(part,hole,block);
part_C113(part,hole,block);
part_D17(part,hole,block);
part_D27(part,hole,block);
part_D32(part,hole,block);
part_C84(part,hole,block);
part_C107(part,hole,block);
part_D73(part,hole,block);
part_C1(part,hole,block);
part_U2(part,hole,block);
part_D100(part,hole,block);
part_D4(part,hole,block);
part_C115(part,hole,block);
part_L1(part,hole,block);
part_D36(part,hole,block);
part_D64(part,hole,block);
part_C43(part,hole,block);
part_D40(part,hole,block);
part_D80(part,hole,block);
part_C37(part,hole,block);
part_D48(part,hole,block);
part_C105(part,hole,block);
part_R3(part,hole,block);
part_C2(part,hole,block);
part_C130(part,hole,block);
part_C97(part,hole,block);
part_D99(part,hole,block);
part_D116(part,hole,block);
part_PCB1(part,hole,block);
part_C17(part,hole,block);
part_D15(part,hole,block);
part_C76(part,hole,block);
part_D98(part,hole,block);
part_D84(part,hole,block);
part_D72(part,hole,block);
part_D38(part,hole,block);
part_D105(part,hole,block);
part_C111(part,hole,block);
part_D44(part,hole,block);
part_C88(part,hole,block);
part_D106(part,hole,block);
part_D11(part,hole,block);
part_C95(part,hole,block);
part_C86(part,hole,block);
part_D77(part,hole,block);
part_D90(part,hole,block);
part_D112(part,hole,block);
part_D107(part,hole,block);
part_D68(part,hole,block);
part_C121(part,hole,block);
part_C101(part,hole,block);
part_C112(part,hole,block);
part_C29(part,hole,block);
part_C56(part,hole,block);
part_C134(part,hole,block);
part_C118(part,hole,block);
part_D49(part,hole,block);
part_C19(part,hole,block);
part_C66(part,hole,block);
part_C38(part,hole,block);
part_D78(part,hole,block);
part_C48(part,hole,block);
part_R6(part,hole,block);
part_C136(part,hole,block);
part_C61(part,hole,block);
part_D45(part,hole,block);
part_R1(part,hole,block);
part_D47(part,hole,block);
part_C30(part,hole,block);
part_D81(part,hole,block);
part_C31(part,hole,block);
part_C137(part,hole,block);
part_D123(part,hole,block);
part_C3(part,hole,block);
part_C69(part,hole,block);
part_D10(part,hole,block);
part_C131(part,hole,block);
part_C133(part,hole,block);
part_D13(part,hole,block);
part_D85(part,hole,block);
part_C67(part,hole,block);
part_D41(part,hole,block);
part_C83(part,hole,block);
part_C59(part,hole,block);
part_D23(part,hole,block);
part_C109(part,hole,block);
part_D29(part,hole,block);
part_D24(part,hole,block);
part_D55(part,hole,block);
part_C87(part,hole,block);
part_C18(part,hole,block);
part_C33(part,hole,block);
part_C9(part,hole,block);
part_C58(part,hole,block);
part_C12(part,hole,block);
part_D89(part,hole,block);
part_C27(part,hole,block);
part_D70(part,hole,block);
part_D121(part,hole,block);
part_C106(part,hole,block);
part_C20(part,hole,block);
part_D115(part,hole,block);
part_V2(part,hole,block);
part_D18(part,hole,block);
part_C42(part,hole,block);
part_C49(part,hole,block);
part_D88(part,hole,block);
part_D9(part,hole,block);
part_C108(part,hole,block);
part_C46(part,hole,block);
part_C120(part,hole,block);
part_C124(part,hole,block);
part_D67(part,hole,block);
part_D5(part,hole,block);
part_D6(part,hole,block);
part_C57(part,hole,block);
part_D12(part,hole,block);
part_C80(part,hole,block);
part_C90(part,hole,block);
part_C94(part,hole,block);
part_D83(part,hole,block);
part_D25(part,hole,block);
part_C32(part,hole,block);
part_D56(part,hole,block);
part_D95(part,hole,block);
part_D94(part,hole,block);
part_C63(part,hole,block);
part_D22(part,hole,block);
part_C100(part,hole,block);
part_C129(part,hole,block);
part_D101(part,hole,block);
part_C70(part,hole,block);
part_D120(part,hole,block);
part_C24(part,hole,block);
part_D50(part,hole,block);
part_D26(part,hole,block);
part_D57(part,hole,block);
part_C62(part,hole,block);
part_D79(part,hole,block);
part_D96(part,hole,block);
part_C15(part,hole,block);
part_D92(part,hole,block);
part_D66(part,hole,block);
part_C81(part,hole,block);
part_C51(part,hole,block);
part_V1(part,hole,block);
part_C102(part,hole,block);
part_C23(part,hole,block);
part_D117(part,hole,block);
part_D2(part,hole,block);
part_D51(part,hole,block);
part_D62(part,hole,block);
part_C7(part,hole,block);
part_U1(part,hole,block);
part_C123(part,hole,block);
part_D74(part,hole,block);
part_D59(part,hole,block);
part_D21(part,hole,block);
part_D14(part,hole,block);
part_D39(part,hole,block);
part_R2(part,hole,block);
part_C79(part,hole,block);
part_C98(part,hole,block);
part_D118(part,hole,block);
part_D87(part,hole,block);
part_C52(part,hole,block);
part_D61(part,hole,block);
part_C117(part,hole,block);
part_C91(part,hole,block);
part_D122(part,hole,block);
part_D3(part,hole,block);
part_D110(part,hole,block);
part_D30(part,hole,block);
part_C5(part,hole,block);
part_D65(part,hole,block);
part_C47(part,hole,block);
part_D82(part,hole,block);
part_C39(part,hole,block);
part_C40(part,hole,block);
part_R5(part,hole,block);
part_D54(part,hole,block);
part_C21(part,hole,block);
part_D37(part,hole,block);
part_D28(part,hole,block);
part_D43(part,hole,block);
part_D31(part,hole,block);
part_D1(part,hole,block);
part_C26(part,hole,block);
part_D93(part,hole,block);
part_C45(part,hole,block);
part_D52(part,hole,block);
part_D35(part,hole,block);
part_V4(part,hole,block);
part_C64(part,hole,block);
part_C16(part,hole,block);
part_C72(part,hole,block);
part_D34(part,hole,block);
part_C10(part,hole,block);
part_C28(part,hole,block);
part_D111(part,hole,block);
part_C50(part,hole,block);
part_D97(part,hole,block);
part_D60(part,hole,block);
}

parts_top=127;
module J1(){translate([0.000000,0.000000,0.000000])rotate([0,0,-90.000000])rotate([180,0,0])children();}
module part_J1(part=true,hole=false,block=false)
{
};
module J2(){translate([17.460000,0.016000,0.000000])rotate([180,0,0])children();}
module part_J2(part=true,hole=false,block=false)
{
};
// Parts to go on PCB (bottom)
module parts_bottom(part=false,hole=false,block=false){
part_J1(part,hole,block);
part_J2(part,hole,block);
}

parts_bottom=0;
module b(cx,cy,z,w,l,h){translate([cx-w/2,cy-l/2,z])cube([w,l,h]);}
module m0(part=false,hole=false,block=false,height)
{ // RevK:C_0402 C_0402_1005Metric
// 0402 Capacitor
if(part)
{
	b(0,0,0,1.0,0.5,1); // Chip
	b(0,0,0,1.5,0.65,0.2); // Pad size
}
}

module m1(part=false,hole=false,block=false,height)
{ // RevK:USB-C-Socket-H CSP-USC16-TR
// USB connector
rotate([-90,0,0])translate([0,1.9,0])
{
	if(part)
	{
        b(0,1.57,0,7,1.14,0.2); // Pads

		translate([0,1.76-7.55,1.63])
		rotate([-90,0,0])
		hull()
		{
			translate([(8.94-3.26)/2,0,0])
			cylinder(d=3.26,h=7.55,$fn=24);
			translate([-(8.94-3.26)/2,0,0])
			cylinder(d=3.26,h=7.55,$fn=24);
		}
		translate([-8.94/2,0.99-1.1/2,0])cube([8.94,1.1,1.6301]);
		translate([-8.94/2,-3.2-1.6/2,0])cube([8.94,1.6,1.6301]);
	}
	if(hole)
		translate([0,-5.79,1.63])
		rotate([-90,0,0])
	{
		// Plug
		hull()
		{
			translate([(8.34-2.5)/2,0,-23+1])
			cylinder(d=2.5,h=23,$fn=24);
			translate([-(8.34-2.5)/2,0,-23+1])
			cylinder(d=2.5,h=23,$fn=24);
		}
		hull()
		{
            translate([(12-7)/2,0,-21-1])
			cylinder(d=7,h=21,$fn=24);
            translate([-(12-7)/2,0,-21-1])
			cylinder(d=7,h=21,$fn=24);
		}
		translate([0,0,-100-10])
			cylinder(d=5,h=100,$fn=24);
	}
}
}

module m2(part=false,hole=false,block=false,height)
{ // D108
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

module m3(part=false,hole=false,block=false,height)
{ // RevK:C_0603 C_0603_1608Metric
// 0603 Capacitor
if(part)
{
	b(0,0,0,1.6,0.8,1); // Chip
	b(0,0,0,1.6,0.95,0.2); // Pad size
}
}

module m4(part=false,hole=false,block=false,height)
{ // RevK:SOT-23-6-MD8942 SOT-23-6
// SOT-23-6
if(part)
{
	b(0,0,0,1.726,3.026,1.2); // Part
	b(0,0,0,3.6,2.5,0.5); // Pins
}
}

module m5(part=false,hole=false,block=false,height)
{ // RevK:R_0402_ R_0402_1005Metric
// 0402 Resistor
if(part)
{
	b(0,0,0,1.5,0.65,0.2); // Pad size
	b(0,0,0,1.0,0.5,0.5); // Chip
}
}

module m6(part=false,hole=false,block=false,height)
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

module m7(part=false,hole=false,block=false,height)
{ // RevK:L_4x4_ TYA4020
// 4x4 Inductor
if(part)
{
	b(0,0,0,4,4,3);
}
}

module m8(part=false,hole=false,block=false,height)
{ // C131
if(part)
{
	b(0,0,0,3.5,2.8,1.9);
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
