#include <iostream>
#include <string>
#include "chatserver.hpp"
using namespace std;  // 第二版优化， 优化命名空间





int main(int args, char* argv[]) 
{
    cout <<" --------------" <<endl;
    /* 1.定义一个事件循环用于构造ChatServer对象 */
    EventLoop loop;

    /* 2.定义一个服务器地址信息用于构造ChatServer对象 */
    InetAddress addr("127.0.0.1", 6000);  // 第三版优化，做成配置

    /* 3.定义一个服务器名称用于构造ChatServer对象 */
    string serverName = "ChatServer";

    /* 4.构造ChatServer对象 */
    ChatServer server(&loop, addr, serverName);

    /* 5.开启服务器 */
    server.start();

    /* 开启服务器事件循环 */
    loop.loop();
    return 0;
}