// Tree_test.cpp : Defines the entry point for the console application.
//




#include "FaultIDs.h"
#include "AlarmCommon.h"
#include "stdio.h"
#include "stdlib.h"
//#include <iostream>
#include "string.h"




void createNode(Fault fault, uint64_t instance)
{

	AlarmTreeNode* temp = new AlarmTreeNode();

	temp->fltID = fault.type.fltID;
	temp->layer = fault.type.layer;
	temp->instance = instance;
	temp->parent = fault.parent;
	if(fault.type.fltID ==0)
	{
		temp->isAlarmable = false;
	}
	TreeCls::Node* tempNode = new TreeCls::Node (temp);
	nodeList.push_back(tempNode);

}

void defineAlarms()
{

	int dataSize = sizeof(faultData)/sizeof(Fault);
	int i =0;
	while(i < dataSize )
	{
		if(faultData[i].type.layer == almModuleLayer)
		{

			for(int instance =0 ; instance < MAX_MOD_INSTANCE; instance++)
			{


				createNode(faultData[i], instance);
				//printf("%d\n",dummyData[i][0].layer);

			}
		}
		else if(faultData[i].type.layer == almXCVRLayer)
		{
			for(int instance =0 ; instance < MAX_PTP_XCVR_INSTANCE; instance++)
			{

				createNode(faultData[i], instance);

			}

		}
		else if(faultData[i].type.layer == almPTPLayer)
		{
			for(int instance =0 ; instance < MAX_PTP_XCVR_INSTANCE; instance++)
			{

				createNode(faultData[i], instance);
			}
		}

//		else
//		{
//			printf("HAS TO BELONG TO A LAYER!!");
//		}

		i++;
	}
}

void printAllAlarms()
{
	for( int i =0; i <  nodeList.size(); i++)
	{
		TreeCls::Node* n = nodeList[i];
		printf("NUM : %d , ID - %d, LAYER - %d, INSTANCE - %d \n", i+1, n->data()->fltID,
														n->data()->layer,
														n->data()->instance);
	}

	printf("\n \n \n ");
}

void buildAlarmTree()
{
	defineAlarms();
	TreeCls::Node* root;
	printAllAlarms();

	for( int i =0; i <  nodeList.size(); i++)
	{
		TreeCls::Node* currentChild = nodeList[i];
		if(currentChild->data()->layer != NULL_NODE)
		{
			uint64_t parentId = currentChild->data()->parent.fltID;
			uint64_t parentLayer = currentChild->data()->parent.layer;
			for(int i =0; i <  nodeList.size(); i++)
			{
				TreeCls::Node* potentialParent = nodeList[i];
				if(potentialParent->data()->layer)
				{

					if((potentialParent->data()->fltID == parentId)&&
					   (potentialParent->data()->layer == parentLayer)&&
					   (potentialParent->data()->instance == currentChild->data()->instance)&&
					   (potentialParent->data()->fltID != 0))
					{
						potentialParent->add_child(currentChild);
					}
					else if((potentialParent->data()->fltID == parentId)&&
							(potentialParent->data()->layer == parentLayer)&&
							(potentialParent->data()->fltID == 0))
					{

						if(potentialParent->data()->layer == almChassisLayer)
						{
							potentialParent->add_child(currentChild);
							//printf("CHASSIS FAULT	CHILDREN : ID - %d, LAYER - %d, INSTANCE - %d \n", potentialChild->data()->fltID,
							//																	   potentialChild->data()->layer,
							//																	   potentialChild->data()->instance);
						}
						else if(potentialParent->data()->layer == almModuleLayer)
						{
							//TODO: Will add instance checks
							potentialParent->add_child(currentChild);
							//printf("MODULE FAULT	CHILDREN : ID - %d, LAYER - %d, INSTANCE - %d \n", potentialChild->data()->fltID,
							//																	   potentialChild->data()->layer,
							//																	   potentialChild->data()->instance);
						}
						else if((potentialParent->data()->layer == almXCVRLayer) )
						{
							if(potentialParent->data()->instance == currentChild->data()->instance)
							{
								potentialParent->add_child(currentChild);
								//printf("XCVR FAULT	CHILDREN : ID - %d, LAYER - %d, INSTANCE - %d \n", potentialChild->data()->fltID,
								//																	   potentialChild->data()->layer,
								//																	   potentialChild->data()->instance);
							}

						}
						else if((potentialParent->data()->layer == almPTPLayer) )
						{
							if(potentialParent->data()->instance == currentChild->data()->instance)
							{
								potentialParent->add_child(currentChild);
								//printf("PTP FAULT	CHILDREN : ID - %d, LAYER - %d, INSTANCE - %d \n", potentialChild->data()->fltID,
								//																	   potentialChild->data()->layer,
								//																	   potentialChild->data()->instance);
							}

						}
						else
						{
							printf("ERROR : Create the alarm table properly");
						}

					}
				}



			 }
		}

	}

	for(int i =0; i < nodeList.size(); i++)
	{
		TreeCls::Node* temp = nodeList[i];
		if((temp->data()->fltID == WS_MODULE_MISSING_ID)
		 &&(temp->data()->layer == almModuleLayer)
		 &&(temp->data()->instance == 0))
		{
			root = temp;
		}
	}
	//root = nodeList[0];


	AlarmTree.set_root (root);

	//Check for cycles in tree
	if(AlarmTree.checkCycles())
	{
		printf("ERROR: TREE CONTAINS CYCLES!\n");
		exit(0);
	}




}

