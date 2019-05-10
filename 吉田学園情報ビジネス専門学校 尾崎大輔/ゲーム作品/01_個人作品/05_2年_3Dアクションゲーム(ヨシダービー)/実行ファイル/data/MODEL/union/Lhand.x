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
 62;
 0.57605;0.54328;-0.05545;,
 0.85346;0.48947;-0.25567;,
 0.57605;0.48947;-0.37658;,
 0.57605;0.54328;-0.05545;,
 0.92197;0.48947;0.01601;,
 0.57605;0.54328;-0.05545;,
 0.73000;0.48947;0.23389;,
 0.57605;0.54328;-0.05545;,
 0.42210;0.48947;0.23389;,
 0.57605;0.54328;-0.05545;,
 0.23012;0.48947;0.01601;,
 0.57605;0.54328;-0.05545;,
 0.29864;0.48947;-0.25567;,
 0.57605;0.54328;-0.05545;,
 0.57605;0.48947;-0.37658;,
 1.07593;0.33873;-0.41624;,
 0.57605;0.33873;-0.63411;,
 1.19938;0.33873;0.07332;,
 0.85346;0.33873;0.46592;,
 0.29864;0.33873;0.46592;,
 -0.04729;0.33873;0.07332;,
 0.07617;0.33873;-0.41624;,
 0.57605;0.33873;-0.63411;,
 1.19938;0.12089;-0.50535;,
 0.57605;0.12089;-0.77703;,
 1.35334;0.12089;0.10512;,
 0.92197;0.12089;0.59468;,
 0.23012;0.12089;0.59468;,
 -0.20124;0.12089;0.10512;,
 -0.04729;0.12089;-0.50535;,
 0.57605;0.12089;-0.77703;,
 1.19938;-0.12089;-0.50535;,
 0.57605;-0.12089;-0.77703;,
 1.35334;-0.12089;0.10512;,
 0.92197;-0.12089;0.59468;,
 0.23012;-0.12089;0.59468;,
 -0.20124;-0.12089;0.10512;,
 -0.04729;-0.12089;-0.50535;,
 0.57605;-0.12089;-0.77703;,
 1.07593;-0.33873;-0.41624;,
 0.57605;-0.33873;-0.63411;,
 1.19938;-0.33873;0.07332;,
 0.85346;-0.33873;0.46592;,
 0.29864;-0.33873;0.46592;,
 -0.04729;-0.33873;0.07332;,
 0.07617;-0.33873;-0.41624;,
 0.57605;-0.33873;-0.63411;,
 0.85346;-0.48947;-0.25567;,
 0.57605;-0.48947;-0.37658;,
 0.92197;-0.48947;0.01601;,
 0.73000;-0.48947;0.23389;,
 0.42210;-0.48947;0.23389;,
 0.23012;-0.48947;0.01601;,
 0.29864;-0.48947;-0.25567;,
 0.57605;-0.48947;-0.37658;,
 0.57605;-0.54328;-0.05545;,
 0.57605;-0.54328;-0.05545;,
 0.57605;-0.54328;-0.05545;,
 0.57605;-0.54328;-0.05545;,
 0.57605;-0.54328;-0.05545;,
 0.57605;-0.54328;-0.05545;,
 0.57605;-0.54328;-0.05545;;
 
 49;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 4;2,1,15,16;,
 4;1,4,17,15;,
 4;4,6,18,17;,
 4;6,8,19,18;,
 4;8,10,20,19;,
 4;10,12,21,20;,
 4;12,14,22,21;,
 4;16,15,23,24;,
 4;15,17,25,23;,
 4;17,18,26,25;,
 4;18,19,27,26;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;24,23,31,32;,
 4;23,25,33,31;,
 4;25,26,34,33;,
 4;26,27,35,34;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;32,31,39,40;,
 4;31,33,41,39;,
 4;33,34,42,41;,
 4;34,35,43,42;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;40,39,47,48;,
 4;39,41,49,47;,
 4;41,42,50,49;,
 4;42,43,51,50;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 3;48,47,55;,
 3;47,49,56;,
 3;49,50,57;,
 3;50,51,58;,
 3;51,52,59;,
 3;52,53,60;,
 3;53,54,61;;
 
 MeshMaterialList {
  9;
  49;
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
   0.800000;0.718400;0.618400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.778400;0.656000;0.517600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.633600;0.197600;0.169600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.545600;0.545600;0.545600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.630400;0.344800;0.633600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.467200;0.125600;0.094400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.072000;0.081600;0.254400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  44;
  0.000001;1.000000;-0.000002;,
  0.000000;0.940786;-0.339000;,
  0.242779;0.946591;-0.212186;,
  0.303395;0.949839;0.075881;,
  0.134355;0.942569;0.305798;,
  -0.134352;0.942568;0.305801;,
  -0.303391;0.949840;0.075880;,
  -0.242778;0.946591;-0.212191;,
  0.000001;0.728046;-0.685528;,
  0.503605;0.746694;-0.434546;,
  0.633892;0.757438;0.156426;,
  0.276086;0.733688;0.620869;,
  -0.276084;0.733686;0.620872;,
  -0.633892;0.757438;0.156425;,
  -0.503603;0.746694;-0.434549;,
  0.000003;0.289776;-0.957095;,
  0.724948;0.304403;-0.617891;,
  0.922704;0.313255;0.224697;,
  0.391998;0.294105;0.871688;,
  -0.392000;0.294105;0.871687;,
  -0.922705;0.313252;0.224698;,
  -0.724949;0.304405;-0.617889;,
  0.000003;-0.289776;-0.957095;,
  0.724948;-0.304403;-0.617891;,
  0.922704;-0.313255;0.224697;,
  0.391998;-0.294105;0.871688;,
  -0.392000;-0.294105;0.871687;,
  -0.922705;-0.313252;0.224698;,
  -0.724949;-0.304405;-0.617889;,
  0.000001;-0.728046;-0.685528;,
  0.503605;-0.746694;-0.434546;,
  0.633892;-0.757438;0.156426;,
  0.276086;-0.733688;0.620869;,
  -0.276084;-0.733686;0.620872;,
  -0.633892;-0.757438;0.156425;,
  -0.503603;-0.746694;-0.434549;,
  0.000000;-0.940786;-0.339000;,
  0.242779;-0.946591;-0.212186;,
  0.303395;-0.949839;0.075881;,
  0.134355;-0.942569;0.305798;,
  -0.134352;-0.942568;0.305801;,
  -0.303391;-0.949840;0.075880;,
  -0.242778;-0.946591;-0.212191;,
  0.000001;-1.000000;-0.000002;;
  49;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,1,7;,
  4;1,2,9,8;,
  4;2,3,10,9;,
  4;3,4,11,10;,
  4;4,5,12,11;,
  4;5,6,13,12;,
  4;6,7,14,13;,
  4;7,1,8,14;,
  4;8,9,16,15;,
  4;9,10,17,16;,
  4;10,11,18,17;,
  4;11,12,19,18;,
  4;12,13,20,19;,
  4;13,14,21,20;,
  4;14,8,15,21;,
  4;15,16,23,22;,
  4;16,17,24,23;,
  4;17,18,25,24;,
  4;18,19,26,25;,
  4;19,20,27,26;,
  4;20,21,28,27;,
  4;21,15,22,28;,
  4;22,23,30,29;,
  4;23,24,31,30;,
  4;24,25,32,31;,
  4;25,26,33,32;,
  4;26,27,34,33;,
  4;27,28,35,34;,
  4;28,22,29,35;,
  4;29,30,37,36;,
  4;30,31,38,37;,
  4;31,32,39,38;,
  4;32,33,40,39;,
  4;33,34,41,40;,
  4;34,35,42,41;,
  4;35,29,36,42;,
  3;36,37,43;,
  3;37,38,43;,
  3;38,39,43;,
  3;39,40,43;,
  3;40,41,43;,
  3;41,42,43;,
  3;42,36,43;;
 }
 MeshTextureCoords {
  62;
  0.071430;0.000000;,
  0.142860;0.142860;,
  0.000000;0.142860;,
  0.214290;0.000000;,
  0.285710;0.142860;,
  0.357140;0.000000;,
  0.428570;0.142860;,
  0.500000;0.000000;,
  0.571430;0.142860;,
  0.642860;0.000000;,
  0.714290;0.142860;,
  0.785710;0.000000;,
  0.857140;0.142860;,
  0.928570;0.000000;,
  1.000000;0.142860;,
  0.142860;0.285710;,
  0.000000;0.285710;,
  0.285710;0.285710;,
  0.428570;0.285710;,
  0.571430;0.285710;,
  0.714290;0.285710;,
  0.857140;0.285710;,
  1.000000;0.285710;,
  0.142860;0.428570;,
  0.000000;0.428570;,
  0.285710;0.428570;,
  0.428570;0.428570;,
  0.571430;0.428570;,
  0.714290;0.428570;,
  0.857140;0.428570;,
  1.000000;0.428570;,
  0.142860;0.571430;,
  0.000000;0.571430;,
  0.285710;0.571430;,
  0.428570;0.571430;,
  0.571430;0.571430;,
  0.714290;0.571430;,
  0.857140;0.571430;,
  1.000000;0.571430;,
  0.142860;0.714290;,
  0.000000;0.714290;,
  0.285710;0.714290;,
  0.428570;0.714290;,
  0.571430;0.714290;,
  0.714290;0.714290;,
  0.857140;0.714290;,
  1.000000;0.714290;,
  0.142860;0.857140;,
  0.000000;0.857140;,
  0.285710;0.857140;,
  0.428570;0.857140;,
  0.571430;0.857140;,
  0.714290;0.857140;,
  0.857140;0.857140;,
  1.000000;0.857140;,
  0.071430;1.000000;,
  0.214290;1.000000;,
  0.357140;1.000000;,
  0.500000;1.000000;,
  0.642860;1.000000;,
  0.785710;1.000000;,
  0.928570;1.000000;;
 }
}
