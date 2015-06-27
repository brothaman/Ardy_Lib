// cmu will pan left and right for equal ammounts of time
// the car will move in a progressive forward direction while avoiding obstacles
// - if obstacle incountered
// - 0-turn look left and right and determine the longest open path and take it
// - though if path not open 0-turn 180 and progress backwards
// - if last turn was left the next preferred turn will be right

// function turns to avoid walls while panning the cmucam searching for objects
void Search() {
  front_ping.updateRange( &front_range);
  if(front_range <= RANGEF*25.4) {
    front_ping.updateRange( &front_range);
    if(front_range <= RANGEF*25.4) {
      //debug();
      obstacle_avoidance();
    }
  } else {
    //debug();
    car_speed = 50;
    goforward();
  }
  detachisr();
  pan();
  attachisr();
}

// when ever an obstacle is encounter this function decides the best direction if any to go
void obstacle_avoidance() {
  stop();
  delay(20);
  front_ping.updateRange( &front_range);
  if(front_range <= RANGEF*25.4) {
    //Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    // scan right  
    left_ping.updateRange( &left_range);
    // scan left
    right_ping.updateRange( &right_range);
    // choose direction greater than twelve inches
    if(left_range > right_range && left_range >= RANGEF*25.4) {
      // go left
      attachInterrupt( leftISR, doLeftEncoder, CHANGE);
      attachInterrupt( rightISR, doRightEncoder, CHANGE);
      zero_angle_turn(-90);
      detachInterrupt(leftISR); 
      detachInterrupt(rightISR);
    } else if(right_range > left_range && right_range >= RANGEF*25.4) {
      // go right
      attachInterrupt( leftISR, doLeftEncoder, CHANGE);
      attachInterrupt( rightISR, doRightEncoder, CHANGE);
      zero_angle_turn(90);
      detachInterrupt(leftISR); 
      detachInterrupt(rightISR);
    } else {
      // go backward until left or right range is greater than 12 inches
      attachInterrupt( leftISR, doLeftEncoder, CHANGE);
      attachInterrupt( rightISR, doRightEncoder, CHANGE);
      back_out();
      detachInterrupt(leftISR); 
      detachInterrupt(rightISR);
    }
  }
  // go direction with the most distance
  // if no direction avaialble reverse while pinging until 12 inches left or 
  // 12 inches left or right is available
}

// if no direction is available this function tells the robot to gobackward until the a left or right turn is available
void back_out() {
   while((left_range < RANGEF*25.4 || right_range < RANGEF*25.4) && !pixy.getBlocks()) {
     left_ping.updateRange( &left_range);
     right_ping.updateRange( &right_range);
     left_motor->run(BACKWARD);
     right_motor->run(BACKWARD);
     left_motor->setSpeed(75);
     right_motor->setSpeed(75);
   } 
}

// set car to go forwards
void goforward() {
  left_desired_rpm = car_speed;
  right_desired_rpm = car_speed;
}
// set car to go backwards
void gobackward() {
  left_desired_rpm = -car_speed;
  right_desired_rpm = -car_speed;
}

// zero turn function 
void zero_angle_turn(const double angle_degrees) {
  // 0 turn by angle
  left_motor->setSpeed(0);
  right_motor->setSpeed(0);
  ck = angle_degrees*PI/180*512*75/208;
  left_clicks = 0;
  right_clicks = 0;
  (angle_degrees > 0 ? zadir=1:zadir=-1);
  if(angle_degrees > 0) {
    // add to left subtract from right
    //Serial.println("right");
    while(left_clicks <= ck && right_clicks >= -ck) {
      left_motor->run(FORWARD);
      right_motor->run(BACKWARD);
      left_motor->setSpeed(75);
      right_motor->setSpeed(75);
      //zatdebug();
    }
  } else {
    //Serial.println("left");
    while(left_clicks >= ck && right_clicks <= -ck) {
      left_motor->run(BACKWARD);
      right_motor->run(FORWARD);
      left_motor->setSpeed(75);
      right_motor->setSpeed(75);
      //zatdebug();
    }
  }
  left_clicks = 0;
  right_clicks = 0;
  left_motor->setSpeed(0);
  right_motor->setSpeed(0);
}

// zero turn debug statement
void zatdebug() {
  Serial.print("Left wheel position: "); Serial.println(left_clicks);
  Serial.print("Right wheel position: "); Serial.println(right_clicks);
  Serial.print("Desired clicks: "); Serial.println(ck);
}

// vary wheel speeds to vary turn angle 
void turn(const double attitude) {
  // attitude limited between -300 and 300
//  if(attitude <= 0) {
    // turn left
  left_desired_rpm = car_speed + attitude;
  right_desired_rpm = car_speed - attitude;
    //if(
//  } else {
    // turn right
//    left_desired_rpm = car_speed;
//    right_desired_rpm = car_speed + attitude;
//  }
}

// increment the values of the position variable for the cmu servo
void pan() {
  apos = pos;
  if(dir > 0) {
    apos++;
  } else {
    apos--;
  }
  pos = apos;
  if(pos == 90 || pos == -90) {
    dir = -dir;
  }
  servo.write(pos+90);
}

// stop car
void stop() {
  left_motor->run(RELEASE);
  right_motor->run(RELEASE);
  left_motor->setSpeed(0);
  right_motor->setSpeed(0);
}

// attach encoder ISR
void attachisr() {
  attachInterrupt( leftISR, doLeftEncoder, CHANGE);
  attachInterrupt( rightISR, doRightEncoder, CHANGE);
}

// detach encoder ISR
void detachisr() {
  detachInterrupt(leftISR); 
  detachInterrupt(rightISR);
}
