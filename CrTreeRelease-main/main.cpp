#include "port.hpp"
#include "pin.hpp"
#include "gpiocregisters.hpp"
#include "gpioaregisters.hpp"
#include "rccregisters.hpp"
#include <cstdint>
#include <iostream>
#include "led.hpp"
#include "button.hpp"
#include "garlands.hpp"
#include "nvicregisters.hpp"
#include "newYearTree.hpp"

extern "C"
{
  int __low_level_init(void)
  {
    RCC::CR::HSEON::On::Set();
    while (!RCC::CR::HSERDY::Ready::IsSet())
    {
    }
    RCC::CFGR::SW::Hse::Set();
    while (!RCC::CFGR::SWS::Hse::IsSet())
    {
    }
    RCC::CR::HSION::Off::Set();                                                 //Отключаем внешний источник тактирования
    RCC::AHB1ENR::GPIOCEN::Enable::Set();                                       
    RCC::AHB1ENR::GPIOAEN::Enable::Set();
    GPIOC::MODER::MODER5::Output::Set();                                        //Светодиоды на выход
    GPIOA::MODER::MODER5::Output::Set();
    GPIOC::MODER::MODER9::Output::Set();                                        
    GPIOC::MODER::MODER8::Output::Set();                                        
    GPIOC::MODER::MODER13::Input::Set();                                        //Кнопка на выход
    
    return 1;
  }
}


Pin buttonPin(13, PortC);


Button button(buttonPin);
Timer timer;
Garlands garlands(button);
NewYearTree newYearTree;

int main()
{
  
  newYearTree.Update();
  
  for(;;)
  {

  }
  return 0;
}
