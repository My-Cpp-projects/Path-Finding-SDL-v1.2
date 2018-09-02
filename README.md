# Path-Finding-SDL-v1.2
Implementation of A star algorithm using SDL v1.2 for visualization

 As the SDL v1.2 is old, only downloading the libs may not work. One has to download the source code from the official site: 
 https://www.libsdl.org/download-1.2.php. Then the source projects needs to be compiled by the IDE that you use. This will
 generate all the files that you need for the project. Then just link the appropriate files (libs, includes etc) to the project and 
 it will work :)

Green squares represent the nodes that are in open set, while blue ones are the ones that are in closed set.
The target node is drawn in blue and start is drawn green (because it is in open set from the start).

The white nodes are the nodes where it is possible to move. The black ones are the nodes that represent walls.
If you see a red node that means that passed map has unrecognized terrain type.

At first user is given a map with all nodes possible to move. Using the left mouse button, clicking on nodes that represent
walls will delete the wall, and clicking on white nodes will result turning them into walls.

To start the path search press Enter (both enters will work !).

To quit the application either press escape, or close buttons.


