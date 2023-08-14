/*****
* Mor Hanania
* 315112870
* ass05
*****/
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define COMA ","
#define COMMA ','


//create the word struct that contain a pointer to an array of word with it's translation and pointer to the next word in the list
typedef struct Word {
	char** translations;
	struct Word* next;
} Word;
//create the Dictionary struct that contain a pointer to an array of the languages in the dictionary,the size of the array and pointer to a linked list of words
typedef struct {
	char** languages;
	int numOfLanguages;
	Word* wordList;
} Dictionary;

//declare on the functions
Dictionary* createNewD(Dictionary*, int*);
void Menu(Dictionary*, int*,int);
Dictionary* chooseD(Dictionary*, int*, int*);
void countLanguages(char*, int*);
char** getWordsArray(char*, int);
char* getStr();
void* addAWord(Dictionary*);
void deleteWord(Dictionary*);
void freeArray(int, char**);
void wordSearch(Dictionary*, Dictionary*, int*);
Dictionary* deleteDictionary(Dictionary*, int*, Dictionary*, int*,int);
void deleteAllD(Dictionary*, int*);
int sure();


void main() {
	//creats the pointer for thr dictionaries and pointer for the num of the dictionaries
	Dictionary* dictionaries = NULL;
	int numOfDictionaries = 0;
	int* numOfDPtr = &numOfDictionaries;
	//call to the menu function
	Menu(dictionaries, numOfDPtr,0);
}
/******
* Function Name: freeArray
* Input:ArraySize-size of the pointer array,** wordsArray-the array that the function will free
* Output:---
* Function Operation:the function free an array of strings
******/
void freeArray(int ArraySize, char** wordsArray) {

	for (int i = ArraySize - 1; i >= 0; i--)
	{
		free(wordsArray[i]);
		wordsArray[i] = NULL;
	}
	free(wordsArray);
}
/******
* Function Name: wordSearch
* Input:choosenDictionary
* Output:---
* Function Operation:the function search for word and display it's transilations.
******/
void wordSearch(Dictionary* choosenDictionary, Dictionary* dictionaries, int* numOfDPtr) {
	char* wordsStr = NULL;
	Word* temp = (*choosenDictionary).wordList;
	printf("Enter a word in %s:\n", (*choosenDictionary).languages[0]);
	//get requsted word
	wordsStr = getStr();
	if (!wordsStr)
	{
		printf("The search has failed successfully!");
		free(wordsStr);
		return;
	}
	//if there are no words in this Dictionar
	if (temp== NULL)
	{
		printf("There are no translations for \"%s\" in this dictionary.\n", wordsStr);
		Menu(dictionaries, numOfDPtr,0);
		free(wordsStr);
		return;
	}
	//lookimg for the choosen word
	while (strcmp((*temp).translations[0], wordsStr))
	{
		//next word
		temp = temp->next;
		if (temp==NULL)
		{
			//the word doesnt exsit
			printf("There are no translations for \"%s\" in this dictionary.\n", wordsStr);
			free(wordsStr);
			Menu(dictionaries, numOfDPtr,0);
			return;
		}
	}
	printf("The translations are:\n");
	int numOfWords = (*choosenDictionary).numOfLanguages;
	for (int j = 1; j < (*choosenDictionary).numOfLanguages; j++)
	{
		//display the translation of the word
		printf("%s: %s", choosenDictionary->languages[j],temp->translations[j]);
		if (j != numOfWords - 1)
		{
			printf(", ");
		}
		else
		{
			printf("\n");
		}
	}
	free(wordsStr);
	Menu(dictionaries, numOfDPtr,0);
	return;
}
/******
* Function Name: addAWord
* Input:choosenDictionary
* Output:---
* Function Operation:the function add a new word to the choosen dictionary
******/
void* addAWord(Dictionary* choosenDictionary) {
	char* wordsStr = NULL;
	char** wordsArray = NULL;
	int numOfWords = (*choosenDictionary).numOfLanguages;
	//display the request
	printf("Enter a word in ");
	for (int j = 0; j < numOfWords; j++)
	{
		//display the Languages of each dictionary
		printf("%s", (*choosenDictionary).languages[j]);
		if (j != numOfWords - 1)
		{
			printf(COMA);
		}
		else
		{
			printf(":\n");
		}
	}
	//get the string from the user
	wordsStr = getStr();
	//save the new translation into an Array of strings
	wordsArray = getWordsArray(wordsStr, (*choosenDictionary).numOfLanguages);
	//allocate a new place to the new word
	Word* newWordPointer = (Word*)malloc(1 * sizeof(Word));
	//if the allocaion faild
	if (newWordPointer == NULL) {
		printf("The addition of the word has failed!\n");
		//free all the word information
		free(wordsStr);
		freeArray(numOfWords, wordsArray);
		return NULL;
	}
	//insert the new word data
	newWordPointer->translations = wordsArray;
	newWordPointer->next = NULL;
	//if we add the first word
	if (!(*choosenDictionary).wordList)
	{
		(*choosenDictionary).wordList = newWordPointer;
	}
	//if we allready have some words
	else
	{
		//pointer to the first word
		Word* temp = (*choosenDictionary).wordList;
		//run until we get to the last word
		while (temp->next)
		{
			temp = temp->next;
		}
		//update newWordPointer to be the last word
		temp->next = newWordPointer;
	}
	printf("The word has been added successfully!\n");
	return NULL;
}
/******
* Function Name: getWordsArray
* Input:str,numOfWords
* Output:---
* Function Operation:the function sperate the str to strings by "," and put it into array of strings
******/
char** getWordsArray(char* str, int numOfWords) {
	int counter = 0;
	char** wordsArray = NULL;
	//insert to pice the firs word before ','
	char* piece = strtok(str, COMA);
	char* string = NULL;
	char* temp = string;
	//create a string that will contain pice value
	string = (char*)malloc(strlen(piece) + 1 * sizeof(char));
	if (string == NULL) {
		free(temp);
		return NULL;
	}
	strcpy(string, piece);
	//create an array of strings
	wordsArray = (char**)malloc(numOfWords * sizeof(char*));
	if (wordsArray == NULL) {
		free(string);
		free(wordsArray);
		return NULL;
	}
	//insert string to the array of strings
	wordsArray[counter] = string;
	string = NULL;
	//creating sparate pointer for eatch word
	while (piece != NULL) {
		piece = strtok(NULL, COMA);
		if (piece != NULL)
		{
			temp = string;
			string = (char*)malloc(strlen(piece) + 1 * sizeof(char));
			if (string == NULL) {
				free(temp);
				free(wordsArray);
				return NULL;
			}
			strcpy(string, piece);
			counter++;
			//insert eatch pointer to an array of pointers
			wordsArray[counter] = string;
			string = NULL;
		}


	}
	free(str);
	return wordsArray;
}
/******
* Function Name:deleteWord
* Input: choosenDictionary
* Output:---
* Function Operation:the function delete a choosen word from the choosen Dictionary
******/
void deleteWord(Dictionary* choosenDictionary) {
	char* str = NULL;
	char* useDecision = "0";
	int flagFirstWord = 1;
	//temp pionted to the first word or to null
	Word* temp = (*choosenDictionary).wordList;
	//if there are no words
	if (temp==NULL)
	{
		printf("there are no words in this Dictionary\n");
		return;
	}
	printf("Enter a word in %s:\n", (*choosenDictionary).languages[0]);
	//get the source word that we want to delete
	str = getStr();
	if (!str)
	{
		printf("The deletion of the word has failed!\n");
		return;
	}
	//save a prev word pointer
	Word* prevWordPoiter = (*choosenDictionary).wordList;
	//while the strings doesnt equel.
	if (sure())
	{
		while (strcmp(str, (*temp).translations[0]))
		{
			//if the word that the user want to delete isnt the first word
			flagFirstWord = 0;
			prevWordPoiter = temp;
			temp = temp->next;
			//the word doesnt exsit in the Dictionary
			if (temp == NULL)
			{
				printf("The deletion of the word has failed!\n");
				free(str);
				return;
			}
		}
	
		//save a next word pointer
		Word* nextWordPoiter = temp->next;
		//free all the data of the choosen word
		freeArray((*choosenDictionary).numOfLanguages, temp->translations);
		free(temp);
		//the user want to dalate the first word
		if (flagFirstWord)
		{
			(*choosenDictionary).wordList = nextWordPoiter;
		}
		else
		{
			//update the prev pointer to the next
			(*prevWordPoiter).next = nextWordPoiter;
		}
		free(str);
		printf("The word has been deleted successfully!\n");

	}
	else
	{
		free(str);
		printf("The deletion of the word has been canceled.\n");
	}
}
/******
* Function Name:sure
* Input:--
* Output:1/0
* Function Operation:the function display Q to the user and return his answer
******/
int sure() {
	char* y = "y";
	printf("Are you sure? (y/n)\n");
	char* useDecision;
	useDecision = getStr();
	if (strcmp(useDecision, y))
	{
		free(useDecision);
		return 0;
	}
	free(useDecision);
	return 1;
}
/******
* Function Name: chooseD
* Input:Dictionary* dictionaries-pointer to the dictionaries, int* numOfDPtr-pointer to thr num of dictionaries.
* Output:---
* Function Operation:the function display the dictionaries and get from the user the number of the choosen dictionary.
******/
Dictionary* chooseD(Dictionary* dictionaries, int* numOfDPtr, int* numOfdictionary) {
	
		int choosenDictionary = 0;
		Dictionary* chooseDPpointer = NULL;
		printf("Choose a dictionary:\n");
		//run on the number of the dictionaries
		for (int i = 0; i < *numOfDPtr; i++)
		{
			//print the number of the dictionaries as humen count
			printf("%d. ", i + 1);
			for (int j = 0; j < dictionaries[i].numOfLanguages; j++)
			{
				//display the Languages of each dictionary
				printf("%s", dictionaries[i].languages[j]);
				if (j != dictionaries[i].numOfLanguages - 1)
				{
					printf(COMA);
				}
				else
				{
					printf("\n");
				}
			}
		}
		scanf("%d", &choosenDictionary);
		//if the user choose Dictionary that doesnt exist
		while (choosenDictionary > *numOfDPtr)
		{
			printf("you choose dictionary that dosen't exist, please choose again\n");
			scanf("%d", &choosenDictionary);
		}
		*numOfdictionary = choosenDictionary - 1;
		return &dictionaries[choosenDictionary - 1];

	
}
/******
* Function Name: getStr
* Input:--
* Output:pointer to string "str"
* Function Operation:the function get unknown string fron the user and put it into an array
******/
char* getStr() {
	scanf(" ");
	//recive the string from the user
	char* str = NULL;
	char* tmp = str;
	char latter;
	int size = 0;
	do
	{
		//rise the counter of chars by one
		size++;
		tmp = str;
		//allocate new "box" to the char
		str = (char*)realloc(str, size * sizeof(char));
		if (str == NULL) {
			free(tmp);
			return NULL;
		}
		scanf("%c", &latter);
		//insert the char to the cell in the array
		str[size - 1] = latter;
		//if the last char is enter get out of the while
	} while (str[size - 1] != '\n');
	//instead of enter insert \0
	str[size - 1] = '\0';
	return str;
}
/******
* Function Name: countLanguages
* Input:str,numOfLanguages
* Output:--
* Function Operation:count the number of word that in the string each word sperate by","
******/
void countLanguages(char* str, int* numOfLanguages) {
	//start from one because the first Languages
	*numOfLanguages = 1;
	//the length of the string
	int strsize = strlen(str);
	//looking for comma
	for (int i = 0; i < strsize; i++)
	{
		if (str[i] == COMMA)
		{
			//rise the num of Languages by one
			*numOfLanguages = *numOfLanguages + 1;
		}
	}
}
/******
* Function Name:createNewD
* Input: Dictionary* dictionaries,int * numOfDPtr
* Output:---
* Function Operation:add Dictionary
******/
Dictionary* createNewD(Dictionary* dictionaries, int* numOfDPtr)
{
	//rise the number of dictionaries by one
	*numOfDPtr = *numOfDPtr + 1;
	char* str = NULL;
	int numLanguages = 0;
	int* numOfLanguages = &numLanguages;
	printf("Define a new dictionary:\n");
	str = getStr();
	countLanguages(str, numOfLanguages);
	char** LanguagesPtr = getWordsArray(str, numLanguages);
	Dictionary* tmp = dictionaries;
	//add 1 index for the new Dictionary
	dictionaries = realloc(dictionaries, (*numOfDPtr) * sizeof(Dictionary));
	if (dictionaries == NULL) {
		//not losing all the dictionaries
		dictionaries = tmp;
		printf("The creation of the dictionary has failed!\n");
		*numOfDPtr = *numOfDPtr - 1;
		//free the new Dictionary information
		freeArray(*numOfLanguages, LanguagesPtr);
		free(tmp);
		return dictionaries;
	}
	else
	{
		//insert the new Dictionary and update the data
		dictionaries[*numOfDPtr - 1].languages = LanguagesPtr;
		dictionaries[*numOfDPtr - 1].numOfLanguages = *numOfLanguages;
		dictionaries[*numOfDPtr - 1].wordList = NULL;
		printf("The dictionary has been created successfully!\n");
		return dictionaries;
	}
}
/******
* Function Name:deleteAllD
* Input: Dictionary* dictionaries,int * numOfDPtr
* Output:---
* Function Operation:deleting all the dictionaries
******/
void deleteAllD(Dictionary* dictionaries, int* numOfDPtr) {
	if (dictionaries!=NULL)
	{
		for (int i = *numOfDPtr - 1; i >= 0; i--)
		{
			dictionaries = deleteDictionary(&(dictionaries[i]), numOfDPtr, dictionaries, &i, 1);

		}

	}
	
}
/******
* Function Name:deleteDictionary
* Input: Dictionary* choosenDictionary,int * numOfDPtr,Dictionary* dictionaries,int* numOfdictionary
* Output:Dictionary* dictionaries the pointer to the dictionary array
* Function Operation:delete a choosen dictionary
******/
Dictionary* deleteDictionary(Dictionary* choosenDictionary, int* numOfDPtr, Dictionary* dictionaries, int* numOfdictionary,int flagTaskSix) {
	//if the user sure that he want ro delete the Dictionary or if we send to here from tast 6
	if (flagTaskSix || sure())
	{
		//free the languages of the Dictionary
		freeArray(choosenDictionary->numOfLanguages, choosenDictionary->languages);
		Word* temp = (*choosenDictionary).wordList;
		//if there are words in the Dictionary
		if (temp != NULL)
		{
			
			Word* prevWordPointer = NULL;
			//run until we get to the last word
			while (temp->next != NULL)
			{
				prevWordPointer = temp;
				temp = temp->next;
				freeArray((*choosenDictionary).numOfLanguages, prevWordPointer->translations);
				prevWordPointer = NULL;
			}
			//free the last word
		    freeArray((*choosenDictionary).numOfLanguages, temp->translations);
			free(temp);
		}
		//decrease the num of the dictionaries by 1
		*numOfDPtr = *numOfDPtr - 1;
		Dictionary* tempDictionaries = dictionaries;
		//forward all the dictionaries
		for (int i = *numOfdictionary; i < *numOfDPtr; i++)
		{
			dictionaries[i] = dictionaries[i + 1];
		}
		//decrease the size of the  dictionaries array
		dictionaries = realloc(dictionaries, *numOfDPtr * sizeof(Dictionary));
		if (dictionaries == NULL && *numOfDPtr != 0)
		{
			printf("The deletion of the dictionary has failed!\n");
			*numOfDPtr = *numOfDPtr + 1;
			return tempDictionaries;
		}
	}
	else
	{
		printf("The deletion of the dictionary has been canceled.\n");
		return dictionaries;
	}
	if (!flagTaskSix)
	{
		printf("The dictionary has been deleted successfully!\n");

	}
	return dictionaries;
}
/******
* Function Name:Menu
* Input:---
* Output:---
* Function Operation: reprisenting the menue.
******/
void Menu(Dictionary* dictionaries, int* numOfDPtr,int flagNotAavilable) {
	if (!flagNotAavilable) {
		printf("Welcome to the dictionaries manager!\nChoose an option:\n1. Create a new dictionary.\n2. Add a word to a dictionary.\n3. Delete a word from a dictionary.\n4. Find a word in a dictionary.\n5. Delete a dictionary.\n6. Exit.\n");
	}
	int userNum,NotAavilable=0;
	int NumChoosenD = 0;
	int* numOfdictionary = &NumChoosenD;
	Dictionary* choosenDictionary;
	scanf("%d", &userNum);
	switch (userNum)
	{
	case 1: {
		dictionaries = createNewD(dictionaries, numOfDPtr);
		Menu(dictionaries, numOfDPtr,0);
		break;
	}
	case 2: {
		//if the choose an option that requires an Dictionary that doesnt exist
		if (*numOfDPtr == 0)
		{
			printf("This option is not available right now, try again:\n");
			NotAavilable = 1;
		}
		else
		{
			choosenDictionary = chooseD(dictionaries, numOfDPtr, numOfdictionary);
			addAWord(choosenDictionary);
		}
		Menu(dictionaries, numOfDPtr, NotAavilable);
		break;
	}
	case 3: {
		//if the choose an option that requires an Dictionary that doesnt exist
		if (*numOfDPtr == 0)
		{
			printf("This option is not available right now, try again:\n");
			NotAavilable = 1;
		}
		else
		{
			choosenDictionary = chooseD(dictionaries, numOfDPtr, numOfdictionary);
			deleteWord(choosenDictionary);
			
			
		}
		Menu(dictionaries, numOfDPtr, NotAavilable);
		break;
	}
	case 4: {
		//if the choose an option that requires an Dictionary that doesnt exist
		if (*numOfDPtr == 0)
		{
			printf("This option is not available right now, try again:\n");
			NotAavilable = 1;
			Menu(dictionaries, numOfDPtr, NotAavilable);
		}
		else
		{
			choosenDictionary = chooseD(dictionaries, numOfDPtr, numOfdictionary);
			wordSearch(choosenDictionary, dictionaries, numOfDPtr);
			
		}
		break;
	}
	case 5: {
		//if the choose an option that requires an Dictionary that doesnt exist
		if (*numOfDPtr == 0)
		{
			printf("This option is not available right now, try again:");
			NotAavilable = 1;
		}
		else
		{
			choosenDictionary = chooseD(dictionaries, numOfDPtr, numOfdictionary);
			dictionaries = deleteDictionary(choosenDictionary, numOfDPtr, dictionaries, numOfdictionary, 0);
		}
		Menu(dictionaries, numOfDPtr, NotAavilable);
		break;
	}
	case 6: {

		deleteAllD(dictionaries, numOfDPtr);
		printf("Bye!");
		return;
	}
	default: {
		printf("Wrong option, try again:\n");
		Menu(dictionaries, numOfDPtr, NotAavilable);
	}

	}
}
