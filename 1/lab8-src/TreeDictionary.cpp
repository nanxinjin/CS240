
#include <string.h>
#include <stdio.h>

#include "TreeDictionary.h"

TreeDictionary::TreeDictionary()
{
	char * _key;
	int _data;
	 _root = NULL;
	 _numberOfEntries = 0;

}

// Add a record to the dictionary. Overwrite data if key
// already exists. It returns false if key already exists
bool 
TreeDictionary::addRecord( const char * key, int data) {
	
	TreeNode * n = _root;
	TreeNode * prev = NULL;


	while (n != NULL){
	
		if(strcmp(key, n->_key)<0){
			prev = n;
			n = n->_left;
			
		}
		else if(strcmp(key,n->_key)>0){
			prev = n;
			n = n->_right;
			
						
		}
		
		else{	
			n->_data = data;
			return false;
		}
		
	}

	n = new TreeNode();
	n->_key = key;
	n->_data = data;
	n->_left = NULL;
	n->_right = NULL;

	if(prev == NULL){
		_root = n;
	}
	else{
		if(strcmp(key,prev->_key)<0){
			prev->_left = n;
			
	
		}
		else{
			prev->_right = n;
			
			
		}
	}
	_numberOfEntries ++;
	return true;

}

int
TreeDictionary::numberOfEntries() {
  
  return _numberOfEntries;
}

// Find a key in the dictionary and return corresponding record.
bool 
TreeDictionary::findRecord( const char * key, int & data) {
	TreeNode * n = _root;
	
	while(n != NULL){
		if(strcmp(key,n->_key)<0){
			n = n->_left;
		}
		else if(strcmp(key, n->_key)>0){
			n = n->_right;
		}
		else{
			data ++;
			return true;
		}
	
	}	
	return false;
}

void 
TreeDictionary::printIndented(TreeNode * node, int level) {
	int i = 0;
	for(i;i<level;i++){
		printf("  ");
	}
	if(node == NULL){
		printf("NULL\n");
		return;
	}
	printf("%s:%d\n",node->_key,node->_data);
	level++;
	printIndented(node->_left,level);
	printIndented(node->_right,level);

}

void 
TreeDictionary::printIndented(){
	printIndented(_root,0);
}

void 
TreeDictionary::print(TreeNode *node) {
	if(node == NULL)return;
	printf("%s:%d\n", node->_key,node->_data);
	print(node->_left);
	print(node->_right);
}

void TreeDictionary::print()
{
	print(_root);
}

// Max depth in tree
void
TreeDictionary::computeDepthHelper(TreeNode * node, int depth, int & currentMaxDepth) {
	if(node == NULL){
		depth -1;
		return;
	}
	depth++;
	if(currentMaxDepth<depth){
		currentMaxDepth = depth;
	}
	computeDepthHelper(node->_left,depth,currentMaxDepth);
	computeDepthHelper(node->_right,depth,currentMaxDepth);

}

int 
TreeDictionary::maxDepth() {
	
	int currentMaxDepth = -1;
	computeDepthHelper(_root, -1,currentMaxDepth);
	return currentMaxDepth;
}


TreeDictionary::~TreeDictionary()
{
}

// Minimum key. The leftmost node
const char * 
TreeDictionary::minimumKey()
{
	TreeNode * n = _root;

	while(n->_left != NULL){
		n = n->_left;
	}
 	return n->_key;
}

// Maximum Key. The rightmost node
const char * 
TreeDictionary::maximumKey()
{
	TreeNode * n = _root;

	while(n->_right != NULL){
	        n = n->_right;
	}
	return n->_key;
}

void
TreeDictionary::collectKeys(TreeNode * node, const char **keys, int & nkeys)
{
}

const char ** 
TreeDictionary::keys( int & nkeys)
{
  return NULL;
}




