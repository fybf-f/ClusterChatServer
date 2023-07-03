#include "chatserver.hpp"
#include "json.hpp"
#include "chatservice.hpp"
/* 第一版代码，下一版代码需要对此优化 */
#include <functional>
#include <string>
using namespace std;
using namespace placeholders;
using json = nlohmann::json;

/* 定义构造函数 */
ChatServer::ChatServer(EventLoop *loop,
                       const InetAddress &listenAddr,
                       const string &nameArg)
    : _server(loop, listenAddr, nameArg), _loop(loop)
{
    /* 注册连接回调（类成员方法内置this参数，需要传值） */
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

    /* 注册消息回调 */
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

    /* 设置线程数量 */
    _server.setThreadNum(4);
}

/* 启动服务器 */
void ChatServer::start()
{
    _server.start();
}

/* 用户连接与断开的回调函数 */
void ChatServer::onConnection(const TcpConnectionPtr &conn)
{

}

/* 用户读写事件相关信息的回调函数 */
void ChatServer::onMessage(const TcpConnectionPtr &conn,
                           Buffer *buffer, Timestamp time)
{
    string buf = buffer->retrieveAllAsString();

    /* 数据反序列化 */
    json js = json::parse(buf);

    /* 完全解耦网络模块代码与业务模块代码 */
    /* 通过js["msgid"]获取业务handler(recator事件处理器) conn js time */
    auto msghandler = ChatService::instance()->getMsgHandler(js["msgid"].get<int>());
    /* 回调msgid对应的事件处理器，来执行相应的业务处理 */
    msghandler(conn, js, time);
}
