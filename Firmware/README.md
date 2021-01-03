**Firmware for OpenTOFLidar**  
  
"not_scanning_fw" - simplified testing firmware. Laser is constantly "blinking" at 1000 Hz frequency.  
Supported work with "LidarTestingUtility".  
Motor is not supported.  
**BE CAREFULL - INVISIBLE LASER RADIATION! DO NOT STARE AT LASER BEAM, USE PROTECTION GLASSES! AVOID DIRECTING LASER TO REFLECTING SURFACES!**  
  
"scanning_fw" - basic Lidar's firmware. Supported motor controlling.  
Supported work with "LidarTestingUtility", "LidarScanningTest", ROS driver.  
This firmware contains protection from long laser radiation exposure - laser is working only when mirror is rotating stably. 

Firmware configuration is placed in "config.h" file.  
   
See "BUILD_FW_HEX" folder - it is containing already build HEX files.


