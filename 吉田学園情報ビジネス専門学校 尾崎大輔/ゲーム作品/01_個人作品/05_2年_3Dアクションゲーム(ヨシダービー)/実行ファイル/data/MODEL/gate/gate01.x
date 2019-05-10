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
 278;
 -1.17741;12.73433;-0.53074;,
 14.04451;12.73433;-0.53074;,
 14.04451;10.61448;-0.53074;,
 -1.17741;10.61448;-0.53074;,
 14.04451;12.73433;-0.53074;,
 14.04451;12.73433;0.62283;,
 14.04451;10.61448;0.62283;,
 14.04451;10.61448;-0.53074;,
 14.04451;12.73433;0.62283;,
 -1.17741;12.73433;0.62283;,
 -1.17741;10.61448;0.62283;,
 14.04451;10.61448;0.62283;,
 -1.17741;12.73433;0.62283;,
 -1.17741;12.73433;-0.53074;,
 -1.17741;10.61448;-0.53074;,
 -1.17741;10.61448;0.62283;,
 14.04451;12.73433;-0.53074;,
 -1.17741;12.73433;-0.53074;,
 -1.17741;10.61448;-0.53074;,
 14.04451;10.61448;-0.53074;,
 -1.17741;-3.26074;-0.53074;,
 14.04451;-3.26074;-0.53074;,
 14.04451;-5.38059;-0.53074;,
 -1.17741;-5.38059;-0.53074;,
 14.04451;-3.26074;-0.53074;,
 14.04451;-3.26074;0.62283;,
 14.04451;-5.38059;0.62283;,
 14.04451;-5.38059;-0.53074;,
 14.04451;-3.26074;0.62283;,
 -1.17741;-3.26074;0.62283;,
 -1.17741;-5.38059;0.62283;,
 14.04451;-5.38059;0.62283;,
 -1.17741;-3.26074;0.62283;,
 -1.17741;-3.26074;-0.53074;,
 -1.17741;-5.38059;-0.53074;,
 -1.17741;-5.38059;0.62283;,
 14.04451;-3.26074;-0.53074;,
 -1.17741;-3.26074;-0.53074;,
 -1.17741;-5.38059;-0.53074;,
 14.04451;-5.38059;-0.53074;,
 -1.24546;10.61717;-0.53074;,
 2.67469;10.61717;-0.53074;,
 2.67469;-3.21037;-0.53074;,
 -1.24546;-3.21037;-0.53074;,
 2.67469;10.61717;-0.53074;,
 2.67469;10.61717;0.62283;,
 2.67469;-3.21037;0.62283;,
 2.67469;-3.21037;-0.53074;,
 2.67469;10.61717;0.62283;,
 -1.24546;10.61717;0.62283;,
 -1.24546;-3.21037;0.62283;,
 2.67469;-3.21037;0.62283;,
 -1.24546;10.61717;0.62283;,
 -1.24546;10.61717;-0.53074;,
 -1.24546;-3.21037;-0.53074;,
 -1.24546;-3.21037;0.62283;,
 2.67469;10.61717;-0.53074;,
 -1.24546;10.61717;-0.53074;,
 -1.24546;-3.21037;-0.53074;,
 2.67469;-3.21037;-0.53074;,
 10.09465;10.61717;-0.53074;,
 14.01478;10.61717;-0.53074;,
 14.01478;-3.21037;-0.53074;,
 10.09465;-3.21037;-0.53074;,
 14.01478;10.61717;-0.53074;,
 14.01478;10.61717;0.62283;,
 14.01478;-3.21037;0.62283;,
 14.01478;-3.21037;-0.53074;,
 14.01478;10.61717;0.62283;,
 10.09465;10.61717;0.62283;,
 10.09465;-3.21037;0.62283;,
 14.01478;-3.21037;0.62283;,
 10.09465;10.61717;0.62283;,
 10.09465;10.61717;-0.53074;,
 10.09465;-3.21037;-0.53074;,
 10.09465;-3.21037;0.62283;,
 14.01478;10.61717;-0.53074;,
 10.09465;10.61717;-0.53074;,
 10.09465;-3.21037;-0.53074;,
 14.01478;-3.21037;-0.53074;,
 3.87395;10.75310;-0.59411;,
 4.26003;10.75310;-0.47496;,
 4.26003;-3.07432;-0.47496;,
 3.87395;-3.07432;-0.59411;,
 4.18282;10.75310;-0.41743;,
 3.87395;10.75310;-0.51275;,
 3.87395;-3.07432;-0.51275;,
 4.18282;-3.07432;-0.41743;,
 4.41994;10.75310;-0.18730;,
 4.41994;-3.07432;-0.18730;,
 4.31075;10.75310;-0.18730;,
 4.31075;-3.07432;-0.18730;,
 4.26003;10.75310;0.10035;,
 4.26003;-3.07432;0.10035;,
 4.18282;10.75310;0.04282;,
 4.18282;-3.07432;0.04282;,
 3.87395;10.75310;0.21950;,
 3.87395;-3.07432;0.21950;,
 3.87395;10.75310;0.13814;,
 3.87395;-3.07432;0.13814;,
 3.48788;10.75310;0.10035;,
 3.48788;-3.07432;0.10035;,
 3.56510;10.75310;0.04282;,
 3.56510;-3.07432;0.04282;,
 3.32796;10.75310;-0.18730;,
 3.32796;-3.07432;-0.18730;,
 3.43715;10.75310;-0.18730;,
 3.43715;-3.07432;-0.18730;,
 3.48788;10.75310;-0.47496;,
 3.48788;-3.07432;-0.47496;,
 3.56510;10.75310;-0.41743;,
 3.56510;-3.07432;-0.41743;,
 3.87395;10.75310;-0.59411;,
 3.87395;-3.07432;-0.59411;,
 3.87395;10.75310;-0.51275;,
 3.87395;-3.07432;-0.51275;,
 4.18282;10.75310;-0.41743;,
 4.26003;10.75310;-0.47496;,
 3.87395;-3.07432;-0.59411;,
 4.26003;-3.07432;-0.47496;,
 4.18282;-3.07432;-0.41743;,
 3.87395;-3.07432;-0.51275;,
 4.31075;10.75310;-0.18730;,
 4.41994;10.75310;-0.18730;,
 4.41994;-3.07432;-0.18730;,
 4.31075;-3.07432;-0.18730;,
 4.18282;10.75310;0.04282;,
 4.26003;10.75310;0.10035;,
 4.26003;-3.07432;0.10035;,
 4.18282;-3.07432;0.04282;,
 3.87395;10.75310;0.13814;,
 3.87395;10.75310;0.21950;,
 3.87395;-3.07432;0.21950;,
 3.87395;-3.07432;0.13814;,
 3.56510;10.75310;0.04282;,
 3.48788;10.75310;0.10035;,
 3.48788;-3.07432;0.10035;,
 3.56510;-3.07432;0.04282;,
 3.43715;10.75310;-0.18730;,
 3.32796;10.75310;-0.18730;,
 3.32796;-3.07432;-0.18730;,
 3.43715;-3.07432;-0.18730;,
 3.56510;10.75310;-0.41743;,
 3.48788;10.75310;-0.47496;,
 3.48788;-3.07432;-0.47496;,
 3.56510;-3.07432;-0.41743;,
 5.85538;10.75310;-0.59411;,
 6.24144;10.75310;-0.47496;,
 6.24144;-3.07432;-0.47496;,
 5.85538;-3.07432;-0.59411;,
 6.16424;10.75310;-0.41743;,
 5.85538;10.75310;-0.51275;,
 5.85538;-3.07432;-0.51275;,
 6.16424;-3.07432;-0.41743;,
 6.40137;10.75310;-0.18730;,
 6.40137;-3.07432;-0.18730;,
 6.29216;10.75310;-0.18730;,
 6.29216;-3.07432;-0.18730;,
 6.24144;10.75310;0.10035;,
 6.24144;-3.07432;0.10035;,
 6.16424;10.75310;0.04282;,
 6.16424;-3.07432;0.04282;,
 5.85537;10.75310;0.21950;,
 5.85537;-3.07432;0.21950;,
 5.85538;10.75310;0.13814;,
 5.85538;-3.07432;0.13814;,
 5.46929;10.75310;0.10035;,
 5.46929;-3.07432;0.10035;,
 5.54651;10.75310;0.04282;,
 5.54651;-3.07432;0.04282;,
 5.30938;10.75310;-0.18730;,
 5.30938;-3.07432;-0.18730;,
 5.41859;10.75310;-0.18730;,
 5.41859;-3.07432;-0.18730;,
 5.46929;10.75310;-0.47496;,
 5.46929;-3.07432;-0.47496;,
 5.54651;10.75310;-0.41743;,
 5.54651;-3.07432;-0.41743;,
 5.85538;10.75310;-0.59411;,
 5.85538;-3.07432;-0.59411;,
 5.85538;10.75310;-0.51275;,
 5.85538;-3.07432;-0.51275;,
 6.16424;10.75310;-0.41743;,
 6.24144;10.75310;-0.47496;,
 5.85538;-3.07432;-0.59411;,
 6.24144;-3.07432;-0.47496;,
 6.16424;-3.07432;-0.41743;,
 5.85538;-3.07432;-0.51275;,
 6.29216;10.75310;-0.18730;,
 6.40137;10.75310;-0.18730;,
 6.40137;-3.07432;-0.18730;,
 6.29216;-3.07432;-0.18730;,
 6.16424;10.75310;0.04282;,
 6.24144;10.75310;0.10035;,
 6.24144;-3.07432;0.10035;,
 6.16424;-3.07432;0.04282;,
 5.85538;10.75310;0.13814;,
 5.85537;10.75310;0.21950;,
 5.85537;-3.07432;0.21950;,
 5.85538;-3.07432;0.13814;,
 5.54651;10.75310;0.04282;,
 5.46929;10.75310;0.10035;,
 5.46929;-3.07432;0.10035;,
 5.54651;-3.07432;0.04282;,
 5.41859;10.75310;-0.18730;,
 5.30938;10.75310;-0.18730;,
 5.30938;-3.07432;-0.18730;,
 5.41859;-3.07432;-0.18730;,
 5.54651;10.75310;-0.41743;,
 5.46929;10.75310;-0.47496;,
 5.46929;-3.07432;-0.47496;,
 5.54651;-3.07432;-0.41743;,
 8.34558;10.75310;-0.59411;,
 8.73165;10.75310;-0.47496;,
 8.73165;-3.07432;-0.47496;,
 8.34558;-3.07432;-0.59411;,
 8.65444;10.75310;-0.41743;,
 8.34558;10.75310;-0.51275;,
 8.34558;-3.07432;-0.51275;,
 8.65444;-3.07432;-0.41743;,
 8.89157;10.75310;-0.18730;,
 8.89157;-3.07432;-0.18730;,
 8.78236;10.75310;-0.18730;,
 8.78236;-3.07432;-0.18730;,
 8.73165;10.75310;0.10035;,
 8.73165;-3.07432;0.10035;,
 8.65444;10.75310;0.04282;,
 8.65444;-3.07432;0.04282;,
 8.34558;10.75310;0.21950;,
 8.34558;-3.07432;0.21950;,
 8.34558;10.75310;0.13814;,
 8.34558;-3.07432;0.13814;,
 7.95950;10.75310;0.10035;,
 7.95950;-3.07432;0.10035;,
 8.03672;10.75310;0.04282;,
 8.03672;-3.07432;0.04282;,
 7.79958;10.75310;-0.18730;,
 7.79958;-3.07432;-0.18730;,
 7.90878;10.75310;-0.18730;,
 7.90878;-3.07432;-0.18730;,
 7.95950;10.75310;-0.47496;,
 7.95950;-3.07432;-0.47496;,
 8.03672;10.75310;-0.41743;,
 8.03672;-3.07432;-0.41743;,
 8.34558;10.75310;-0.59411;,
 8.34558;-3.07432;-0.59411;,
 8.34558;10.75310;-0.51275;,
 8.34558;-3.07432;-0.51275;,
 8.65444;10.75310;-0.41743;,
 8.73165;10.75310;-0.47496;,
 8.34558;-3.07432;-0.59411;,
 8.73165;-3.07432;-0.47496;,
 8.65444;-3.07432;-0.41743;,
 8.34558;-3.07432;-0.51275;,
 8.78236;10.75310;-0.18730;,
 8.89157;10.75310;-0.18730;,
 8.89157;-3.07432;-0.18730;,
 8.78236;-3.07432;-0.18730;,
 8.65444;10.75310;0.04282;,
 8.73165;10.75310;0.10035;,
 8.73165;-3.07432;0.10035;,
 8.65444;-3.07432;0.04282;,
 8.34558;10.75310;0.13814;,
 8.34558;10.75310;0.21950;,
 8.34558;-3.07432;0.21950;,
 8.34558;-3.07432;0.13814;,
 8.03672;10.75310;0.04282;,
 7.95950;10.75310;0.10035;,
 7.95950;-3.07432;0.10035;,
 8.03672;-3.07432;0.04282;,
 7.90878;10.75310;-0.18730;,
 7.79958;10.75310;-0.18730;,
 7.79958;-3.07432;-0.18730;,
 7.90878;-3.07432;-0.18730;,
 8.03672;10.75310;-0.41743;,
 7.95950;10.75310;-0.47496;,
 7.95950;-3.07432;-0.47496;,
 8.03672;-3.07432;-0.41743;;
 
 120;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;52,45,56,57;,
 4;58,59,46,55;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;72,65,76,77;,
 4;78,79,66,75;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;81,88,89,82;,
 4;90,84,87,91;,
 4;88,92,93,89;,
 4;94,90,91,95;,
 4;92,96,97,93;,
 4;98,94,95,99;,
 4;96,100,101,97;,
 4;102,98,99,103;,
 4;100,104,105,101;,
 4;106,102,103,107;,
 4;104,108,109,105;,
 4;110,106,107,111;,
 4;108,112,113,109;,
 4;114,110,111,115;,
 4;80,85,116,117;,
 4;118,119,120,121;,
 4;117,116,122,123;,
 4;119,124,125,120;,
 4;123,122,126,127;,
 4;124,128,129,125;,
 4;127,126,130,131;,
 4;128,132,133,129;,
 4;131,130,134,135;,
 4;132,136,137,133;,
 4;135,134,138,139;,
 4;136,140,141,137;,
 4;139,138,142,143;,
 4;140,144,145,141;,
 4;143,142,85,80;,
 4;144,118,121,145;,
 4;146,147,148,149;,
 4;150,151,152,153;,
 4;147,154,155,148;,
 4;156,150,153,157;,
 4;154,158,159,155;,
 4;160,156,157,161;,
 4;158,162,163,159;,
 4;164,160,161,165;,
 4;162,166,167,163;,
 4;168,164,165,169;,
 4;166,170,171,167;,
 4;172,168,169,173;,
 4;170,174,175,171;,
 4;176,172,173,177;,
 4;174,178,179,175;,
 4;180,176,177,181;,
 4;146,151,182,183;,
 4;184,185,186,187;,
 4;183,182,188,189;,
 4;185,190,191,186;,
 4;189,188,192,193;,
 4;190,194,195,191;,
 4;193,192,196,197;,
 4;194,198,199,195;,
 4;197,196,200,201;,
 4;198,202,203,199;,
 4;201,200,204,205;,
 4;202,206,207,203;,
 4;205,204,208,209;,
 4;206,210,211,207;,
 4;209,208,151,146;,
 4;210,184,187,211;,
 4;212,213,214,215;,
 4;216,217,218,219;,
 4;213,220,221,214;,
 4;222,216,219,223;,
 4;220,224,225,221;,
 4;226,222,223,227;,
 4;224,228,229,225;,
 4;230,226,227,231;,
 4;228,232,233,229;,
 4;234,230,231,235;,
 4;232,236,237,233;,
 4;238,234,235,239;,
 4;236,240,241,237;,
 4;242,238,239,243;,
 4;240,244,245,241;,
 4;246,242,243,247;,
 4;212,217,248,249;,
 4;250,251,252,253;,
 4;249,248,254,255;,
 4;251,256,257,252;,
 4;255,254,258,259;,
 4;256,260,261,257;,
 4;259,258,262,263;,
 4;260,264,265,261;,
 4;263,262,266,267;,
 4;264,268,269,265;,
 4;267,266,270,271;,
 4;268,272,273,269;,
 4;271,270,274,275;,
 4;272,276,277,273;,
 4;275,274,217,212;,
 4;276,250,253,277;;
 
 MeshMaterialList {
  6;
  120;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.586400;0.580000;0.633600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.367200;0.690400;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.140800;0.172800;0.564800;1.000000;;
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
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game109\\Pictures\\1.png";
   }
  }
 }
 MeshNormals {
  78;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000003;0.000000;-1.000000;,
  0.629865;0.000000;-0.776705;,
  1.000000;0.000000;0.000008;,
  0.629860;0.000000;0.776709;,
  0.000003;0.000000;1.000000;,
  -0.629857;0.000000;0.776711;,
  -1.000000;0.000000;0.000008;,
  -0.629862;0.000000;-0.776707;,
  0.000001;0.000000;1.000000;,
  -0.629872;0.000000;0.776699;,
  -1.000000;0.000000;-0.000008;,
  -0.629866;0.000000;-0.776704;,
  0.000001;0.000000;-1.000000;,
  0.629853;0.000000;-0.776715;,
  1.000000;0.000000;-0.000008;,
  0.629859;0.000000;0.776709;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000004;0.000000;-1.000000;,
  0.629863;0.000000;-0.776706;,
  1.000000;0.000000;0.000008;,
  0.629856;0.000000;0.776712;,
  -0.000003;0.000000;1.000000;,
  -0.629860;0.000000;0.776709;,
  -1.000000;0.000000;0.000008;,
  -0.629862;0.000000;-0.776707;,
  -0.000005;0.000000;1.000000;,
  -0.629873;0.000000;0.776698;,
  -1.000000;0.000000;-0.000008;,
  -0.629866;0.000000;-0.776703;,
  -0.000005;0.000000;-1.000000;,
  0.629874;0.000000;-0.776697;,
  1.000000;0.000000;-0.000008;,
  0.629881;0.000000;0.776692;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000003;0.000000;-1.000000;,
  0.629865;0.000000;-0.776705;,
  1.000000;0.000000;0.000008;,
  0.629860;0.000000;0.776709;,
  0.000003;0.000000;1.000000;,
  -0.629857;0.000000;0.776711;,
  -1.000000;0.000000;0.000008;,
  -0.629862;0.000000;-0.776707;,
  0.000000;0.000000;1.000000;,
  -0.629873;0.000000;0.776698;,
  -1.000000;0.000000;-0.000008;,
  -0.629866;0.000000;-0.776704;,
  0.000000;0.000000;-1.000000;,
  0.629853;0.000000;-0.776715;,
  1.000000;0.000000;-0.000008;,
  0.629859;0.000000;0.776709;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  120;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,25,25,24;,
  4;33,32,32,33;,
  4;25,26,26,25;,
  4;34,33,33,34;,
  4;26,27,27,26;,
  4;35,34,34,35;,
  4;27,28,28,27;,
  4;36,35,35,36;,
  4;28,29,29,28;,
  4;37,36,36,37;,
  4;29,30,30,29;,
  4;38,37,37,38;,
  4;30,31,31,30;,
  4;39,38,38,39;,
  4;31,24,24,31;,
  4;32,39,39,32;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;42,43,43,42;,
  4;51,50,50,51;,
  4;43,44,44,43;,
  4;52,51,51,52;,
  4;44,45,45,44;,
  4;53,52,52,53;,
  4;45,46,46,45;,
  4;54,53,53,54;,
  4;46,47,47,46;,
  4;55,54,54,55;,
  4;47,48,48,47;,
  4;56,55,55,56;,
  4;48,49,49,48;,
  4;57,56,56,57;,
  4;49,42,42,49;,
  4;50,57,57,50;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;60,61,61,60;,
  4;69,68,68,69;,
  4;61,62,62,61;,
  4;70,69,69,70;,
  4;62,63,63,62;,
  4;71,70,70,71;,
  4;63,64,64,63;,
  4;72,71,71,72;,
  4;64,65,65,64;,
  4;73,72,72,73;,
  4;65,66,66,65;,
  4;74,73,73,74;,
  4;66,67,67,66;,
  4;75,74,74,75;,
  4;67,60,60,67;,
  4;68,75,75,68;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;76,76,76,76;,
  4;77,77,77,77;;
 }
 MeshTextureCoords {
  278;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
