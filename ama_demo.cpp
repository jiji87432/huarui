#include <string.h>
#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>
#include <ama.h>
#include <ama_tools.h>

#ifdef _WIN32
#pragma warning (disable:4996)
#endif
        
static std::mutex g_mutex;  //同步cout输出

// 继承IAMDSpi，实现自己的回调处理类
class MySpi : public amd::ama::IAMDSpi
{
public:
    // 定义日志回调处理方法
    virtual void OnLog(const int32_t& level,
                       const char* log,
                       uint32_t len) override
    {
        std::lock_guard<std::mutex> _(g_mutex);
        std::cout << "AMA log: " << "    level: " << level << "    log:   " << log << std::endl;
    }

    // 定义监控回调处理方法
    virtual void OnIndicator(const char* indicator,
                             uint32_t len) override
    {
        std::lock_guard<std::mutex> _(g_mutex);
        std::cout << "AMA indicator: " << indicator << std::endl;
    }

    // 定义事件回调处理方法  level 对照 EventLevel 数据类型 code 对照 EventCode 数据类型
    virtual void OnEvent(uint32_t level, uint32_t code, const char* event_msg, uint32_t len)
    {
        std::lock_guard<std::mutex> _(g_mutex);
        std::cout << "AMA event: " << event_msg << std::endl;
    }

