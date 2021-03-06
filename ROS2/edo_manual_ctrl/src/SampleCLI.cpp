#include "EdoFunctions.cpp"

// ===============================================================
// This file is meant to be an example of how this library of functions can be used
// It can also just be used as a standalone executable if that is preferrable.
// ===============================================================
int main(int argc, char **argv){
  
  // Initialize "edo_manual_ctrl" ROS node and NodeHandle for Publishers and
  // Subscribers
  rclcpp::init(argc, argv);
  auto calibrate_node = rclcpp::Node::make_shared("calibrate_node"); 
  auto jog_node = rclcpp::Node::make_shared("jog_ctrl"); 
  auto move_node = rclcpp::Node::make_shared("move_ctrl"); 
 
  
  rclcpp::executors::SingleThreadedExecutor exec;
 
 

  std::cout << std::fixed;                // Set precision of decimals to 
  std::cout << std::setprecision(2);      // 2 decimal places for output

  

  // Create/run initial startup to check e.DO state and calibrate if necessary
  // If bad state, exit and return -1
  // COMMENT THIS OUT IF YOU WANT TO AVOID HAVING TO MANUALLY PUBLISH MESSAGES 
  // AND ECHO TOPICS. iF YOU WANT TO TEST THAT THIS IS WORKING, OPEN A DIFFERENT 
  // TERMINAL OR TERMINALS AND USE THE FOLLOWING COMMANDS TO SIMULATE THE SUBSCRIBERS
  // AND PUBLISHERS THAT WOULD BE IN THE REAL EDO ROBOT:
  // TERMINAL1: ros2 topic pub /machine_state edo_core_msgs/msg/MachineState '{current_state: 1, opcode: 4}'
  // TERMINAL2: ros2 topic echo /bridge_init
  // TERMINAL3: ros2 topic echo /bridge_jnt_reset
  // TERMINAL4: ros2 topic echo /bridge_jnt_calib
  // NOTE: IF YOU GET THE ERROR THAT ROS2 CANT FIGURE OUT THE TYPE FOR THE TOPICS, THEN RUN THE COMMANDS 
  // AFTER YOU HAVE STARTED THIS PROGRAM BUT BEFORE YOU TYPE 'Y' FOR ANY OF THE PROMPTS
  
  if(!initialStartup(exec, calibrate_node)){
    return -1;
    }
  
  
  
  int choice = 0;

  do {
    std::cout << "1 for jog control\n"
              << "2 for move control\n"
              << "3 to re-calibrate\n"
              << "4 to print eDO data\n"
              << "-1 to exit: ";
    std::cin >> choice;

    switch(choice){

    case 1:
      jog(jog_node);
      break;
    
    case 2:
     move(move_node);
      break;
      
    case 3:
     calibrate(calibrate_node, true);
      break;

    case 4:
     getData(exec);
      break;
 
    } // switch(choice)
  } while(choice != -1);

  return 0;
}  // main() 


