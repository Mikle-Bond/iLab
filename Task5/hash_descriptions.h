//=========================================================
// Hash - it's an array of lists. So there are two kinds of
// data are used in the project. Here you can find short
// descriptions of functions to booth of them.

//=========================================================
//+++++++++++++++++++++++[ LIST ]++++++++++++++++++++++++++
//=========================================================

//=========================================================
// TYPEDEFS
/*
list_elem           -  one data element (int by default)
list_counter        -  counter type (int by default)
list_chain          -  one node of list
list_ptr            -  pointer to node
list_head           -  head with (head) and (tail) pointers
list_t              -  pointer to list by its head
*/

//===========================================================================================
// DESCRIBING PICTURE
/*
                                               .
        <<[ CTOR/DTOR SECTION ]>>              .         <<[ EVERYTHING ELSE ]>>
                                               .
.............................................................................................
                                               .
            |-----------|                      .
list_t ---> |list_head: |                      .
            |-----------|      |------------|  .   |------------|      |------------|
            |           |      | head == 0  |  .   |list_chain  |      |list_chain  | <-\
            |   head   ------> |------------|  .   |------------|      |------------|    \
            |           |      |    next    | ---> |    next    | ---> |    next   ----\  \
            |           | NULL <--- prev    | <--- |    prev    | <--- |    prev    |   \ |
            |           |      |------------|  .   |------------|      |------------|   | |
            |           |                      .                                        | |
            |-----------|  ===========================================================  | |
            |           |                      .                                        | |
            |           |      |------------|  .   |------------|      |------------|   | |
            |           |      | tail == 0  |  .   |list_chain  |      |list_chain  |   / |
            |   tail   ------> |------------|  .   |------------|      |------------|<-/  /
            |           | NULL <--- next    | <--- |    next    | <--- |    next    |    /
            |           |      |    prev    | ---> |    prev    | ---> |    prev   -----/
            |-----------|      |------------|  .   |------------|      |------------|
                                               .
                                               .

*/
//===========================================================================================

//=========================================================
int ListOk(const list_t lst);
// Searching for mistakes in the list, assertion if found.
// !!! not completed.

//=========================================================
list_t list_ctor();
// Creates header structure and two first elements.
// Then links them together.
// Returns pointer to header;

//=========================================================
int list_insert_after(list_ptr chain, list_elem data);
int list_insert_before(list_ptr chain, list_elem data);
// Creates new node and place it after/before the gotten
// one. Could be used with list_search().

//=========================================================
int list_add_first(list_t lst, list_elem data);
int list_add_last(list_t lst, list_elem data);
// Placing new element to the list. "First" and "last"
// means "after/before head/tail element" as could be seen
// on the picture above.

//=========================================================
list_elem list_remove(list_ptr chain);
// Clears one element by the pointer. Useful with function
// list_search().

//=========================================================
list_elem list_get_first(list_t lst);
list_elem list_get_last(list_t lst);
// Clears begin/end of the list. Head and tail are skipped.

//=========================================================
list_ptr list_search(list_t lst, list_elem data);
// Returns pointer to the node with heeded element in the
// list. If element was not found, returns (NULL).

//=========================================================
int list_print(list_t lst);
// Prints all elements of the list in one row.

//=========================================================
int list_dtor(list_t *lst);
// Destroys all elements in the list.

//=========================================================
//+++++++++++++++++++++++[ HASH ]++++++++++++++++++++++++++
//=========================================================

//=========================================================
// TYPEDEFS
/*
hasher_func         -  hasher function type
hash_t              -  pointer to structure with hash table
                       and hasher function
*/

//=========================================================
hash_t hash_ctor(hasher_func hasher, size_t size);
// Gets hasher function and variety of its keys as a
// parameters. That means, that hasher() will return
// integers form 0 to (size)-1.
// Than creates array of (size) ready-to-work lists.
// Links array and hasher() in one structure and returns
// pointer to it.

//=========================================================
int hash_push(hash_t h, data_t t);
// Finds place to (t) by its hash key and place it to the
// needed list.

//=========================================================
list_ptr hash_find(hash_t h, data_t t);
// Finds (t) in the hash table. Returns pointer to node
// with (t). If it was not found returns (NULL).

//=========================================================
int hash_print(hash_t h);
// Prints all lists in hash table.

//=========================================================
int hash_get(hash_t h, data_t t, data_t *res);
// Replace the (res) on (t) if it exists in hash table, and
// delete (t) from it. Returns 1 if success and 0 if not.

//=========================================================
int hash_dtor(hash_t *h);
// Destroys whole hash table. Changes (h) to (NULL).
