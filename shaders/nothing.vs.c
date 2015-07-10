/* attribute vec4 vPosition; // (1) works */
attribute vec2 vPosition; // (2) works
attribute vec3 vColour;

varying vec3 fColour;

void main(){
  /* gl_Position = vPosition; // (1) works */
  fColour = vColour;
  gl_Position = vec4 (vPosition, 0.0, 1.0 ); // (2 works)
}
