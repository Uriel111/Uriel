#include <Network/EventHandler.h>
namespace Uriel {
Handler::Handler(Event * event) : event_(event) {
	InitCbRlt();
}

Handler::~Handler()
{

}

void Handler::InitCbRlt()
{
	readCb_ = [](){};
	writeCb_ = [](){};
	errorCb_ = [](){};
}

void Handler::SetReadCallback(ReadCallback&& readCb)
{
	readCb_ = readCb;
}

void Handler::SetWriteCallback(WriteCallback&& writeCb)
{
	writeCb_ = writeCb;
}

void Handler::SetErrorCallback(ErrorCallback&& errorCb)
{
	errorCb_ = errorCb;
}

Event::Event(int socketFd, Epoller* epoller): socketFd_(socketFd), handler_(std::make_unique<Handler>(this)), epoller_(epoller)
{
	rawEvent_.data.fd = socketFd;
	rawEvent_.data.ptr = this;

}


} // namespace Uriel