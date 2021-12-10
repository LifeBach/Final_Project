#include "headers.h"
#include "parser.h"

int GlobalVar::GetMaxCellMove()                       { return this->maxcellmove_; }
GridBoundaryIdx GlobalVar::GetGridBound()             { return this->gridbound_; }
int GlobalVar::GetNumLayer()                          { return this->numlayer_; }
vector<Layer> GlobalVar::GetLayerVec()                { return this->layer_vec_; }
int GlobalVar::GetNumNonDefaultSupply()               { return this->numnondefaultsupply_; }
vector<NonDefaultSupply> GlobalVar::GetNonDefaultSupplyVec() { return this-> nondefaultsupply_vec_; }
int GlobalVar::GetNumMasterCell()                     { return this->nummastercell_; }
unordered_map<string, MasterCell> GlobalVar::GetMasterCellHash() { return this->mastercell_hash_; }

int GridBoundaryIdx::GetRowBeginIdx()     { return this->rowbeginidx_; }
int GridBoundaryIdx::GetRowEndIdx()       { return this->rowendidx_; }
int GridBoundaryIdx::GetColBeginIdx()     { return this->colbeginidx_; }
int GridBoundaryIdx::GetColEndIdx()       { return this->colendidx_; }

string Layer::GetName()                   { return this->name_; }
int Layer::GetIdx()                       { return this->idx_; }
char Layer::GetRoutingDir()               { return this->routingdir_; }
int Layer::GetDefaultSupply()             { return this->defaultsupply_; }
float Layer::GetPowerFactor()             { return this->powerfactor_; }

string Pin::GetName()                     { return this->name_; }
string Pin::GetLayer()                    { return this->layer_;}

string Blkg::GetName()                    { return this->name_; }
string Blkg::GetLayer()                   { return this->layer_; }
int Blkg::GetDemand()                     { return this->demand_; }

string MasterCell::GetName()              { return this->name_; }
int MasterCell::GetNumPin()               { return this->numpin_; }
int MasterCell::GetNumBlockage()          { return this->numblockage_;}
vector<Pin> MasterCell::GetPinVec()               { return this->pin_vec_; }
vector<Blkg> MasterCell::GetBlkgVec()             { return this->blkg_vec_; }

ostream &operator<<(ostream &os, const Blkg &blkg)
{
    os << "BlkgName: " << blkg.name_
       << " BlkgLayer: " << blkg.layer_
       << " BlkgDemand: " << blkg.demand_ << "\n";
}

ostream &operator<<(ostream &os, const Pin &pin)
{
    os << "PinName: " << pin.name_
       << " PinLayer: " << pin.layer_ << "\n";
    return os;
}

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

ostream &operator<<(ostream &os, const NonDefaultSupply &nondefaultsupply)
{
    os << "RowIndex: " << nondefaultsupply.rowidx_
       << " ColIndex: " << nondefaultsupply.colidx_
       << " LayIndex: " << nondefaultsupply.layidx_
       << " ChangeVal: " << nondefaultsupply.changeval_<<"\n";
    return os;
}

ostream  &operator<<(ostream &os, const Layer &layer)
{
    os << "Layer name: " << layer.name_ 
       << " Index: " << layer.idx_ 
       << " RoutingDirection: " << layer.routingdir_ 
       << " DefaultSupplyOfOneGGrid: " << layer.defaultsupply_
       << " PowerFactor: " << layer.powerfactor_ << "\n";
    return os;
}

ostream  &operator<<(ostream &os, const GridBoundaryIdx &gridbound)
{
    os << "RowBeginIndex: " << gridbound.rowbeginidx_
       << " RowEndIndex: " << gridbound.rowendidx_ 
       << " ColBeginIndex: " << gridbound.colbeginidx_
       << " ColEndIndex: " << gridbound.colendidx_<<"\n";
    return os;
}

void parser(const char *filename)
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
    int kNumLayer;
    vector<Layer> kLayerVec;
    fscanf(fp,"NumLayer %d\n",&kNumLayer);
    for (int i = 0; i < kNumLayer; i++)
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
    int kNumNonDefaultSupply;
    vector<NonDefaultSupply> kNonDefaultSupplyVec;
    fscanf(fp,"NumNonDefaultSupplyGGrid %d\n",&kNumNonDefaultSupply);
    for (int i = 0; i < kNumNonDefaultSupply; i++)
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
    int kNumMasterCell;
    unordered_map<string, MasterCell> kMasterCellHash;
    fscanf(fp,"NumMasterCell %d\n",&kNumMasterCell);
    cout << kNumMasterCell<<endl;
    for (int i = 0; i < kNumMasterCell; i++)
    {
        char kMasterCellName_temp[5];
        int kNumPin;
        int kNumBlockage;
        vector<Pin> kPinVec;
        vector<Blkg> kBlkgVec;
        fscanf(fp,"MasterCell %s %d %d\n",&kMasterCellName_temp, &kNumPin, &kNumBlockage);
        string kMasterCellName = kMasterCellName_temp;
        char kPinName_temp[5];
        char kPinLayer_temp[5];
        for (int j = 0; j < kNumPin; j++)
        {
            fscanf(fp,"Pin %s %s\n",&kPinName_temp, &kPinLayer_temp);
            string kPinName = kPinName_temp;
            string kPinLayer = kPinLayer_temp;
            Pin kPin(kPinName, kPinLayer);
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
            Blkg kBlkg(kBlkgName, kBlkgLayer, kBlkgDemand);
            kBlkgVec.push_back(kBlkg);
        }
        MasterCell kMasterCell(kMasterCellName, kNumPin, kNumBlockage, kPinVec, kBlkgVec);
        kMasterCellHash.insert(make_pair(kMasterCellName, kMasterCell));
    }
    GlobalVar kGlobalVar(kMaxCellMove, kGridBound, kNumLayer, kLayerVec, kNumNonDefaultSupply, kNonDefaultSupplyVec, kNumMasterCell, kMasterCellHash);
    string ttname = kGlobalVar.GetMasterCellHash().begin()->first;
    MasterCell m1 = kGlobalVar.GetMasterCellHash().begin()->second;
    cout << m1;
}