precision mediump float;

// (1) works
varying vec3 fColour; // (2)

void main(){
  /* gl_FragColor = vec4( 1.0, 1.0, 1.0, 1.0 ); // (1) */
  gl_FragColor = vec4( fColour , 1.0 ); // (2)
}
