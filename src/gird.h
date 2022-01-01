#ifndef GRID_H
#define GRID_H

/************************************************************************************************************************
*                                                                                                                       
*   CLASS:DEFINITION                                                                                                    
*   (阅读顺序从下往上)                                                                                                     
************************************************************************************************************************/
class Grid
{
    public:
        Grid(const int &capacity, const int &demand) : capacity_(capacity), demand_(demand) {};
        int GetCapacity();
        int GetDemand();
        int GetSupply();
        bool IsOverflow();
        void AddDemand(int val);
        void AddCapacity(int val);
    private:
        int capacity_;
        int demand_;
};
#endif