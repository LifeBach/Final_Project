#include "headers.h"
#include "parser.h"
#include "grid.h"

int  Grid::GetCapacity()       const { return capacity_; }
int  Grid::GetDemand()         const { return demand_; }
int  Grid::GetSupply()         const { return capacity_ - demand_; }
bool Grid::IsOverflow()        const { return GetSupply() < 0; }
void Grid::AddDemand(int val)        { demand_ += val; }
void Grid::AddCapacity(int val)      { capacity += val; }