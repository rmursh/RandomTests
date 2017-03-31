/*
 * AlarmCommon.h
 *
 *  Created on: Mar 28, 2017
 *      Author: rmurshed
 */

#ifndef ALARMCOMMON_H_
#define ALARMCOMMON_H_


#define MAX_PORT_INSTANCE 8
#define MAX_PTP_XCVR_INSTANCE 2
#define MAX_MOD_INSTANCE 1
#define CHASSIS_INSTANCE 1

#define MAX_ALARMS 120
#define MAX_CHILDREN 62
#define NULL_NODE 255
#include "Tree.h"
#include <vector>
#include <map>
#include "FaultIDs.h"


typedef unsigned long long uint64_t;
typedef enum
{
	SET = 1,
	CLEAR = 0
}FaultState;

typedef struct almType_t
{
	uint64_t fltID;
	uint64_t layer;

	//almType_t(): fltID(NULL_NODE),layer(NULL_NODE){}

}FaultType;

//typedef struct almNode_t
//{
//	FaultType type;
//	std::vector<FaultType> children;
//}Fault;

typedef struct
{
	FaultType type;
	FaultType parent;
}Fault;

typedef struct almLocation_t
{
	uint64_t fltID;
	uint64_t layer;
	uint64_t instance;

}FaultLocation;



typedef struct dumTreeNode
{
	uint64_t fltID;
	uint64_t layer;
	uint64_t instance;
	bool myMask = false;
	bool isAlarmable = true;
	bool myFault = false;
	bool myCorrelatedFault = false;
	FaultType parent;
}AlarmTreeNode;

/*
 * Use the following template
 *
 *
 * {
 *   {Node, layer},
 *    {
 *      {child1,layer},
 *      {child2,layer},
 *      {child3,layer},
 *      .......
 *      ......
 *    }
 * }
 */




