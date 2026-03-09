# Raspberry_pi_pico_calculator
*STILL A WORK IN PROGRESS*
-------------------------------------------------
*TABLE OF CONTENT*
-------------------------------------------------
1) [INTRODUCTION](#introduction)
2) [FEATURES](#features)
   
    • [FEATURES OF THE CALCULATOR WITHOUT THE EXPANSION MODULE](#features-of-the-calculator-without-the-expansion-module)
   
    • [FEATURES OF THE CALCULATOR WITH THE EXPANSION MODULE](#features-of-the-calculator-with-the-expansion-module)

3) [HARDWARE REQUIREMENTS](#hardware-requirements)






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

## FEATURES OF THE CALCULATOR WITHOUT THE EXPANSION MODULE
-------------------------------------------------------------------------
1) All basic arithmetic functions such as addtion, substruction, division, multiplication, square root and power.
2) Ability to work with demical values.
3) A scrolling display (So you are not limited by the space of a 16x2 LCD).
4) Custom boot up animation. (Can be modified according to your references).


------------------------------------------------------------------------
## FEATURES OF THE CALCULATOR WITH THE EXPANSION MODULE
------------------------------------------------------------------------
1) All functions of the regular calculator
   
   **MAIN FEATURE**
2) Contains a seperate module which can be plugged in to your regular calculator to add more functionality
   (Inside this module contains a separate raspberry pi pico running its own code. but is connected to communicate in serial with your main calculator)


-------------------------------------------------
## HARDWARE REQUIREMENTS
*Links provided for the exact hardware I used*
-------------------------------------------------
1) 1x Raspberry pi pico (2 x pico's if you are planning to make the expansion module)
2) 20 Low profile mechanical keyboard switches (https://it.aliexpress.com/item/1005005783406100.html?spm=a2g0o.order_list.order_list_main.5.663e3696NJjg2b&gatewayAdapt=glo2ita)

3) 16x2 LCD display with an I2C module (https://it.aliexpress.com/item/1005006100081942.html?spm=a2g0o.order_list.order_list_main.53.663e3696NJjg2b&gatewayAdapt=glo2ita

4) 4X 18650 AA Battery case (https://it.aliexpress.com/item/1005006117644933.html?spm=a2g0o.cart.0.0.20b218fcTmu9Ou&mp=1&pdp_npi=6%40dis%21EUR%21EUR%203.37%21EUR%201.62%21%21EUR%200.60%21%21%21%40211b618e17730842754156541e854e%2112000035829498633%21ct%21IT%212963873461%21%211%210%21&gatewayAdapt=glo2ita)
