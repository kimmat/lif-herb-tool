# lif-herb-tool
Herbalism tool for Life is Feudal computer game

## Installation

* Place the files in the directory mod/lif-herb-tool/ under the game root directory.
* Add the following line in the file script/client/init.cs. It should be tha last line in the function "loadAllGuiProperty()" (around line 454).
   exec("mod/lif-herb-tool/init.cs");
   
## Usage

* Open your inventory
* Press ctrl+s to sort all herbs
