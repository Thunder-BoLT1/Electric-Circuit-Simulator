#include "items.h"

//Override Pure Virtual Function For IVS
void IVSItem::WriteToMatrix(){


}
void IVSItem::ReadFromMatrix(){


}

IComponent* IVSItem::CreateCopy(){ return new IVSItem(*this); }

//Override Pure Virtual Function For ICS
void ICSItem::WriteToMatrix(){


}
void ICSItem::ReadFromMatrix(){


}

IComponent* ICSItem::CreateCopy(){ return new ICSItem(*this); }

//Override Pure Virtual Function For RES
void RESItem::WriteToMatrix(){


}
void RESItem::ReadFromMatrix(){


}

IComponent* RESItem::CreateCopy(){ return new RESItem(*this); }
