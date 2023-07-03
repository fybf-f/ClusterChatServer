#ifndef PUBLIC_H
#define PUBLIC_H

/* server和client的公共文件 */

enum EnMsgType // 第三次优化，enum class
{
    LOGIN_MSG = 1,  // 绑定用户连接、登陆的回调函数
    REG_MSG         // 用户消息
};
#endif