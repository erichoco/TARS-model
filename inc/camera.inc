#declare checkPoint1=2;
#declare checkPoint2=checkPoint1+5;
#declare checkPoint3=checkPoint2+2;

#declare checkPointC1=checkPoint1+1;
#declare checkPointC2=checkPoint3;

//--------------------------------------------------------------------------
// camera ------------------------------------------------------------------

#macro Camera(mode, dist)
#if (mode = 0)

#declare cam = camera {/*ultra_wide_angle*/ angle 75      // front view
                        location  <0.2+clock*0.5 , 1.2 ,0.2+clock>*dist
                        right     x*image_width/image_height
                        look_at   <4 , 9 , clock*3>}
#elseif (mode = 1) 

#declare cam = camera {/*ultra_wide_angle*/ angle 90   // diagonal view
                            location  <-2.0 , 2+(clock-checkPointC1),15.0-(clock-checkPointC1)*2>*dist
                            right     x*image_width/image_height
                            look_at   <0.0 , 8.0 , 15+(clock-checkPointC1)*14>}
#elseif (mode = 2) 

#declare cam = camera {/*ultra_wide_angle*/ angle 90 // right side view
                            location  <3.0 , 1.0 , 0.0>*dist
                            right     x*image_width/image_height
                            look_at   <0.0 , 8.0 , 5+clock>}
#elseif (mode = 3) 

#declare cam = camera {/*ultra_wide_angle*/ angle 90        // top view
                            location  <0.0 , 3.0 ,-0.001>*dist
                            right     x*image_width/image_height
                            look_at   <0.0 , 8.0 , 0.0>}
                            
#elseif (mode = 4) 

#declare cam = camera {/*ultra_wide_angle*/ angle 90        // moving view
                            location  <1.0, 0.5, (clock-checkPointC2)*2+10>*dist
                            right     x*image_width/image_height
                            look_at   <0.0 , 8.0 , 0>}

#end

camera{cam}

#end
