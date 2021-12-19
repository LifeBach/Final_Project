#include "headers.h"
#include "parser.h"

/************************************************************************************************************************
*                                                                                                                       
*   CLASS:INTERFACE                                                                                                     
*                                                                                                                       
************************************************************************************************************************/
/************************************************************************************************************************
*   Interface: GlobalVar                                                                                                
************************************************************************************************************************/
int GlobalVar::GetMaxCellMove()                                      { return this->maxcellmove_; }
GridBoundaryIdx GlobalVar::GetGridBound()                            { return this->gridbound_; }
int GlobalVar::GetNumLayers()                                        { return this->numlayers_; }
vector<Layer> GlobalVar::GetLayerVec()                               { return this->layer_vec_; }
int GlobalVar::GetNumNonDefaultSupplys()                             { return this->numnondefaultsupplys_; }
vector<NonDefaultSupply> GlobalVar::GetNonDefaultSupplyVec()         { return this-> nondefaultsupply_vec_; }
int GlobalVar::GetNumMasterCells()                                   { return this->nummastercells_; }
unordered_map<string, MasterCell> GlobalVar::GetMasterCellHash()     { return this->mastercell_hash_; }
int GlobalVar::GetNumCellInsts()                                     { return this->numcellinsts_; }
unordered_map<string, CellInst> GlobalVar::GetCellInstHash()         { return this->cellinst_hash_; }
int GlobalVar::GetNumNets()                                          { return this->numnets_; }
unordered_map<string, Net> GlobalVar::GetNetHash()                   { return this->net_hash_; }
int GlobalVar::GetNumRoutes()                                        { return this->numroutes_; }
vector<Route> GlobalVar::GetRouteVec()                               { return this->route_vec_; }
int GlobalVar::GetNumVoltageAreas()                                  { return this->numvoltageareas_; }
unordered_map<string, VoltageArea> GlobalVar::GetVoltageAreaHash()   { return this->voltagearea_hash_; }
/***********************************************************************************************************************
*   Interface: GridBoundaryIdx                                                                                         
************************************************************************************************************************/
int GridBoundaryIdx::GetRowBeginIdx()                                { return this->rowbeginidx_; }
int GridBoundaryIdx::GetRowEndIdx()                                  { return this->rowendidx_; }
int GridBoundaryIdx::GetColBeginIdx()                                { return this->colbeginidx_; }
int GridBoundaryIdx::GetColEndIdx()                                  { return this->colendidx_; }
/************************************************************************************************************************
*   Interface: Layer                                                                                                    
************************************************************************************************************************/
string Layer::GetName()                                              { return this->name_; }
int Layer::GetIdx()                                                  { return this->idx_; }
char Layer::GetRoutingDir()                                          { return this->routingdir_; }
int Layer::GetDefaultSupply()                                        { return this->defaultsupply_; }
float Layer::GetPowerFactor()                                        { return this->powerfactor_; }
/************************************************************************************************************************
*   Interface: MasterCell                                                                                               
************************************************************************************************************************/
string MasterCell::GetName()                                         { return this->name_; }
int MasterCell::GetNumPin()                                          { return this->numpin_; }
int MasterCell::GetNumBlockage()                                     { return this->numblockage_;}
vector<MasterCell::Pin> MasterCell::GetPinVec()                      { return this->pin_vec_; }
vector<MasterCell::Blkg> MasterCell::GetBlkgVec()                    { return this->blkg_vec_; }
/**********************************************************
*   Interface: MasterCell::Pin                            
**********************************************************/
string MasterCell::Pin::GetName()                                    { return this->name_; }
string MasterCell::Pin::GetLayer()                                   { return this->layer_; }
/**********************************************************
*   Interface: MasterCell::Blkg                           
**********************************************************/
string MasterCell::Blkg::GetName()                                   { return this->name_; }
string MasterCell::Blkg::GetLayer()                                  { return this->layer_; }
int MasterCell::Blkg::GetDemand()                                    { return this->demand_; }
string CellInst::GetInstName()                                       { return this->instname_; }
string CellInst::GetMasterCellName()                                 { return this->mastercellname_; }
int CellInst::GetGridRowIdx()                                        { return this->gridrowidx_; }
int CellInst::GetGridColIdx()                                        { return this->gridcolidx_; }
bool CellInst::IsMovable()                                           { return this->ismovable_; }
/************************************************************************************************************************
*   Interface: Net                                                                                                      
************************************************************************************************************************/
string Net::GetNetName()                                             { return this->netname_; }
int Net::GetNumPin()                                                 { return this->numpin_; }
string Net::GetMinRoutingLayConstraint()                             { return this->minroutinglayconstraint_; }
vector<Net::Pin> Net::GetPinVec()                                    { return this->pin_vec_; }
float Net::GetWeight()                                               { return this->weight_; }
/**********************************************************
*   Interface: Net::Pin                                   
**********************************************************/
string Net::Pin::GetInstName()                                       { return this->instname_; }
string Net::Pin::GetMasterPinName()                                  { return this->masterpinname_; }
/************************************************************************************************************************           
*   Interface: Route                                                                                                    
************************************************************************************************************************/
int Route::GetsRowIdx()                                              { return this->srowidx_; }                     
int Route::GetsColIdx()                                              { return this->scolidx_; }
int Route::GetsLayIdx()                                              { return this->slayidx_; }
int Route::GeteRowIdx()                                              { return this->erowidx_; }
int Route::GeteColIdx()                                              { return this->ecolidx_; }
int Route::GeteLayIdx()                                              { return this->elayidx_; }
string Route::GetnetName()                                           { return this->netname_; }
/************************************************************************************************************************
*   Interface: VoltageArea                                                                                              
************************************************************************************************************************/
string VoltageArea::GetVoltageAreaName()                             { return this->voltageareaname_; }
int VoltageArea::GetNumGGrids()                                      { return this->numggrids_; }
vector<VoltageArea::GGrid> VoltageArea::GetGGridVec()                { return this->ggrid_vec_; }
int VoltageArea::GetNumInstances()                                   { return this->numinstances_; }
vector<VoltageArea::Instance> VoltageArea::GetInstanceVec()          { return this->instance_vec_; }
/**********************************************************
*   Interface: VoltageArea::GGrid                         
**********************************************************/
int VoltageArea::GGrid::GetGGridRowIdx()                             { return this->ggridrowidx_; }
int VoltageArea::GGrid::GetGGridColIdx()                             { return this->ggridcolidx_; }
/**********************************************************
*   Interface: VoltageArea::Instance                      
**********************************************************/
string VoltageArea::Instance::GetInstanceName()                      { return this->instancename_; }

