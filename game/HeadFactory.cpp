#include "HeadFactory.h"

struct Head
{
    Part part;
    std::string PartType;
    std::string Name;
    std::string Manufacturer;
    std::string Notes;

    Head(Part basePart, std::string partType, std::string name, std::string manufacturer, std::string notes) :
        part(basePart), PartType(partType), Name(name), Manufacturer(manufacturer), Notes(notes)
    {}
};

Part CreateHead()
{
    PartsFactory partsfactory;

    Head tempHeadPart(partsfactory.CreatePart(), partsfactory.data_["Heads"][0]["PartType"], partsfactory.data_["Heads"][0]["Manufacturer"], partsfactory.data_["Heads"][0]["Notes"]);

}