//Fault faultsData[] =
//{
//
//  /*
//   * MODULE FAULTS
//   */
//  {
//	{WS_MODULE_MISSING_ID, almModuleLayer},
//		  {
//			{WS_MODULE_PROVISIONING_MISMATCH_ID,almModuleLayer}
//		  }
//  },
//
//  {
//	{WS_MODULE_PROVISIONING_MISMATCH_ID, almModuleLayer},
//		  {
//			{WS_MODULE_FAILED_ID,almModuleLayer}
//		  }
//  },
//
//  {
//	{WS_MODULE_FAILED_ID, almModuleLayer},
//		  {
//		   {WS_MODULE_OVER_TEMPERTURE_ID,almModuleLayer},
//		   {WS_MODULE_COMMUNICATIONS_SUSPECTED_ID,almModuleLayer},
//		   {WS_MODULE_LAYER_FAULT_ID,almModuleLayer}
//		  }
//  },
//
//  {
//	{WS_MODULE_OVER_TEMPERTURE_ID, almModuleLayer},
//		  {
//
//		  }
//  },
//
//  {
//	{WS_MODULE_COMMUNICATIONS_SUSPECTED_ID, almModuleLayer},
//		  {
//
//		  }
//  },
//
//  {
//	{WS_MODULE_LAYER_FAULT_ID, almModuleLayer},
//		  {
//			{WS_XCVR_FAILED_ID,almXCVRLayer},
//			{WS_XCVR_MISSING_ID,almXCVRLayer}
//		  }
//  },
//
//
//  /*
//   * XCVR FAULTS
//   */
//  {
//	{WS_XCVR_FAILED_ID, almXCVRLayer},
//		  {
//			{WS_XCVR_COMMUNICATIONS_SUSPECT_ID,almXCVRLayer},
//			{WS_XCVR_OVER_TEMPERATURE_ID,almXCVRLayer},
//			{WS_XCVR_UNDER_TEMPERATURE_ID,almXCVRLayer},
//			{WS_XCVR_LAYER_FAULT_ID, almXCVRLayer}
//		  }
//  },
//
//  {
//	{WS_XCVR_MISSING_ID, almXCVRLayer},
//		  {
//			{WS_XCVR_PROVISIONING_MISMATCH_ID,almXCVRLayer},
//			{WS_XCVR_CAPABILITY_MISMATCH_ID,almXCVRLayer},
//		  }
//  },
//
//
//  {
//	{WS_XCVR_CAPABILITY_MISMATCH_ID, almXCVRLayer},
//		  {
//
//		  }
//  },
//
//  {
//	{WS_XCVR_PROVISIONING_MISMATCH_ID, almXCVRLayer},
//		  {
//			{WS_XCVR_FAILED_ID,almXCVRLayer},
//		  }
//  },
//
//
//  {
//	{WS_XCVR_COMMUNICATIONS_SUSPECT_ID, almXCVRLayer},
//		  {
//
//		  }
//  },
//
//  {
//	{WS_XCVR_OVER_TEMPERATURE_ID, almXCVRLayer},
//		  {
//
//		  }
//  },
//
//  {
//	{WS_XCVR_UNDER_TEMPERATURE_ID, almXCVRLayer},
//		  {
//
//		  }
//  },
//
//  {
//	{WS_XCVR_LAYER_FAULT_ID, almXCVRLayer},
//		  {
//		    {WS_PTP_LOSS_OF_SIGNAL_ID,almPTPLayer},
//			{WS_TX_PROVISIONING_REQUIRED_ID,almPTPLayer}
//		  }
//  },
//
//
//  //PTP Faults
//  {
//	    {WS_PTP_LOSS_OF_SIGNAL_ID, almPTPLayer},
//		  	  {
//				{WS_RX_POWER_LOW_ID,almPTPLayer},
//				{WS_RX_POWER_HIGH_ID, almPTPLayer},
//				{WS_LOSS_OF_CHANNEL_ID, almPTPLayer},
//				{WS_TX_CHANNEL_CONTENTION_ID, almPTPLayer},
//				{WS_CHANNEL_CONTENTION_AND_PROVISIONING_REQUIRED_ID, almPTPLayer}
//
//		  	  }
//   },
//
//   {
//		{WS_CHANNEL_CONTENTION_AND_PROVISIONING_REQUIRED_ID, almPTPLayer},
//			  {
//				{WS_TX_TUNING_IN_PROGRESS_ID,almPTPLayer}
//			  }
//   },
//
//   {
//	   {WS_TX_TUNING_IN_PROGRESS_ID, almPTPLayer},
//			   {
//				 {WS_FREQUENCY_PROVISIONING_MISMATCH_ID, almPTPLayer}
//			   }
//   },
//
//   {
//	   {WS_TX_CHANNEL_CONTENTION_ID, almPTPLayer},
//			  {
//
//			  }
//  },
//
//
//
//   {
//	    {WS_TX_PROVISIONING_REQUIRED_ID, almPTPLayer},
//			{
//
//			}
//    },
//
//	{
//	  	{WS_LOSS_OF_CHANNEL_ID, almPTPLayer},
//	  		{
//	  		    {WS_RX_CHANNEL_POWER_LOW_ID,almPTPLayer},
//	  			{WS_RX_CHANNEL_POWER_HIGH_ID, almPTPLayer},
//				{WS_PTP_LOSS_OF_CLOCK_ID, almPTPLayer}
//
//	  		}
//	 },
//
//
//	 {
//		{WS_PTP_LOSS_OF_CLOCK_ID, almPTPLayer},
//			  {
//				 {WS_PTP_FREQUENCY_OUT_OF_RANGE_ID,almPTPLayer},
//				 {WS_LOSS_OF_FRAME_ID, almPTPLayer}
//
//			  }
//	  },
//
//	 {
//		{WS_LOSS_OF_FRAME_ID, almPTPLayer},
//			  {
//				 {WS_LOSS_OF_MULTIFRAME_ID,almPTPLayer}
//			  }
//	 },
//
//	 {
//		{WS_LOSS_OF_MULTIFRAME_ID, almPTPLayer},
//			  {
//				 {WS_GID_MISMATCH_ID,almPTPLayer}
//			  }
//	 },
//
//	 {
//		{WS_GID_MISMATCH_ID, almPTPLayer},
//			  {
//				 {WS_PHY_MAP_MISMATCH_ID,almPTPLayer}
//			  }
//	 },
//
//	 {
//		{WS_PHY_MAP_MISMATCH_ID, almPTPLayer},
//			  {
//				 {WS_PTP_PRE_FEC_SIGNAL_FAIL_ID,almPTPLayer}
//			  }
//	 },
//
//	 {
//		{WS_PTP_PRE_FEC_SIGNAL_FAIL_ID, almPTPLayer},
//			  {
//				 {WS_MODEM_CLASS_MISMATCH_ID,almPTPLayer}
//			  }
//	 },
//
//	 {
//		{WS_MODEM_CLASS_MISMATCH_ID, almPTPLayer},
//			  {
//				 {WS_REACH_VIOLATION_ID,almPTPLayer}
//			  }
//	 },
//
//	 {
//		{WS_REACH_VIOLATION_ID, almPTPLayer},
//			  {
//				 {WS_PTP_PRE_FEC_SIGNAL_DEGRADE_ID,almPTPLayer},
//				 {WS_RDI_ID,almPTPLayer},
//				 {WS_PTP_LAYER_FAULT_ID,almPTPLayer}
//			  }
//	 },
//
//	 {
//		{WS_PTP_LAYER_FAULT_ID, almPTPLayer},
//			  {
//
//			  }
//	 },
//
//
//};


