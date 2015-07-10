/* attribute vec4 vPosition; // (1) works */
attribute vec3 vPosition; // (2) works
attribute vec3 vColour;

varying vec3 fColour;

void main(){
  /* gl_Position = vPosition; // (1) works */
  fColour = vColour;
  gl_Position = vec4 (0.5*vPosition.x, -0.5*vPosition.y, vPosition.z, 1.0 ); // (2 works)
}
