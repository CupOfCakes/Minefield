# Minefield
Final project for the "language and tecnique from programming" class.

> ⚠️ **Note**: The game is fully written in **Portuguese (Brazilian)**.

This game was developed in C, as taught in the course.
## How it works

- The game generates a minefield using two global variables:
  - `TAM` defines the size of the field.
  - `MINAS` defines the number of mines.

- At the start, one safe cell (with 0 adjacent mines) is revealed to help the player begin.

- The player is shown the field and must choose an action:
  - Open a cell.
  - Mark (or flag) a cell.

- After choosing the action, the player selects the row and column.

- The game continues until one of the following happens:

### Game Over Conditions
- The player opens a cell that contains a mine.
- The player correctly marks all the mines.
- The player opens all the non-mine cells.