/***
 * DUMMY
 */
Fault faultData[] =
{

  /*
   * MODULE FAULTS
   */
	{
	 {WS_MODULE_MISSING_ID, almModuleLayer},{NULL_NODE,NULL_NODE}
	},

	{
	 {WS_MODULE_PROVISIONING_MISMATCH_ID, almModuleLayer},{WS_MODULE_MISSING_ID, almModuleLayer}
	},

	{
	{WS_MODULE_FAILED_ID, almModuleLayer},{WS_MODULE_PROVISIONING_MISMATCH_ID, almModuleLayer}
	},

	{
	{WS_MODULE_OVER_TEMPERTURE_ID, almModuleLayer}, {WS_MODULE_FAILED_ID, almModuleLayer}
	},

	{
	{WS_MODULE_COMMUNICATIONS_SUSPECTED_ID, almModuleLayer},{WS_MODULE_FAILED_ID, almModuleLayer}
	},

	{
	{WS_MODULE_LAYER_FAULT_ID, almModuleLayer},{WS_MODULE_FAILED_ID, almModuleLayer}
	},


	/*
	* XCVR FAULTS
	*/


	{
	{WS_XCVR_MISSING_ID, almXCVRLayer}, {WS_MODULE_LAYER_FAULT_ID, almModuleLayer}
	},


	{
	{WS_XCVR_CAPABILITY_MISMATCH_ID, almXCVRLayer},{WS_XCVR_MISSING_ID, almXCVRLayer}
	},

	{
	{WS_XCVR_PROVISIONING_MISMATCH_ID, almXCVRLayer}, {WS_XCVR_MISSING_ID, almXCVRLayer}
	},

	{
	{WS_XCVR_FAILED_ID, almXCVRLayer},{WS_XCVR_PROVISIONING_MISMATCH_ID, almXCVRLayer}
	},

	{
	{WS_XCVR_COMMUNICATIONS_SUSPECT_ID, almXCVRLayer},{WS_XCVR_FAILED_ID, almXCVRLayer}
	},

	{
	{WS_XCVR_OVER_TEMPERATURE_ID, almXCVRLayer}, {WS_XCVR_FAILED_ID, almXCVRLayer}
	},

	{
	{WS_XCVR_UNDER_TEMPERATURE_ID, almXCVRLayer},{WS_XCVR_FAILED_ID, almXCVRLayer}
	},

	{
	{WS_XCVR_LAYER_FAULT_ID, almXCVRLayer}, {WS_XCVR_FAILED_ID, almXCVRLayer}
	},


  //PTP Faults
	{
		{WS_PTP_LOSS_OF_SIGNAL_ID, almPTPLayer},{WS_XCVR_LAYER_FAULT_ID, almXCVRLayer}
	},

	{
		{WS_CHANNEL_CONTENTION_AND_PROVISIONING_REQUIRED_ID, almPTPLayer}, {WS_PTP_LOSS_OF_SIGNAL_ID, almPTPLayer}
	},

	{
	   {WS_TX_TUNING_IN_PROGRESS_ID, almPTPLayer},{WS_CHANNEL_CONTENTION_AND_PROVISIONING_REQUIRED_ID, almPTPLayer}
	},

	{
	   {WS_TX_CHANNEL_CONTENTION_ID, almPTPLayer},{WS_PTP_LOSS_OF_SIGNAL_ID, almPTPLayer}
	},

	{
	   {WS_TX_PROVISIONING_REQUIRED_ID, almPTPLayer}, {WS_XCVR_LAYER_FAULT_ID, almXCVRLayer}
	},

	{
		{WS_FREQUENCY_PROVISIONING_MISMATCH_ID, almPTPLayer}, {WS_TX_TUNING_IN_PROGRESS_ID, almPTPLayer}
	},

	{
		{WS_RX_POWER_HIGH_ID, almPTPLayer}, {WS_PTP_LOSS_OF_SIGNAL_ID, almPTPLayer}
	},

	{
		{WS_RX_POWER_LOW_ID, almPTPLayer}, {WS_PTP_LOSS_OF_SIGNAL_ID, almPTPLayer}
	},

	{
		{WS_LOSS_OF_CHANNEL_ID, almPTPLayer}, {WS_PTP_LOSS_OF_SIGNAL_ID, almPTPLayer}
	},

	{
		{WS_RX_CHANNEL_POWER_LOW_ID, almPTPLayer}, {WS_LOSS_OF_CHANNEL_ID, almPTPLayer}
	},

	{
		{WS_RX_CHANNEL_POWER_HIGH_ID, almPTPLayer}, {WS_LOSS_OF_CHANNEL_ID, almPTPLayer}
	},

	{
		{WS_PTP_LOSS_OF_CLOCK_ID, almPTPLayer}, {WS_LOSS_OF_CHANNEL_ID, almPTPLayer}
	},

	{
		{WS_PTP_FREQUENCY_OUT_OF_RANGE_ID, almPTPLayer}, {WS_PTP_LOSS_OF_CLOCK_ID, almPTPLayer}
	},

	{
		{WS_LOSS_OF_FRAME_ID, almPTPLayer}, {WS_PTP_LOSS_OF_CLOCK_ID, almPTPLayer}
	},

	{
		{WS_LOSS_OF_MULTIFRAME_ID, almPTPLayer}, {WS_LOSS_OF_FRAME_ID, almPTPLayer}
	},

	{
		{WS_GID_MISMATCH_ID, almPTPLayer}, {WS_LOSS_OF_MULTIFRAME_ID, almPTPLayer}
	},

	{
		{WS_PHY_MAP_MISMATCH_ID, almPTPLayer},{WS_GID_MISMATCH_ID, almPTPLayer}
	},

	{
		{WS_PTP_PRE_FEC_SIGNAL_FAIL_ID, almPTPLayer}, {WS_PHY_MAP_MISMATCH_ID, almPTPLayer}
	},

	{
		{WS_MODEM_CLASS_MISMATCH_ID, almPTPLayer}, {WS_PTP_PRE_FEC_SIGNAL_FAIL_ID, almPTPLayer}
	},

	{
		{WS_REACH_VIOLATION_ID, almPTPLayer}, {WS_MODEM_CLASS_MISMATCH_ID, almPTPLayer}
	},

	{
		{WS_PTP_PRE_FEC_SIGNAL_DEGRADE_ID, almPTPLayer},{WS_REACH_VIOLATION_ID, almPTPLayer}
	},

	{
		{WS_RDI_ID, almPTPLayer},{WS_REACH_VIOLATION_ID, almPTPLayer}
	},

	{
		{WS_PTP_LAYER_FAULT_ID, almPTPLayer},{WS_REACH_VIOLATION_ID, almPTPLayer}
	}

};



typedef Tree <AlarmTreeNode*> TreeCls;
TreeCls AlarmTree;

std::map<FaultLocation, TreeCls::Node*> nodeTable;
std::vector<TreeCls::Node*> nodeList;

#endif /* ALARMCOMMON_H_ */
