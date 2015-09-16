// Maths function
function degreeToRadian(degrees) {
    return degrees * Math.PI / 180.0;
}
function createPerspectiveProjectionMatrix(fov, aspect, near, far){
    
    var f= aspect/Math.tan(fov*0.5);
    var n= 1.0/(near-far);
    
	return new Float32Array([	f/aspect	, 0.0			, 0.0			, 0.0,
                             0.0			, f             , 0.0			, 0.0,
                             0.0			, 0.0			, (far+near)*n	, -1.0,
                             0.0			, 0.0           , 2.0*far*near*n, 0.0
                             ]);
    
}
function createLookAtMatrix(pos, lookAt, up){
    
	var viewDir= lookAt.minus(pos);
	viewDir.normalize();
	
	var right= viewDir.cross(up);
    right.normalize();
	var upV= right.cross(viewDir);
    upV.normalize();
    
	return new Float32Array([
                             right.x, upV.x, -viewDir.x,  0,
                             right.y, upV.y, -viewDir.y,  0,
                             right.z, upV.z, -viewDir.z,  0,
                             -right.x * pos.x -right.y * pos.y- right.z * pos.z,
                             -upV.x * pos.x -upV.y * pos.y- upV.z * pos.z,
                             viewDir.x * pos.x +viewDir.y * pos.y+ viewDir.z * pos.z,
                             1
                             ]);
}
function createTranslationMatrix(x, y, z){
	return new Float32Array([	1.0         , 0.0			, 0.0			, 0.0,
                             0.0			, 1.0           , 0.0			, 0.0,
                             0.0			, 0.0			, 1.0           , 0.0,
                             x			, y             , z             , 1.0
                             ]);
}
function createScaleMatrix(x, y, z){
	return new Float32Array([	x           , 0.0			, 0.0			, 0.0,
                             0.0			, y             , 0.0			, 0.0,
                             0.0			, 0.0			, z             , 0.0,
                             0.0			, 0.0           , 0.0           , 1.0
                             ]);
}
function createRotationYMatrix(radian){
	var cosR= Math.cos(radian);
	var sinR= Math.sin(radian);
    
	return new Float32Array([cosR           , 0.0			, -sinR			, 0.0,
                             0.0			, 1.0           , 0.0			, 0.0,
                             sinR			, 0.0			, cosR           , 0.0,
                             0.0			, 0.0           , 0.0             , 1.0
                             ]);
}
function createRotationXMatrix(radian){
	var cosR= Math.cos(radian);
	var sinR= Math.sin(radian);
    
	return new Float32Array([   1.0         , 0.0			, 0.0			, 0.0,
                             0.0			, cosR          , sinR			, 0.0,
                             0.0			, -sinR			, cosR           , 0.0,
                             0.0			, 0.0           , 0.0             , 1.0
                             ]);
}
function matrixMultiplyMatrix(m1, m2){
    
	return new Float32Array([
                             m1[0]* m2[0] + m1[4]* m2[1] + m1[8]* m2[2] + m1[12]* m2[3],
                             m1[1]* m2[0] + m1[5]* m2[1] + m1[9]* m2[2] + m1[13]* m2[3],
                             m1[2]* m2[0] + m1[6]* m2[1] + m1[10]* m2[2] + m1[14]* m2[3],
                             m1[3]* m2[0] + m1[7]* m2[1] + m1[11]* m2[2] + m1[15]* m2[3],
                             
                             m1[0]* m2[4] + m1[4]* m2[5] + m1[8]* m2[6] + m1[12]* m2[7],
                             m1[1]* m2[4] + m1[5]* m2[5] + m1[9]* m2[6] + m1[13]* m2[7],
                             m1[2]* m2[4] + m1[6]* m2[5] + m1[10]* m2[6] + m1[14]* m2[7],
                             m1[3]* m2[4] + m1[7]* m2[5] + m1[11]* m2[6] + m1[15]* m2[7],
                             
                             m1[0]* m2[8] + m1[4]* m2[9] + m1[8]* m2[10] + m1[12]* m2[11],
                             m1[1]* m2[8] + m1[5]* m2[9] + m1[9]* m2[10] + m1[13]* m2[11],
                             m1[2]* m2[8] + m1[6]* m2[9] + m1[10]* m2[10] + m1[14]* m2[11],
                             m1[3]* m2[8] + m1[7]* m2[9] + m1[11]* m2[10] + m1[15]* m2[11],
                             
                             m1[0]* m2[12] + m1[4]* m2[13] + m1[8]* m2[14] + m1[12]* m2[15],
                             m1[1]* m2[12] + m1[5]* m2[13] + m1[9]* m2[14] + m1[13]* m2[15],
                             m1[2]* m2[12] + m1[6]* m2[13] + m1[10]* m2[14] + m1[14]* m2[15],
                             m1[3]* m2[12] + m1[7]* m2[13] + m1[11]* m2[14] + m1[15]* m2[15]
                             
                             ]);
}
function matrixMultiplyVector3(mat, vec){
    return Vector3( mat[0]*vec.x + mat[4]*vec.y + mat[8]*vec.z + mat[12],
                   mat[1]*vec.x + mat[5]*vec.y + mat[9]*vec.z + mat[13],
                   mat[2]*vec.x + mat[6]*vec.y + mat[10]*vec.z + mat[14]
                   );
}
function matrixRotateVector3(mat, vec){
    return Vector3( mat[0]*vec.x + mat[4]*vec.y + mat[8]*vec.z,
                   mat[1]*vec.x + mat[5]*vec.y + mat[9]*vec.z,
                   mat[2]*vec.x + mat[6]*vec.y + mat[10]*vec.z
                   );
}
function matrixMultiplyVector4(mat, vec){
    return Vector4( mat[0]*vec.x + mat[4]*vec.y + mat[8]*vec.z + mat[12]*vec.w,
                   mat[1]*vec.x + mat[5]*vec.y + mat[9]*vec.z + mat[13]*vec.w,
                   mat[2]*vec.x + mat[6]*vec.y + mat[10]*vec.z + mat[14]*vec.w,
                   mat[3]*vec.x + mat[7]*vec.y + mat[11]*vec.z + mat[15]*vec.w                   
                   );
}
function matrixDebugPrint(mat){
	console.debug(	mat[0] +", " + mat[4] +", " + mat[8] +", " + mat[12] +"\n"+
                  mat[1] +", " + mat[5] +", " + mat[9] +", " + mat[13] +"\n"+
                  mat[2] +", " + mat[6] +", " + mat[10] +", " + mat[14] +"\n"+
                  mat[3] +", " + mat[7] +", " + mat[11] +", " + mat[15]
                  );
}

