# [Game of Life]

Author: [Swathi Ram]

---

### Project Overview
  For my final project, I created a version of John Conway's Game of Life. This concept is a cellular automaton that was first created by John Conway. The game models how cells interact with one another, living or dying based on its location on the grid and interaction with neighboring cells. In my project, I would like to successfully model the cells data and have a working graphic of the evolution and interaction of the cells. 
### Background knowledge
  I recently heard about this game as its creator, John Conway, recently passed away due to Covid-19. His work remains revolutionary and is continued to be researched on and expanded. The automaton of the cells is based on rules that Conway discovered that would bring the game to life. The interaction of the cells is dependent on their location in the grid and can be explaining in three base rules:
  1. Any live cell with two or three live neighbors survives.
  2. Any dead cell with three live neighbors becomes a live cell.
  3. All other live cells die in the next generation. Similarly, all other dead cells stay dead.

  I worked on this project because of how interested I am not only in John Conway's works but also Alan Turing's whose research layed foundations to this concept. Further, I would like to learn more about modeling and graphing biological data with programs which I can focus on through this project. 
### External Libraries
  The external library I used in this project is JSON https://github.com/nlohmann/json. The initial configuraiton of the cells on the grid is integral to the movement of the cells, so I would like to use JSON files to store the data of the pattern and coordinates of the starting cells. 
### Timeline
  By the end of week one I set up my environment and made sure I was able to work with my libraries in the way I expected. Further, I set up the initial grid and matrices of the automaton and completed the initial configuration of the starting cells. In week 2 I focused on finishing the main logic of the cells' interaction and set up the GUI to display the movement of the cells. In week 3 I finished up any remaining parts of the logic behind the cells' interaction and focused on the display and user interaction.
### Stretch Goals
  After I finished the base project, I worked mainly on adding to and developing the UI of the project. I added features to allow the user to pause and resume the automaton. Additionally, I added functionality to allow the users to restart the automaton and choose another initial configuration.