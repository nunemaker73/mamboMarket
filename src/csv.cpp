/*
    mamboMarket 
    Copyright (C) {2015}  {Craig Nunemaker}

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
#include "csv.h"

/// <summary>loads a CSV record from the stream is</summary>
/// <remarks>
/// * leading and trailing white space is removed outside of 
//    quoted sections when trimWhiteSpace is true
/// * line breaks are preserved in quoted sections
/// * quote literals consist of two adjacent quote characters
/// * quote literals must be in quoted sections
/// </remarks>
/// <param name=is>input stream for CSV records</param>
/// <param name=trimWhiteSpace>trims white space on unquoted fields</param>
/// <param name=fieldDelim>field delimiter. defaults to ',' for CSV</param>
/// <param name=recordDelim>record delimiter. defaults to '\n' for CSV</param>
/// <param name=quote>delimiter for quoted fields. defaults to '"'</param>
/// <returns>a list of fields in the record</returns>
std::vector<std::string> CsvGetLine(std::istream& is, 
                                    bool trimWhiteSpace,
                                    const char fieldDelim,
                                    const char recordDelim,
                                    const char quote)
{
    using namespace std;

    vector<string> record; // result record list. default empty
    string field;          // temporary field construction zone
    int start = -1,        // start of a quoted section for trimming
        end = -1;          // end of a quoted section for trimming
    char ch;

    while (is.get(ch))
    {
        if (ch == fieldDelim || ch == recordDelim)
            // fieldDelim and recordDelim mark the end of a
            // field. save the field, reset for the next field,
            // and break if there are no more fields
        {
            if (trimWhiteSpace)
                // trim all external white space
                // exclude chars between start and end
            {
                const string wsList = " \t\n\f\v\r";
                int ePos, sPos;

                // order dependency: right trim before let trim
                // left trim will invalidate end's index value
                if ((ePos = field.find_last_not_of(wsList)) != string::npos)
                {
                    // ePos+1 because find_last_not_of stops on white space
                    field.erase((end > ePos) ? end : ePos + 1);
                }

                if ((sPos = field.find_first_not_of(wsList)) != string::npos)
                {
                    field.erase(0, (start != -1 && start < sPos) ? start : sPos);
                }

                // reset the quoted section
                start = end = -1;
            }

            // save the new field and reset the temporary
            record.push_back(field);
            field.clear();

            // exit case 1: !is, managed by loop condition
            // exit case 2: recordDelim, managed here
            if (ch == recordDelim) break;
        }
        else if (ch == quote)
        {
            // save the start of the quoted section
            start = field.length();

            while (is.get(ch))
            {
                if (ch == '"')
                {
                    // consecutive quotes are an escaped quote literal
                    // only applies in quoted fields
                    // 'a""b""c' becomes 'abc'
                    // 'a"""b"""c' becomes 'a"b"c'
                    // '"a""b""c"' becomes 'a"b"c'
                    if (is.peek() != '"')
                    {
                        // save the end of the quoted section
                        end = field.length();
                        break;
                    }
                    else field.push_back(is.get());
                }
                else field.push_back(ch);
            }
        }
        else field.push_back(ch);
    }

    return record;
}