#pragma once
#include "nvicregisters.hpp"
#include "tim5registers.hpp"
#include "gpiocregisters.hpp"
#include "gpioaregisters.hpp"
#include "rccregisters.hpp"
#include "tim2registers.hpp"

class Timer
{
  public:
    
    void Start(std::uint32_t Period)
    {
      RCC::APB1ENR::TIM5EN::Enable::Set();
      TIM5::PSC::Write(7999U);
      TIM5::ARR::Write(Period);
      TIM5::CNT::Write(0U);
      NVIC::ISER1::Write(1U << 18U);
      TIM5::DIER::UIE::Value1::Set();
      TIM5::SR::UIF::NoInterruptPending::Set();
      TIM5::CR1::CEN::Enable::Set();
    }
    void ChangePeriod(uint32_t UpdatePeriod) 
    {
      TIM5::ARR::Write(UpdatePeriod);
      TIM5::CNT::Write(0U);
    }
    void Start2()
    {
      NVIC::ISER0::Write(1U << 28U);
      TIM2::CR1::URS::OverflowEvent::Set();  
      RCC::APB1ENR::TIM2EN::Enable::Set();
      TIM2::PSC::Set(7999U);
      TIM2::ARR::Write(100U);
      TIM2::SR::UIF::NoInterruptPending::Set();
      TIM2::CNT::Write(0U);      
      TIM2::DIER::UIE::Enable::Set();      
      TIM2::CR1::CEN::Enable::Set();
    }
private:
  uint32_t Period;
  
};