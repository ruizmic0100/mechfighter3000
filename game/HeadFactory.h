#ifndef HEAD_FACTORY_H
#define HEAD_FACTORY_H

#include "../json/json.h"
using json = nlohmann::json;

#include <iostream>

#include "PartsFactory.h"

Part CreateHead();

#endif // HEAD_FACTORY_H