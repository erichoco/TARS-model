// ==== Standard POV-Ray Includes ====
#include "colors.inc"	  // Standard Color definitions
#include "textures.inc"	  // Standard Texture definitions
#include "functions.inc"  // internal functions usable in user defined functions
#include "metals.inc" 


// perspective (default) camera

#macro vue_courante(Distance)
//===================
camera {
//  orthographic
  perspective
  location  <10.0, 5.0, 10.0>/4*Distance
  look_at   <0.0, 0.0,  0.0> 
  right     x*image_width/image_height
}           
#end

#macro vue_mouve(Distance)
//===================
camera {
//  orthographic
  perspective
  location  <10.0, 5.0, 10.0+clock*10>/4*Distance
  look_at   <0.0, 0.0,  0.0> 
  right     x*image_width/image_height
}           
#end

#macro vue_dessus(Distance)
//===================
camera {
  orthographic
  location  <0.0,Distance , 0.0>
  look_at   <0.0, 0.0,  0.0> 
}           
#end


#macro vue_face(Distance)
//===================
camera {
  orthographic
  location  <Distance, 0, 0.0>
  look_at   <0.0, 0,  0.0> 
}           
#end

#macro vue_cote(Distance)
//===================
camera {
  orthographic
  location  <0,0,Distance>
  look_at   <0.0, 0.0,  0.0> 
}           
#end

#macro vue_dessus(Hauteur)
//===================
camera {
  orthographic
  location  <0.0, Hauteur, 0.0>/4
  look_at   <0.0, 0.0,  0.0> 
}           
#end


// ==========================================================================


#macro AXES_XYZ(Laxe,Raxe)
//===========================================  
// Les 3axes 
// Laxes = longueur des axes
// Raxes = Rayon des axes
//
#if ( Laxe <= 0 )
  #declare Laxe=5;
#end
#if ( Raxe <= 0 )
//  #declare Raxe=0.1;
  #declare Raxe=Laxe/50;
#end
//
#declare AxeX= union {
cylinder {  <0,0,0> <Laxe,0,0>  Raxe }
cone { <Laxe,0,0> 2*Raxe <Laxe+4*Raxe,0,0> 0 }  
}
#declare AxeY= union {
cylinder {  <0,0,0> <0,Laxe,0>  Raxe }
cone { <0,Laxe,0> 2*Raxe <0,Laxe+4*Raxe,0> 0 }  
}
#declare AxeZ= union {
cylinder {  <0,0,0> <0,0,Laxe>  Raxe }
cone { <0,0,Laxe> 2*Raxe <0,0,Laxe+4*Raxe> 0 }  
}
//
object { AxeX  pigment { color red 1}  }
object { AxeY  pigment { color green 1}  } 
object { AxeZ  pigment { color blue 1}  } 
#end

//==============================================

#macro DAMIER()
// ==========================
// An infinite planar surface
// plane {<A, B, C>, D } where: A*x + B*y + C*z = D
plane {
  y, // <X Y Z> unit surface normal, vector points "away from surface"
  0.0 // distance from the origin in the direction of the surface normal
  hollow on // has an inside pigment?     
  
  pigment {
  // solid pattern for use in texture/pigment/normal(/density)
// cube checker pattern, alternates color1 and color2
  checker
    color rgbt <1, 1, 1,0.5>,
    color rgbt <0, 1, 0,0.5>        
    }

}  // plane   
#end

#macro BASIC_LIGHTS()
// ====================================
// An area light (creates soft shadows)
// WARNING: This special light can significantly slow down rendering times!
light_source {
  0*x                 // light's position (translated below)
  color rgb 1.0       // light's color
  translate <0,5,5>   // <x y z> position of light
}

light_source {
  0*x                 // light's position (translated below)
  color rgb 1.0       // light's color
  translate <2,0.15,0>   // <x y z> position of light
}    
#end

#macro LIGHT()  
// // general light definition
light_source {
  <0, 10, 10+clock*10>      // position of the light source
  color rgb 1.0     // color of the light

  // put this inside a light_source to make it parallel
  parallel
  point_at <5, 0, -10>

  // put this inside a light_source to add light fading
  fade_distance 10
  fade_power 2
 }
#end

#macro HALL()
plane {
  y, // <X Y Z> unit surface normal, vector points "away from surface"
  0.0 // distance from the origin in the direction of the surface normal
  hollow on // has an inside pigment?
         texture { Polished_Chrome
                   // pigment{ color rgb<1,0,0> } 
                   finish { phong 1 }
                 } // end of texture 

  //pigment { color rgb<1,1,1> }    
  
}
/*plane {
  x, // <X Y Z> unit surface normal, vector points "away from surface"
  -40 // distance from the origin in the direction of the surface normal
  hollow on // has an inside pigment?
 

  
  pigment { color rgb<0,0,0> }    
  
}
plane {
  x, // <X Y Z> unit surface normal, vector points "away from surface"
  40 // distance from the origin in the direction of the surface normal
  hollow on // has an inside pigment?
 

  
  pigment { color rgb<0,0,0> }    
  
} */   
#end
