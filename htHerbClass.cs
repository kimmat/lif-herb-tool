// htHerb class functions
function htHerb::onAdd(%this)
{
  echo("HT debug: created htHerb" @ %this @ " successfully");
}

function htHerb::onRemove(%this)
{
  echo("HT debug: removed htHerb" @ %this @ " successfully");
}

function htHerb::isThisHerb(%this, %filename)
{
  return endsWith(%filename, %this.imageFilename, false);
}


// HerbTool class functions
function HerbTool::onAdd(%this)
{
  echo("HT debug: created HerbTool:" @ %this @ " successfully");
}

function HerbTool::onRemove(%this)
{
  echo("HT debug: removed HerbTool:" @ %this @ " successfully");
}

function HerbTool::getHerbId(%this, %filename)
{
  for (%i=0; %i<%this.herbCount; %i++)
  {
    if ( %this.herb[%i].isThisHerb(%filename) == true )
	{
	  return %i;
	}
  }
  
  return -1;
}

function HerbTool::sortInventories(%this)
{
  %i_max = PlayGui.getCount();
  for (%i=0; %i<%i_max; %i++)
  {
    %obj = PlayGui.getObject(%i);
	if ( %obj.isMemberOfClass("GuiInventoryContainer") )
	{
	  %this.sortContainer(%obj);
	}
  }
}

function HerbTool::sortContainer(%this, %container)
{
  // init herb stack count
  for (%i=0; %i<%this.herbCount; %i++)
  {
    %stack[%i] = 0;
  }

  %i_max = %container.getCount();
  for (%i=0; %i<%i_max; %i++)
  {
    %obj = %container.getObject(%i);
	if ( %obj.isMemberOfClass("GuiInventoryItem") )
	{
	  %herbId = %this.getHerbId(%obj.bitmap);
	  if ( %herbId >= 0 )
	  {
	    %this.sortHerb(%herbId, %obj, %stack[%herbId]);
		%stack[%herbId]++;
	  }
	}
  }
}

function HerbTool::sortHerb(%this, %herbId, %invItem, %stackCount)
{
  %startX = 12;
  %startY = 32;
  %stackSpace = 10;
  %spaceX = 70;
  %spaceY = 32;
  %rows = 14;
  
  %row = %herbId % %rows;
  %col = mFloor(%herbId/%rows);
  
  %x = %startX + (%col*%spaceX) + (%stackSpace*%stackCount);
  %y = %startY + (%row*%spaceY);
  %pos = %x @ " " @ %y;
  
  echo(%pos);
  
  %invItem.position = %pos;
}

$htGlobal = ht.getId();

function htSortInventories()
{
  echo("test");
  $htGlobal.sortInventories();
}

GlobalActionMap.bindObj(keyboard, "ctrl s","sortInventories", $htGlobal);
