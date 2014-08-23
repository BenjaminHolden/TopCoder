#include <vector>
#include <iostream>

class treeNode{
public:
  int id;
  int myTime;
  int totalDepthTime;
  std::vector<treeNode*> myChildren;
  treeNode *myParent; 
  bool visited;
  treeNode(){
    id = -1;
    myTime = -1;
    totalDepthTime = -1;
    visited = false;
    myParent = NULL;
  }
  void print(){
    std::cout<<"id: "<<id<<", time: "<<myTime<<", visited: "<<visited<<", depth: "<<totalDepthTime;
    if(myParent !=NULL){
      std::cout<<", parent_id: "<<myParent->id<<std::endl;
    }else{
      std::cout<<std::endl;
    }
  }
};

class PowerOutage{
public:
	
  int mySearch(treeNode* n, int time){
    std::cout <<"Visited: "<< n->id<<", Current Time: "<<time<<std::endl;
    n->visited = true;
    //time += n->myTime;
		
    std::vector<treeNode*> children = n->myChildren;
    int N = children.size();
    bool called_child = false;
    for(int i=0;i<N;i++){
      treeNode* child = children[i];
      if(!child->visited){
	called_child =true;
	std::cout<<"\tCalled on child (myID="<<n->id<<")"<<std::endl;
	time = mySearch(child,time+child->myTime); //time from child to parent is stored in child!!			
      }
    }
    if(called_child){
      return time;
    }
    if(n->myParent == NULL){	//We are at the root, and have gone through all children
      return time;
    }
    std::cout<<"\tcalled on parent (myID="<<n->id<<")"<<std::endl;
    time = mySearch(n->myParent,time+n->myTime);
    return time;
  }
  void updateDepth(treeNode* n){
    int N = n->myChildren.size();
    int depth = n->totalDepthTime;
    for(int i=0;i<N;i++){
      treeNode* child = n->myChildren[i];
      child->totalDepthTime = depth + child->myTime;
      updateDepth(child);
    }
  }
  int estimateTimeOut(std::vector<int> fromJunction, std::vector<int> toJunction, std::vector<int> ductLength){
    //First create tree;
    int N_juncs = fromJunction.size();
    int N=0;
    for(int i=0;i<N_juncs;i++){
      int f = fromJunction[i];
      int t = toJunction[i];
      if(f>N){
	N = f;
      }
      if(t>N){
	N = t;
      }
    }
    N = N+1; //Length is +1 the highest value (because there is a 0 element)
    std::vector<treeNode> myNodes(N);
		
    std::cout<<"N: "<<N<<", N_Juncs: "<<N_juncs<<std::endl;
    for(int i=0;i<N;i++){
      myNodes[i].id = i;
      //myNodes[i].myTime = ductLength[i];
    }
    //each node is now created -- now connect parents with children!
    for(int i=0;i<N_juncs;i++){
      treeNode* tree_start = &(myNodes[fromJunction[i]]);
      treeNode* tree_end = &(myNodes[toJunction[i]]);
			
      std::cout<<"Tree_start, i="<<fromJunction[i]<<", ";
      tree_start->print();
      std::cout<<"Tree_end, i="<<toJunction[i]<<", ";
      tree_end->print();
			
      int t = ductLength[i];
      tree_start->myChildren.push_back(tree_end);
      if(tree_end->myParent != NULL){
	std::cerr<< "Already had a parent: " << tree_end->myParent->id <<", id: "<<tree_end->id<< ", new parent_id: "<<tree_start->id <<"(i= "<<i<<")";
	return -1;
      }
      tree_end->myParent = tree_start;
      tree_end->myTime = t;
    }
    //Now the tree has been created!
    //Now find the deepest node
    updateDepth(&(myNodes[0])); //start at root -- update all depths
    myNodes[0].totalDepthTime = myNodes[0].myTime;
    //find max
    int myMax = -1;
    int myId = -1;
    for(int i=0;i<N;i++){
      int curVal = myNodes[i].totalDepthTime;
      if(curVal >= myMax){ //made is or equal so that I get the highest ID with this value
	myId = i;
	myMax = curVal;
      }
    }
    std::cout<< "Found max depth, id= "<<myId<<", ";
    myNodes[myId].print();
    // Now find shortest path
    return mySearch(&(myNodes[myId]),0);
  }
	
};
