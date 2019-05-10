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
 61;
 -1.14815;-1.05647;-6.25890;,
 0.04654;-0.68754;-6.62782;,
 0.04654;-0.81847;-6.80141;,
 -1.40577;-0.81847;-6.43248;,
 1.24123;-1.05647;-6.25890;,
 1.49885;-0.81847;-6.43248;,
 0.04654;-3.09666;-6.41168;,
 -1.14815;-2.72774;-6.04276;,
 1.24123;-2.72774;-6.04276;,
 1.24123;-1.05647;-6.25890;,
 1.72903;-0.31853;-2.64377;,
 1.98664;-0.81847;-2.42763;,
 1.49885;-0.81847;-6.43248;,
 1.24123;0.38230;1.18750;,
 1.49885;-0.81847;1.57723;,
 1.72903;-2.69542;-2.42763;,
 1.24123;-2.72774;-6.04276;,
 1.24123;-2.72774;1.18750;,
 1.24123;0.38230;1.18750;,
 0.04654;0.75122;1.55642;,
 0.04654;-0.81847;1.94615;,
 1.49885;-0.81847;1.57723;,
 -1.14815;0.38230;1.18750;,
 -1.40577;-0.81847;1.57723;,
 0.04654;-2.72538;1.55642;,
 1.24123;-2.72774;1.18750;,
 -1.14815;-2.72774;1.18750;,
 -1.14815;0.38230;1.18750;,
 -1.63594;-0.31853;-2.64377;,
 -1.89356;-0.81847;-2.42763;,
 -1.40577;-0.81847;1.57723;,
 -1.14815;-1.05647;-6.25890;,
 -1.40577;-0.81847;-6.43248;,
 -1.63594;-2.69542;-2.42763;,
 -1.14815;-2.72774;1.18750;,
 -1.14815;-2.72774;-6.04276;,
 0.04654;-0.52343;-3.97604;,
 -1.63594;-0.31853;-2.64377;,
 1.72903;-0.31853;-2.64377;,
 0.04654;-0.68754;-6.62782;,
 -1.14815;-1.05647;-6.25890;,
 1.24123;-1.05647;-6.25890;,
 -1.14815;-2.72774;-6.04276;,
 0.04654;-3.09666;-6.41168;,
 0.04654;-3.06435;-2.42763;,
 -1.63594;-2.69542;-2.42763;,
 1.24123;-2.72774;-6.04276;,
 1.72903;-2.69542;-2.42763;,
 -1.14815;0.85869;-2.18837;,
 0.04654;0.81521;-2.24972;,
 0.04654;-0.59906;-4.83413;,
 -1.68231;-0.14272;-3.40804;,
 1.24123;0.84918;-2.22265;,
 1.74379;-0.16458;-3.46368;,
 0.04654;-0.52236;-6.76136;,
 -1.14815;-0.89128;-6.39244;,
 1.24123;-0.89128;-6.39244;,
 0.04654;0.81521;-2.24972;,
 0.04654;-0.59906;-4.83413;,
 1.24123;0.84918;-2.22265;,
 -1.68231;-0.14272;-3.40804;;
 
 32;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;3,2,6,7;,
 4;2,5,8,6;,
 4;9,10,11,12;,
 4;10,13,14,11;,
 4;12,11,15,16;,
 4;11,14,17,15;,
 4;18,19,20,21;,
 4;19,22,23,20;,
 4;21,20,24,25;,
 4;20,23,26,24;,
 4;27,28,29,30;,
 4;28,31,32,29;,
 4;30,29,33,34;,
 4;29,32,35,33;,
 4;27,19,36,37;,
 4;19,13,38,36;,
 4;37,36,39,40;,
 4;36,38,41,39;,
 4;42,43,44,45;,
 4;43,46,47,44;,
 4;45,44,24,34;,
 4;44,47,17,24;,
 4;48,49,50,51;,
 4;49,52,53,50;,
 4;51,50,54,55;,
 4;50,53,56,54;,
 4;52,53,50,49;,
 4;57,58,53,59;,
 4;49,50,51,48;,
 4;48,60,58,57;;
 
 MeshMaterialList {
  1;
  32;
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
  0;;
  Material {
   0.056800;0.056800;0.056800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  57;
  -0.184270;0.981772;-0.046573;,
  -0.000000;0.999830;-0.018444;,
  0.184273;0.981771;-0.046574;,
  -0.186156;0.982516;-0.002649;,
  -0.000000;0.995120;0.098677;,
  0.186160;0.982516;-0.002650;,
  -0.288322;-0.192312;-0.938023;,
  0.000000;-0.200841;-0.979624;,
  0.288322;-0.192312;-0.938023;,
  0.411068;0.906488;-0.096446;,
  0.930612;0.358706;0.072740;,
  0.948614;0.316303;-0.009165;,
  0.988625;0.110119;0.102440;,
  0.989151;-0.146900;-0.000000;,
  0.981346;-0.145741;0.125375;,
  0.000000;0.299320;0.954153;,
  -0.291786;0.286295;0.912632;,
  0.000000;0.041921;0.999121;,
  -0.287219;0.040154;0.957023;,
  0.000000;-0.216210;0.976347;,
  -0.264678;-0.208499;0.941527;,
  -0.411065;0.906490;-0.096447;,
  -0.948613;0.316305;-0.009166;,
  -0.989151;-0.146903;-0.000000;,
  -0.000000;0.986874;-0.161494;,
  -0.000000;-0.999718;0.023742;,
  -0.112320;0.988699;-0.099294;,
  0.000561;0.995038;-0.099498;,
  0.113435;0.988658;-0.098431;,
  0.091804;0.904537;-0.416396;,
  0.077274;0.825877;-0.558530;,
  -0.003339;0.828538;-0.559923;,
  -0.083929;0.825807;-0.557673;,
  -0.095959;0.904286;-0.416004;,
  -0.002098;0.908423;-0.418046;,
  0.981346;-0.145741;-0.125375;,
  0.291786;0.286295;0.912632;,
  0.287219;0.040154;0.957023;,
  0.264678;-0.208499;0.941527;,
  -0.930610;0.358712;0.072737;,
  -0.988625;0.110121;0.102438;,
  -0.981346;-0.145744;0.125373;,
  -0.981346;-0.145744;-0.125374;,
  -0.156063;0.970340;-0.184622;,
  -0.000000;0.982377;-0.186912;,
  0.156063;0.970340;-0.184622;,
  -0.253736;-0.967254;-0.006211;,
  -0.000000;-0.999979;-0.006421;,
  -0.187275;-0.982031;0.023322;,
  0.253735;-0.967254;-0.006211;,
  0.187275;-0.982031;0.023322;,
  -0.000000;-0.998589;0.053108;,
  -0.119784;-0.991399;0.052726;,
  0.119783;-0.991399;0.052726;,
  0.003339;-0.828538;0.559923;,
  -0.077274;-0.825877;0.558530;,
  0.083929;-0.825807;0.557673;;
  32;
  4;0,1,4,3;,
  4;1,2,5,4;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;2,9,11,5;,
  4;9,10,12,11;,
  4;35,11,13,35;,
  4;11,12,14,13;,
  4;36,15,17,37;,
  4;15,16,18,17;,
  4;37,17,19,38;,
  4;17,18,20,19;,
  4;39,21,22,40;,
  4;21,0,3,22;,
  4;40,22,23,41;,
  4;22,42,42,23;,
  4;43,44,24,21;,
  4;44,45,9,24;,
  4;21,24,1,0;,
  4;24,9,2,1;,
  4;46,47,25,48;,
  4;47,49,50,25;,
  4;48,25,51,52;,
  4;25,50,53,51;,
  4;32,31,34,33;,
  4;31,30,29,34;,
  4;33,34,27,26;,
  4;34,29,28,27;,
  4;30,29,34,31;,
  4;54,54,55,55;,
  4;31,34,33,32;,
  4;56,56,54,54;;
 }
 MeshTextureCoords {
  61;
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
