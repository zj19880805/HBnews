/********************************************************************
	File :			KeyedAveragedMeasure.cpp
	Creation date :	2010/6/27

	License :			Copyright 2010 Ahmed Charfeddine, http://www.pushframework.com

				   Licensed under the Apache License, Version 2.0 (the "License");
				   you may not use this file except in compliance with the License.
				   You may obtain a copy of the License at

					   http://www.apache.org/licenses/LICENSE-2.0

				   Unless required by applicable law or agreed to in writing, software
				   distributed under the License is distributed on an "AS IS" BASIS,
				   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
				   See the License for the specific language governing permissions and
				   limitations under the License.


*********************************************************************/
#include "StdAfx.h"
#include "KeyedAveragedMeasure.h"

namespace PushFramework
{


KeyedAveragedMeasure::KeyedAveragedMeasure(std::string name)
    :Measure(name)
{
}

KeyedAveragedMeasure::~KeyedAveragedMeasure(void)
{
}

void KeyedAveragedMeasure::addObservation( MeasureArgs& args )
{
    MKAveragedMeasureArgs& myArgs = (MKAveragedMeasureArgs&) args;
    //
    if (mappedValues.find(myArgs.key) == mappedValues.end())
    {
        mappedValues[myArgs.key] = myArgs.dwValue;
    }
    else
        mappedValues[myArgs.key] += myArgs.dwValue;
}

double KeyedAveragedMeasure::getMean()
{
    double total = 0;
    double count = 0;
    for (mappedValuesT::iterator it=mappedValues.begin();
            it!=mappedValues.end();
            it++)
    {
        total+= it->second;
        count++;
    }
    return count == 0 ? 0 : (total / count);
}

double KeyedAveragedMeasure::getDispersion( double mean )
{
    double temp= 0;
    double count = 0;
    for (mappedValuesT::iterator it=mappedValues.begin();
            it!=mappedValues.end();
            it++)
    {
        temp += pow(it->second - mean, 2);
        count++;
    }
    return count == 0 ? 0 : sqrt(temp/count);
}

std::string KeyedAveragedMeasure::collectAndReset( std::string timeStamp )
{
    //Calculate Avg and dispersion
    double mean = getMean();
    double dispersion = getDispersion(mean);

    std::stringstream ss;
    ss << std::noskipws;

    ss << "<" << name << " mean=\"" << mean << "\" disp=\"" << dispersion << "\" />";

    std::string retVal = ss.str();


    //Reset
    mappedValues.clear();

    return retVal;
}

}
