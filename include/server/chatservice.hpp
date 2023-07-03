#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include "json.hpp"

#include <muduo/net/TcpServer.h>
#include <unordered_map>
#include <functional>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;

/* 处理消息事件的回调函数类型 */
using MsgHandler = std::function<void(const TcpConnectionPtr &conn,
                                      json &js, Timestamp time)>;

/* 聊天服务器业务类（单例模式） */
class ChatService
{
public:
    /* 获取单例对象的接口函数 */
    static ChatService *instance();
    /* 处理登陆业务 */
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);

    /* 处理注册业务 */
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);

    /* 获取消息对应的处理器 */
    MsgHandler getMsgHandler(int msgid);

private:
    ChatService();
    /* 存储消息id和其对应的业务处理器 */
    unordered_map<int, MsgHandler> _msgHandlerMap;
};

#endif