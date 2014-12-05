#include "textures.inc" 
#include "metals.inc"
#include "shapes.inc"


#macro box_border_base(dim, xLen, yLen, zLen)

#local triBase=
// linear prism in x-direction: from ... to ..., number of points (first = last)
prism { 0.00, zLen, 4
        <0.00, 0.00>, // first point
        <0.05, 0.00>, 
        <0.00, 0.05>,
        <0.00, 0.00>  // last point = first point!!!
      }; // end of prism --------------------------------------------------------

union {
    prism {
        triBase
        rotate<0,0,0>
        translate<0,0,0>
    } 
    prism {
        triBase
        rotate<0,-90,0>
        translate<xLen,0,0>
    }
    prism {
        triBase
        rotate<0,90,0>
        translate<0,0,yLen>
    }
    prism {
        triBase
        rotate<0,180,0>
        translate<xLen,0,yLen>
    }
    #if (dim = 0)
        rotate<0,0,0> translate<0,0,0>
    #elseif (dim = 1)
        rotate<-90,0,0> translate<0,0,zLen>
    #elseif (dim = 2)
        rotate<0,0,-90> translate<0,xLen,0>
    #end
}
     
#end


#macro box_border(mode)

#if (mode = 0)
union {
    box_border_base(0, 0.5, 0.5, 1)
    box_border_base(1, 0.5, 1, 0.5)
    box_border_base(2, 1, 0.5, 0.5)
}

#elseif (mode = 1)
union {
    box_border_base(0, 0.5, 0.5, 4)
    box_border_base(1, 0.5, 4, 0.5)
    box_border_base(2, 4, 0.5, 0.5)
}

#end

#end


#macro small_box(yPos)

difference {
    box { <0, 0, 0>, <0.5, 1, 0.5> }
    box_border(0)
    texture { T_Chrome_1A
        finish { phong 1 reflection {0.8 metallic 1.0} ambient 0 diffuse 0.7}
    }
    translate<0, yPos, 0>
}

#end

#macro long_box(yPos)

difference {
    box { <0, 0, 0>, <0.5, 4, 0.5> }
    box_border(1)
    texture { T_Chrome_3A
        pigment{ color rgb<0.1, 0.1, 0.1>}
        finish { phong 1 reflection {0.8 metallic 1.0} ambient 0 diffuse 0.7}
    }
    translate<0, yPos, 0>
}

#end
    
    
#macro bar_unit(xPos, zPos)

union {
        small_box(0) small_box(1) small_box(2) small_box(3)
        long_box(4) long_box(8)
        small_box(12) small_box(13) small_box(14) small_box(15)
        translate<xPos,0,zPos>
      }

#end


#macro bar(xPos, zPos)

union {
    bar_unit(0,0) bar_unit(0.5,0) bar_unit(1,0) bar_unit(1.5,0)
    bar_unit(0,0.5) bar_unit(0.5,0.5) bar_unit(1,0.5) bar_unit(1.5,0.5)
    bar_unit(0,1) bar_unit(0.5,1) bar_unit(1,1) bar_unit(1.5,1)
    bar_unit(0,1.5) bar_unit(0.5,1.5) bar_unit(1,1.5) bar_unit(1.5,1.5)
    translate<xPos, 0, zPos>
}

#end


#macro screen()
    
union {
    box { <-0.01, 0.00, -0.05>,<2.01, 2.00, 2.05>   
        material {
            texture { 
                pigment { image_map { gif "resource/code.gif" } }
                finish { diffuse 0.1 reflection 0.1  
                specular 0.8 roughness 0.0003 phong 1 phong_size 400 }
            }
            interior { ior 1.5 caustics 0.5 }
        }
        scale <1,1,1> rotate<0,0,0> translate<0,12,0> 
    }
}    

#end


#macro leg_walk(deg, pivot, index)                                                     

scale <1,1,1> rotate<deg,0,0> translate<index*2,1*sin(deg*degToRad),-pivot*tan(deg*degToRad)>

#end    

#macro leg_run(deg, pivot, index)                                                     

scale <1,1,1> rotate<deg,0,0> translate<index*2,pivot-pivot*cos(deg*degToRad)+1*sin(deg*degToRad),-pivot*sin(deg*degToRad)+1-1*cos(deg*degToRad)>

#end


#macro leg1(deg, pivot, mode)

union { bar(0,0)    
        texture { pigment{ color rgb<1.00, 1.00, 1.00>}  
                  finish { phong 1 reflection{ 0.00 metallic 0.00} } 
                }
                        
        #if (mode = 1)
            leg_walk(deg, pivot, 0)
        #elseif (mode = 2)
            leg_run(deg, pivot, 0)
        #else
            scale <1,1,1> rotate<0,0,0> translate<0,0,0>
        #end
      }

#end


#macro leg2(deg, pivot, mode)

union { bar(0,0)
        screen()   
        texture { pigment{ color rgb<1.00, 1.00, 0.00>}  
                  finish { phong 1 reflection{ 0.00 metallic 0.00} } 
                }

        #if (mode = 1)
            leg_walk(deg, pivot, 1)
        #elseif (mode = 2)
            leg_run(deg, pivot, 1)
        #else
            scale <1,1,1> rotate<0,0,0> translate<2,0,0>
        #end  
      }

#end


#macro leg3(deg, pivot, mode)

union { bar(0,0)

        //Bevelled_Text(Font, String, Cuts, BevelAng, BevelDepth, Depth, Offset, UseMerge)
        object{ 
            Bevelled_Text("calibri.ttf", "MINES", 10 , 35, 0.045, 1, 0, 0)
            texture { 
                pigment { color rgb<0.2,0.1,0.0>} 
                normal { bumps 0.2 scale 0.01}
                finish { specular 1 reflection { 0.4 metallic 0.8 } }
            }
            rotate<180,0,90>
            scale<1,1,1>*1.2 
            translate<1.1,8.5,2.1>
        }
   
        screen()
        
   
        #if (mode = 1)
            leg_walk(deg, pivot, 2)
        #elseif (mode = 2)
            leg_run(deg, pivot, 2)
        #else
            scale <1,1,1> rotate<0,0,0> translate<4,0,0>
        #end
      }

#end
            
            
#macro leg4(deg, pivot, mode)
union { bar(0,0)   

        texture { pigment{ color rgb<0.00, 1.00, 1.00>}  
                  finish { phong 1 reflection{ 0.00 metallic 0.00} } 
                }

        #if (mode = 1)
            leg_walk(deg, pivot, 3)
        #elseif (mode = 2)
            leg_run(deg, pivot, 3)
        #else
            scale <1,1,1> rotate<0,0,0> translate<6,0,0>       
        #end        
      }

#end

