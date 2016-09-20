
// Data structs for a list of ints

struct ListNode {
	char *name;
	char*password;
	struct ListNode * next;
};

typedef struct ListNode ListNode;

struct LinkedList {
	ListNode * head;
};

typedef struct LinkedList LinkedList;

struct MessageNode {
	char * room;
	char * user;
	char * message;
	struct MessageNode *next;
};

typedef struct MessageNode MessageNode;

struct MessageList{
	MessageNode *head;
};

typedef struct MessageList MessageList;

struct RoomNode{
	char * roomlist;
	struct RoomNode * next;
};

typedef struct RoomNode RoomNode;

struct RoomList{
	RoomNode *head;
}; 

typedef struct RoomList RoomList;

void llist_init(LinkedList * list);
void llist_print(LinkedList * list);
void llist_add(LinkedList * list, const char* name,const char*password);
int llist_exists(LinkedList * list, const char* name,const char*password);
int llist_remove(LinkedList * list, const char* name);
int llist_remove_room(LinkedList * list,const char * name, const char * password);
int llist_number_elements(LinkedList * list);
int llist_save(LinkedList * list, char * file_name);
int llist_read(LinkedList * list, char * file_name);
void llist_sort_descend(LinkedList * list);
void llist_sort_ascend(LinkedList * list);
void llist_clear(LinkedList *list);
void llist_init_message(MessageList * list);
void llist_add_message(MessageList * list, const char* roomP, const char * userP, const char * messageP);