    // 定义快照数据回调处理方法
    virtual void OnMDSnapshot(amd::ama::MDSnapshot* snapshot,
                              uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(snapshot[i]) << std::endl;
        }
        
        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(snapshot);
    }

    // 定义期权快照数据接收回调处理方法
    virtual void OnMDOptionSnapshot(amd::ama::MDOptionSnapshot* snapshots, uint32_t cnt)
    {

        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(snapshots[i]) << std::endl;
        }
        
        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(snapshots);
    }

    //定义港股快照数据回调处理方法
    virtual void OnMDHKTSnapshot(amd::ama::MDHKTSnapshot* snapshots, uint32_t cnt)
    {

        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(snapshots[i]) << std::endl;
        }
        
        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(snapshots);
    }

    //定义指数快照数据回调处理方法
    virtual void OnMDIndexSnapshot(amd::ama::MDIndexSnapshot* snapshots, uint32_t cnt)
    {

        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(snapshots[i]) << std::endl;
        }
        
        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(snapshots);
    }

    //定义逐笔委托数据回调处理方法
    virtual void OnMDTickOrder(amd::ama::MDTickOrder* ticks, uint32_t cnt)
    {

        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(ticks[i]) << std::endl;
        }
        
        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(ticks);
    }

    // 定义逐笔成交数据回调处理方法
    virtual void OnMDTickExecution(amd::ama::MDTickExecution* tick, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(tick[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(tick);
    }

    // 定义委托队列数据回调处理方法
    virtual void OnMDOrderQueue(amd::ama::MDOrderQueue* orderqueues, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(orderqueues[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(orderqueues);
    }

    // 定义逐笔成交数据回调处理方法
    virtual void OnMDAfterHourFixedPriceSnapshot(amd::ama::MDAfterHourFixedPriceSnapshot* snapshots, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(snapshots[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(snapshots);
    }

    // 定义盘后逐笔成交数据回调处理方法
    virtual void OnMDAfterHourFixedPriceTickExecution(amd::ama::MDAfterHourFixedPriceTickExecution* ticks, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(ticks[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(ticks);
    }

    // 定义期货数据回调处理方法
    virtual void OnMDFutureSnapshot(amd::ama::MDFutureSnapshot* snapshots, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(snapshots[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(snapshots);
    }

    // 定义中证指数数据回调处理方法
    virtual void OnMDCSIIndexSnapshot(amd::ama::MDCSIIndexSnapshot* snapshots, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(snapshots[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(snapshots);
    }

    // 定义成交量统计指标数据回调处理方法
    virtual void OnMDIndicatorOfTradingVolumeSnapshot(amd::ama::MDIndicatorOfTradingVolumeSnapshot*  snapshots, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(snapshots[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(snapshots);
    }

    // 定义国正指数数据回调处理方法
    virtual void OnMDCnIndexSnapshot(amd::ama::MDCnIndexSnapshot* snapshots, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(snapshots[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(snapshots);
    }

    // 定义深交所转融通逐笔委托数据回调处理方法
    virtual void OnMDRefinancingTickOrder(amd::ama::MDRefinancingTickOrder* ticks, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(ticks[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(ticks);
    }

    // 定义深交所转融通逐笔成交数据回调处理方法
    virtual void OnMDRefinancingTickExecution(amd::ama::MDRefinancingTickExecution* ticks, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(ticks[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(ticks);
    }

    // 定义深交所协议交易逐笔委托数据回调处理方法
    virtual void OnMDNegotiableTickOrder(amd::ama::MDNegotiableTickOrder* ticks, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(ticks[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(ticks);
    }

    // 定义深交所协议交易逐笔成交数据回调处理方法
    virtual void OnMDNegotiableTickExecution(amd::ama::MDNegotiableTickExecution* ticks, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(ticks[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(ticks);
    }

    // 定义港股通实时额度数据回调处理方法
    virtual void OnMDHKTRealtimeLimit(amd::ama::MDHKTRealtimeLimit* limits, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(limits[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(limits);
    }

    // 定义港股通产品状态数据回调处理方法
    virtual void OnMDHKTProductStatus(amd::ama::MDHKTProductStatus* status, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(status[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(status);
    }

    // 定义VCM数据数据回调处理方法
    virtual void OnMDHKTVCM(amd::ama::MDHKTVCM* vcms, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(vcms[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(vcms);
    }

    // 定义股转证券行情态数据回调处理方法
    virtual void OnMDNEEQSnapshot(amd::ama::MDNEEQSnapshot* snapshots, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(snapshots[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(snapshots);
    }

    // 定义股转证券信息数据回调处理方法
    virtual void OnMDNEEQSecurityInfo(amd::ama::MDNEEQSecurityInfo* infos, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(infos[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(infos);
    }

    // 定义股转非公开转让申报信息数据回调处理方法
    virtual void OnMDNEEQNonPublicTransDeclaredInfo(amd::ama::MDNEEQNonPublicTransDeclaredInfo* infos, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(infos[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(infos);
    }

    // 定义股转分层信息信息数据回调处理方法
    virtual void OnMDNEEQHierarchicalInfo(amd::ama::MDNEEQHierarchicalInfo* infos, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(infos[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(infos);
    }

    //定义委托薄数据回调处理方法
    virtual void OnMDOrderBook(std::vector<amd::ama::MDOrderBook>& order_book)
    {
        std::lock_guard<std::mutex> _(g_mutex);
        for(uint32_t i = 0; i< order_book.size(); i++)
        {
            std::cout << amd::ama::Tools::Serialize(order_book[i]) << std::endl;
        }
        //不需要手动释放内存
    }

    // 定义港股通市场状态数据回调处理方法
    virtual void OnMDHKMarketStatus(amd::ama::MDHKMarketStatus* status, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(status[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(status);
    }

    // 定义股转系统协议转让申报信息数据回调处理方法
    virtual void OnMDNEEQNegotiableDeclaredInfo(amd::ama::MDNEEQNegotiableDeclaredInfo* infos, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(infos[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(infos);
    }

    // 定义股转系统做市业务申报信息数据回调处理方法
    virtual void OnMDNEEQMarketMakerDeclaredInfo(amd::ama::MDNEEQMarketMakerDeclaredInfo* infos, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(infos[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(infos);
    }

    // 定义股转系统协议转让申报信息数据回调处理方法
    virtual void OnMDNEEQNonPublicTransferDealInfo(amd::ama::MDNEEQNonPublicTransferDealInfo* infos, uint32_t cnt) override
    {
        for (uint32_t i = 0; i < cnt; ++i)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(infos[i]) << std::endl;
        }

        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(infos);
    }
};

// 代码表接口获取示例
void GetCodeList()
{
    amd::ama::CodeTableRecordList list;
    bool ret = amd::ama::IAMDApi::GetCodeTableList(list);
    if(ret)
    {
        for(uint32_t i=0; i< list.list_nums; i++)
        {
            /*
                handle list.records
                records 是代码表数据头指针
            */
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << amd::ama::Tools::Serialize(list.records[i]);
        }
        if(list.list_nums > 0)
            amd::ama::IAMDApi::FreeMemory(list.records);  //释放代码表内存池数据
    }
}

int main()
{
    
    amd::ama::Cfg cfg; // 准备AMA配置

    /*
        通道模式设置及各个通道说明:
        cfg.channel_mode = amd::ama::ChannelMode::kTCP;   ///< TCP 方式计入上游行情系统
        cfg.channel_mode = amd::ama::ChannelMode::kAMI;   ///< AMI 组播方式接入上游行情系统
        cfg.channel_mode = amd::ama::ChannelMode::kRDMA;  ///< 开启硬件加速RDMA通道,抓取网卡数据包数据
        cfg.channel_mode = amd::ama::ChannelMode::kEXA;   ///< 开启硬件加速EXA通道,抓取网卡数据包数据
        cfg.channel_mode = amd::ama::ChannelMode::kPCAP;  ///< 开启硬件加速PCAP通道,抓取网卡数据包数据
        cfg.channel_mode = amd::ama::ChannelMode::kMDDP;  ///< 直接接入交易所网关组播数据，现在只有深圳交易所开通了此服务
        cfg.channel_mode = amd::ama::ChannelMode::kTCP|amd::ama::ChannelMode::kAMI;  ///< 同时通过TCP方式和AMI组播方式接入上游，通过cfg.ha_mode 设置对应的高可用设置模式
    */
    cfg.channel_mode = amd::ama::ChannelMode::kTCP;

    cfg.tcp_compress_mode = 0;  //TCP传输数据方式: 0 不压缩 1 华锐自定义压缩 2 zstd压缩(仅TCP模式有效)
    
    
    /*
        通道高可用模式设置
        1. cfg.channel_mode 为单通道时,建议设置值为kMasterSlaveA / kMasterSlaveB
        2. cfg.channel_mode 混合开启多个通道时,根据需求设置不同的值
            1) 如果需要多个通道为多活模式接入,请设置kRegularDataFilter值
            2) 如果需要多个通道互为主备接入，请设置值为kMasterSlaveA / kMasterSlaveB,kMasterSlaveA / kMasterSlaveB 差别请参看注释说明
               通道优先级从高到低依次为 kRDMA/kEXA/kMDDP/kAMI/kTCP/kPCAP
    */
    cfg.ha_mode = amd::ama::HighAvailableMode::kMasterSlaveA;


    
    cfg.min_log_level = amd::ama::LogLevel::kInfo; // 设置日志最小级别：Info级, AMA内部日志通过 OnLog 回调函数返回
    
    /*
        设置是否输出监控数据: true(是), false(否), 监控数据通过OnIndicator 回调函数返回
        监控数据格式为json, 主要监控数据包括订阅信息，数据接收数量统计
        数据量统计:包括接收数量和成功下发的数量统计,两者差值为过滤的数据量统计
        eg: "RecvSnapshot": "5926", "SuccessSnapshot": "5925",表示接收了快照数据5926个,成功下发5925个，过滤数据为 5926 - 5925 = 1 个
            过滤的数据有可能为重复数据或者非订阅数据
    */
    cfg.is_output_mon_data = false;   
    
    /*
        设置逐笔保序开关: true(开启保序功能) , false(关闭保序功能)
        主要校验逐笔成交数据和逐笔委托数据是否有丢失,如果丢失会有告警日志,缓存逐笔数据并等待keep_order_timeout(单位s)时间等待上游数据重传,
        如果超过此时间,直接下发缓存数据,默认数据已经丢失,如果之后丢失数据过来也会丢弃。
        同时由于深圳和上海交易所都是通道内序号连续,如果打开了保序开关,必须订阅全部代码的逐笔数据,否则一部分序号会被订阅过滤,导致数据超时等待以及丢失告警。
    */
    cfg.keep_order = false;
    cfg.keep_order_timeout_ms = 3000;


    cfg.is_subscribe_full = false; //设置默认订阅: true 代表默认全部订阅, false 代表默认全部不订阅

    /*
        配置UMS信息:
        username/password 账户名/密码, 一个账户只能保持一个连接接入（注意: 如果需要使用委托薄功能，注意账号需要有委托薄功能权限）
        ums地址配置:
            1) ums地址可以配置1-8个 建议值为2 互为主备, ums_server_cnt 为此次配置UMS地址的个数
            2) ums_servers 为UMS地址信息数据结构:
                local_ip 为本地地址,填0.0.0.0 或者本机ip
                server_ip 为ums服务端地址
                server_port 为ums服务端端口
    */
    strcpy(cfg.username, "u_by_test1");
    strcpy(cfg.password, "by_test@123");
    cfg.ums_server_cnt = 1;
    strcpy(cfg.ums_servers[0].local_ip, "0.0.0.0");
    strcpy(cfg.ums_servers[0].server_ip, "61.144.241.205");
    cfg.ums_servers[0].server_port = 8400;

    
    /*
        业务数据回调接口(不包括 OnIndicator/OnLog等功能数据回调)的线程安全模式设置:
        true: 所有的业务数据接口为接口集线程安全
        false: 业务接口单接口为线程安全,接口集非线程安全
    */
    cfg.is_thread_safe = false;

    /*
        委托薄前档行情参数设置(仅委托薄版本API有效，若非委托薄版本参数设置无效):
            1) 行情输出设置，包括档位数量以及每档对应的委托队列数量
            2）委托薄计算输出参数设置，包括线程数量以及递交间隔设置
    */
   cfg.enable_order_book = false;                          //是否开启委托薄计算功能 (注意：委托薄需要订阅相应的逐笔成交和逐笔委托)
   cfg.entry_size = 10;                                    //委托薄输出档位数量
   cfg.order_queue_size = 10;                              //每个档位输出的委托队列揭示
   cfg.thread_num = 3;                                     //计算委托薄的线程数量
   cfg.order_book_deliver_interval_microsecond = 0;        //递交的最小时间间隔，默认为0


    MySpi spi;   //初始化回调类
    
    /*
        初始化回调以及配置信息,此函数为异步函数, 如果通道初始化以及登陆出现问题会通过onLog / onEvent 返回初始化结果信息
    */
    if (amd::ama::IAMDApi::Init(&spi, cfg)
        != amd::ama::ErrorCode::kSuccess)
    {
        std::lock_guard<std::mutex> _(g_mutex);
        std::cout << "Init AMA failed" << std::endl;
        amd::ama::IAMDApi::Release();
        return -1;
    }

    //订阅示例1
    {
        /*
        按数据权限订阅信息设置:
        1. 订阅信息分三个维度 market:市场, flag:数据类型(比如现货快照, 逐笔成交, 指数快照等), 证券代码
        2. 订阅操作有三种:
            kSet 设置订阅, 以市场为单位覆盖订阅信息
            kAdd 增加订阅, 在前一个基础上增加订阅信息
            kDel 删除订阅, 在前一个基础上删除订阅信息
            kCancelAll 取消所有订阅信息
        */
        amd::ama::SubscribeItem sub[3];
        memset(sub, 0, sizeof(sub));

        /* 订阅深交所全部证券的逐笔委托和逐笔成交数据 */
        sub[0].market = amd::ama::MarketType::kSZSE;
        sub[0].flag = amd::ama::SubscribeDataType::kTickOrder
                    | amd::ama::SubscribeDataType::kTickExecution;
        sub[0].security_code[0] = '\0';

        /* 订阅上交所600000、600004两只证券的全部数据 */
        sub[1].market = amd::ama::MarketType::kSSE;
        sub[1].flag = amd::ama::SubscribeDataType::kNone;
        strcpy(sub[1].security_code, "600000");
        sub[2].market = amd::ama::MarketType::kSSE;
        sub[2].flag = amd::ama::SubscribeDataType::kNone;
        strcpy(sub[2].security_code, "600004");
        
        /* 发起订阅 */
        if (amd::ama::IAMDApi::SubscribeData(
                    amd::ama::SubscribeType::kSet, sub, 3)
            != amd::ama::ErrorCode::kSuccess)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << "Subscribe data failed" << std::endl;
            amd::ama::IAMDApi::Release();
            return -1;
        }
    }

    //订阅示例2
    {
        /*
        按品种类型订阅信息设置:
        1. 订阅信息分三个维度 market:市场, data_type:证券数据类型(), category_type:品种类型, security_code:证券代码
        2. 订阅操作有三种:
            kSet 设置订阅, 以市场为单位覆盖订阅信息
            kAdd 增加订阅, 在前一个基础上增加订阅信息
            kDel 删除订阅, 在前一个基础上删除订阅信息
            kCancelAll 取消所有订阅信息
        */
        amd::ama::SubscribeCategoryItem sub1[3];
        memset(sub1, 0, sizeof(sub1));

        /* 订阅深交所全部证券代码的股票逐笔委托和逐笔成交数据 */
        sub1[0].market = amd::ama::MarketType::kSZSE;
        sub1[0].data_type = amd::ama::SubscribeDataType::kSnapshot
                    | amd::ama::SubscribeDataType::kTickExecution;
        sub1[0].category_type = amd::ama::SubscribeCategoryType::kStock;
        sub1[0].security_code[0] = '\0';

        /* 订阅上交所全部证券代码的基金逐笔委托和逐笔成交数据 */
        sub1[1].market = amd::ama::MarketType::kSSE;
        sub1[1].data_type = amd::ama::SubscribeDataType::kSnapshot
                    | amd::ama::SubscribeDataType::kTickExecution;
        sub1[1].category_type = amd::ama::SubscribeCategoryType::kFund;
        sub1[1].security_code[0] = '\0';

        /* 订阅上交所全部证券代码的基金逐笔委托和逐笔成交数据 */
        sub1[2].market = amd::ama::MarketType::kSSE;
        sub1[2].data_type = amd::ama::SubscribeDataType::kSnapshot
                    | amd::ama::SubscribeDataType::kTickExecution;
        sub1[2].category_type = amd::ama::SubscribeCategoryType::kFund;
        memset(sub1[2].security_code, 0 , sizeof(sub1[2].security_code));
        strcpy(sub1[2].security_code, "600004");
        
        /* 发起订阅 */
        if (amd::ama::IAMDApi::SubscribeData(
                    amd::ama::SubscribeType::kSet, sub1, 3)
            != amd::ama::ErrorCode::kSuccess)
        {
            std::lock_guard<std::mutex> _(g_mutex);
            std::cout << "Subscribe data failed" << std::endl;
            amd::ama::IAMDApi::Release();
            return -1;
        }
    }
    
    /* 保持主线程不退出 */
    bool is_running = true;
    while (is_running)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> _(g_mutex);
        std::cout << "AMA is running ..." << std::endl;
    }

    amd::ama::IAMDApi::Release();

    return 0;
}
