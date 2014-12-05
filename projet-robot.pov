#include "inc/basics.inc"
#include "inc/robot.inc"
#include "inc/water.inc"
#include "inc/camera.inc" 

/*
BASIC_LIGHTS()
LIGHT()

// Le repere avec les axes X,Y,Z
#declare Laxe=100;
#declare Raxe=0.02;
//AXES_XYZ(Laxe,Raxe)

// Un quadrillage
//DAMIER()


// Choix de la vue
#declare distance_camera =30;
//vue_dessus(distance_camera) 
//vue_cote(distance_camera/2) 
//vue_face(distance_camera)
//vue_mouve(distance_camera) 
//vue_courante(distance_camera)
*/

#declare degToRad=2*pi/360;
#declare degMax=30;
                    
#macro walk(d_theta, pivot)

#local curClock = clock-checkPoint1;

#declare degree = cos((d_theta*curClock-90)*degToRad)*degMax;

#local curIter = int((d_theta*curClock+90)/180);

#if (mod(curIter,2) = 0)
    #declare position = curIter*pivot*tan(degMax*degToRad)*2+pivot*tan(degree*degToRad);
#else
    #declare position = curIter*pivot*tan(degMax*degToRad)*2-pivot*tan(degree*degToRad);
#end

#end


#macro run(d_theta, pivot)

#local curClock = clock-checkPoint3;

#declare degree = (d_theta*clock);

#local curIter = int(d_theta*clock/45);

#declare position = curClock*40;

#end


#macro legs(d_theta, pivot, mode)

#if (mode = 1)
    walk(d_theta, pivot)
    union {
        leg1(degree, pivot, mode)
        leg2(-degree, pivot, mode)
        leg3(-degree, pivot, mode)
        leg4(degree, pivot, mode)
        translate<0,0,position>
    }

#elseif (mode = 2)
    run(d_theta, pivot)
    #local degree1 = degree-45;
    #local degree2 = degree-135;
    #local degree3 = degree-90;
    #debug concat("clock: ", str((clock*10-checkPoint3*10),1,0), "\n")
    #if (clock*10-checkPoint3*10 < 10)
        #if (mod(degree,360) < 45)
            #local degree1 = 0;
            #local degree2 = 0;
            #local degree3 = 0;
        #elseif (mod(degree,360) < 90)
            #local degree2 = 0;
            #local degree3 = 0;
        #elseif (mod(degree,360) < 135)
            #local degree3 = 0;
        #end
    #end
    union {
        leg1(degree1, pivot, mode)
        leg2(degree2, pivot, mode)
        leg3(degree3, pivot, mode)
        leg4(degree, pivot, mode)
        translate<0,0,position>
    }
      
#elseif (mode = 3)  
    union {
        leg1(0, pivot, mode)
        leg2(0, pivot, mode)
        leg3(0, pivot, mode)
        leg4(0, pivot, mode)
        translate<0,0,(checkPoint2-checkPoint1)*2*pivot*tan(degMax*degToRad)*2>
    }

#else
    union {
        leg1(0, pivot, mode)
        leg2(0, pivot, mode)
        leg3(0, pivot, mode)
        leg4(0, pivot, mode)
        translate<0,0,0>
      }
#end

#end


/* main */ 

#if (clock < checkPointC1)
    Camera(0,10)
#elseif (clock < checkPointC2)
    Camera(1,8)
#elseif (clock < 15)
    Camera(4,10)
#end 
   

#if (clock < checkPoint1)
    legs(360, 8, 0)
#elseif (clock < checkPoint2)
    legs(360, 8, 1)
#elseif (clock < checkPoint3)
    legs(360, 8, 3)
#elseif (clock < 15)
    legs(720, 8, 2)
#else
#end