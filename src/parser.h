#ifndef PARSER_H
#define PARSER_H

/************************************************************************************************************************
*                                                                                                                       *
*   CLASS:DEFINITION                                                                                                    *
*                                                                                                                       *
************************************************************************************************************************/
/************************************************************************************************************************
*   Definition: VoltageArea                                                                                             *
************************************************************************************************************************/
class VoltageArea
{
    public:
        class GGrid
        {
            public:
                GGrid(const int ggridrowidx, const int ggridcolidx) : ggridrowidx_(ggridrowidx), ggridcolidx_(ggridcolidx) {};
                int GetGGridRowIdx();
                int GetGGridColIdx();
                friend ostream &operator<<(ostream &os, const VoltageArea::GGrid &ggrid);
            private:
                const int ggridrowidx_;
                const int ggridcolidx_;
        };
        class Instance
        {
            public:
                Instance(const string &instancename) : instancename_(instancename) {}; 
                string GetInstanceName();
                friend ostream &operator<<(ostream &os, const VoltageArea::Instance &instance);
            private:
                const string instancename_; 
        };
    public: 
        VoltageArea(const string &voltageareaname, const int &numggrids, const vector<GGrid> &ggrid_vec, const int &numinstances, const vector<Instance> instance_vec)
            : voltageareaname_(voltageareaname),
              numggrids_(numggrids),
              ggrid_vec_(ggrid_vec),
              numinstances_(numinstances),
              instance_vec_(instance_vec) {};
        string GetVoltageAreaName();
        int GetNumGGrids();
        vector<GGrid> GetGGridVec();
        int GetNumInstances();
        vector<Instance> GetInstanceVec();
        friend ostream &operator<<(ostream &os, const VoltageArea &voltagearea);
    private:
        const string voltageareaname_;
        const int numggrids_;
        const vector<GGrid> ggrid_vec_;
        const int numinstances_;
        const vector<Instance> instance_vec_;
};
/************************************************************************************************************************
*   Definition: Route                                                                                                   *
************************************************************************************************************************/
class Route
{
    public:
        Route(const int &srowidx, const int &scolidx, const int &slayidx, const int &erowidx, const int &ecolidx, const int &elayidx,const string netname)
            : srowidx_(srowidx),
              scolidx_(scolidx),
              slayidx_(slayidx),
              erowidx_(erowidx),
              ecolidx_(ecolidx),
              elayidx_(elayidx),
              netname_(netname) {};
        int GetsRowIdx();
        int GetsColIdx();
        int GetsLayIdx();
        int GeteRowIdx();
        int GeteColIdx();
        int GeteLayIdx();
        string GetnetName();
        friend ostream &operator<<(ostream &os, const Route &route);
    private:
        const int srowidx_;
        const int scolidx_;
        const int slayidx_;
        const int erowidx_;
        const int ecolidx_;
        const int elayidx_;
        const string netname_;
};
/************************************************************************************************************************
*   Definition: Net                                                                                                     *
************************************************************************************************************************/
class Net
{
    public: 
        class Pin
        {
            public:
                Pin(const string &instname, const string &masterpinname) : instname_(instname), masterpinname_(masterpinname) {};
                string GetInstName();
                string GetMasterPinName();
                friend ostream &operator<<(ostream &os, const Pin &pin);
            private:
                const string instname_;
                const string masterpinname_;
        };
    public:
        Net(const string &netname, const int &numpin, const string &minroutinglayconstraint, const vector<Pin> &pin_vec, const float &weight)
            : netname_(netname),
              numpin_(numpin),
              minroutinglayconstraint_(minroutinglayconstraint),
              pin_vec_(pin_vec),
              weight_(weight) {};
        string GetNetName();
        int GetNumPin();
        string GetMinRoutingLayConstraint();
        vector<Pin> GetPinVec();
        float GetWeight();
        friend ostream &operator<<(ostream &os, const Net &net);
    private:
        const string netname_;
        const int numpin_;
        const string minroutinglayconstraint_;
        const vector<Pin> pin_vec_;
        const float weight_;
};
/************************************************************************************************************************
*   Definition: CellInst                                                                                                *
************************************************************************************************************************/
class CellInst
{
    public:
        CellInst(const string &instname, const string &mastercellname, const int &gridrowidx, const int &gridcolidx, const bool & ismovable)
            : instname_(instname),
              mastercellname_(mastercellname),
              gridrowidx_(gridrowidx),
              gridcolidx_(gridcolidx),
              ismovable_(ismovable) {};
        string GetInstName();
        string GetMasterCellName();
        int GetGridRowIdx();
        int GetGridColIdx();
        bool IsMovable();
        friend ostream &operator<<(ostream &os, const CellInst &cellinst);
    private: 
        const string instname_;
        const string mastercellname_;
        const int gridrowidx_;
        const int gridcolidx_;
        const bool ismovable_;
};
/************************************************************************************************************************
*   Definition: MasterCell                                                                                              *
************************************************************************************************************************/
class MasterCell
{
    public:
        class Pin
        {
            public:
                Pin(const string &name, const string &layer) : name_(name), layer_(layer) {};
                string GetName();
                string GetLayer();
                friend ostream &operator<<(ostream &os, const Pin &pin);
            private:
                const string name_;
                const string layer_;
        };
        class Blkg
        {
             public:
                Blkg(const string &name, const string &layer, const int &demand) : name_(name), layer_(layer), demand_(demand) {};
                string GetName();
                string GetLayer();
                int GetDemand();
                friend ostream &operator<<(ostream &os, const Blkg &blkg);
            private:
                const string name_;
                const string layer_;
                const int demand_;
        };
    public:
        MasterCell() = default;
        MasterCell(const string &name, const int &numpin, const int &numblockage, const vector<Pin> &pin_vec, const vector<Blkg> &blkg_vec) 
            : name_(name),
              numpin_(numpin),
              numblockage_(numblockage),
              pin_vec_(pin_vec),
              blkg_vec_(blkg_vec) {};
        string GetName();
        int GetNumPin();
        int GetNumBlockage();
        vector<Pin> GetPinVec();
        vector<Blkg> GetBlkgVec();
        friend ostream &operator<<(ostream &os, const MasterCell &mastercell);
    private:
        const string name_;
        const int numpin_;
        const int numblockage_;
        const vector<Pin> pin_vec_;
        const vector<Blkg> blkg_vec_;
};
/************************************************************************************************************************
*   Definition: NonDefaultSupply                                                                                        *
************************************************************************************************************************/
class NonDefaultSupply
{
    public:
        NonDefaultSupply() = default;
        NonDefaultSupply(const int &rowidx, const int &colidx, const int &layidx, const int &changeval) 
            : rowidx_(rowidx),
              colidx_(colidx),
              layidx_(layidx),
              changeval_(changeval) {};
        int GetRowIdx();
        int GetColIdx();
        int GetLayIdx();
        int GetChangeVal();
        friend ostream &operator<<(ostream &os, const NonDefaultSupply &nondefaultsupply);
    private:
        const int rowidx_;
        const int colidx_;
        const int layidx_;
        const int changeval_;
};
/************************************************************************************************************************
*   Definition: Layer                                                                                                   *
************************************************************************************************************************/
class Layer
{
    public:
        Layer() = default;
        Layer(const string &name, const int &idx, const char &routingdir, const int &defaultsupply, const float &powerfactor) 
            : name_(name), 
              idx_(idx), 
              routingdir_(routingdir), 
              defaultsupply_(defaultsupply),
              powerfactor_(powerfactor) {};
        string GetName();
        int GetIdx();
        char GetRoutingDir();
        int GetDefaultSupply();
        float GetPowerFactor();
        friend ostream &operator<<(ostream &os, const Layer &layer);
    private: 
        const string name_;
        const int idx_;
        const char routingdir_;
        const int defaultsupply_;
        const float powerfactor_;
};
/************************************************************************************************************************
*   Definition: GridBoundaryIdx                                                                                         *
************************************************************************************************************************/
class GridBoundaryIdx
{
    public:
        GridBoundaryIdx() = default;
        GridBoundaryIdx(const int &rowbegin, const int &rowend, const int &colbegin, const int &colend) 
            : rowbeginidx_(rowbegin), 
              rowendidx_(rowend), 
              colbeginidx_(colbegin), 
              colendidx_(colend) {};
        int GetRowBeginIdx();
        int GetRowEndIdx();
        int GetColBeginIdx();
        int GetColEndIdx();
        friend ostream &operator<<(ostream &os, const GridBoundaryIdx &gridbound);
    private:
        const int rowbeginidx_;
        const int rowendidx_;
        const int colbeginidx_;
        const int colendidx_;
};
/************************************************************************************************************************
*   Definition: GlobalVar                                                                                               *
************************************************************************************************************************/
class GlobalVar
{
    public:
        GlobalVar() = default;
        GlobalVar(const int &maxcellmove, const GridBoundaryIdx &gridbound, const int &numlayers, const vector<Layer> &layer_vec, const int &numnondefaultsupplys, const vector<NonDefaultSupply> &nondefaultsupply_vec, const int &nummastercells, const unordered_map<string, MasterCell> &mastercell_hash, const int &numcellinsts, const unordered_map<string, CellInst> &cellinst_hash, const int &numnet, const unordered_map<string, Net> &net_hash, const int &numroutes, const vector<Route> &route_vec, const int &numvoltageareas, const unordered_map<string, VoltageArea> &voltagearea_hash)
        : maxcellmove_(maxcellmove), 
          gridbound_(gridbound),
          numlayers_(numlayers),
          layer_vec_(layer_vec),
          numnondefaultsupplys_(numnondefaultsupplys),
          nondefaultsupply_vec_(nondefaultsupply_vec), 
          nummastercells_(nummastercells),
          mastercell_hash_(mastercell_hash),
          numcellinsts_(numcellinsts),
          cellinst_hash_(cellinst_hash),
          numnets_(numnet),
          net_hash_(net_hash),
          numroutes_(numroutes),
          route_vec_(route_vec),
          numvoltageareas_(numvoltageareas),
          voltagearea_hash_(voltagearea_hash) {};
        GlobalVar& operator=(const GlobalVar&) = delete;
        int GetMaxCellMove();
        GridBoundaryIdx GetGridBound();
        int GetNumLayers();
        vector<Layer> GetLayerVec();
        int GetNumNonDefaultSupplys();
        vector<NonDefaultSupply> GetNonDefaultSupplyVec();
        int GetNumMasterCells();
        unordered_map<string, MasterCell> GetMasterCellHash();
        int GetNumCellInsts();
        unordered_map<string, CellInst> GetCellInstHash();
        int GetNumNets();
        unordered_map<string, Net> GetNetHash();
        int GetNumRoutes();
        vector<Route> GetRouteVec();
        int GetNumVoltageAreas();
        unordered_map<string, VoltageArea> GetVoltageAreaHash();
    private:
        const int maxcellmove_; //最多可以移动的cell数量
        const GridBoundaryIdx gridbound_;
        const int numlayers_;
        const vector<Layer> layer_vec_;
        const int numnondefaultsupplys_;
        const vector<NonDefaultSupply> nondefaultsupply_vec_;
        const int nummastercells_;
        const unordered_map<string, MasterCell> mastercell_hash_;
        const int numcellinsts_;
        const unordered_map<string, CellInst> cellinst_hash_;
        const int numnets_;
        const unordered_map<string, Net> net_hash_;
        const int numroutes_;
        const vector<Route> route_vec_;
        const int numvoltageareas_;
        const unordered_map<string, VoltageArea> voltagearea_hash_;
};
/************************************************************************************************************************
*                                                                                                                       *
*   FUNCTION:DECLEAR                                                                                                    *
*                                                                                                                       *
************************************************************************************************************************/
GlobalVar parser(const char *filename);

#endif

