**PCB projects with schematics**  
"PCB_project_v1" - PCB version of 2019, designed for AD500-8. Designed for external motor driver. Be careful - there is no protection diode for TIA!  
"PCB_project_v4" - PCB version of 2020, designed for MTAPD-07-13. Contains integrated motor driver. Better documented.  
Both PCBs were tested, they are working fine.  
  
Top Copper layer - is layer with MCU.  

  
**Attention - "PCB_project_v4" board is more sensitive to WiFi signals** (if WiFi antenna is placed < 20 cm from the board).  
I had tried to install foil shield abound LIDAR board and optics, but this did not help.  
I had to install a special metallic shield between WiFi antenna and this LIDAR. It is not shown at the photos.  This is the only working solution that I know.  
I have found that WiFI signals are "received" by TIA input. I don't know why this effect is much stronger at "PCB_project_v4".
There are some of differences between PCB's: 
* TIA is placed at top/bottom sides (internal ground (Layer 1) is closer to the Top Copper layer)
* AD500-8 is shielded, MTAPD-07-13 is not shielded.
