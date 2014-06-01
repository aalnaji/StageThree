# INFO3220 - Assignment Stage 3

## ASSUMPTIONS

* Default values such as the location of the config file and  are stored in the defaults.h. This may need to be modified to execute.
* Setting up a level is done by first defining the level:
[LEVEL]
level {level number}
ballVelocityFactor {ball speed up factor}
Then, followed be the bricks inside that level and so on for as many levels as you want.
[BLOCK]
... :
... :

* keyboard keys K and L are used to move the paddle.
* Keyboard key S is used to show the highest scores.
* Keyboard key H is used for help.
* Keyboard key Q is used to quit.
* Tests.pro has the paths to stage 3 project files. These paths may need to be changed depening on their location in deployment.

## DESIGN PATTERN
* The behavioural design pattern used in this program is Chain of Responsibility pattern.
* It was used to manage and handle varoius different events in the program.

## EXTENSION
* LeaderBoard Of highest 10 scores.
* Multiple levels that can be configured from the config file.
