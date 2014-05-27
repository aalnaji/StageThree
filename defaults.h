#ifndef DEFAULTS_H
#define DEFAULTS_H

#include <QColor>

namespace Defaults
{

//change this path depending on the location of your config file
const std::string CONFIG_PATH ="//Users//Alnaji//Documents//info3220//A3//AssignmentThreeBaseFour//config.config";

// BOX DEFAULTS
const int BOX_HEIGHT = 500;
const int BOX_WIDTH = 800;
const QColor BOX_COLOR = "#000000";

// BALL DEFAULTS
const float BALL_X_COORDINATE = 300;
const float BALL_Y_COORDINATE = 250;
const float BALL_RADIUS = 10;
const float BALL_X_VELOCITY = -0.9;
const float BALL_Y_VELOCITY = -2.1;
const QColor BALL_COLOR = "#FF0000";

// BLOCK DEFAULTS
const int BLOCK_X_COORDINATE = 400;
const int BLOCK_Y_COORDINATE = 400;
const int BLOCK_WIDTH = 99;
const int BLOCK_HEIGHT = 49;
const int BLOCK_LIVES = 3;
const QColor BLOCK_COLOR = "#00FF00";

}


#endif // DEFAULTS_H
