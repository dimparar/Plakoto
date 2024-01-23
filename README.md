## About
Plakoto is a gaming system tailored for the [Greek Plakoto game](https://en.wikipedia.org/wiki/Plakoto), variant of Backgammon. The game is a simulation at the moment, emphasising on the strategic desision-making capabilities of the AI player, utilizing the Expectiminimax algorithm. Users interact with the system through a Command Line Interface (CLI), ensuring a straightforward and accessible experience.
<br><br>
![image](https://github.com/dimparar/Plakoto/assets/77003325/e1781ae2-cb37-4779-aa3f-a3c8abd9deac)
![image](https://github.com/dimparar/Plakoto/assets/77003325/46d23995-072b-48bf-95c4-e730f3d3bbf7)

## Expectiminimax Algorithm
The [Expectiminimax](https://en.wikipedia.org/wiki/Expectiminimax) algorithm is a variation of the minimax algorithm. The basic difference is the use of chance nodes, which represent points in the game where randomness or uncertainty is introduced, in this case through the rolling of dice. Dice rolls play a crucial role in determining the number of spaces a player can move their checkers. Incorporating chance nodes in the Minimax algorithm involves considering all possible outcomes of random events and adjusting the strategy accordingly.
Emphasizing adaptability, the AI Player is robust, analyzing various in-game scenarios and adjusting its strategies based on opponent moves. The "Choose Depth" feature allows users to customize the AI's decision-making depth, striking a balance between computational resources and desired difficulty levels.

## Structure
```
📦Plakoto
 ┣ 📂examples
 ┣ 📂src
 ┃ ┣ 📂Board
 ┃ ┃ ┣ 📜Board.cpp
 ┃ ┃ ┣ 📜Board.h
 ┃ ┃ ┣ 📜Checker.cpp
 ┃ ┃ ┣ 📜Checker.h
 ┃ ┃ ┣ 📜Dice.cpp
 ┃ ┃ ┗ 📜Dice.h
 ┃ ┣ 📂Player
 ┃ ┃ ┣ 📜Move.cpp
 ┃ ┃ ┣ 📜Move.h
 ┃ ┃ ┣ 📜Player.cpp
 ┃ ┃ ┣ 📜Player.h
 ┃ ┃ ┣ 📜PlayerCPU.cpp
 ┃ ┃ ┗ 📜PlayerCPU.h
 ┃ ┣ 📂Utils
 ┃ ┃ ┗ 📜stdafx.h
 ┃ ┣ 📜Game.cpp
 ┃ ┣ 📜Game.h
 ┃ ┣ 📜Main.cpp
 ┃ ┣ 📜Plakoto.sln
 ┃ ┣ 📜Plakoto.vcxproj
 ┃ ┣ 📜Plakoto.vcxproj.filters
 ┃ ┣ 📜Plakoto.vcxproj.filters.txt
 ┃ ┣ 📜Plakoto.vcxproj.user
 ┃ ┗ 📜Plakoto.vcxproj.xml
 ┣ 📂x64
 ┃ ┣ 📂Debug
 ┃ ┗ 📂Release
 ┗ 📜README.md
```
