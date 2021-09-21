/*
 * Simon Says
 * 
 * This code is written with as few programming
 * concepts as possible to make it easier for
 * beginners to understand. There are no functions
 * and there are as few variables as possible.
 * 
 * "simon-says-2.ino" is an improved version of this
 * sketch with good programming practices to make it
 * readable. However, the two function identically.
 * 
 * 
 * Eric Rackelin
 * 9/20/2021
 */

void setup() {
  // set up outputs (LED pins)
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);

  // set up inputs (button pins)
  pinMode(12, INPUT);
  digitalWrite(12, HIGH);
  pinMode(11, INPUT);
  digitalWrite(11, HIGH);
  pinMode(10, INPUT);
  digitalWrite(10, HIGH);
  pinMode(9, INPUT);
  digitalWrite(9, HIGH);

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
  digitalWrite(7, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  delay(100);

  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  delay(200);

  digitalWrite(7, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  delay(100);

  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  delay(200);

  digitalWrite(7, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  delay(100);

  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  delay(1000);

  // start the game
  int moves[100]; // Array to hold the sequence of moves
  int numMoves = 0; // keeps track of how many moves we're at (and our score)
  bool lost = false; // flag for when the player loses

  while (!lost)
  {
    // add a move to the pattern
    moves[numMoves] = random(4); // choose either 0, 1, 2, or 3 at random
    numMoves += 1;

    // play the pattern
    for (int i = 0; i < numMoves; i = i+1)
    {
      int currentMove = moves[i];
      // turn on the LED for this move for half a second
      if (currentMove == 0)
      {
        digitalWrite(7, HIGH);
      }
      else if (currentMove == 1)
      {
        digitalWrite(6, HIGH);
      }
      else if (currentMove == 2)
      {
        digitalWrite(5, HIGH);
      }
      else if (currentMove == 3)
      {
        digitalWrite(4, HIGH);
      }
      delay(500);

      // turn off all LEDs
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, LOW);
      delay(250);
    }

    // player's turn to repeat the pattern
    for (int i = 0; i < numMoves; i = i+1)
    {
      // wait for a button to be pressed
      bool pressed = false;
      int selection;
      while (!pressed)
      {
        if (!digitalRead(12))
        {
          pressed = true;
          selection =  0;
          digitalWrite(7, HIGH);
        }
        else if (!digitalRead(11))
        {
          pressed = true;
          selection =  1;
          digitalWrite(6, HIGH);
        }
        else if (!digitalRead(10))
        {
          pressed = true;
          selection =  2;
          digitalWrite(5, HIGH);
        }
        else if (!digitalRead(9))
        {
          pressed = true;
          selection =  3;
          digitalWrite(4, HIGH);
        }
      }
      delay(500); // debounce
      
      // wait for the pressed button to be released
      if (selection == 0)
      {
        while (!digitalRead(12)) {} // do nothing while the first button is held
      }
      else if (selection == 1)
      {
        while (!digitalRead(11)) {} // do nothing while the second button is held
      }
      else if (selection == 2)
      {
        while (!digitalRead(10)) {} // do nothing while the third button is held
      }
      else if (selection == 3)
      {
        while (!digitalRead(9)) {} // do nothing while the fourth button is held
      }
      // turn off all LEDs
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, LOW);
      delay(100); // debounce

      // check to see if the wrong button was pressed
      if (selection != moves[i])
      {
        lost = true;
        break; // exit the for loop
      }
    }
    // wait a second before showing the next pattern
    delay(1000);
  }
  // the game has been lost, play game over animation
  digitalWrite(7, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  delay(100);

  digitalWrite(7, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  delay(100);

  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
  delay(100);

  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);
  delay(100);

  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  delay(1000);
}
