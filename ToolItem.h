#pragma once
#include "gameNode.h"



class ToolItem
{
protected:


	string _name;
	string _tag;


public:
	ToolItem() { ; }
	virtual ~ToolItem() { ; }


	virtual inline string GetName() { return _name; }
	virtual inline void SetName(string name) { _name = name; }

	virtual inline string GetTag() { return _tag; }
	virtual inline void SetTag(string tag) { _tag = tag; }

	virtual void Action() = 0;

};

