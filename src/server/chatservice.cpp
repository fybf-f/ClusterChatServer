#include <muduo/base/Logging.h>
#include <string>
// #include <>

#include "chatservice.hpp"
#include "public.hpp"

using namespace std;
using namespace muduo;

ChatService *ChatService::instance()
{
    static ChatService service;
    return &service;
}

/* 注册消息以及对应的Handler回调操作 */
ChatService::ChatService()
{
    _msgHandlerMap.insert({LOGIN_MSG, std::bind(&ChatService::login, this, _1, _2, _3)});
    _msgHandlerMap.insert({REG_MSG, std::bind(&ChatService::reg, this, _1, _2, _3)});
}

/* 处理登陆业务 */
void ChatService::login(const TcpConnectionPtr &conn,
                        json &js, Timestamp time)
{
    LOG_INFO << "do login service!!!";
}

/* 处理注册业务 */
void ChatService::reg(const TcpConnectionPtr &conn,
                        json &js, Timestamp time)
{
    LOG_INFO << "do reg service!!!";
}

MsgHandler ChatService::getMsgHandler(int msgid)
{
    /* 记录错误日志：msgid没有对应的事件处理回调函数返回一个空handler */
    auto it = _msgHandlerMap.find(msgid);  // 此处可与if优化成为一行，第三版
    if (it == _msgHandlerMap.end())
    {
        return [=](const TcpConnectionPtr &conn,
                   json &js, Timestamp time)
        {
            LOG_ERROR << "msgid:" << msgid << "can't find handler!";
        };
    }
    else 
    {
        return _msgHandlerMap[msgid];
    }
    
}
