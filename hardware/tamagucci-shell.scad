// import("file.svg");

frontShell();

module frontShell() {
    difference() {
        frontShellWithoutHoles();
        frontHoles();
    }
}



module frontShellWithoutHoles() {
    difference() {
        union(){
            linear_extrude(15){
                translate([0, 0, 0]) {
                    square(size=[150, 70], center=true);
                }
            }
        }
        v = 2; 
        union(){
            translate([v/2, v/2, 0.1]) {
            linear_extrude(15){
                    square(size=[150-v*2, 70-v*2], center=true);
                }
            }
        }
    }
}

module frontHoles() {
    translate([0, 0, -0.1]) {
        linear_extrude(10){
            color([0/255, 0/255, 0/255]) {
                dpadHole(60,15);
                ssButtonHole(60,-20);
                gameButtonHole(-60,10);
                speakerHoles(-60,-20);
                screenHole();
            }
        }
    }
}

module hsLogo(x,y) {
    translate([x, y, 0]) {
        linear_extrude(height=10, center=true, convexity=10, twist=0) {
        import("Icon_green_transparent.svg");
        }
    }
}

module dpadHole(xPos,yPos) {
    d = 20;    //not acurate number 
    
    translate([xPos, yPos, 0]) {
        circle(r=d/2);
    }
}

module ssButtonHole(x,y) {

    x = x-2; //just to prettify. is bad code.

    d=6;  //depth
    w=10;  //heigth

    xDist = 0; // dist between buttons.
    yDist = 8;

    translate([x, y, 0]) {
        union(){
            circle(r=d/2, $fn=20);
            translate([w-d, 0, 0]) {
                circle(r=d/2, $fn=20);
            }
            translate([w/2 - d/2, 0, 0]) {
                square(size=[w-d, d], center=true);
            }
        }
    }
    translate([x+xDist, y+yDist, 0]) {
        union(){
            circle(r=d/2, $fn=20);
            translate([w-d, 0, 0]) {
                circle(r=d/2, $fn=20);
            }
            translate([w/2 - d/2, 0, 0]) {
                square(size=[w-d, d], center=true);
            }
        }
    }



}

module speakerHoles(xPos,yPos) {

    d=1; //diameter of lines
    l = 20; //mex length of diagonale in lines
    r = 37; //positive verdier.

    
    translate([xPos, yPos, 0]) {

        rotate([0, 0, r]) {
            union(){
                
                speakerHOleLine(d,l);
                //not geometrically parametric
                per = 0.7;
                translate([-cos(r), sin(r)+2*d, 0]) 
                    speakerHOleLine(d,l*per);
                translate([+cos(r), -sin(r)-2*d, 0]) 
                    speakerHOleLine(d,l*per);
                per2 = 0.4;
                translate([-2*cos(r), 2*sin(r)+4*d, 0]) 
                    speakerHOleLine(d,l*per2);
                translate([2*cos(r), -2*sin(r)-4*d, 0]) 
                    speakerHOleLine(d,l*per2);
                

            }
        }
    }
}
module speakerHOleLine(d,l) {
        union(){
            translate([(-l+d)/2, 0, 0]) {
            circle(r=d/2, $fn=15);
            }
            translate([(l-d)/2, 0, 0]) {
                circle(r=d/2, $fn=15);
            }
            square(size=[l-d, d], center=true);
        }
    
}



module gameButtonHole(xPos,yPos) {
    d = 10;     //not acurate number //diameter

    xDist = 15;  //not acurate number
    yDist = 20;  //not acurate number

    res = 30; //resolution of circle (polygon count)

    // translate([xPos, yPos, 0]) {
    //     circle(r=2); //centre pos
    // }
    translate([xPos+xDist/2, yPos, 0]) {
        circle(r=d/2 , $fn=res); //a
    }
    translate([xPos-xDist/2, yPos, 0]) {
        circle(r=d/2 , $fn=res); //y
    }
    translate([xPos, yPos+yDist/2, 0]) {
        circle(r=d/2 , $fn=res); //x
    }
    translate([xPos, yPos-yDist/2, 0]) {
        circle(r=d/2 , $fn=res); //b
    }
}

module screenHole() {
    wScreen = 85;
    hScreen = 56;
    //skjerm
    square(size=[wScreen, hScreen], center=true);
}
