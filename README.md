# ARM Space Invaders

Built space invaders game on a Discovery Board. Ship is controlled by rotating the board (detected via the sensors), and the onboard LCD screen is used for display.

## Context
I took a course in Computer Structures, where we did low-level programming on Discovery boards. In our final project, we were tasked with building a game using all of the knowledge we accumulated over the course of the semester. This was an extremely fun project, but also incredibly annoying to debug. Since we are dealing with such low level programming, I couldn't simply use `printf` to do all my debugging as usual as we had to implement our own `printf` to be able to connect the discover board and our computer using serial communication. Fortunately, many of the modules needed to do communication (serial, I2C) and drivers were built over the course of the semester.

## How to Run
To install, download the STM32f30x files, plug in the Discovery board, then run `make install`. There may be other magical things you gotta do to get the Discovery board working properly, so Google will be your friend.

## Preview
[Preview](https://i.imgur.com/mTeTS0B.gifv) is too large for Github. Click on the link to view.
