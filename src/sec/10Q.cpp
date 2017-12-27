#include "sec/10Q.hpp"

bool sec::10Q::isContextSegment(std::string context)
{
	for (int i=0;;i++)
	{
		std::string s;
		s=getAttribute(context,{0,i},{"xbrl","context"},{xbrli_,xbrli_,""});
		if(s=!"")//we found the right instance
		{
			std::string segment="";
			segment=getChildValue({0,i,0},{"xbrl","context","segment"},{xbrli_,xbrli_,xbrli_);
		}
	}
}

std::string sec::10Q::getValue(std::string name,ns)
{
	//shortcut for getting a quick value from the main xbrl instance file. returns empty if none found
	std::string ret("");
	int index;
	for (index=0;;i++)
	{
		std::string ctx;
		ctx=getAttribute("contextRef",{0,index},{"xbrl",name},{xbrli_,ns,""});
		if (isContextSegment(ctx)){break;}
	}
	ret = getChildValue({0,index},{"xbrl",name},{xbrli_,ns});
}

void sec::10Q::fillFacts()
{
	xbrli_="http://www.xbrl.org/2003/instance"
	sec_=getAttribute("dei",{0},{"xbrl"},{xbrli_,"xmlns"});
	
}