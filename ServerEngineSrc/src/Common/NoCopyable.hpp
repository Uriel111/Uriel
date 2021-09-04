#pragma once
class NoCopyable {
public:
  NoCopyable() = default;

protected:
  NoCopyable(const NoCopyable &inst) = delete;
  NoCopyable &operator=(const NoCopyable &inst) = delete;
};