#ifndef PARSER_H
#define PARSER_H

/************************************************************************************************************************
*                                                                                                                       
*   CLASS:DEFINITION                                                                                                    
*   (阅读顺序从下往上)                                                                                                     
************************************************************************************************************************/
/************************************************************************************************************************
*   Definition: VoltageArea
*   Synopsis: 该类型限定了特定Cell的摆放区域
*   Interface:
*       class: GGrid
*           GetGGridRowIdx: 获取电压区域相关Grid的Row坐标
*           GetGGridColIdx: 获取电压区域相关Grid的Column坐标
*       class: Instance
*           GetInstanceName: 获取限定Cell的名称
*       GetVoltageAreaName: 获取电压区域名称
*       GetNumGGrids: 获取电压区域涵盖的Grid数量
*       GetGGridVec: 获取电压区域涵盖的Grid
*       GetNumInstances: 获取限定只能摆放在电压区域的Cell数量
*       GetInstanceVec: 获取限定只能摆放在电压区域的Cell                                                                                              
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
*   Definition: Route（主要操作对象，通过绕线算法修改位置信息）
*   Synopsis: 该类型定义了绕线的线段位置信息，线段两端点为source跟end 
*   Interface:
*       GetsRowIdx: 获取线段source的Row坐标
*       GetsColIdx: 获取线段source的Col坐标
*       GetsLayIdx: 获取线段source的Layer坐标
*       GeteRowIdx: 获取线段end的Row坐标
*       GeteColIdx: 获取线段end的Col坐标
*       GeteLayIdx: 获取线段end的Layer坐标
*       GetnetName: 获取当前绕线的Net名称
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
*   Definition: Net
*   Synopsis: 该类型规定了Net的具体信息
*   Interface: 
*       Class: Pin
*           GetInstName: 获取Net连接到的Cell Instance的名称
*           GetMasterPinName: 获取Net连接到的Cell Instance上的Pin的名称
*       GetNetName: 获取Net的名称
*       GetNumPin: 获取Net连接到的Pin的数量
*       GetMinRoutingLayConstraint: 获取绕线至少要绕在哪一层之上的Constraint
*       GetPinVec: 获取Net连接到的Pin
*       GetWeight: 获取与Critical Path相关的Weight
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
*   Definition: CellInst(主要操作对象，通过Move操作修改位置信息)
*   Synopsis: 该类型规定了Cell的具体信息
*   Interface:
*       GetInstName: 获取Cell instance名字
*       GetMasterCellName: 获取Cell的MasterCell类型
*       GetGridRowIdx: 获取Cell的Row方向坐标
*       GetGridColIdx: 获取Cell的Column方向坐标
*       IsMovable: 判断该Cell可否被移动
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
*   Definition: MasterCell
*   Synopsis: 该类型规定了Cell的种类（Cell长相是长方体），其信息主要包括每一类相对应的Pin以及Blkg信息
*   Interface: 
*       class: Pin
*           GetName: 获取Pin的名字
*           GetLayer: 获取Pin所在的Layer
*       class: Blkg
*           GetName: 获取Blkg的名字
*           GetLayer: 获取Blkg所在的层数
*           GetDemand: 获取Blkg会花费的绕线资源
*       GetName: 获取MasterCell类型名
*       GetNumPin: 获取MasterCell包含的Pin的数量
*       GetNumBlockage: 获取MasterCell包含的Blockage的数量
*       GetPinVec: 获取MasterCell包含的所有Pin
*       GetBlkgVec: 获取MasterCell包含的所有Blockage
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
*   Definition: NonDefaultSupply
*   Synopsis: 该类型规定了Layer上具体的某个Grid所拥有的额外或需要减少的绕线资源(Supply)
*   Interface:
*       GetRowIdx: 获取某个拥有与Default不同绕线资源的Grid的Row方向坐标
*       GetColIdx: 获取某个拥有与Default不同绕线资源的Grid的Column方向坐标
*       GetLayIdx: 获取某个拥有与Default不同绕线资源的Grid的Layer方向坐标
*       GetChangeVal: 获取由上述三个位置信息得到的Grid的额外/减少的绕线资源
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
*   Definition: Layer
*   Synopsis: 该类型规定了每一层Layer具体的Constraint与已知条件
*   Interface:
*       GetName: 获取当前Layer的名字
*       GetIdx: 获取当前Layer的层数（z轴方向坐标）
*       GetRoutingDir: 获取当前Layer的绕线方向，第一层的绕线方向始终是水平方向(x轴方向，又称H)，层与层之间绕线方向一定不同（比如第二层是y轴方向，又称V）
*                      绕线Layer的绕线方向会影响绕线方式，比如第一层的Cell/Instance之间的绕线只能走x方向
*       GetDefaultSupply: 获取当层每个Grid所拥有的默认绕线资源量，与Supply相对还有Demand的概念：每个Grid上已经被使用的资源总和，
*                         每个Grid的Demand可以由Grid上net的数量与Grid上Cell instance的demands总和得到，
*                         通过Supply-Demand可以算出Capacity有无Overflow
*       GetPowerFactor: 获取用于计算当层总耗电量的factor，【存疑】（总耗电量 = 当层绕线格点数量 * power factor）                            
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
*   Definition: GridBoundaryIdx                                                                                         
*   Synopsis: 该类型规定了绕线所需的Grid的范围，每一层的范围均相同                                                              
*   Interface:                                                                                                          
*       GetRowBeginIdx: 获取Grid的Row方向(竖着数)坐标起始位置
*       GetRowEndIdx: 获取Grid的Row方向(竖着数)坐标终止位置
*       GetColBeginIdx: 获取Grid的Column方向(横着数)坐标起始位置
*       GetColEndIdx: 获取Grid的Column方向(横着数)坐标终止位置                                                                                    
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
*   Definition: GlobalVar                                                                                               
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
        //Constraint: 最多可以移动的cell数量
        const int maxcellmove_; 
        //Constraint：3D IC绕线的Grid边界，每一层都相同，详情参见class: GridBoundaryIdx
        const GridBoundaryIdx gridbound_; 
        //3D IC的层数
        const int numlayers_;  
        //Constraint: 每层Layer具体的参数，详情参见class: Layer
        const vector<Layer> layer_vec_; 
        //拥有特殊supply数量的Grid的数量
        const int numnondefaultsupplys_;
        //Constraint: 拥有特殊Supply数量的Grid，详情参见class: NonDefaultSupply
        const vector<NonDefaultSupply> nondefaultsupply_vec_;
        //Cell的类型数量
        const int nummastercells_;
        //Constraint: Cell的类型，详情参见class: MasterCell
        const unordered_map<string, MasterCell> mastercell_hash_;
        //Cell的数量
        const int numcellinsts_;
        //可操作对象: Cell的具体信息，详情参见class: CellInst
        const unordered_map<string, CellInst> cellinst_hash_;
        //Net的数量
        const int numnets_;
        //Constraint: Net的具体信息，详情参见class: Net
        const unordered_map<string, Net> net_hash_;
        //绕线线段的总数
        const int numroutes_;
        //可操作对象: Route的具体信息，详情参见class: Route
        const vector<Route> route_vec_;
        //电压区域数量
        const int numvoltageareas_;
        //Constraint: 电压限定区域的具体信息，详情参见class: VoltageArea
        const unordered_map<string, VoltageArea> voltagearea_hash_;
};
/************************************************************************************************************************
*                                                                                                                       *
*   FUNCTION:DECLEAR                                                                                                    *
*                                                                                                                       *
************************************************************************************************************************/
GlobalVar parser(const char *filename);

#endif

