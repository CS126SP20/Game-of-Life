# Development

---

#### April 18, 2020
* Added my external library of choice (nlohmann json) to the project configuration
* Created a basic executable and initializing a base cinder app
* Set up the initial 60 x 60 grid on GUI to display the cells
* Filled the grid with statically created cells to test displaying capability

#### April 20, 2020
* Added functionality to main app to serialize cell coordinates from json file
  * Eventually will be able to read from a specific file depending on the user's
  choice of initial configuration of the cells
* Created the grid class to handle the backend logic and movement of the cells

#### April 21, 2020
* Read the coordinates from the json file into a 2D vector to hold information
* Added functionality to fill in the cells from the initial configuration into 
their position on the grid GUI

#### April 22, 2020
* Finished reading from json file and logic of adding basic configuration to GUI
* Added documentation to the grid class' file and cleaned up code

#### April 23, 2020
* Worked on main logic of cell movement, death, and birth 
  * Calculated next generation of cells from the initial configuration
  * Debugged errors with calculation logic and ensured configurations were 
  accurate and matched research
  
#### April 24, 2020
* Worked on figuring out the refresh rate of the main app to eventually deal with
the delay between the display of the next generation of cell configurations
* Began rough draft on how to incorporate user interaction of choosing which
cell configuration to read from the json file and begin with

#### April 26, 2020
* Began to clean up code to replace magic numbers with constant. Still need to 
fully read through code and clean up organization and magic numbers
* Refactored main backend logic to iterate through the configurations of cells
  * The generation that is calculated on vs. the next generation of cells must be
  iterated through in every new configuration to continue until stabilization
* Added to GUI to display the movement of the cells through the generations

#### April 27, 2020
* Added to the draft of user interaction with the app to eventually allow for user
to choose their initial configuration of cells
  * Still need to decide on display of choices of cell configurations and how the
  user will make their choice. Will return to the main display of this.
  
#### April 28, 2020
* Added documentation to both the grid.h and cell_automaton.h files
* Cleaned up code and removed unnecessary prints and commenting
* In progress:
  *  Must further deal with user interaction component to cleanly allow for user to 
  choose with initial cell configuration they want to see
  
#### May 2, 2020
* Focused on UI component to clean up initial display
* Created a type of button to allow for user to choose the initial configuration they want
  * Set up screen to display heading and options

#### May 3, 2020
* Cleaned up code fixing syntax and spacing issues
* Continued to work on display for user and how options are set up
* Added documentation and fixed commenting

#### May 4, 2020
* Added logic to allow for user to pause, resume, and restart the game
* Added these visual components to the UI and updated the main logic to support this
* Worked on adding more documentation
* In progress:
  * Final clean up and documentation of code before submission

#### May 5, 2020
* Completing functionality to allow for user to restart the game
* Working through bugs dealing with not being able to pause/resume after the first round
* Updating documentation from previous submissions

#### May 6, 2020
* Final clean up of code and documentation
* Finishing project for final submission
  * Reviewing code and fixing naming conventions and format