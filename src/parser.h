#ifndef PARSER_H
#define PARSER_H
/*****************************************************************************
*   Structure
*****************************************************************************/

/*****************************************************************************
*   Global variable: declaration
*****************************************************************************/

class Net
{
    public: 
        class Pin
        {
            private:
                const string instname_;
                const string masterpinname_;
            public:
                Pin(const string &instname, const string &masterpinname) : instname_(instname), masterpinname_(masterpinname) {};
                string GetInstName();
                string GetMasterPinName();
                friend ostream &operator<<(ostream &os, const Pin &pin);
        };
    private:
        const string netname_;
        const int numpin_;
        const string minroutinglayconstraint_;
        const vector<Pin> pin_vec_;
        const float weight_;
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
};

class CellInst
{
    private: 
        const string instname_;
        const string mastercellname_;
        const int gridrowidx_;
        const int gridcolidx_;
        const bool ismovable_;
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
};

class MasterCell
{
    public:
        class Pin
        {
            private:
                const string name_;
                const string layer_;
            public:
                Pin(const string &name, const string &layer) : name_(name), layer_(layer) {};
                string GetName();
                string GetLayer();
                friend ostream &operator<<(ostream &os, const Pin &pin);
        };
        class Blkg
        {
            private:
                const string name_;
                const string layer_;
                const int demand_;
            public:
                Blkg(const string &name, const string &layer, const int &demand) : name_(name), layer_(layer), demand_(demand) {};
                string GetName();
                string GetLayer();
                int GetDemand();
                friend ostream &operator<<(ostream &os, const Blkg &blkg);
        };
    private:
        const string name_;
        const int numpin_;
        const int numblockage_;
        const vector<Pin> pin_vec_;
        const vector<Blkg> blkg_vec_;
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
};

class NonDefaultSupply
{
    private:
        const int rowidx_;
        const int colidx_;
        const int layidx_;
        const int changeval_;
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
};

class Layer
{
    private: 
        const string name_;
        const int idx_;
        const char routingdir_;
        const int defaultsupply_;
        const float powerfactor_;
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
};

class GridBoundaryIdx
{
    private:
        const int rowbeginidx_;
        const int rowendidx_;
        const int colbeginidx_;
        const int colendidx_;
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
};

class GlobalVar
{
    private:
        const int maxcellmove_; //最多可以移动的cell数量
        const GridBoundaryIdx gridbound_;
        const int numlayer_;
        const vector<Layer> layer_vec_;
        const int numnondefaultsupply_;
        const vector<NonDefaultSupply> nondefaultsupply_vec_;
        const int nummastercell_;
        const unordered_map<string, MasterCell> mastercell_hash_;
        const int numcellinst_;
        const unordered_map<string, CellInst> cellinst_hash_;
        const int numnet_;
        const unordered_map<string, Net> net_hash_;
    public:
        GlobalVar() = default;
        GlobalVar(const int &maxcellmove, const GridBoundaryIdx &gridbound, const int &numlayer, const vector<Layer> &layer_vec, const int &numnondefaultsupply, const vector<NonDefaultSupply> &nondefaultsupply_vec, const int &nummastercell, const unordered_map<string, MasterCell> &mastercell_hash, const int &numcellinst, const unordered_map<string, CellInst> &cellinst_hash, const int &numnet, const unordered_map<string, Net> &net_hash) 
        : maxcellmove_(maxcellmove), 
          gridbound_(gridbound),
          numlayer_(numlayer),
          layer_vec_(layer_vec),
          numnondefaultsupply_(numnondefaultsupply),
          nondefaultsupply_vec_(nondefaultsupply_vec), 
          nummastercell_(nummastercell),
          mastercell_hash_(mastercell_hash),
          numcellinst_(numcellinst),
          cellinst_hash_(cellinst_hash),
          numnet_(numnet),
          net_hash_(net_hash){};
        GlobalVar& operator=(const GlobalVar&) = delete;
        int GetMaxCellMove();
        GridBoundaryIdx GetGridBound();
        int GetNumLayer();
        vector<Layer> GetLayerVec();
        int GetNumNonDefaultSupply();
        vector<NonDefaultSupply> GetNonDefaultSupplyVec();
        int GetNumMasterCell();
        unordered_map<string, MasterCell> GetMasterCellHash();
        int GetNumCellInst();
        unordered_map<string, CellInst> GetCellInstHash();
        int GetNumNet();
        unordered_map<string, Net> GetNetHash();
};

/*****************************************************************************
*   Operator overload: declaration
*****************************************************************************/


/*****************************************************************************
*   Function: declaration
*****************************************************************************/

void parser(const char *filename);


#endif

