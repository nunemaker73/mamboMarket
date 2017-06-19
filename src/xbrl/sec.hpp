#ifndef _SEC_H
#define _SEC_H
/*
    Copyright (C) {2016}  {Craig Nunemaker}

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/*
	The following code was derived from sec-xbrl python code available on github at
	https://github.com/altova/sec-xbrl which was released under the apache 2,.0 license.
	the apache 2.0 license is compatible with GPL 3.
*/

#include <string>
#include <vector>
#include "url.hpp"

namespace sec{

class report
{
private:
public:
	Url url_;
	report(){};
	report(std::string stock_name);
	void connect();
	void virtual fillFacts(std::string f_name)=0;
};


class sec : public report {
private:
	
public:
	std::string symbol;
	std::string CIK;
	std::string SIC;
	std::string SIC_desc;
	std::string company_name;
	sec(std::string stock_symbol) : report(stock_symbol),symbol(stock_symbol){}; 	// Constructor
	void fillFacts(std::string f_name);
}; // class sec

class report_item_t {
	public:
		std::string CIK_;
		std::string form_;
		std::string accession_;
		std::string date_;
		Url zip_reference;
	};
	
// a single monthly archive report
class archive: public report{
public:
	std::vector<report_item_t> items_;
	std::string year_;
	std::string month_;
	std::string form_;
	std::string CIK_;
	archive(std::string a_CIK, std::string a_form, int a_year, int a_month); // 1= january 12=december
	archive(std::string a_CIK, std::string a_form, std::string a_year, std::string a_month); // 4 digit year and two digit month
	void fillFacts(std::string f_name);
};//class archive
} // namespace sec
#endif //!_SEC_H