/************************************************************************************************************************
*                                                                                                                       
*   CLASS:PRINT OVERLOAD                                                                                                
*                                                                                                                       
************************************************************************************************************************/
/************************************************************************************************************************
*   Print Overload: VoltageArea                                                                                         
************************************************************************************************************************/
ostream &operator<<(ostream &os, const VoltageArea &voltagearea)
{
    os << "VoltageAreaName: " << voltagearea.voltageareaname_
       << " NumGGrids: " << voltagearea.numggrids_
       << " NumInstances: " << voltagearea.numinstances_ << "\n"
       << "GGrid: " << "\n";
    for (auto iter = voltagearea.ggrid_vec_.begin(); iter != voltagearea.ggrid_vec_.end(); iter++)
    {
        os << " " <<(*iter);
    }
    os << "Instance: " << "\n";
    for (auto iter = voltagearea.instance_vec_.begin(); iter != voltagearea.instance_vec_.end(); iter++)
    {
        os << " " <<(*iter);
    }
    return os;
}
/**********************************************************
*   Print Overload: VoltageArea::GGrid                    
**********************************************************/
ostream &operator<<(ostream &os, const VoltageArea::GGrid &ggrid)
{
    os << "GGridRowIndex: " << ggrid.ggridrowidx_
       << " GGridColIndex: " << ggrid.ggridcolidx_ << "\n";
    return os;
}
/**********************************************************
*   Print Overload: VoltageArea::Instance                 
**********************************************************/
ostream &operator<<(ostream &os, const VoltageArea::Instance &instance)
{
    os << "GGridRowIndex: " << instance.instancename_ << "\n";
    return os;
}
/************************************************************************************************************************
*   Print Overload: Route                                                                                               
************************************************************************************************************************/
ostream &operator<<(ostream &os, const Route &route)
{
    os << "sRowIdx: " << route.srowidx_
       << " sColIdx: " << route.scolidx_
       << " sLayIdx: " << route.slayidx_
       << " eRowIdx: " << route.erowidx_
       << " eColIdx: " << route.ecolidx_
       << " eLayIdx: " << route.elayidx_
       << " netname: " << route.netname_ << "\n";
    return os;
}
/************************************************************************************************************************
*   Print Overload: Net                                                                                                 
************************************************************************************************************************/
ostream &operator<<(ostream &os, const Net &net)
{
    os << "NetName: " << net.netname_
       << " NumPins: " << net.numpin_
       << " MinRoutingLayConstraint: " << net.minroutinglayconstraint_
       << " weight: " <<net.weight_ << "\n"
       << "Pin: " << "\n";
    for (auto iter = net.pin_vec_.begin(); iter != net.pin_vec_.end(); iter++)
    {
        os << " " <<(*iter);
    }
    return os;
}
/**********************************************************
*   Print Overload: Net::Pin                              
**********************************************************/
ostream &operator<<(ostream &os, const Net::Pin &pin)
{
    os << "InstanceName: " << pin.instname_
       << " MasterPinName: " << pin.masterpinname_ << "\n";
    return os;
}
/************************************************************************************************************************
*   Print Overload: CellInst                                                                                            
************************************************************************************************************************/
ostream &operator<<(ostream &os, const CellInst &cellinst)
{
    os << "CellInstanceName: " << cellinst.instname_
       << " MasterCellName: " << cellinst.mastercellname_
       << " GridRowIndex: " << cellinst.gridrowidx_ 
       << " GridColIndex: " << cellinst.gridcolidx_;
    if (cellinst.ismovable_ == true)
    {
        os << " IsMovable: " << "Movable" << "\n";
    }
    else if (cellinst.ismovable_ == false)
    {
        os << " IsMovable: " << "Fixed" << "\n";
    }
    else
    {
        os << "Unknown!" << "\n";
    }
    return os;
}
/************************************************************************************************************************
*   Print Overload: MasterCell                                                                                          
************************************************************************************************************************/
ostream &operator<<(ostream &os, const MasterCell &mastercell)
{
    os << "MasterCellName: " << mastercell.name_
       << " NumPin: " << mastercell.numpin_
       << " NumBlockage: " << mastercell.numblockage_ << "\n"
       << "Pin: " << "\n";
    for (auto iter = mastercell.pin_vec_.begin(); iter != mastercell.pin_vec_.end(); iter++)
    {
        os << " " <<(*iter);
    }
    os <<"Blkg: " << "\n";
    for (auto iter = mastercell.blkg_vec_.begin(); iter != mastercell.blkg_vec_.end(); iter++)
    {
        os << " " << (*iter);
    }
    return os;
}
/**********************************************************
*   Print Overload: MasterCell::Blkg                      
**********************************************************/
ostream &operator<<(ostream &os, const MasterCell::Blkg &blkg)
{
    os << "BlkgName: " << blkg.name_
       << " BlkgLayer: " << blkg.layer_
       << " BlkgDemand: " << blkg.demand_ << "\n";
    return os;
}
/**********************************************************
*   Print Overload: MasterCell::Pin                       
**********************************************************/
ostream &operator<<(ostream &os, const MasterCell::Pin &pin)
{
    os << "PinName: " << pin.name_
       << " PinLayer: " << pin.layer_ << "\n";
    return os;
}
/************************************************************************************************************************
*   Print Overload: NonDefaultSupply                                                                                    
************************************************************************************************************************/
ostream &operator<<(ostream &os, const NonDefaultSupply &nondefaultsupply)
{
    os << "RowIndex: " << nondefaultsupply.rowidx_
       << " ColIndex: " << nondefaultsupply.colidx_
       << " LayIndex: " << nondefaultsupply.layidx_
       << " ChangeVal: " << nondefaultsupply.changeval_<<"\n";
    return os;
}
/************************************************************************************************************************
*   Print Overload: Layer                                                                                               
************************************************************************************************************************/
ostream  &operator<<(ostream &os, const Layer &layer)
{
    os << "Layer name: " << layer.name_ 
       << " Index: " << layer.idx_ 
       << " RoutingDirection: " << layer.routingdir_ 
       << " DefaultSupplyOfOneGGrid: " << layer.defaultsupply_
       << " PowerFactor: " << layer.powerfactor_ << "\n";
    return os;
}
/************************************************************************************************************************
*   Print Overload: GridBoundaryIdx                                                                                     
************************************************************************************************************************/
ostream  &operator<<(ostream &os, const GridBoundaryIdx &gridbound)
{
    os << "RowBeginIndex: " << gridbound.rowbeginidx_
       << " RowEndIndex: " << gridbound.rowendidx_ 
       << " ColBeginIndex: " << gridbound.colbeginidx_
       << " ColEndIndex: " << gridbound.colendidx_<<"\n";
    return os;
}
/************************************************************************************************************************
*                                                                                                                       
*   FUNCTION:IMPLEMENT                                                                                                  
*                                                                                                                       
************************************************************************************************************************/
GlobalVar parser(const char *filename)
{
    FILE *fp; 
    fp = fopen(filename,"r");
    // read: MaxCellMove
    int kMaxCellMove;
    fscanf(fp,"MaxCellMove %d\n",&kMaxCellMove);
    // read: GGridBoundaryIdx
    int kRowBegin, kRowEnd, kColBegin, kColEnd;
    fscanf(fp,"GGridBoundaryIdx %d %d %d %d\n",&kRowBegin, &kRowEnd, &kColBegin, &kColEnd);
    GridBoundaryIdx kGridBound(kRowBegin, kRowEnd, kColBegin, kColEnd);
    // read: Layer
    int kNumLayers;
    vector<Layer> kLayerVec;
    fscanf(fp,"NumLayer %d\n",&kNumLayers);
    for (int i = 0; i < kNumLayers; i++)
    {
        char kLayerName_temp[10];
        int kIdx;
        char kRoutingDir;
        int kDefaultSupply;
        float kPowerFactor;
        fscanf(fp,"Lay %s %d %s %d %f\n",&kLayerName_temp, &kIdx, &kRoutingDir, &kDefaultSupply, &kPowerFactor);
        string kLayerName = kLayerName_temp;
        Layer kLayer(kLayerName, kIdx, kRoutingDir, kDefaultSupply, kPowerFactor);
        kLayerVec.push_back(kLayer);
    }
    // read: NonDefaultSupply
    int kNumNonDefaultSupplys;
    vector<NonDefaultSupply> kNonDefaultSupplyVec;
    fscanf(fp,"NumNonDefaultSupplyGGrid %d\n",&kNumNonDefaultSupplys);
    for (int i = 0; i < kNumNonDefaultSupplys; i++)
    {
        int kRowIdx;
        int kColIdx;
        int kLayIdx;
        char kChangeVal_temp[5];
        fscanf(fp,"%d %d %d %s\n",&kRowIdx, &kColIdx, &kLayIdx, &kChangeVal_temp);
        int kChangeVal = atoi(kChangeVal_temp);
        NonDefaultSupply kNonDefaultSupply(kRowIdx, kColIdx, kLayIdx, kChangeVal);
        kNonDefaultSupplyVec.push_back(kNonDefaultSupply);
    }
    // read: MasterCell
    int kNumMasterCells;
    unordered_map<string, MasterCell> kMasterCellHash;
    fscanf(fp,"NumMasterCell %d\n",&kNumMasterCells);
    for (int i = 0; i < kNumMasterCells; i++)
    {
        char kMasterCellName_temp[5];
        int kNumPin;
        int kNumBlockage;
        vector<MasterCell::Pin> kPinVec;
        vector<MasterCell::Blkg> kBlkgVec;
        fscanf(fp,"MasterCell %s %d %d\n",&kMasterCellName_temp, &kNumPin, &kNumBlockage);
        string kMasterCellName = kMasterCellName_temp;
        char kPinName_temp[5];
        char kPinLayer_temp[5];
        for (int j = 0; j < kNumPin; j++)
        {
            fscanf(fp,"Pin %s %s\n",&kPinName_temp, &kPinLayer_temp);
            string kPinName = kPinName_temp;
            string kPinLayer = kPinLayer_temp;
            MasterCell::Pin kPin(kPinName, kPinLayer);
            kPinVec.push_back(kPin);
        }
        char kBlkgName_temp[5];
        char kBlkgLayer_temp[5];
        int kBlkgDemand;
        for (int k = 0; k < kNumBlockage; k++)
        {
            fscanf(fp,"Blkg %s %s %d\n",&kBlkgName_temp, &kBlkgLayer_temp, &kBlkgDemand);
            string kBlkgName = kBlkgName_temp;
            string kBlkgLayer = kBlkgLayer_temp;
            MasterCell::Blkg kBlkg(kBlkgName, kBlkgLayer, kBlkgDemand);
            kBlkgVec.push_back(kBlkg);
        }
        MasterCell kMasterCell(kMasterCellName, kNumPin, kNumBlockage, kPinVec, kBlkgVec);
        kMasterCellHash.insert(make_pair(kMasterCellName, kMasterCell));
    }
    //read: CellInst
    int kNumCellInsts;
    unordered_map<string, CellInst> kCellInstHash;
    fscanf(fp,"NumCellInst %d\n",&kNumCellInsts);
    for (int i = 0; i < kNumCellInsts; i++)
    {
        char kCellInstName_temp[10];
        char kMasterCellName_temp[10];
        int kGridRowIdx;
        int kGridColIdx;
        char kMove_temp[10];
        bool kIsMovable;
        fscanf(fp,"CellInst %s %s %d %d %s\n",&kCellInstName_temp, &kMasterCellName_temp, &kGridRowIdx, &kGridColIdx, &kMove_temp);
        string kCellInstName = kCellInstName_temp;
        string kMasterCellName = kMasterCellName_temp;
        string kMove = kMove_temp;
        if (kMove == "Movable")
        {
            kIsMovable = true;
        }
        else if (kMove == "Fixed")
        {
            kIsMovable = false;
        }
        CellInst kCellInst(kCellInstName, kMasterCellName, kGridRowIdx, kGridColIdx, kIsMovable);
        kCellInstHash.insert(make_pair(kCellInstName, kCellInst));
    }
    //read: Nets
    int kNumNets;
    unordered_map<string, Net> kNetHash;
    fscanf(fp,"NumNets %d\n",&kNumNets);
    for (int i = 0; i < kNumNets; i++)
    {
        char kNetName_temp[10];
        int kNumPin;
        char kMinRoutingLayConstraint_temp[10];
        vector<Net::Pin> kPinVec;
        float kWeight;
        fscanf(fp,"Net %s %d %s %f\n",&kNetName_temp, &kNumPin, &kMinRoutingLayConstraint_temp, &kWeight);
        string kNetName = kNetName_temp;
        string kMinRoutingLayConstraint = kMinRoutingLayConstraint_temp;
        char buf_temp[30];
        for (int j = 0; j < kNumPin; j++)
        {
            fscanf(fp,"Pin %s\n",&buf_temp);
            string buf = buf_temp;
            auto splitpos = buf.find("/");
            string kInstName = buf.substr(0, splitpos);
            string kMasterPinName = buf.substr(splitpos + 1, buf.size());
            Net::Pin kPin(kInstName, kMasterPinName);
            kPinVec.push_back(kPin);
        }
        Net kNet(kNetName, kNumPin, kMinRoutingLayConstraint, kPinVec, kWeight);
        kNetHash.insert(make_pair(kNetName, kNet));
    }
    //read: Route
    int kNumRoutes;
    vector<Route> kRouteVec;
    fscanf(fp,"NumRoutes %d\n",&kNumRoutes);
    for (int i = 0; i < kNumRoutes; i++)
    {
        int ksRowIdx;
        int ksColIdx;
        int ksLayIdx;
        int keRowIdx;
        int keColIdx;
        int keLayIdx;
        char knetName[5];
        fscanf(fp,"%d %d %d %d %d %d %s\n",&ksRowIdx, &ksColIdx, &ksLayIdx, &keRowIdx, &keColIdx, &keLayIdx, &knetName);
        Route route(ksRowIdx, ksColIdx, ksLayIdx, keRowIdx, keColIdx, keLayIdx, knetName);
        kRouteVec.push_back(route);
    }
    //read: VoltageArea
    int kNumVoltageAreas;
    unordered_map<string, VoltageArea> kVoltageAreaHash;
    fscanf(fp,"NumVoltageAreas %d\n",&kNumVoltageAreas);
    for (int i = 0; i < kNumVoltageAreas; i++)
    {
        char kVoltageAreaName_temp[5];
        int kNumGGrids;
        int kNumInstances;
        vector<VoltageArea::GGrid> kGGridVec;
        vector<VoltageArea::Instance> kInstanceVec;
        fscanf(fp,"Name %s\n",&kVoltageAreaName_temp);
        string kVoltageAreaName = kVoltageAreaName_temp;
        fscanf(fp,"GGrids %d\n",&kNumGGrids);
        for (int j = 0; j < kNumGGrids; j++)
        {
            int kGGridRowIdx;
            int kGGridColIdx;
            fscanf(fp,"%d %d\n",&kGGridRowIdx, &kGGridColIdx);
            VoltageArea::GGrid kGGrid(kGGridRowIdx, kGGridColIdx);
            kGGridVec.push_back(kGGrid);
        }
        fscanf(fp,"Instances %d\n",&kNumInstances);
        for (int k = 0; k < kNumInstances; k++)
        {
            char kInstanceName_temp[5];
            fscanf(fp,"%s\n",&kInstanceName_temp);
            string kInstanceName = kInstanceName_temp;
            VoltageArea::Instance kInstance(kInstanceName);
            kInstanceVec.push_back(kInstance);
        }
        VoltageArea kVoltageArea(kVoltageAreaName, kNumGGrids, kGGridVec, kNumInstances, kInstanceVec);
        kVoltageAreaHash.insert(make_pair(kVoltageAreaName, kVoltageArea));
    }
    //create: GlobalVar
    GlobalVar kGlobalVar(kMaxCellMove, kGridBound, kNumLayers, kLayerVec, kNumNonDefaultSupplys, kNonDefaultSupplyVec, kNumMasterCells, kMasterCellHash, kNumCellInsts, kCellInstHash, kNumNets, kNetHash, kNumRoutes, kRouteVec, kNumVoltageAreas, kVoltageAreaHash);
    return kGlobalVar;
}