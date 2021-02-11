#pragma once
#include <cstdint> 
#include <cassert>
#include "led.hpp"
#include "button.hpp"
#include <array>
#include "pinscfg.h"
#include "timer.hpp"
#include <iostream>

extern Timer timer;
class Garlands  
{
  public:
    Garlands(Button& aButton): button(aButton),  leds{
                                                     Led(led1Pin),
                                                     Led(led2Pin),
                                                     Led(led3Pin),
                                                     Led(led4Pin)
                                                     }
    {
      
    }
     
     void Start() 
    {
      timer.Start(Period);
      timer.Start2();
    }
     
    void Update() 
    {
        if(button.IsPressed())
        {
        uint32_t CurrentPeriod = TIM5::ARR::Get();        
        
        if(flag == 0)
        {
          UpdatePeriod = CurrentPeriod - 50U;
          if(UpdatePeriod == 50U)
          {
            flag = 1;
          }
        }
        
        else
        {
          UpdatePeriod = CurrentPeriod + 50U;
          if(UpdatePeriod == 500U)
          {
            flag = 0;
          }
        }          
        
        timer.ChangePeriod(UpdatePeriod);
        std::cout <<"Период: " <<  UpdatePeriod << std::endl;
        }
      
    }
    
    void OnTimeOut() 
    {
      leds[i++ & 0x3].Toggle();      
    }
    
private: 
   std::array<Led, 4> leds;
   Button& button;
   bool flag = 0;
   int i = 0;
   uint32_t Period = 500U;
   uint32_t UpdatePeriod;
};