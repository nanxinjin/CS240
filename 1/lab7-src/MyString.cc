
// String Implementation
// IMPORTANT: Do not use any of the functions in the string C runtime library
// Example. Do not use strcpy, strcmp, etc. Implement your own

// IMPORTANT: See the MyString.h file for a description of
// what each method needs to do.

#include <stdio.h>
#include "MyString.h"

// My own implementation of strlen
int
MyString::slength(const char *s) const
{
 	
 // Add implementation here
  int i = 0;
  while(*(s + i) != '\0'){
  	i++;
  }
  return i;
}

// Initialize _s. Allocate memory for _s and copy s into _s
void
MyString::initialize(const char * s)
{
  // Add implementation here
  _s = new char[slength(s) + 1];
  // Allocate memory for _s.

  // Copy s into _s
  char *dest = _s;
  while(*dest++=*s++);
}

// Create a MyString from a C string
MyString::MyString(const char * s)
{
  initialize(s);
}

// Create a MyString from a copy of another string
MyString::MyString(const MyString &s)
{
  initialize(s._s);
}

// Create a MyString with an empty string
MyString::MyString()
{
  _s = new char[1];
  *_s = 0;
}

// Assignment operator. Without this operator the assignment is
// just a shallow copy that will copy the pointer _s. If the original _s
// goes away then the assigned _s will be a dangling reference.
MyString &
MyString::operator = (const MyString & other) {
  if (this != &other) // protect against invalid self-assignment
  {
    // deallocate old memory
    delete [] _s;

    // Initialize _s with the "other" object.
    initialize(other._s);

    // by convention, always return *this
    return *this;
  }
}

// Obtain a substring of at most n chars starting at location i
// if i is larger than the length of the string return an empty string.
MyString
MyString::substring(int i, int n)
{
  // Add implementation here
	if(i>=slength(_s))
		return MyString();
  // Make sure that i is not beyond the end of string

  // Allocate memory for substring
	char * a = new char[n + 1];
	int c = 0;
	while(n&&_s[i]){
		a[c]=_s[i];
		c++;
		i++;
		n--;
	}
	a[c] = '\0';
  // Copy characters of substring
  MyString sub(a);
	delete [] a;
  // Return substring
  return sub;
}

// Remove at most n chars starting at location i
void
MyString::remove(int i, int n)
{
  // Add implementation here

  // If i is beyond the end of string return
	if(i> slength(_s))
		return;
  // If i+n is beyond the end trunc string
	int c;
	if(i + n >= slength(_s)){
		_s[i]='\0';
	}else{
		for(c = i; c + n <=slength(_s);c++){
			_s[c] = _s[c+n];
		}
	}
  // Remove characters
}

// Return true if strings "this" and s are equal
bool
MyString::operator == (const MyString & s)
{
  // Add implementation here
  int c1 = slength(this->_s);
  int c2 = slength(s._s);
  if(c1 != c2){
		return false;
  }
  else{
  	int j = 0;
	for(; j < c1;j++){
		if(this->_s[j] == s._s[j]){
			continue;
		}
		else{
			return false;
		}
	}
  }
  return true;
}


// Return true if strings "this" and s are not equal
bool
MyString::operator != (const MyString &s)
{
  // Add implementation here
  int c1 = slength(this->_s);
  int c2 = slength(s._s);
  if(c1 != c2){
		return true;
  }
  else{
  	int j = 0;
	for(; j < c1;j++){
		if(this->_s[j] == s._s[j]){
			continue;
		}
		else{
			return true;
		}
	}
  }
  return false;
}

// Return true if string "this" and s is less or equal
bool
MyString::operator <= (const MyString &s)
{
  // Add implementation here
  char *a = _s;
  char *b = s._s;
  while(*a != '\0'){
  	if(*a < *b){
		return true;
	}
	if(*a > *b){
		return false;
	}
	a++;
	b++;
  }
  return true;
}

// Return true if string "this" is greater than s
bool
MyString::operator > (const MyString &s)
{
  // Add implementation here
  int c1 = slength(this->_s);
  int c2 = slength(s._s);
  if(c1 != c2 && c1 > c2){
		return true;
  }
  else{
  	int j = 0;
	for(; j < c1;j++){
		if(this->_s[j] == s._s[j]){
			continue;
		}
		else{
			return true;
		}
	}
  }
  return false;
}

// Return character at position i.  Return '\0' if out of bounds.
char
MyString::operator [] (int i)
{
				
				
// Add implementation here
  if(i < slength(_s)){
  	return *(_s + i);
  }else{
  	return'\0';
  }
}

// Return C representation of string
const char *
MyString::cStr()
{
  // Add implementation here
  return _s;
}

// Get string length of this string.
int
MyString::length() const
{
  // Add implementation here
  return slength(_s);
}

// Destructor. Deallocate the space used by _s
MyString::~MyString()
{
  // Add implementation here
  delete [] _s;
}

// Concatanate two strings (non member method)
MyString operator + (const MyString &s1, const MyString &s2)
{
  // Add implementation here
	MyString s;
  // Allocate memory for the concatenated string
	s._s = new char[s1.length()+s2.length()+1];
  // Add s1
  	int i = 0;
	char *a = s._s;
  // Add s2
  	char *b = s1._s;
	for(i = 0;i<s1.length();i++){
		*a = *b;
		a++;
		b++;
	}
	char *c = s2._s;
	for(i = 0;i<s2.length();i++){
		*a = *c;
		a++;
		c++;
	}
	*a = '\0';


  
  return s;
}

