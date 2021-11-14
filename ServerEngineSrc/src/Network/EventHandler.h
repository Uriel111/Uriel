#pragma once
#include <Network/Socket.h>
#include <functional>
#include <memory>
#include <sys/epoll.h>
namespace Uriel {

using ReadCallback = std::function<void()>;
using WriteCallback = std::function<void()>;
using ErrorCallback = std::function<void()>;
class Handler;
using HandlerUniquePtr = std::unique_ptr<Handler>;
using RawEvent = epoll_event;
enum EventEnum{
	EventRead = EPOLLIN,
	EventWrite = EPOLLOUT,
	EventAll = EventRead | EventWrite
};
class Epoller;
class Event : public NoCopyable {
public:
	Event(int socketFd, Epoller * epoller);
	~Event();
	Handler*  GetHandler() {
		return handler_.get();
	}
	const int GetSockFd() const{
		return socketFd_;
	}
	void SetWriteCallback(WriteCallback &&writeCb);
	void SetReadCallback(ReadCallback &&readCb);
	void ClearWriteCallback();
	void ClearReadCallback();
	void ClearErrorCallback();
	


protected:
	void Update();
	int socketFd_;
	HandlerUniquePtr handler_;
	RawEvent rawEvent_;
	Epoller* epoller_;

};

class Handler : public NoCopyable {
public:
	Handler(Event *event);
	~Handler();
	void Handle();
	void SetWriteCallback(WriteCallback &&writeCb);
	void SetReadCallback(ReadCallback &&readCb);
	void SetErrorCallback(WriteCallback &&errorCb);

protected:
	void InitCbRlt();

private:
	Event *event_;
	ReadCallback readCb_;
	WriteCallback writeCb_;
	ErrorCallback errorCb_;
};

} // namespace Uriel
