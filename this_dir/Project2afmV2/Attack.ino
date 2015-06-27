// precious found attack!!
// avoid obstacles left and right whill constantly approaching precious
// priority
// - level 1 
// -- highest priority of the cmucam will be precious tracking
// -- highest priority of the car will be to avoid objects
// --- using ping sensors a minimum distance of 8 inches from the wall while tracking
// --- 

// function to continually approach the object 
// includes functionality track object using pid and servo
// also simultaneously varies the turn attitude to reduce servo angle effectively 
void Attack() {
  car_speed = 100;
  detachInterrupt(leftISR); 
  detachInterrupt(rightISR);
  follow();
  attachInterrupt( leftISR, doLeftEncoder, CHANGE);
  attachInterrupt( rightISR, doRightEncoder, CHANGE);
  // use pid to turn car
  detachisr();
  actual_servo_angle = servo.read() - 90;
  attachisr();
  // change pid tuning parameter with servo angle
  if(actual_servo_angle > 0) {
    dirt = -1;
  } else {
    dirt = 1;
  }
  if(actual_servo_angle >= 75 || actual_servo_angle <= -75) { // far out side of safe zone
    // change tuning set to agressive attitude
    // more agressive tuning parameters
    car_speed = 0;
    attitude = dirt*50;
  } else if((actual_servo_angle < 75 && actual_servo_angle >= 15) || 
  (actual_servo_angle > -75 && actual_servo_angle <= -15)) {  // just out side of safe zone
    // set to less aggressive attitude
    // much less aggressive tuning paramters
    car_speed = 50;
    attitude = dirt*abs(actual_servo_angle);
  } else if(actual_servo_angle < 15 && actual_servo_angle > -15) {  
    // in safe zone
    car_speed = 50;
    attitude = 0;
  }
  //angle_pid.updateValues( desired_servo_angle, actual_servo_angle, &attitude);
  turn( attitude);
  //debug();
}

// function using pid to calculate and write servo angle according to the objects x position
void follow() {
  pix.x_position = pixy.blocks[0].x-160;
  if(pix.x_position >= 120 || pix.x_position <= -120) {
    // double propotional parameter
    ckp = 2*.0325;
  } else {
    // set back to initial
    ckp = .0325;
  }
  cmu_pid.updateParameters( &ckp, &cki, &ckd);
  cmu_pid.updateValues( 0, pix.x_position, &pos);
  servo.write(pos+90);
}
