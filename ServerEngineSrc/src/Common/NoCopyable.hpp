#pragma
class NoCopyable
{
	protected:
	
	NoCopyable(const NoCopyable& inst) = delete;
	NoCopyable& operator=(const NoCopyable& inst) = delete;

};