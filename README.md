# Raspberry_pi_pico_calculator
*-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_STILL A WORK IN PROGRESS-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-*
-------------------------------------------------
*TABLE OF CONTENT*
-------------------------------------------------
1) [INTRODUCTION](#introduction)
2) [FEATURES](#features)
   
    • [FEATURES OF THE CALCULATOR WITHOUT THE EXPANSION MODULE](#calculator-without-the-expansion-module)
   
    • [FEATURES OF THE CALCULATOR WITH THE EXPANSION MODULE](#calculator-with-the-expansion-module)

3) [HARDWARE REQUIREMENTS](#hardware-requirements)
4) [WIRING DIAGRAM](#wiring-diagram)






-------------------------------------------------
## INTRODUCTION
-------------------------------------------------

A simple but advanced calculator made using a raspberry pi pico. (Project started on 07/03/2026)

The code for this project was written in Arduino IDE in C/C++ and is intended to be uploaded to the Raspberry pi pico through the Arduino IDE software.

I started making this project just for fun and it turned out to be something more serious than I thought.
Still there might be small bugs and glitches here and there, But I'm doing my best to fix everything.

This project contains 2 types of calculator models:

1) The first model contains just the calculator with all basic functions, the number pad and the screen.
2) The second model contains a seperate expansion module that can be plugged in to the usb c port that can be found on the bottom of the calculator

-------------------------------------------------------------------------
*************************************************************************************************************************************
## FEATURES 

## CALCULATOR WITHOUT THE EXPANSION MODULE
-------------------------------------------------------------------------
1) All basic arithmetic functions such as addtion, substruction, division, multiplication, square root and power.
2) Ability to work with demical values.
3) A scrolling display (So you are not limited by the space of a 16x2 LCD).
4) Custom boot up animation. (Can be modified according to your references).
5) Rechargable via USB C.


------------------------------------------------------------------------
## CALCULATOR WITH THE EXPANSION MODULE
------------------------------------------------------------------------
1) All functions of the regular calculator
   
   **MAIN FEATURE**
2) Contains a seperate module which can be plugged in to your regular calculator to add more functionality
   (Inside this module contains a separate raspberry pi pico running its own code. but is connected to communicate in serial with your main calculator)


-------------------------------------------------
## HARDWARE REQUIREMENTS
*Links provided for the exact hardware I used*
-------------------------------------------------
1) 1x Raspberry pi pico (2 x pico's if you are planning to make the expansion module) (https://it.aliexpress.com/item/1005008574488243.html?spm=a2g0o.order_list.order_list_main.47.663e3696NJjg2b&gatewayAdapt=glo2ita)
   
2) 20x Low profile mechanical keyboard switches (https://it.aliexpress.com/item/1005005783406100.html?spm=a2g0o.order_list.order_list_main.5.663e3696NJjg2b&gatewayAdapt=glo2ita)

3) 1x 16x2 LCD display with an I2C module (https://it.aliexpress.com/item/1005006100081942.html?spm=a2g0o.order_list.order_list_main.53.663e3696NJjg2b&gatewayAdapt=glo2ita

4) 1 x 105568 LiPo Battery 3.7V 5000mAh (https://it.aliexpress.com/item/1005009226410684.html?spm=a2g0o.order_list.order_list_main.16.611e36961KwMcX&gatewayAdapt=glo2ita)

5) 1 x Charging module + boost step up module (https://it.aliexpress.com/item/1005005656423941.html?spm=a2g0o.order_list.order_list_main.10.611e36961KwMcX&gatewayAdapt=glo2ita)

6) Male and Female USB C connectors (Only need for the Calculator with the expansion module) (https://it.aliexpress.com/item/1005004301569975.html?spm=a2g0o.order_list.order_list_main.23.663e3696NJjg2b&gatewayAdapt=glo2ita)

7) 22 AWG electrical wires (https://it.aliexpress.com/item/1005008664132121.html?spm=a2g0o.order_list.order_list_main.41.663e3696NJjg2b&gatewayAdapt=glo2ita)

8) 1x ON/OFF Switch (https://it.aliexpress.com/item/1005007798133277.html?spm=a2g0o.order_list.order_list_main.65.663e3696NJjg2b&gatewayAdapt=glo2ita)

9) A variety of screws and bolts (https://it.aliexpress.com/item/1005007123615498.html?spm=a2g0o.order_list.order_list_main.71.663e3696NJjg2b&gatewayAdapt=glo2ita)


------------------------------------------------------------------------
## WIRING DIAGRAM
------------------------------------------------------------------------
