/*
 * Simon Says 2
 * 
 * This version of the simon says code uses more
 * features of the C language than the previous
 * version. It functions the same as
 * "simon-says.ino", but has good programming
 * practices (in my opinion), making it much more
 * readable.
 * 
 * It is still simple code that doesn't implement
 * a time limit or account for pressing multiple
 * buttons at once.
 * 
 * Eric Rackelin
 * 9/20/2021
 */

// define LED pins (makes it easier to read and to
// change pins later)
#define P_LED1 7
#define P_LED2 6
#define P_LED3 5
#define P_LED4 4
// define button pins
#define P_B1 12
#define P_B2 11
#define P_B3 10
#define P_B4 9
// define animation lengths
#define TIME_ON 500
#define TIME_OFF 250
#define TIME_ANIM 100
#define TIME_DEBOUNCE 100
#define TIME_BREAK 1000 // time between new games and turns

// declare functions here so they can be used in
// loop(). We wait until later to define them.
void allOn();
void allOff();
void oneOn();

// Note: you could declare all your variables here if
// you want. However, the C++ standard (which
// Arduino uses) is to declare them as late as
// possible. This is because there may be a cost to
// declaring them in special cases. If you're using
// pure C, then it doesn't matter.

void setup() {
  // set up outputs (LED pins)
  pinMode(P_LED1, OUTPUT);
  pinMode(P_LED2, OUTPUT);
  pinMode(P_LED3, OUTPUT);
  pinMode(P_LED4, OUTPUT);

  // set up inputs (button pins)
  pinMode(P_B1, INPUT);
  digitalWrite(P_B1, HIGH);
  pinMode(P_B2, INPUT);
  digitalWrite(P_B2, HIGH);
  pinMode(P_B3, INPUT);
  digitalWrite(P_B3, HIGH);
  pinMode(P_B4, INPUT);
  digitalWrite(P_B4, HIGH);

  // initalize the random number generator
  randomSeed(analogRead(0));
  // The seed is based on the voltage of a pin with
  // no connections. This means we have no idea
  // what the seed is, as it's basically acting as
  // an antenna, which picks up random noise from
  // the environment.
}

void loop() {
  // new game animation (blink all leds 3 times)
  allOn();
  delay(TIME_ANIM);
  allOff();
  delay(TIME_ANIM);
  allOn();
  delay(TIME_ANIM);
  allOff();
  delay(TIME_ANIM);
  allOn();
  delay(TIME_ANIM);
  allOff();
  delay(TIME_BREAK);

  // start the game
  int moves[100]; // Array to hold the sequence of moves
  int numMoves = 0; // Tracks how many moves we're at
  bool lost = false; // flag for when the player loses

  while (!lost)
  {
    // add a move to the pattern
    moves[numMoves] = random(4);
    numMoves += 1;

    // play the pattern for the player to see
    for (int i = 0; i < numMoves; i = i+1)
    {
      // turn on this move's LED for half a second
      switch (moves[i])
      {
        case 0:
          digitalWrite(P_LED1, HIGH);
          break;
        case 1:
          digitalWrite(P_LED2, HIGH);
          break;
        case 2:
          digitalWrite(P_LED3, HIGH);
          break;
        case 3:
          digitalWrite(P_LED4, HIGH);
          break;
      }
      delay(TIME_ON);
      allOff();
      delay(TIME_OFF);
    }

    // player's turn to repeat the pattern
    for (int i = 0; i < numMoves; i = i+1)
    {
      // wait for a button to be pressed
      // turn on the corresponding LED when it is
      int selection;
      while (1)
      {
        if (!digitalRead(P_B1))
        {
          selection = 0;
          digitalWrite(P_LED1, HIGH);
          break;
        }
        else if (!digitalRead(P_B2))
        {
          selection = 1;
          digitalWrite(P_LED2, HIGH);
          break;
        }
        else if (!digitalRead(P_B3))
        {
          selection = 2;
          digitalWrite(P_LED3, HIGH);
          break;
        }
        else if (!digitalRead(P_B4))
        {
          selection = 3;
          digitalWrite(P_LED4, HIGH);
          break;
        }
      }
      delay(TIME_ON); // debounce
      
      // wait until all buttons are released
      while (!digitalRead(P_B1)
             && !digitalRead(P_B2)
             && !digitalRead(P_B3)
             && !digitalRead(P_B4)) {}
      allOff();
      delay(TIME_DEBOUNCE); // debounce

      // check to see if the wrong button was pressed
      if (selection != moves[i])
      {
        lost = true;
        break; // exit the for loop
      }
    }
    // wait a second before showing the next pattern
    delay(TIME_BREAK);
  }
  // the game has been lost, play game over animation
  oneOn(P_LED1);
  delay(TIME_ANIM);
  oneOn(P_LED2);
  delay(TIME_ANIM);
  oneOn(P_LED3);
  delay(TIME_ANIM);
  oneOn(P_LED4);
  delay(TIME_ANIM);
  allOff();
  delay(TIME_BREAK);
}

// turns off all LEDs
void allOff()
{
  digitalWrite(P_LED1, LOW);
  digitalWrite(P_LED2, LOW);
  digitalWrite(P_LED3, LOW);
  digitalWrite(P_LED4, LOW);
}

// turns on all LEDs
void allOn()
{
  digitalWrite(P_LED1, HIGH);
  digitalWrite(P_LED2, HIGH);
  digitalWrite(P_LED3, HIGH);
  digitalWrite(P_LED4, HIGH);
}

// turns off all LEDs except for one specified by i
void oneOn(int i)
{
  allOff();
  // we can turn everything off right before.
  // It's not efficient, but it's still much faster
  // than any human would be able to notice
  digitalWrite(i, HIGH);
}
