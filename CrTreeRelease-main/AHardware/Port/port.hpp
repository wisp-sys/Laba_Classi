#include <cstdint> //��� ���32, ���8
#include <cassert>
#pragma once

class IPort
{
  public:
    virtual void Toggle(std::uint8_t num) = 0;                                  //������� ���� �����������
    virtual std::uint32_t Get() = 0;
      
      
};


template <typename Reg>
class Port:  public IPort                                                       // ����� ��������� - ��� ������� ������������ � IPort
{
  public:
    void Toggle(std::uint8_t num) override
    {
      assert(num < 16);
      Reg::ODR::Toggle(1 << num);
    }
    std::uint32_t Get() override
    {
      
      return Reg::IDR::Get();
    }
};