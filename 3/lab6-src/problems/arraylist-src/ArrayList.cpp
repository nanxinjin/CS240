#include "ArrayList.h"
# include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**
 * @brief      Default Constructor.
 *
 * @tparam     T     Typename
 */
template<class T>
ArrayList<T>::ArrayList() :
	m_size(0),
	m_capacity(SIZE_INCREMENT)
{
	pElements = new T[SIZE_INCREMENT];
}

/**
 * @brief      Clear the ArrayList
 *
 * @tparam     T     Typename
 */
template<class T>
void ArrayList<T>::clear()
{
	/** @todo Clear the list and shrink the array. **/
	int i = 0;
//	pElements = new T[SIZE_INCREMENT];
	//for(i; i < m_size;i++){
	//	pElements[i] = 0;
	//	m_size --;
	//}
	if (!std::is_pointer<T>::value){
		delete[] pElements;
	}else{
		delete pElements;
	}

	pElements = new T[m_capacity = 16];
	m_size = 0;
}

/**
 * @brief      Adds a thing to the ArrayList
 *
 * @param[in]  toPush  The to be added.
 *
 * @tparam     T       Typename
 */
template<class T>
void ArrayList<T>::add(const T& toPush)
{
	/**
	 * @todo Add toPush to the end of the array,
	 * allocating resources if adding another
	 * element exceeds current capacity.
	 * 
	 * Please use "new"
	 */
//	pElements = new T[SIZE_INCREMENT];
	if(m_size >= m_capacity){
		//realloc memory
		m_capacity *= SIZE_INCREMENT;
		T * temp = new T[m_capacity];
		std::copy(pElements, pElements + m_size, temp);
		if (!std::is_pointer<T>::value){
			delete[] pElements;
		}else{
			delete pElements;
		}

		pElements = temp;
	}
	pElements[m_size++] = toPush;
	
}

//ADD SOMETHING
template<class T>
void ArrayList<T>::addTwo(const T& toPush, int index)
{
	T * temp = new T[m_capacity];
	if(m_size >= m_capacity){
		m_capacity *= SIZE_INCREMENT;
	//	T * temp = new T[m_capacity];
		std::copy(pElements, pElements + m_size, temp);
		if (!std::is_pointer<T>::value){
			delete[] pElements;
		}else{
			delete pElements;
		}
		
		//pElements = new T();
		pElements = temp;
	
	}
	std::copy(pElements + index, pElements + m_size, pElements + index + 1);
	pElements[index] = toPush;
	m_size++;




}


//

/**
 * @brief      Adds a thing in a specific index.
 *
 * @param[in]  toPush  Thing to add
 * @param[in]  index   Where it is to be added.
 *
 * @tparam     T       Type of thing
 */
template<class T>
void ArrayList<T>::add(const T& toPush, int index)
{
	
		//realloc memory
//	std::cout<< "msize: " << m_size <<std::endl;
//	std::cout << "mcapacity: " << m_capacity << std::endl; 
	T * temp = new T[m_capacity];
	if(m_size >= m_capacity){
		m_capacity *= SIZE_INCREMENT;
	//	T * temp = new T[m_capacity];
		std::copy(pElements, pElements + m_size, temp);
		if (!std::is_pointer<T>::value){
			delete[] pElements;
		}else{
			delete pElements;
		}

		pElements = temp;
	
	}
//	std::copy(pElements + index, pElements + m_size, pElements + index + 1);
//	pElements[index] = toPush;
	int j = 0;
	for(int i = 0;i<m_size;i++){
		if(i == index){
			temp[j] = toPush;
			j++;	
		}
		temp[j] = pElements[i];
		j++;
	}
	pElements = temp;
//	pElements[index] = toPush;
//	for(int j=m_size;j>index;j--){
//	      pElements[j+1] = pElements[j];
//	
//	}
//	for (int i = 0; i < m_size; i++) std::cout << temp[i] << std::endl;
	
//	pElements = temp;
//	pElements[index] = toPush;
	m_size++;
	/**
	 * @todo Add toPush to the array in the specified index.
	 * Again, reallocate if necessary.
	 */
}

/**
 * @brief      Pushes to the back of the list.
 *
 * @param[in]  toPush  Thing to push back.
 *
 * @tparam     T       Typename
 */
template<class T>
void ArrayList<T>::push_back(const T& toPush)
{
	/**
	 * @todo Add toPush to the back of the array.
	 */
	add(toPush);
}

/**
 * @brief      Push a thing to the front of the list.
 *
 * @param[in]  toPush  Thing to be pushed.
 *
 * @tparam     T       Typename
 */
