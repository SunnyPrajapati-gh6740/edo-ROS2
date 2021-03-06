

/***************************************************************
**                Function(s) Definition
****************************************************************/


/** @file DataDisplay.cpp
 *  @brief Class definiton for DataDisplay - converted for RO2
 *  @date October 8, 2020
 *  @author Seth Buchinger - based on Jack Shelata ROS1 class

*/

#include "DataDisplay.h"


/**ROS1**
DataDisplay::DataDisplay(ros::NodeHandle& nh_in){
  nh = nh_in;
  cartesian_pose_sub = nh.subscribe("/cartesian_pose", 10,
      &DataDisplay::printPoseData, this);
  machine_state_sub = nh.subscribe("/machine_state", 10,
      &DataDisplay::printState, this);
  joint_pose_sub = nh.subscribe("/machine_algo_jnt_state", 10,
      &DataDisplay::printJointPose, this);
  cartesianPrinted = false;
  statePrinted = false;
  jointPrinted = false;
}  // DataDisplay::DataDisplay()


*/

//**ROS2**
DataDisplay::DataDisplay() : Node("data_display")
{
  //create three subscibers on instantiation of an object
  cartesian_pose_sub_ =
  this->create_subscription<edo_core_msgs::msg::CartesianPose>(
  "/cartesian_pose", 10, std::bind(&DataDisplay::printPoseData, this,_1));
  machine_state_sub_ =
  this->create_subscription<edo_core_msgs::msg::MachineState>(
  "/machine_state", 10, std::bind(&DataDisplay::printState, this,_1));
  joint_pose_sub_ =
  this->create_subscription<edo_core_msgs::msg::JointStateArray>(
  "/machine_algo_jnt_state_bridge", 10, std::bind(&DataDisplay::printJointPose,
  this,_1)); 

  cartesianPrinted = false; 
  statePrinted = false; 
  jointPrinted =false;

}
//=======================================================================================
/** @brief Callback function to print CartesianPose message
 *  @param pose - CartesianPose message type from "/cartesian_pose" ROS topic
 *  @return void
 *  @exception None
 */

/**ROS1**
void DataDisplay::printPoseData(const edo_core_msgs::CartesianPose& pose){
  if(!cartesianPrinted){
    std::cout << pose << "\n";
    cartesianPrinted = true;
*/

//**ROS2**
void DataDisplay::printPoseData(const edo_core_msgs::msg::CartesianPose::SharedPtr pose){
  if(!cartesianPrinted){
    std::cout << "CartesianPose/x: " << pose->x <<"\n" 
    << "CartesianPose/y: " << pose->y <<"\n" 
    << "CartesianPose/z: " << pose->z <<"\n"
    <<"CartesianPose/a: " << pose->a << "\n" 
    <<"CartesianPose/e: " << pose->e << "\n"
    <<"CartesianPose/r: " << pose->r << "\n";
    cartesianPrinted = true;
  }
}  // DataDisplay::printPoseData()

//=======================================================================================
/** @brief Callback function to print MachineState message
 *  @param pose - MachineState message type from "/machine_state" ROS topic
 *  @return void
 *  @exception None
 */

/**ROS1**
void DataDisplay::printState(const edo_core_msgs::MachineState& state){
  if(!statePrinted){
    std::cout << state << "\n";
    statePrinted = true;
  }
} */


//**ROS2**
void DataDisplay::printState(const edo_core_msgs::msg::MachineState::SharedPtr state){
  if(!statePrinted){
    std::cout << "MachineState/current_state: " << unsigned(state->current_state) << "\n";
    std::cout << "MachineState/opcode: " << unsigned(state->opcode) << "\n";
    statePrinted = true;
  }
}  // DataDisplay::printState()


//=======================================================================================
/** @brief Callback function to print JointStateArray message
 *  @param pose - MachineState message type from "/machine_algo_jnt_state"
 *  ROS topic
 *  @return void
 *  @exception None
 */

/**ROS1**
void DataDisplay::printJointPose(const edo_core_msgs::JointStateArray& pose){
  if(!jointPrinted){
    std::cout << pose << "\n";
    jointPrinted = true;
  }
}*/


//**ROS2**
void DataDisplay::printJointPose(const edo_core_msgs::msg::JointStateArray::SharedPtr pose){
  if(!jointPrinted){
     std::cout << "JointStateArray/joints_mask: " << pose->joints_mask << "\n";
    //std::cout << "JointStateArray/joints: " << pose->joints[0].position << endl;
     int i = 0;

  //loop through all e.DO joints and print out JointState message within JointStateArray
   for(edo_core_msgs::msg::JointState joint : pose->joints)
    {
      std::cout << "edo_core_msgs/msg/JointState[" << i << "] position: " << joint.position << "\n";
      std::cout << "edo_core_msgs/msg/JointState[" << i << "] velocity: " << joint.velocity << "\n";
      std::cout << "edo_core_msgs/msg/JointState[" << i << "] current: " << joint.current << "\n";
      std::cout << "edo_core_msgs/msg/JointState[" << i << "] command_flag: " << joint.command_flag << "\n";
      std::cout << "edo_core_msgs/msg/JointState[" << i << "] r_jnt: " << joint.r_jnt << "\n";

      i++;
    }
    jointPrinted = true;
 }
}  // DataDisplay::printJointPose()


//=======================================================================================

/** @brief Getter member function to tell whether cartesian data has been
 *  printed
 *  @param None 
 *  @return bool - Value of cartesianPrinted (true if data was printed)
 *  @exception None
 */

bool DataDisplay::getCartesianPrinted(){
  return cartesianPrinted;
}  // DataDisplay::getCartesianPrinted()

//=======================================================================================
/** @brief Getter member function to tell whether State data has been
 *  printed
 *  @param None 
 *  @return bool - Value of statePrinted (true if data was printed)
 *  @exception None
*/
bool DataDisplay::getStatePrinted(){
  return statePrinted;
}  // DataDisplay::getStatePrinted()


//=======================================================================================
/** @brief Getter member function to tell whether Joint data has been
 *  printed
 *  @param None 
 *  @return bool - Value of jointPrinted (true if data was printed)
 *  @exception None
*/
bool DataDisplay::getJointPrinted(){
  return jointPrinted;
}  // DataDisplay::getJointPrinted()
 
