#pragma once
#include "PluginSettings.h"

//A class that is convertable
//*Currently only converts to string but can be made to convert to other things
class PLUGIN_API Convertable
{
public:
	virtual std::string ToString()=0;
	virtual void SetValue(std::string toConv) = 0;
};