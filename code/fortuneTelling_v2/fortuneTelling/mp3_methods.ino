// for cases music is not played
// ref: https://reprage.com/post/dfplayer-mini-cheat-sheet
void playTrack(uint8_t track) {
   mp3.stop();
   delay(200);
   mp3.playMp3FolderTrack(track);
   delay(200);
   int file = mp3.getCurrentTrack();

   Serial.print("Track:");Serial.println(track);
   Serial.print("File:");Serial.println(file);

}
