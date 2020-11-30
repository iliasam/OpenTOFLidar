# OpenTOFLidar
Open Hardware scanning laser rangefinder based on Time-of-Flight principle. No standalone laser rangefinder modules were used in this LIDAR, so its schematic and firmware are fully open.  
 
Its parameters:  
* Scanning speed: 15 scans/second
* Resolution: ~ 1% of distance, but not better than ±2 cm
* Minimal distance: 5 cm
* Maximal distance: ~25 m (white surface)
* Angular resolution: 0.5 deg
* Measurements frequency: ~11 kHz
* Scanning angular range: ~230 deg, could be increased by changing mechanics
* Power: 0.1 A  at 5V (0.5 W). Start current could be bigger than 0.8 A.
* Size: 50x50x120 mm

Price of the components of this LIDAR is ~114$ (without delivery).  
See BOM with all calculations: "TotalBOM.xlsx".  
This LIDAR is using COTS (Commercial Off-The-Shelf) optical components - standard lenses for surveillance cameras.  
  
There is a big article in Russian about this project: https://habr.com/ru/post/485574/   
Google translation: https://translate.google.com/translate?hl=en&sl=auto&tl=en&u=https%3A%2F%2Fhabr.com%2Fru%2Fpost%2F485574%2F  

**See project's Wiki for more information:** https://github.com/iliasam/OpenTOFLidar/wiki  


![](https://github.com/iliasam/OpenTOFLidar/blob/develop/Images/lidar_photo_small.jpg)  

That is how its components are assembled:  
<img src="https://github.com/iliasam/OpenTOFLidar/blob/develop/Mechanical/Assembly2.png" height="600">  
  
Structure schematic of this LIDAR:  
<img src="https://github.com/iliasam/OpenTOFLidar/blob/develop/Images/structure.png" width="600">  

Example of Hector SLAM result:  
<img src="https://github.com/iliasam/OpenTOFLidar/blob/develop/Images/slam_result_example.png" width="700">  
  
**Video** about OpenTOFLidar:
https://youtu.be/lTPH_Xa9yCk
  
Please leave me feedback if you will be able to reproduce this project.  
