#pragma once

#include "tinyXml/tinyxml.h"
#include "noiseoutput.h"

TiXmlDocument* generateXmlFromOutputModule(NoiseOutputModule *module);
