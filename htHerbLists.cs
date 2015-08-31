// This file defines all list methods
function htHerbTool::listEffects(%this)
{
  for (%i=0; %i<%this.effectCount; %i++)
  {
    echo(%i @ " - " @ effect[%i]);
  }
}

function htHerbTool::listEffectsShort(%this)
{
  for (%i=0; %i<%this.effectCount; %i++)
  {
    echo(%i @ " - " @ effectShort[%i]);
  }
}

function htHerbTool::listHerbs(%this)
{
  for (%i=0; %i<%this.herbCount; %i++)
  {
    echo(%i @ " - " @ herbName[%i]);
  }
}

function htHerbTool::listHerbsShort(%this)
{
  for (%i=0; %i<%this.herbCount; %i++)
  {
    echo(%i @ " - " @ herbShortName[%i]);
  }
}

function htHerbTool::listHerbEffects(%this)
{
  for (%i=0; %i<%this.herbCount; %i++)
  {
    echo(%i @ " - " @ herbName[%i] @ "\t" @ getEffect(1, %i) @ "\t" @ getEffect(2, %i) @ "\t" @ getEffect(3, %i) @ "\t" );
  }
}

function htHerbTool::listHerbEffectsShort(%this)
{
  for (%i=0; %i<%this.herbCount; %i++)
  {
    echo(%i @ " - " @ herbShortName[%i] @ "\t" @ getEffectShort(1, %i) @ "\t" @ getEffectShort(2, %i) @ "\t" @ getEffectShort(3, %i) @ "\t" );
  }
}