var def_Vector3_cross= function(v2){
    var newX= this.y * v2.z - this.z * v2.y;
    var newY= this.z * v2.x - this.x * v2.z;
    var newZ= this.x * v2.y - this.y * v2.x;
    return Vector3(newX, newY, newZ);
};
var def_Vector3_length2= function(){
    return this.x * this.x + this.y * this.y + this.z * this.z;
}
var def_Vector3_length= function(){
    return Math.sqrt(this.length2());
}
var def_Vector3_normalize= function(){
    var oneOverLen= 1.0 / this.length();
    this.x *= oneOverLen; 
    this.y *= oneOverLen;
    this.z *= oneOverLen;
};
var def_Vector3_add= function(v2){
    return Vector3( this.x + v2.x, this.y + v2.y, this.z + v2.z );
};
var def_Vector3_minus= function(v2){
    return Vector3( this.x - v2.x, this.y - v2.y, this.z - v2.z );
};
var def_Vector3_scale= function(scalar){
    return Vector3(
                   this.x* scalar,
                   this.y* scalar,
                   this.z* scalar
                   );
}
var def_Vector3_lerp= function(t, v2){
    var invT= 1.0-t;
    return Vector3( 
                   t * v2.x + invT * this.x,
                   t * v2.y + invT * this.y,
                   t * v2.z + invT * this.z
                   );
}
var def_Vector3_copy= function(){
    return Vector3(this.x, this.y, this.z);
}
function Vector3(x, y, z){
    return { 
        x           : x,
        y           : y,
        z           : z,
        cross       : def_Vector3_cross,
        length2     : def_Vector3_length2,
        length      : def_Vector3_length,
        normalize   : def_Vector3_normalize,
        add         : def_Vector3_add,
        minus       : def_Vector3_minus,
        scale       : def_Vector3_scale,
        lerp        : def_Vector3_lerp,
        copy        : def_Vector3_copy
    };
}

var def_Vector2_scale= function(scalar){
    return Vector2(
                   this.x* scalar,
                   this.y* scalar
                   );
}
var def_Vector2_add= function(v2){
    return Vector2( this.x + v2.x, this.y + v2.y);
}
var def_Vector2_copy= function(){
    return Vector2(this.x, this.y);
}
var def_Vector2_lerp= function(t, v2){
    var invT= 1.0-t;
    return Vector2( 
                   t * v2.x + invT * this.x,
                   t * v2.y + invT * this.y
                   );
}
function Vector2(x, y){
    return {
                x       : x,
                y       : y,
                scale   : def_Vector2_scale,
                add     : def_Vector2_add,
                copy    : def_Vector2_copy,
                lerp    : def_Vector2_lerp
            };
}

var def_Vector4_scale= function(scalar){
    return Vector4(
                   this.x* scalar,
                   this.y* scalar,
                   this.z* scalar,
                   this.w* scalar
                   );
}
var def_Vector4_add= function(v2){
    return Vector4( this.x + v2.x, this.y + v2.y, this.z + v2.z , this.w + v2.w );
}
var def_Vector4_lerp= function(t, v2){
    var invT= 1.0-t;
    return Vector4( 
                   t * v2.x + invT * this.x,
                   t * v2.y + invT * this.y,
                   t * v2.z + invT * this.z,
                   t * v2.w + invT * this.w
                   );
}
var def_Vector4_copy= function(){
    return Vector4(this.x, this.y, this.z, this.w);
}
function Vector4(x, y, z, w){
    return {
        x       : x,
        y       : y,
        z       : z,
        w       : w,
        scale   : def_Vector4_scale,
        add     : def_Vector4_add,
        copy    : def_Vector4_copy,
        lerp    : def_Vector4_lerp
    };
}