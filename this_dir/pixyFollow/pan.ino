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
  
