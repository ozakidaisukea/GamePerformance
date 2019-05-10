xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 235;
 -1.21180;0.27339;0.86581;,
 -1.38754;0.16844;-0.27973;,
 -1.20099;-0.58039;-0.08584;,
 -0.88360;-0.29094;0.96341;,
 -1.01716;-0.89868;-0.02290;,
 -0.77497;-1.97536;0.19726;,
 -0.66462;-1.83891;0.97750;,
 -0.36987;-1.85592;1.23192;,
 -0.43188;-0.34561;1.22136;,
 -0.77303;-4.18820;0.41881;,
 -0.68280;-4.05458;1.27935;,
 -1.07933;-5.27838;0.51734;,
 -0.97613;-5.14496;1.45811;,
 -0.38451;-4.07732;1.53631;,
 -0.55804;-5.17387;1.71763;,
 -1.47726;-6.22833;0.27475;,
 -1.28473;-6.45664;1.72680;,
 -1.20475;-6.90403;1.47651;,
 -1.37041;-6.63659;0.17022;,
 -0.75895;-7.92836;0.68905;,
 -0.86161;-7.37468;0.96391;,
 -0.97092;-7.18952;0.14554;,
 -0.87800;-7.73467;-0.04671;,
 -0.63782;-6.99363;1.85477;,
 -0.71282;-6.52388;2.06421;,
 -1.02217;-8.81959;-1.87121;,
 -0.98284;-9.83288;-2.13022;,
 -1.41899;-9.83288;-1.07293;,
 -1.36385;-9.09751;-0.87840;,
 -1.25646;-8.09980;-0.43567;,
 -1.13371;-8.34818;0.47852;,
 -0.86117;-9.38650;1.10015;,
 -1.22975;-9.28222;0.29503;,
 -1.24798;-9.83288;0.24924;,
 -0.80702;-9.84189;1.16859;,
 -0.98284;-9.98187;-2.13022;,
 -1.41899;-9.98187;-1.07293;,
 -1.24798;-9.98187;0.24924;,
 -0.78147;-9.98187;1.17705;,
 -0.83337;-8.74477;0.95786;,
 -1.08578;-8.62808;0.35466;,
 -0.83627;-8.66803;0.97465;,
 -1.08102;-8.55034;0.37806;,
 -0.88400;-8.49606;1.11516;,
 -1.20364;-8.36792;-0.53476;,
 -1.19830;-8.28145;-0.50173;,
 -0.74328;-8.18924;-1.22135;,
 -0.72579;-8.10669;-1.17121;,
 -0.74773;-7.92890;-1.12729;,
 -0.70450;-9.98187;-1.61823;,
 -1.00492;-9.98187;-0.89250;,
 -1.41899;-9.98187;-1.07293;,
 -0.98284;-9.98187;-2.13022;,
 -0.88714;-9.98187;0.01501;,
 -0.62306;-9.98187;0.65188;,
 -0.78147;-9.98187;1.17705;,
 -1.24798;-9.98187;0.24924;,
 -0.86318;-9.64407;0.00236;,
 -0.61390;-9.61145;0.63830;,
 -0.97817;-9.64407;-0.88457;,
 0.83566;-9.64407;-0.03586;,
 0.85316;-9.98187;-0.02406;,
 0.69306;-9.98187;0.63802;,
 0.68632;-9.61145;0.62450;,
 0.90265;-9.64407;-0.87030;,
 0.92176;-9.98187;-0.87792;,
 -0.25998;-9.61297;0.05301;,
 -0.26993;-9.58186;0.54140;,
 -0.19054;-9.61297;-0.71905;,
 0.28458;-9.58186;0.56584;,
 0.25537;-9.61297;0.02467;,
 0.06892;-9.61297;-0.73148;,
 0.28458;-9.98489;0.56584;,
 0.24938;-9.98489;0.05261;,
 0.07136;-9.98489;-0.72338;,
 -0.06316;-9.98489;-0.92253;,
 -0.05812;-9.61889;-0.91733;,
 -0.26993;-9.98489;0.54140;,
 -0.25282;-9.98489;0.08902;,
 -0.18663;-9.98489;-0.71772;,
 0.00792;-9.98187;0.10819;,
 -0.04701;-9.98187;-0.45439;,
 -0.12779;-9.98187;1.40774;,
 -0.12779;-9.98187;1.40774;,
 -0.12740;-9.85387;1.40005;,
 -0.04090;-9.64383;-1.92336;,
 -0.04430;-9.98187;-1.93222;,
 0.65593;-9.98187;-1.61408;,
 0.65137;-9.64397;-1.60703;,
 0.57020;-9.64970;-1.47308;,
 -0.69526;-9.64379;-1.61274;,
 -0.02997;-9.63725;-1.77745;,
 -0.60099;-9.64872;-1.47571;,
 1.37034;0.14691;-0.14849;,
 1.10659;-0.60725;0.05323;,
 0.55465;-0.76880;-0.84632;,
 0.67252;0.04446;-1.10634;,
 0.13721;-0.30606;1.45248;,
 0.45562;-0.40315;1.23824;,
 0.59727;0.35357;1.40412;,
 0.92309;-0.50985;1.05842;,
 1.32892;0.26130;0.87722;,
 0.98336;-0.90555;0.14112;,
 0.65465;-1.89424;1.13467;,
 0.75642;-1.90238;0.32583;,
 0.50335;-1.13205;-0.63276;,
 0.32144;-2.00265;-0.36333;,
 0.32442;-1.86683;1.29305;,
 0.12045;-1.85582;1.56641;,
 0.13101;-4.05646;1.91423;,
 0.35670;-4.11182;1.56175;,
 0.18543;-5.13177;2.13904;,
 0.52261;-5.23260;1.70735;,
 0.69512;-4.15449;1.37819;,
 1.00146;-5.29146;1.49866;,
 0.76560;-4.16452;0.57054;,
 1.06491;-5.30351;0.69222;,
 0.31046;-4.22797;-0.05758;,
 0.41085;-5.33149;0.12515;,
 1.46213;-6.15604;0.42181;,
 0.62805;-6.01399;-0.27330;,
 1.41177;-6.45034;1.65188;,
 0.58632;-6.43209;-0.36851;,
 1.38272;-6.57884;0.29888;,
 1.34175;-6.86207;1.46884;,
 0.39954;-7.60289;-0.55402;,
 0.43447;-7.02195;-0.33604;,
 1.08842;-7.18157;0.20785;,
 1.02521;-7.79424;-0.05671;,
 0.94973;-7.38992;0.94395;,
 0.81768;-7.90092;0.66275;,
 0.49203;-7.52022;1.50891;,
 0.45001;-8.04620;1.22173;,
 0.87432;-6.51556;1.98077;,
 0.76956;-7.00030;1.73116;,
 0.34678;-6.57096;2.46265;,
 0.31984;-7.05758;2.18658;,
 1.23465;-8.12073;-0.42435;,
 0.72063;-7.93224;-1.12353;,
 0.91088;-8.78757;-1.90476;,
 1.34489;-9.07143;-0.86495;,
 1.37813;-9.83288;-1.05167;,
 0.99220;-9.83288;-2.12419;,
 0.97280;-9.86433;1.14127;,
 1.29339;-9.82620;0.18729;,
 1.31142;-9.29784;0.26685;,
 1.04175;-9.39446;1.12878;,
 1.04534;-8.49982;1.14885;,
 1.26304;-8.34374;0.47464;,
 0.71013;-8.18764;-1.22260;,
 1.18693;-8.38228;-0.52403;,
 0.69846;-8.10756;-1.16996;,
 1.18153;-8.29913;-0.49102;,
 1.20573;-8.62647;0.34797;,
 1.20454;-8.54730;0.37294;,
 0.99248;-8.75354;0.98628;,
 0.99446;-8.67430;1.00446;,
 0.28616;-9.39788;1.44973;,
 0.29503;-9.85338;1.39192;,
 -0.68127;0.01031;-1.26362;,
 -0.53887;-0.77984;-0.97897;,
 -0.43921;-1.12676;-0.69620;,
 -0.27165;-1.98121;-0.40736;,
 -0.20469;-1.84404;1.51086;,
 -0.21930;-0.33508;1.44064;,
 -0.47317;0.40802;1.60642;,
 -0.27646;-4.23327;-0.17030;,
 -0.39725;-5.36357;-0.05625;,
 -0.19067;-4.04573;1.88504;,
 -0.25746;-5.12192;2.13615;,
 -0.55909;-6.07623;-0.52494;,
 -0.53866;-6.47835;-0.57990;,
 -0.43754;-8.00909;1.18441;,
 -0.40503;-7.49912;1.51877;,
 -0.45384;-7.01370;-0.40611;,
 -0.46186;-7.58572;-0.57432;,
 -0.22245;-7.08419;2.21322;,
 -0.21160;-6.60250;2.52729;,
 -0.00896;-7.82541;-1.52458;,
 -0.01692;-8.65611;-2.27515;,
 -0.02439;-9.83288;-2.58764;,
 0.08625;-8.56235;1.47014;,
 -0.02439;-9.98187;-2.58764;,
 0.08613;-8.80586;1.29288;,
 0.08503;-8.73172;1.30899;,
 -0.00774;-8.08276;-1.60558;,
 -0.00716;-8.00170;-1.55255;,
 -0.02439;-9.98187;-2.58764;,
 0.99220;-9.98187;-2.12419;,
 1.37813;-9.98187;-1.05167;,
 1.27853;-9.98187;0.19228;,
 0.96442;-9.98187;1.16590;,
 -0.07499;-9.40007;1.44888;,
 0.28031;-9.98187;1.39710;,
 0.07042;-9.98187;0.87824;,
 0.07042;-9.98187;0.87824;,
 0.07042;-9.89319;0.87824;,
 0.07042;-9.57882;0.95151;,
 -0.47317;0.40802;1.60642;,
 -0.21930;-0.33508;1.44064;,
 -0.68127;0.01031;-1.26362;,
 -0.53887;-0.77984;-0.97897;,
 -0.20469;-1.84404;1.51086;,
 -0.43921;-1.12676;-0.69620;,
 -0.27165;-1.98121;-0.40736;,
 -0.19067;-4.04573;1.88504;,
 -0.25746;-5.12192;2.13615;,
 -0.27646;-4.23327;-0.17030;,
 -0.39725;-5.36357;-0.05625;,
 -0.55909;-6.07623;-0.52494;,
 -0.21160;-6.60250;2.52729;,
 -0.53866;-6.47835;-0.57990;,
 -0.22245;-7.08419;2.21322;,
 -0.46186;-7.58572;-0.57432;,
 -0.45384;-7.01370;-0.40611;,
 -0.40503;-7.49912;1.51877;,
 -0.43754;-8.00909;1.18441;,
 0.08625;-8.56235;1.47014;,
 -0.00896;-7.82541;-1.52458;,
 -0.02439;-9.83288;-2.58764;,
 -0.01692;-8.65611;-2.27515;,
 -0.02439;-9.98187;-2.58764;,
 0.99220;-9.98187;-2.12419;,
 1.37813;-9.98187;-1.05167;,
 1.27853;-9.98187;0.19228;,
 0.96442;-9.98187;1.16590;,
 0.08503;-8.73172;1.30899;,
 0.08613;-8.80586;1.29288;,
 -0.00774;-8.08276;-1.60558;,
 -0.00716;-8.00170;-1.55255;,
 -0.07499;-9.40007;1.44888;,
 0.28031;-9.98187;1.39710;,
 0.07042;-9.89319;0.87824;,
 0.07042;-9.98187;0.87824;,
 0.07042;-9.57882;0.95151;;
 
 199;
 4;0,1,2,3;,
 3;2,4,3;,
 4;4,5,6,3;,
 4;6,7,8,3;,
 4;5,9,10,6;,
 4;9,11,12,10;,
 4;6,10,13,7;,
 4;10,12,14,13;,
 4;12,11,15,16;,
 4;17,16,15,18;,
 4;19,20,21,22;,
 4;20,17,18,21;,
 3;20,23,17;,
 4;17,23,24,16;,
 4;16,24,14,12;,
 4;25,26,27,28;,
 4;19,22,29,30;,
 4;31,32,33,34;,
 4;32,28,27,33;,
 4;35,36,27,26;,
 4;37,38,34,33;,
 4;36,37,33,27;,
 4;31,39,40,32;,
 4;39,41,42,40;,
 4;41,43,30,42;,
 4;32,40,44,28;,
 4;40,42,45,44;,
 4;42,30,29,45;,
 4;28,44,46,25;,
 4;44,45,47,46;,
 4;45,29,48,47;,
 4;49,50,51,52;,
 4;53,54,55,56;,
 4;50,53,56,51;,
 4;57,58,54,53;,
 4;59,57,53,50;,
 4;60,61,62,63;,
 4;64,65,61,60;,
 4;58,57,66,67;,
 4;57,59,68,66;,
 4;69,70,60,63;,
 4;70,71,64,60;,
 4;72,69,63,62;,
 4;73,70,69,72;,
 4;74,71,70,73;,
 4;75,76,71,74;,
 4;77,54,58,67;,
 4;78,77,67,66;,
 4;79,78,66,68;,
 4;75,79,68,76;,
 4;80,81,74,73;,
 4;81,79,75,74;,
 4;54,77,82,55;,
 4;80,78,79,81;,
 4;83,84,34,38;,
 4;85,86,87,88;,
 3;89,88,64;,
 4;85,90,49,86;,
 4;90,59,50,49;,
 4;71,76,68,91;,
 4;71,91,89,64;,
 4;92,91,68,59;,
 4;85,88,89,91;,
 4;90,85,91,92;,
 4;88,87,65,64;,
 3;90,92,59;,
 4;93,94,95,96;,
 3;97,98,99;,
 4;100,94,93,101;,
 3;100,102,94;,
 4;100,103,104,102;,
 4;94,102,105,95;,
 4;102,104,106,105;,
 4;100,98,107,103;,
 4;98,97,108,107;,
 4;98,100,101,99;,
 4;108,109,110,107;,
 4;109,111,112,110;,
 4;107,110,113,103;,
 4;110,112,114,113;,
 4;103,113,115,104;,
 4;113,114,116,115;,
 4;104,115,117,106;,
 4;115,116,118,117;,
 4;118,116,119,120;,
 4;121,119,116,114;,
 4;122,120,119,123;,
 4;123,119,121,124;,
 4;125,126,127,128;,
 4;126,122,123,127;,
 4;128,127,129,130;,
 4;127,123,124,129;,
 4;130,129,131,132;,
 4;121,133,134,124;,
 4;133,135,136,134;,
 3;124,134,129;,
 4;134,136,131,129;,
 4;114,112,133,121;,
 4;112,111,135,133;,
 4;125,128,137,138;,
 4;139,140,141,142;,
 4;143,144,145,146;,
 4;144,141,140,145;,
 4;147,148,130,132;,
 4;148,137,128,130;,
 4;139,149,150,140;,
 4;149,151,152,150;,
 4;151,138,137,152;,
 4;140,150,153,145;,
 4;150,152,154,153;,
 4;152,137,148,154;,
 4;145,153,155,146;,
 4;153,154,156,155;,
 4;154,148,147,156;,
 4;143,146,157,158;,
 4;1,159,160,2;,
 4;160,161,4,2;,
 4;161,162,5,4;,
 4;7,163,164,8;,
 4;3,8,165,0;,
 3;8,164,165;,
 4;162,166,9,5;,
 4;166,167,11,9;,
 4;7,13,168,163;,
 4;13,14,169,168;,
 4;167,170,15,11;,
 4;18,15,170,171;,
 4;172,173,20,19;,
 4;22,21,174,175;,
 4;21,18,171,174;,
 4;20,173,176,23;,
 4;23,176,177,24;,
 4;24,177,169,14;,
 3;48,175,178;,
 4;25,179,180,26;,
 4;29,22,175,48;,
 4;172,19,30,43;,
 3;172,43,181;,
 4;182,35,26,180;,
 4;183,184,41,39;,
 4;184,181,43,41;,
 4;25,46,185,179;,
 4;46,47,186,185;,
 4;47,48,178,186;,
 4;86,187,188,87;,
 4;87,188,189,65;,
 4;86,49,52,187;,
 4;61,190,191,62;,
 4;65,189,190,61;,
 4;192,183,39,31;,
 4;62,191,193,72;,
 3;193,194,72;,
 4;194,80,73,72;,
 3;82,77,194;,
 4;194,77,78,80;,
 4;195,196,84,83;,
 4;196,197,192,84;,
 4;84,192,31,34;,
 4;99,198,199,97;,
 4;200,96,95,201;,
 4;97,199,202,108;,
 4;95,105,203,201;,
 4;105,106,204,203;,
 4;202,205,109,108;,
 4;205,206,111,109;,
 4;106,117,207,204;,
 4;117,118,208,207;,
 4;120,209,208,118;,
 4;210,135,111,206;,
 4;211,209,120,122;,
 4;136,135,210,212;,
 4;213,214,126,125;,
 4;214,211,122,126;,
 4;132,131,215,216;,
 4;131,136,212,215;,
 3;147,132,217;,
 3;216,217,132;,
 3;218,125,138;,
 4;139,142,219,220;,
 3;218,213,125;,
 4;221,219,142,222;,
 4;222,142,141,223;,
 4;224,144,143,225;,
 4;223,141,144,224;,
 4;155,156,226,227;,
 4;156,147,217,226;,
 4;220,228,149,139;,
 4;228,229,151,149;,
 4;229,218,138,151;,
 3;230,157,227;,
 4;146,155,227,157;,
 4;225,143,158,231;,
 4;231,158,232,233;,
 4;158,157,234,232;,
 3;157,230,234;,
 3;1,0,198;,
 4;198,99,200,1;,
 4;99,101,96,200;,
 3;101,93,96;;
 
 MeshMaterialList {
  2;
  199;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  0,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  0,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0;;
  Material {
   0.564800;0.220000;0.135200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.148260;0.057750;0.035490;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.940000;0.940000;0.940000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  219;
  -0.957249;-0.144129;-0.250802;,
  -0.896335;-0.435196;-0.084783;,
  -0.927356;-0.349727;-0.133048;,
  -0.777265;-0.342086;0.528049;,
  -0.860978;-0.020404;0.508233;,
  -0.910366;-0.394033;-0.126382;,
  -0.820468;-0.268427;0.504756;,
  -0.733734;0.034682;0.678551;,
  -0.666728;-0.194218;0.719550;,
  -0.943438;0.079271;-0.321932;,
  -0.863741;0.176125;0.472155;,
  -0.742771;0.159915;0.650168;,
  -0.922297;0.164238;-0.349847;,
  -0.854564;-0.037687;0.517976;,
  -0.748415;-0.570069;0.338962;,
  -0.859615;-0.325556;-0.393797;,
  -0.889801;-0.286591;-0.355133;,
  -0.569644;-0.575580;0.586696;,
  -0.637810;-0.098318;0.763892;,
  -0.775742;-0.543122;0.321314;,
  -0.892082;0.307913;-0.330726;,
  -0.813087;0.300019;0.498876;,
  -0.665415;0.235779;0.708260;,
  -0.681588;-0.116502;0.722402;,
  -0.695583;0.355812;-0.624150;,
  -0.730242;0.088929;-0.677376;,
  -0.703436;0.416556;-0.575898;,
  -0.935952;0.319939;-0.147085;,
  -0.975452;0.200646;-0.090751;,
  -0.992188;0.035078;-0.119720;,
  -0.949649;0.103863;0.295599;,
  -0.954906;0.083348;0.284970;,
  -0.959158;-0.014977;0.282473;,
  -0.725950;0.000000;-0.687748;,
  -0.991391;0.000000;-0.130935;,
  -0.956999;-0.034227;0.288066;,
  -0.696067;0.033437;0.717198;,
  -0.682908;-0.377639;0.625321;,
  -0.959661;0.063341;0.273933;,
  -0.958272;-0.197242;0.206906;,
  -0.957110;0.261257;-0.125238;,
  -0.970928;0.015744;-0.238852;,
  -0.649985;0.532092;-0.542584;,
  -0.671758;0.259747;-0.693738;,
  0.007983;-0.027201;0.999598;,
  -0.737666;-0.033909;0.674314;,
  -0.990553;-0.048392;0.128305;,
  0.000000;-1.000000;-0.000000;,
  -0.986958;-0.048434;-0.153519;,
  0.989719;-0.068074;0.125785;,
  0.965283;-0.067094;-0.252443;,
  -0.000313;-1.000000;0.000871;,
  0.989114;-0.012891;-0.146584;,
  0.000274;-0.999996;0.002796;,
  0.914983;-0.010588;-0.403352;,
  0.827155;-0.005164;-0.561950;,
  0.001463;-0.999996;0.002374;,
  -0.998262;-0.014749;-0.057060;,
  -0.947406;-0.007589;-0.319943;,
  -0.681775;0.109343;0.723345;,
  -0.661961;-0.021391;0.749233;,
  -0.001774;-0.999998;0.001162;,
  -0.025927;-0.999507;0.017728;,
  0.026881;-0.999501;0.016572;,
  0.061101;-0.997838;0.024212;,
  -0.055459;-0.998085;0.027403;,
  -0.973155;-0.042171;-0.226255;,
  0.926194;-0.057989;-0.372562;,
  -0.345850;0.020196;0.938072;,
  -0.672929;-0.013628;0.739581;,
  -0.284979;-0.013796;-0.958434;,
  0.076318;-0.995892;0.048735;,
  0.159355;-0.016380;-0.987085;,
  -0.065902;-0.996579;0.049873;,
  0.000382;-0.999990;0.004538;,
  0.000333;-0.999863;0.016530;,
  0.727802;-0.044998;0.684310;,
  0.003942;-0.999972;0.006326;,
  -0.916273;0.141948;0.374559;,
  -0.913441;0.381970;-0.140446;,
  0.367673;0.087236;0.925854;,
  0.309125;-0.094006;0.946364;,
  0.519690;-0.222063;-0.824991;,
  0.503246;-0.451082;-0.737068;,
  0.504709;-0.359544;-0.784854;,
  0.968098;-0.142077;-0.206399;,
  0.913676;-0.378920;-0.147027;,
  0.909475;-0.371829;-0.186005;,
  0.340950;-0.203481;0.917795;,
  0.810439;-0.020325;0.585470;,
  0.761484;-0.309467;0.569537;,
  0.936444;-0.321567;-0.140244;,
  0.503940;-0.443205;-0.741360;,
  0.823916;-0.242901;0.512017;,
  0.609449;0.047283;0.791414;,
  0.509895;-0.118748;0.852001;,
  0.599981;0.177830;0.779999;,
  0.659037;0.144181;0.738162;,
  0.817142;0.167704;0.551502;,
  0.956291;0.068291;-0.284329;,
  0.511158;-0.077232;-0.856010;,
  0.898744;0.231340;-0.372480;,
  0.412305;0.347007;-0.842372;,
  0.435705;-0.125573;0.891287;,
  0.912468;0.184494;0.365190;,
  0.412301;-0.030849;-0.910525;,
  0.873807;-0.210643;-0.438281;,
  0.775477;-0.533940;0.336962;,
  0.386293;-0.633718;0.670208;,
  0.388304;0.043413;-0.920509;,
  0.802205;-0.165796;-0.573567;,
  0.400310;-0.642619;0.653294;,
  0.621777;-0.087109;0.778335;,
  0.563941;-0.568191;0.599275;,
  0.781004;-0.525641;0.337247;,
  0.890097;0.327548;-0.316923;,
  0.456517;0.257828;-0.851538;,
  0.426562;0.250382;0.869111;,
  0.784919;0.312964;0.534749;,
  0.621572;0.237152;0.746597;,
  0.502082;0.454403;0.735820;,
  0.918770;0.326896;-0.221360;,
  0.614748;0.528615;-0.585364;,
  0.691100;0.424738;-0.584789;,
  0.730405;0.098285;-0.675906;,
  0.968686;0.197751;-0.150143;,
  0.989322;0.021348;-0.144176;,
  0.981625;-0.049530;0.184282;,
  0.982357;0.047704;0.180828;,
  0.963330;0.151004;0.221796;,
  0.646706;0.529661;-0.548845;,
  0.943914;0.262709;-0.200027;,
  0.674604;0.262937;-0.689764;,
  0.950620;0.039192;-0.307874;,
  0.983970;0.064463;0.166273;,
  0.979206;-0.174516;0.103435;,
  0.720831;0.031716;0.692385;,
  0.696301;-0.384484;0.606083;,
  0.724588;0.064631;0.686145;,
  0.238830;0.159287;0.957908;,
  0.351565;0.006614;0.936140;,
  0.723205;-0.036681;0.689659;,
  0.361556;0.734015;-0.574890;,
  0.749723;0.590419;-0.298867;,
  0.309636;-0.067875;0.948430;,
  0.916789;0.146220;0.371642;,
  -0.366288;-0.139459;0.919991;,
  -0.319225;-0.652598;0.687177;,
  -0.394433;-0.641567;0.657886;,
  -0.436730;0.241041;0.866699;,
  -0.018013;-0.111439;0.993608;,
  -0.009598;0.084025;0.996417;,
  -0.012431;-0.472606;0.881186;,
  -0.002748;-0.999993;0.002710;,
  -0.001086;-0.999998;0.001694;,
  0.932868;-0.113332;0.341927;,
  -0.244569;0.182156;0.952368;,
  0.001686;-0.999998;0.000917;,
  0.936199;-0.052172;0.347576;,
  -0.456703;0.063770;0.887331;,
  -0.521733;0.080111;0.849339;,
  -0.409742;-0.127221;0.903286;,
  -0.413867;-0.306913;0.857041;,
  -0.524955;0.182786;0.831271;,
  -0.255455;0.342773;-0.904018;,
  -0.268108;-0.100140;-0.958170;,
  -0.342547;-0.031898;-0.938959;,
  -0.268093;0.271320;-0.924398;,
  0.006388;0.750417;-0.660934;,
  -0.007008;0.124582;-0.992185;,
  -0.004136;0.545186;-0.838305;,
  -0.008772;0.000000;-0.999961;,
  0.000707;0.688055;-0.725658;,
  0.004735;0.382098;-0.924110;,
  -0.372700;0.735618;-0.565651;,
  -0.376717;-0.230198;-0.897270;,
  -0.535906;-0.529858;-0.657309;,
  -0.791774;-0.329216;-0.514500;,
  -0.378157;-0.486495;-0.787604;,
  -0.323739;-0.072792;-0.943342;,
  0.015663;-0.999865;0.005045;,
  -0.011152;-0.999923;0.005451;,
  0.998113;-0.010022;-0.060586;,
  -0.999541;-0.010543;-0.028412;,
  -0.844295;0.004200;-0.535862;,
  -0.007187;-0.999966;0.004094;,
  -0.013522;-0.999907;0.001729;,
  0.007660;-0.999966;0.002933;,
  0.000124;-0.999984;0.005668;,
  0.004508;-0.999989;0.001525;,
  0.012897;-0.999917;0.000013;,
  -0.327476;0.027979;0.944445;,
  0.017289;-0.999828;-0.006649;,
  0.000634;-0.999772;0.021361;,
  0.000146;-0.999996;0.002848;,
  -0.011170;-0.999926;-0.004854;,
  0.952908;-0.251284;0.169772;,
  0.484809;-0.452124;0.748695;,
  0.646373;0.613705;0.453396;,
  0.644191;-0.580625;0.497888;,
  -0.322525;0.869910;-0.373140;,
  -0.006014;-0.999980;0.002119;,
  0.935988;0.009186;0.351911;,
  0.117333;-0.317811;-0.940866;,
  -0.122327;0.159899;0.979525;,
  0.735607;0.000000;-0.677408;,
  0.990520;-0.023599;-0.135323;,
  0.980014;-0.044344;0.193924;,
  0.716032;0.024375;0.697642;,
  0.333437;0.085559;0.938882;,
  -0.921716;0.060267;0.383155;,
  -0.917154;-0.011165;0.398376;,
  -0.907681;-0.082538;0.411464;,
  0.004904;-0.940601;0.339478;,
  -0.040364;0.993440;-0.106993;,
  -0.105943;0.991571;-0.074591;,
  0.019509;0.991281;-0.130315;,
  0.009741;0.993178;-0.116199;,
  0.005899;0.993848;-0.110598;;
  199;
  4;3,2,1,6;,
  3;1,5,6;,
  4;5,0,4,6;,
  4;4,7,8,6;,
  4;0,9,10,4;,
  4;9,20,21,10;,
  4;4,10,11,7;,
  4;10,21,22,11;,
  4;21,20,12,13;,
  4;14,13,12,15;,
  4;78,19,16,79;,
  4;19,14,15,16;,
  3;19,17,14;,
  4;14,17,18,13;,
  4;13,18,22,21;,
  4;26,25,29,28;,
  4;78,79,27,30;,
  4;59,31,32,69;,
  4;31,28,29,32;,
  4;33,34,29,25;,
  4;35,60,69,32;,
  4;34,35,32,29;,
  4;59,36,38,31;,
  4;36,37,39,38;,
  4;37,23,30,39;,
  4;31,38,40,28;,
  4;38,39,41,40;,
  4;39,30,27,41;,
  4;28,40,42,26;,
  4;40,41,43,42;,
  4;41,27,24,43;,
  4;47,47,47,47;,
  4;47,61,61,47;,
  4;47,47,47,47;,
  4;50,67,67,50;,
  4;49,50,50,49;,
  4;48,48,66,66;,
  4;46,46,48,48;,
  4;71,64,64,71;,
  4;64,180,63,64;,
  4;73,65,65,73;,
  4;65,62,181,65;,
  4;72,72,72,72;,
  4;52,52,182,182;,
  4;54,54,52,52;,
  4;55,55,54,54;,
  4;70,70,70,70;,
  4;57,183,183,57;,
  4;58,57,57,58;,
  4;184,58,58,184;,
  4;51,53,185,186;,
  4;53,187,188,185;,
  4;61,189,56,61;,
  4;51,190,187,53;,
  4;191,68,69,60;,
  4;44,44,45,45;,
  3;74,192,181;,
  4;44,76,76,44;,
  4;76,49,49,76;,
  4;62,193,63,75;,
  4;62,75,74,181;,
  4;77,75,63,180;,
  4;194,192,74,75;,
  4;195,194,75,77;,
  4;45,45,46,46;,
  3;195,77,180;,
  4;87,86,83,84;,
  3;81,95,88;,
  4;93,86,87,90;,
  3;93,91,86;,
  4;93,89,85,91;,
  4;86,91,92,83;,
  4;91,85,82,92;,
  4;93,95,94,89;,
  4;95,81,80,94;,
  4;95,93,90,88;,
  4;80,96,97,94;,
  4;96,117,119,97;,
  4;94,97,98,89;,
  4;97,119,118,98;,
  4;89,98,99,85;,
  4;98,118,115,99;,
  4;85,99,100,82;,
  4;99,115,116,100;,
  4;116,115,101,102;,
  4;104,101,115,118;,
  4;105,102,101,106;,
  4;106,101,104,107;,
  4;142,109,110,143;,
  4;109,105,106,110;,
  4;196,196,114,145;,
  4;110,106,107,114;,
  4;145,114,111,144;,
  4;197,112,113,107;,
  4;112,103,108,113;,
  3;107,113,114;,
  4;113,108,111,114;,
  4;118,119,112,104;,
  4;119,117,103,112;,
  4;142,143,121,122;,
  4;123,125,126,124;,
  4;141,127,128,138;,
  4;127,126,125,128;,
  4;120,129,145,198;,
  4;129,121,143,145;,
  4;123,130,131,125;,
  4;130,132,133,131;,
  4;132,122,121,133;,
  4;125,131,134,128;,
  4;131,133,135,134;,
  4;133,121,129,135;,
  4;128,134,136,138;,
  4;134,135,137,136;,
  4;135,129,199,137;,
  4;141,138,139,140;,
  4;2,177,176,1;,
  4;176,178,5,1;,
  4;178,175,0,5;,
  4;7,160,161,8;,
  4;6,8,162,3;,
  3;8,161,162;,
  4;175,179,9,0;,
  4;179,167,20,9;,
  4;7,11,163,160;,
  4;11,22,149,163;,
  4;167,164,12,20;,
  4;15,12,164,165;,
  4;159,148,19,78;,
  4;79,16,166,174;,
  4;16,15,165,166;,
  4;19,148,147,17;,
  4;17,147,146,18;,
  4;18,146,149,22;,
  3;200,174,168;,
  4;26,170,169,25;,
  4;27,79,174,24;,
  4;159,78,30,23;,
  3;159,23,150;,
  4;171,33,25,169;,
  4;151,152,37,36;,
  4;152,150,23,37;,
  4;26,42,172,170;,
  4;42,43,173,172;,
  4;43,24,168,173;,
  4;47,47,47,47;,
  4;47,47,47,47;,
  4;47,47,47,47;,
  4;47,47,157,157;,
  4;47,47,47,47;,
  4;156,151,36,59;,
  4;157,157,153,201;,
  3;153,154,201;,
  4;154,51,186,201;,
  3;56,189,154;,
  4;154,189,190,51;,
  4;202,158,158,202;,
  4;158,155,155,158;,
  4;68,156,59,69;,
  4;88,162,161,81;,
  4;203,84,83,203;,
  4;81,161,160,80;,
  4;83,92,178,176;,
  4;92,82,175,178;,
  4;160,163,204,80;,
  4;163,149,117,96;,
  4;82,100,179,175;,
  4;100,116,167,179;,
  4;102,164,167,116;,
  4;146,103,117,149;,
  4;165,164,102,105;,
  4;108,103,146,147;,
  4;174,166,109,142;,
  4;166,165,105,109;,
  4;144,111,148,159;,
  4;111,108,147,148;,
  3;120,144,150;,
  3;159,150,144;,
  3;168,142,122;,
  4;123,124,169,170;,
  3;168,174,142;,
  4;171,169,124,205;,
  4;205,124,126,206;,
  4;207,127,141,208;,
  4;206,126,127,207;,
  4;136,137,152,151;,
  4;137,199,150,152;,
  4;170,172,130,123;,
  4;172,173,132,130;,
  4;173,168,122,132;,
  3;156,139,151;,
  4;138,136,151,139;,
  4;208,141,140,209;,
  4;210,211,211,210;,
  4;211,212,212,211;,
  3;213,213,213;,
  3;214,215,214;,
  4;214,216,216,214;,
  4;216,217,217,216;,
  3;217,218,217;;
 }
 MeshTextureCoords {
  235;
  0.258130;0.126660;,
  0.247360;0.125190;,
  0.249220;0.117850;,
  0.259540;0.119360;,
  0.250160;0.113630;,
  0.252400;0.101610;,
  0.259540;0.102940;,
  0.263560;0.102600;,
  0.265330;0.118140;,
  0.254820;0.080210;,
  0.262610;0.081270;,
  0.255520;0.067820;,
  0.264140;0.068690;,
  0.266940;0.081570;,
  0.269380;0.069240;,
  0.254200;0.058880;,
  0.265650;0.057100;,
  0.263900;0.052520;,
  0.253030;0.054760;,
  0.257210;0.040960;,
  0.260300;0.046940;,
  0.251730;0.048840;,
  0.249690;0.043090;,
  0.270160;0.050410;,
  0.271900;0.056270;,
  0.233310;0.029880;,
  0.230310;0.021470;,
  0.240660;0.021230;,
  0.242250;0.027880;,
  0.246540;0.038000;,
  0.254140;0.036340;,
  0.259900;0.025990;,
  0.252190;0.026680;,
  0.251870;0.021490;,
  0.260490;0.021860;,
  0.230060;0.019510;,
  0.240680;0.019430;,
  0.251960;0.019780;,
  0.260740;0.020350;,
  0.259230;0.031540;,
  0.253030;0.032780;,
  0.259400;0.032770;,
  0.253380;0.034090;,
  0.260020;0.034840;,
  0.245270;0.034700;,
  0.245740;0.036090;,
  0.237650;0.036980;,
  0.238310;0.038400;,
  0.239170;0.040130;,
  0.300150;0.620050;,
  0.303880;0.612820;,
  0.306860;0.614780;,
  0.301420;0.624230;,
  0.303380;0.603560;,
  0.299260;0.597830;,
  0.299610;0.593630;,
  0.305740;0.601390;,
  0.300610;0.604380;,
  0.297650;0.599360;,
  0.300930;0.612140;,
  0.284260;0.604760;,
  0.281590;0.604180;,
  0.284770;0.598190;,
  0.286760;0.599570;,
  0.284450;0.612300;,
  0.281370;0.612970;,
  0.296850;0.603900;,
  0.294900;0.598540;,
  0.295160;0.610570;,
  0.289600;0.598300;,
  0.288070;0.604410;,
  0.290480;0.610950;,
  0.289600;0.598300;,
  0.290480;0.603290;,
  0.292210;0.609120;,
  0.293620;0.610250;,
  0.292810;0.612170;,
  0.294900;0.598540;,
  0.294300;0.602990;,
  0.293400;0.608600;,
  0.292300;0.602610;,
  0.292650;0.606870;,
  0.294410;0.591760;,
  0.265830;0.021060;,
  0.265990;0.022220;,
  0.292670;0.620730;,
  0.292800;0.623290;,
  0.285040;0.620220;,
  0.286660;0.618190;,
  0.287290;0.617140;,
  0.298460;0.618120;,
  0.292590;0.618880;,
  0.297750;0.617050;,
  0.802450;0.139350;,
  0.801050;0.130080;,
  0.810630;0.128710;,
  0.812680;0.138320;,
  0.782890;0.131150;,
  0.786610;0.130360;,
  0.785390;0.139810;,
  0.791450;0.130030;,
  0.793470;0.139920;,
  0.800500;0.126090;,
  0.791540;0.112050;,
  0.799380;0.112970;,
  0.809190;0.123860;,
  0.807210;0.112210;,
  0.788030;0.111940;,
  0.784830;0.111670;,
  0.782220;0.084580;,
  0.786120;0.084090;,
  0.779440;0.072310;,
  0.784450;0.071230;,
  0.789760;0.083380;,
  0.789040;0.069750;,
  0.797500;0.083860;,
  0.796640;0.069470;,
  0.804900;0.084010;,
  0.804810;0.070310;,
  0.797930;0.059130;,
  0.806400;0.061250;,
  0.788200;0.057110;,
  0.807330;0.056690;,
  0.798830;0.054630;,
  0.789060;0.053020;,
  0.810660;0.044000;,
  0.808540;0.050370;,
  0.800150;0.047580;,
  0.802470;0.040250;,
  0.792200;0.045300;,
  0.794070;0.039180;,
  0.784570;0.043990;,
  0.786500;0.037370;,
  0.783140;0.056780;,
  0.784290;0.050610;,
  0.777140;0.056590;,
  0.778620;0.050890;,
  0.805330;0.035220;,
  0.813190;0.036990;,
  0.819540;0.027610;,
  0.809480;0.025220;,
  0.811450;0.018010;,
  0.821970;0.018260;,
  0.791950;0.016250;,
  0.800570;0.018130;,
  0.799470;0.023160;,
  0.791800;0.020260;,
  0.791240;0.031240;,
  0.797280;0.033050;,
  0.814260;0.034440;,
  0.806430;0.032380;,
  0.813850;0.035280;,
  0.806120;0.033280;,
  0.798290;0.029900;,
  0.798080;0.030710;,
  0.791390;0.025790;,
  0.791850;0.028880;,
  0.784100;0.019120;,
  0.785510;0.014780;,
  0.236800;0.122730;,
  0.239300;0.114480;,
  0.241890;0.109920;,
  0.245230;0.100600;,
  0.266690;0.102540;,
  0.268470;0.117910;,
  0.268230;0.126750;,
  0.247830;0.080410;,
  0.247000;0.068640;,
  0.270770;0.082140;,
  0.274340;0.070030;,
  0.243740;0.060860;,
  0.243180;0.056380;,
  0.263460;0.039210;,
  0.267550;0.044230;,
  0.244260;0.050770;,
  0.242660;0.045070;,
  0.275900;0.049070;,
  0.278040;0.055480;,
  0.232170;0.043690;,
  0.225420;0.033930;,
  0.220600;0.023980;,
  0.268570;0.034420;,
  0.219970;0.022100;,
  0.268120;0.030950;,
  0.268190;0.032220;,
  0.230240;0.040500;,
  0.231000;0.041860;,
  0.292670;0.627910;,
  0.283350;0.624350;,
  0.278040;0.614870;,
  0.278760;0.602040;,
  0.283410;0.593960;,
  0.267250;0.025730;,
  0.288720;0.591930;,
  0.291760;0.595440;,
  0.269250;0.020810;,
  0.269630;0.022040;,
  0.270530;0.024810;,
  0.775720;0.139730;,
  0.779330;0.130370;,
  0.824540;0.136330;,
  0.820890;0.126960;,
  0.781900;0.111790;,
  0.817890;0.121830;,
  0.812780;0.111320;,
  0.779090;0.085290;,
  0.775760;0.073100;,
  0.810440;0.084020;,
  0.812850;0.070870;,
  0.816780;0.062600;,
  0.772050;0.056550;,
  0.817330;0.058090;,
  0.774000;0.049050;,
  0.817700;0.047580;,
  0.816520;0.052420;,
  0.776920;0.041130;,
  0.778420;0.036070;,
  0.782470;0.031360;,
  0.820050;0.040320;,
  0.831990;0.021770;,
  0.826910;0.031270;,
  0.832640;0.020120;,
  0.822260;0.016660;,
  0.811450;0.016520;,
  0.800660;0.016620;,
  0.792060;0.015220;,
  0.782450;0.028490;,
  0.783170;0.025110;,
  0.821850;0.037440;,
  0.821110;0.038640;,
  0.780820;0.020040;,
  0.785790;0.013620;,
  0.780830;0.012630;,
  0.781100;0.011880;,
  0.780350;0.015320;;
 }
}