template<class T>
void ArrayList<T>::push_front(const T& toPush)
{
	/**
	 * @todo Add toPUsh to the front of the array.
	 */

	//addTwo(toPush, 0);
	
}

/**
 * @brief      Remove the item at a specific index.
 *
 * @param[in]  index  Index of the thing to be removed.
 *
 * @tparam     T      Typename
 *
 * @return     Shallow copy of the item we removed.
 */
template<class T>
const T ArrayList<T>::remove(int index)
{
	const T myT = T();
	/**
	 * @todo Remove the item in the index-th
	 * index and return it.
	 */
	if(index > m_size){
		return myT;
	}
	for(int i = index;i<m_size;i++){
		pElements[i] = pElements[i+1];
	}
	m_size --;
	return myT;
}

/**
 * @brief      Removes a particular item from the list.
 *
 * @param[in]  toRemove  Thing to remove.
 * @param      ok        True upon successful removal.
 *
 * @tparam     T         Typename
 */
template<class T>
void ArrayList<T>::remove(const T & toRemove, bool * ok) {
	/**
	 * @todo Find and remove toRemove within the array.
	 *  Upon successful removal, set ok to true.
	 */
	*ok = false;
	for(int i = 0;i<m_size;i++){
		if (*ok == false)
		{
			if (pElements[i] == toRemove) {
				*ok = true;
			}
		}
		if (*ok == true)
		{
			pElements[i] = pElements[i+1];
		}
		/*
		if(pElements[i] == toRemove){
			std::copy(pElements + i, pElements + m_size, pElements + i - 1);	
			*ok = true;
		} */
	}
	if(*ok == true){
		m_size--;
	}
	//*ok = false;


}

/**
 * @brief      Check if an item is in the ArrayList.
 *
 * @param[in]  object The thing we want to know about.
 *
 * @tparam     T       Typename
 *
 * @return     Returns true if it's there.
 */
template<class T>
bool ArrayList<T>::contains(const T& object)
{
	/**
	 * @todo Return true if object is in the list.
	 */
	int i = 0;
	for(i;i<m_size;i++){
		if(pElements[i] == object){
			return true;
		}
	}
	return false;
}

/**
 * @brief      Returns the first index of T.
 *
 * @param[in]  object  Thing.
 *
 * @tparam     T       Typename
 *
 * @return     The first index of thing.
 */
template<class T>
int ArrayList<T>::indexOf(const T& object)
{
	/**
	 * @todo Find the index of object in the array,
	 * or return -1 if not found.
	 */
	int i = 0;
	for(i;i<m_size;i++){
		if(pElements[i] == object){
			return i;
		}
	}

	return -1;
}

/**
 * @brief      Return the ith occurance of T.
 *
 * @param[in]  object     Thing.
 * @param[in]  occurance  Occurance of thing to find.
 *
 * @tparam     T          Type of thing.
 *
 * @return     Location of thing.
 */
template<class T>
int ArrayList<T>::indexOf(const T& object, int occurrence)
{
	/**
	 * @todo Return the index of the occurrence-th
	 * occurrence of object.
	 */
	int i = 0;
	int count = 0;
	for(i;i<m_size;i++){
		if(pElements[i] == object){
			count++ ;
			if(occurrence == count){
				return i;
			}
		}
	}
//	return occurrence;
}

/**
 * @brief      Check for the last index of an object.
 *
 * @param[in]  object  Thing to check
 *
 * @tparam     T       Typename
 *
 * @return     Integer location of the last location, or -1.
 */
template<class T>
int ArrayList<T>::lastIndexOf(const T& object)
{
	/**
	 * @todo Return the last index of object in the array.
	 */
	int i = 0;
	int save = -1;
	for(i;i<m_size;i++){
		if(pElements[i] == object){
			save = i;
		}
	}

	return save;
}

/**
 * @brief      Sorts the given list in ascending order.
 * 
 * This sorts the list in ascending order. It is assumed
 * that the < operator has been overloaded.
 *
 * @tparam     T   type.  
 */
template<class T>
void ArrayList<T>::sort()
{
	/**
	 * @todo Sort the array in ascending order.
	 */
	int i = 0;
	int j = 0;
	double temp;
	for(i;i<m_size;i++){
		j = i;
		for(j;j<m_size;j++){
			if(pElements[j] < pElements[i]){
				temp = pElements[i];
				pElements[i] = pElements[j];
				pElements[j] = temp;
			}
		}
	}
}
