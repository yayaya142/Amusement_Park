## Amusement Park Manager
![UML -Luna Park Manager](https://github.com/yayaya142/Amusement_Park/assets/82652251/982f6883-03db-4085-b12d-1cd7bbd58d4c)
**Introduction:**

The Amusement Park Management System is a comprehensive system that allows full control over all aspects of the park's activities, from managing employees and guests to creating tickets and ongoing operations.

**Main Functions:**
- Guests: Creating guest profiles, tracking visits, purchasing tickets.
- Employees: Managing employee system and departments.
- Shops: Managing shop system and controlling operating hours.
- Opening Hours: Setting opening and closing hours.
- Weather: Controlling weather conditions.
- Facilities: Creating facilities and defining categories (children, extreme, etc.), setting minimum and maximum height.
- Ticket System: Creating various types of tickets (military, child, adult, student), defining discounts, assigning a unique number to each ticket, and more.

**Structures:**
- **STRUCT**: The structure implementing the function.
- Each structure implements general functions:
  - initSTRUCT
  - initSTRUCTByUser
  - printSTRUCT
  - freeSTRUCT
  - compareSTRUCT
  - saveSTRUCTToBinFile
  - saveSTRUCTToTextFile
  - loadSTRUCTFromTextFile
  - loadSSTRUCTFromBinFile

## Key Entities:

### Luna Park
- **Attributes:**
  1. Name: `char*`
  2. Opening Time: `time`
  3. Closing Time: `time`
  4. Employees: `Person**` (polymorphism, inheritance)
  5. Number of Employees: `int`
  6. Guests: `Person**` (polymorphism, inheritance)
  7. Number of Guests: `int`
  8. Shops: `shop*`
  9. Number of Shops: `int`
  10. Facilities: `LIST`
  11. Weather: `weather`
  12. Ticket System: `ticketMaster`

- **Functions:**
  1. `printProfit`: Computes daily profit based on purchased tickets.
  2. `changeLunaPrakWeatherByUser`: Modifies weather description and temperature by user.
  3. `changeLunaPrakTimeByUser`: Modifies opening and closing time by user.
  4. `addSTRUCTToLunaPark`: Adds a desired structure to Luna Park.
  5. `addSTRUCTToLunaParkByUser`: Creates a desired structure based on user parameters and adds it to Luna Park.

### Weather
- **Attributes:**
  1. Weather Type: `enum`
  2. Temperature: `int`

### Time
- **Attributes:**
  1. Hour: `int`
  2. Minute: `int`

### Shop 
- **Attributes:**
  1. Name: `char*`
  2. Type: `enum`
  3. Opening Time: `time`
  4. Closing Time: `time`
  5. Dynamic Allocation Flag: `int`

### Person 
- **Attributes:**
  1. Name: `char*`
  2. Structure: `void*`
  3. Height: `double`
  4. Age: `int`

### Guest 
- **Attributes:**
  1. Person: `person*`
  2. Ticket: `ticket*`

### Date 
- **Attributes:**
  1. Day: `int`
  2. Month: `int`
  3. Year: `int`

### Ticket 
- **Attributes:**
  1. Ticket Number: `[12]char` (e.g., "T2754FC32SA2")
  2. Visitor Type: `enum`
  3. Price: `double`
  4. Utilized: `int`
  5. Visit Date: `date`

### Facility 
- **Attributes:**
  1. Name: `char*`
  2. Minimum Height: `int`
  3. Maximum Height: `int`
  4. Category: `enum`

### Worker 
- **Attributes:**
  1. Person: `person*`
  2. Department: `enum`
  3. Worker Number: `int`

### Ticket Master
- **Attributes:**
  1. Tickets: `ticket**`
  2. Number of Tickets: `int`
  3. Sorting Type: `enum`

- **Functions:**
  1. `addTicket`: Adds a ticket to the system.
  2. `calcDaily`: Computes daily profit based on tickets for a specific date.
  3. `calcAllIncome`: Computes total profit from all tickets.
  4. `sortTicketByID`: Sorts tickets by ID.
  5. `sortTicketByDate`: Sorts tickets by date.
  6. `sortTicketByGuestType`: Sorts tickets by guest type.
  7. `sortTicketByUser`: Sorts tickets based on user's choice.
  8. `searchTicket`: Searches for a ticket based on specified criteria.
  9. `buyTicket`: Allows a user to purchase a new ticket and returns a pointer to the ticket.
  10. `findTicketByUser`: Finds the desired ticket based on the chosen sorting type.
  11. `findTicketByID`: Retrieves the guest's ticket during system startup from files.
  12. `printTicketMaster`: General print function (void*).
 
## Macros:
# SUM
# IS_FILE_NULL
# CLOSE_FILE

## Helper Libraries for Project Usage:

### fileHelper Library:
- Manages all file operations for binary and text files.
  - `int writeStringToTextFile(FILE* file, const char* str);`
  - `int writeIntToTextFile(FILE* file, int num);`
  - `int writeDoubleToTextFile(FILE* file, const double num);`
  - `int writeStringTobinFile(FILE* file, const char* str);`
  - `int readIntFromTextFile(FILE* file, int* num);`
  - `int readDoubleFromTextFile(FILE* file, double* num);`
  - `char* readStringFromTextFile(FILE* file, char* buffer, int size);`
  - `char* readStringFromBinFile(FILE* file);`
  - `int writeGeneralToBinFile(FILE* file, const void* fileType, size_t sizeOfElement);`
  - `int readGeneralFromBinFile(FILE* file, void* readValue, size_t sizeOfElement);`

### General Library:
- Handles user input and relevant conversions, suitable for string and integer.
  - `char* getStrExactName(const char* msg);`
  - `char* myGets(char* buffer, int size);`
  - `char* getDynStr(char* str);`
  - `char** splitCharsToWords(char* str, int* pCount, int* pTotalLength);`
  - `void generalArrayFunction(void* arr, int size, size_t typeSize, void* (*func)(void* element));`
  - `int randomNum(int min, int max);`
  - `int validName(char* name);`

### listGen Library:
- Deals with linked lists, creating and operating on them in a general manner (void*).
  - `BOOL L_init(LIST* pList);`
  - `NODE* L_insert(NODE* pNode, DATA Value);`
  - `BOOL L_delete(NODE* pNode, void (*freeFunc)(void*));`
  - `const NODE* L_find(const NODE* pNode, DATA Value, int(*compare)(const void*, const void*));`
  - `BOOL L_free(LIST* pList, void (*freeFunc)(void*));`
  - `int L_print(const LIST* pList, void(*print)(const void*));`
  - `NODE* L_insertSorted(LIST* pList, DATA Value, int(*compare)(const void*, const void*));`
  - `int L_count(const LIST* pList);`

## User Operations in the System:

1. Upload the system from a text file.
2. Upload the system from a binary file.
3. Initialize Luna Park and reset it:
   * Luna Park Initialization: Initialize all data from a file based on user selection.

After the initial setup, present a menu allowing the following operations:

1) Print the entire system (Printing Luna Park) - Section 8.1.2
2) Display system components - Section 8.1.3
3) Add components to the system (Adding: Worker, Facility, Shop, Guest) - Section 8.1.4
4) Sorting (by tickets - detailed in structure) - Section 8.1.5
5) Search (by tickets - detailed in structure) - Section 8.1.6
6) Additional operations: Section 8.1.7
   * Change the opening and closing times of Luna Park
   * Change Luna Park's weather conditions
   * Calculate and print profit based on user selection (date/total)
   * Automatic execution of the program (the program will display a demo of the system)
7) Exit and print credits to the program writers.



