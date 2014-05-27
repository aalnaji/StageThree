# INFO3220 - Assignment Stage 2

## ASSUMPTIONS

* Default values such as the location of the config file are stored in the defaults.h. This may need to be modified to execute.

## DESIGN PATTERN

The _structural_ design pattern used in this program is __Apdater__ pattern. It was used on the config class, as an adapter to a vector container. The config class contains many different config items and can be extentend to include others.

## EXTENSION

* You can add extra blocks by left-clicking in the box.
* You can add extra balls by right-clicking in the box.
* Any new items are given the default values found in defaults.h.
* Balls have correct elastic collisions.
* The bricks change colour as their lives diminish.
* You can specify the hue of each item, block or ball using the colorHue