#include "gui_techlist.hpp"

TechListViewer::TechListViewer(std::vector<Techprocess *> *const ptr)
{
    for (auto techItem: *ptr)
    {
        techItem->printToConsole();
        
    }
}

    
