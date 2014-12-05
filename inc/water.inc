// PoVRay  3.7 Scene File " ... .pov"
// author:   ...  
// date:   ...
//--------------------------------------------------------------------------
#version 3.7;
global_settings{ assumed_gamma 1.0 }
#default{ finish{ ambient 0.1 diffuse 0.9 }} 
//--------------------------------------------------------------------------
// adding a photon{} block to global_settings activates photon mapping.
// photons also need to be adjusted for light sources and objects.
global_settings {
  photons {
    spacing 0.01                 // specify the density of photons
    //count 100000               // alternatively use a total number of photons

    //gather min, max            // amount of photons gathered during render [20, 100]
    //media max_steps [,factor]  // media photons
    //jitter 1.0                 // jitter phor photon rays
    //max_trace_level 5          // optional separate max_trace_level
    //adc_bailout 1/255          // see global adc_bailout
    //save_file "filename"       // save photons to file
    //load_file "filename"       // load photons from file
    //autostop 0                 // photon autostop option
    //radius 10                  // manually specified search radius
    // (---Adaptive Search Radius---)
    //steps 1
    //expand_thresholds 0.2, 40
  }
}
//---------------------------------------------------------------------------
#include "colors.inc"
#include "textures.inc"
#include "glass.inc"
#include "metals.inc"
#include "golds.inc"
#include "stones.inc"
#include "woods.inc"
#include "shapes.inc"
#include "shapes2.inc"
#include "functions.inc"
#include "math.inc"
#include "transforms.inc"
// sun ---------------------------------------------------------------------
light_source{<1500,2500, -500> color White
// photon block for a light source
  photons {
    refraction on
    reflection on
    //area_light
  }
}
// fog on the ground -------------------------------------------------
fog { fog_type   2
      distance   50
      color      White  
      fog_offset 0.1
      fog_alt    1.5
      turbulence 1.8
    }
// sea ---------------------------------------------------------------------
difference{ 
plane{ <0,1,0>, 0 } 
box{ <-3,-1,-3>,<3,0.1,3> }

       texture{ Polished_Chrome
                normal { bumps 1.75 scale 0.2 turbulence 0.25 } 
                finish { reflection 0.60}
                scale  3
              }
  photons{
    collect off       // ignore photons
  }

}