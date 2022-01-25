color([0/255, 0/255, 0/255]) {
    dpadHull();
    buttonHull();
    skjermHull();
    skjermHull();
}

module dpadHole() {
    d = 20;    //not acurate number 
    xPos = 55; //not acurate number
    yPos = 15;  //not acurate number
    
    translate([xPos, yPos, 0]) {
        circle(r=d/2);
        
    }
}

module ssButtonHole() {
    xPos = -65; //not acurate number //dist from centre
    yPos = -10;   //not acurate number // dist from centre

    translate([xPos, yPos, 0]) {
        
    }

}

module speakerHole() {
    xPos = -65; //not acurate number //dist from centre
    yPos = -10;   //not acurate number // dist from centre

    translate([xPos, yPos, 0]) {
        
    }

}


module gameButtonHole() {
    d = 16;     //not acurate number //diameter
    xPos = -65; //not acurate number //dist from centre
    yPos = 0;   //not acurate number // dist from centre

    xDist = 20;  //not acurate number
    yDist = 30;  //not acurate number

    // translate([xPos, yPos, 0]) {
    //     circle(r=2); //centre pos
    // }
    translate([xPos+xDist/2, yPos, 0]) {
        circle(r=d/2); //a
    }
    translate([xPos-xDist/2, yPos, 0]) {
        circle(r=d/2); //y
    }
    translate([xPos, yPos+yDist/2, 0]) {
        circle(r=d/2); //x
    }
    translate([xPos, yPos-yDist/2, 0]) {
        circle(r=d/2); //b
    }
}

module screenHole() {
    wScreen = 85;
    hScreen = 56;
    //skjerm
    square(size=[wScreen, hScreen], center=true);
}