void printTree(TreeCls::Node* root, std::string prefix)
{
	    if (root->num_children() == 0) {
	    	 std::cout << prefix << "+- " << "(ID: " << root->data()->fltID
										  <<" Layer: " << root->data()->layer
										  << " Instance: " << root->data()->instance
										  << " IsMasked: " << root->data()->myMask
										  << " IsAlarmed: " << root->data()->myFault
										  << ")" << std::endl;
			return;
	    }

	    std::cout << prefix << "+- " << "(ID: " << root->data()->fltID
	    							 <<" Layer: " << root->data()->layer
									 << " Instance: " << root->data()->instance
									 << " IsMasked: " << root->data()->myMask
									 << " IsAlarmed: " << root->data()->myFault
									 << ")" << std::endl;
	    for(int i = 0; i < root->num_children(); i++)
	    {
		    printTree(root->child(i), prefix + "|  ");
	    }


}

void updateTree(TreeCls::Node* currentFault, bool parentMask)
{
	currentFault->data()->myMask = parentMask;
	bool childMask = parentMask;

	if((!(currentFault->data()->myMask)) && (currentFault->data()->myFault))
	{
		currentFault->data()->myCorrelatedFault =true;
		childMask = true;
	}
	else
	{
		currentFault->data()->myCorrelatedFault = false;
	}

	if(!currentFault->has_children())
	{
		return;
	}
	else
	{
		for(int i = 0 ; i < currentFault->num_children(); i++)
		{
			updateTree(currentFault->child(i),childMask);
		}
	}
}



void correlateFaults(uint64_t fltID, uint64_t layer, uint64_t instance, FaultState state)
{
	TreeCls::Node* faultOccuredNode;
	for(int i =0; i < nodeList.size(); i++)
	{
		TreeCls::Node* temp = nodeList[i];
		if((temp->data()->fltID == fltID)
		 &&(temp->data()->layer == layer)
		 &&(temp->data()->instance == instance))
		{
			faultOccuredNode = temp;
		}
	}
//	printf("PARENT : ID - %d, LAYER - %d, INSTANCE - %d \n", faultOccuredNode->data()->fltID,
//			faultOccuredNode->data()->layer,
//			faultOccuredNode->data()->instance);
	faultOccuredNode->data()->myFault = state;
    updateTree(AlarmTree.get_root(), false);
}

void reportAlarms()
{

	bool faultToReport = false;
	for(int i =0; i < nodeList.size(); i++)
	{
		TreeCls::Node* temp = nodeList[i];
		if((!(temp->data()->myMask))&&(temp->data()->myFault)&&(temp->data()->isAlarmable))
		{

			 printf("Fault Raised: %d %d %d \n", temp->data()->fltID,
					 	 	 	 	 	 	 	  temp->data()->layer,
					                              temp->data()->instance);
			 faultToReport = true;
		}
	}

	if(!faultToReport) printf("No Faults \n");

	std::cout <<"\n\n\n";

}

int main(int argc, char* argv[])
{


	buildAlarmTree();


	std::cout <<"############## TREE INFORMATION ##################";
	std::cout <<"\n\n\n";
	std::cout << "Node count : " << AlarmTree.nodeCount() << std::endl;
	std::cout <<"\n\n\n";
	std::cout <<"CURRENTLY IN TREE \n";

	for(int i =0 ; i < AlarmTree.getAllNodes().size(); i++)
	//for(Node* n : parent->getChildren())
	{
		TreeCls::Node* n = AlarmTree.getAllNodes()[i];

		printf("ID - %d, LAYER - %d, INSTANCE - %d \n", n->data()->fltID,
														n->data()->layer,
														n->data()->instance);
	}

	std::cout <<"\n\n\n";

	correlateFaults(WS_LOSS_OF_CHANNEL_ID, almPTPLayer,1, SET);

	reportAlarms();
	correlateFaults(WS_XCVR_LAYER_FAULT_ID, almXCVRLayer,0, SET);
	reportAlarms();

	correlateFaults(WS_MODULE_MISSING_ID, almModuleLayer,0, SET);

	reportAlarms();

	printTree(AlarmTree.get_root(), "");

	return 0;


}

