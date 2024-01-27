/*
10. Napisati program koji cita datoteku drzave.txt u kojoj su zapisani nazivi pojedinih drzava. Uz
ime drzave u datoteci se nalazi i ime dodatne datoteke u kojoj se nalaze gradovi pojedine
drzave. Svaka datoteka koja predstavlja drzavu sadrzi popis gradova u formatu naziv_grada,
broj_stanovnika.
a) Potrebno je formirati sortiranu vezanu listu drzava po nazivu. Svaki cvor vezane liste
sadrzi stablo gradova sortirano po broju stanovnika, zatim po nazivu grada.
b) Potrebno je formirati stablo drzava sortirano po nazivu. Svaki cvor stabla sadrzi vezanu
listu gradova sortiranu po broju stanovnika, zatim po nazivu grada.
Nakon formiranja podataka potrebno je ispisati drzave i gradove te omoguciti korisniku putem
tastature pretragu gradova odredjene drzave koji imaju broj stanovnika veci od unosa na
tastaturi.

11. Prepraviti zadatak 10 na nacin da se formira hash tablica drzava. Tablica ima 11 mjesta, a
funkcija za preslikavanje kljuc racuna da se zbraja ASCII vrijednost prvih pet slova države zatim
raèuna ostatak cjelobrojnog dijeljenja te vrijednosti s velicinom tablice. Drzave s istim kljucem se
pohranjuju u vezanu listu sortiranu po nazivu drzave. Svaki cvor vezane liste sadrzi stablo
gradova sortirano po broju stanovnika, zatim po nazivu grada.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH (50)
#define MAX_LINE (1024)
#define FILE_NOT_OPEN (-1)
#define FAILED_MEMORY_ALLOCATION (NULL)
#define HASH_TABLE_SIZE 11

struct _town;
typedef struct _town* TownPosition;
typedef struct _town
{
	char name[MAX_LENGTH];
	int population;
	TownPosition next;
	TownPosition left;
	TownPosition right;
} Town;

struct _country;
typedef struct _country* CountryPosition;
typedef struct _country
{
	char name[MAX_LENGTH];
	CountryPosition next;
	CountryPosition left;
	CountryPosition right;
	TownPosition townRootTree;
	Town townListHead;
} Country;

struct _hash_table {
	CountryPosition buckets[HASH_TABLE_SIZE];
};
typedef struct _hash_table HashTable;

CountryPosition readAndFillCountries(CountryPosition countryHeadList, CountryPosition countryRootTree, HashTable* hashTable);
int createNewCountryFromBuffer(char* countryName, char* countryFile, CountryPosition* countries);
CountryPosition createNewCountry(char* countryName);
TownPosition createNewTown(char* townName, int townPopulation);
int insertSortedNewTownList(TownPosition townHeadList, TownPosition newTown);
int insertTownAfter(TownPosition townCurrent, TownPosition newTown);
TownPosition insertNewTownTree(TownPosition townRootTree, TownPosition newTown);
int insertSortedNewCountryList(CountryPosition townHeadList, CountryPosition newCountry);
int insertCountryAfter(CountryPosition countryCurrent, CountryPosition newCountry);
CountryPosition insertNewCountryTree(CountryPosition countryRootTree, CountryPosition newCountry);
int printCountryList(CountryPosition countryHeadList);
int printCountryTree(CountryPosition countryRootTree);
int printTownList(TownPosition townHeadList);
int printTownTree(TownPosition townRootTree);
int findCountries(CountryPosition countryHeadList, CountryPosition countryRootTree, CountryPosition* countries);
CountryPosition searchCountryTree(CountryPosition countryRootTree, char* countryName);

// Function to create and initialize a new hash table
HashTable* createHashTable() {
	HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
	if (!hashTable) {
		printf("Can't allocate memory for hash table!\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		hashTable->buckets[i] = NULL;
	}

	return hashTable;
}

// Function to calculate the hash value for a given country name
unsigned int calculateHash(char* countryName) {
	unsigned int hashValue = 0;
	int i = 0;
	while (i < 5 && countryName[i] != '\0') {
		hashValue += (unsigned int)countryName[i];
		i++;
	}
	return hashValue % HASH_TABLE_SIZE;
}

// Function to insert a country into the hash table
void insertCountryIntoHashTable(HashTable* hashTable, CountryPosition newCountry) {
	unsigned int index = calculateHash(newCountry->name);

	if (hashTable->buckets[index] == NULL) {
		hashTable->buckets[index] = newCountry;
		newCountry->next = NULL;
	}
	else {
		// Handle collision by adding the new country to the linked list at this index
		newCountry->next = hashTable->buckets[index];
		hashTable->buckets[index] = newCountry;
	}
}

// Function to search for a country in the hash table
CountryPosition searchCountryInHashTable(HashTable* hashTable, char* countryName) {
	unsigned int index = calculateHash(countryName);
	CountryPosition currentCountry = hashTable->buckets[index];

	while (currentCountry != NULL && strcmp(currentCountry->name, countryName) != 0) {
		currentCountry = currentCountry->next;
	}

	return currentCountry;
}

int printAllCountriesFromHash(HashTable* hashTable) {
	for (int index = 0; index < HASH_TABLE_SIZE; index++) {
		CountryPosition currentCountry = NULL;
		currentCountry = hashTable->buckets[index];

		while (currentCountry != NULL) {
			printf("\n%s", currentCountry->name);
			printTownTree(currentCountry->townRootTree);
			currentCountry = currentCountry->next;
		}
	}
}

int main() {
	Country countryHeadList = {
		.name = { 0 },
		.next = NULL,
		.left = NULL,
		.right = NULL,
		.townRootTree = NULL,
		.townListHead = {
			.name = { 0 },
			.population = 0,
			.next = NULL,
			.left = NULL,
			.right = NULL,
		}
	};

	CountryPosition countryRootTree = NULL;

	CountryPosition countryCurrentList = NULL;
	CountryPosition countryCurrentTree = NULL;
	CountryPosition countries[] = { NULL, NULL };

	HashTable* hashTable = createHashTable();

	countryRootTree = readAndFillCountries(&countryHeadList, countryRootTree, hashTable);
	printf("LIST");
	printCountryList(&countryHeadList);
	printf("\n\n\n\n");
	printf("TREE");
	printCountryTree(countryRootTree);
	printf("\n\n\n\n");
	printf("HASH");
	printAllCountriesFromHash(hashTable);

	// Example of searching for a country in the hash table
	char searchCountryName[MAX_LENGTH] = { 0 };
	printf("\nEnter country name to search in the hash table: ");
	scanf(" %s", searchCountryName);

	CountryPosition foundCountry = searchCountryInHashTable(hashTable, searchCountryName);

	if (foundCountry != NULL) {
		printf("\nCountry found in the hash table: %s", foundCountry->name);
	}
	else {
		printf("\nCountry not found in the hash table.");
	}

	// Free allocated memory

	return EXIT_SUCCESS;
}

CountryPosition readAndFillCountries(CountryPosition countryHeadList, CountryPosition countryRootTree, HashTable* hashTable) {
	FILE* filePointer = NULL;
	char countryName[MAX_LINE] = { 0 };
	char countryFile[MAX_LINE] = { 0 };
	char nullString[MAX_LINE] = { 0 };
	CountryPosition newCountryList = NULL;
	CountryPosition newCountryTree = NULL;
	CountryPosition newCountryHash = NULL;
	CountryPosition countries[] = { NULL, NULL, NULL };

	filePointer = fopen("drzave.txt", "r");
	if (!filePointer) {
		printf("\033[31mCan't open file!\033[0m\n");
		return FILE_NOT_OPEN;
	}

	while (!feof(filePointer)) {
		fscanf(filePointer, " %s %s", countryName, countryFile);
		createNewCountryFromBuffer(countryName, countryFile, countries);
		newCountryList = countries[0];
		newCountryTree = countries[1];
		newCountryHash = countries[2];
		insertSortedNewCountryList(countryHeadList, newCountryList);
		countryRootTree = insertNewCountryTree(countryRootTree, newCountryTree);
		insertCountryIntoHashTable(hashTable, newCountryHash);
		strcpy(countryName, nullString);// provjeri treba li
		strcpy(countryFile, nullString);// provjeri treba li
	}

	fclose(filePointer);

	return countryRootTree;
}

int createNewCountryFromBuffer(char* countryName, char* countryFile, CountryPosition* countries) {
	char countryLocation[MAX_LENGTH] = { 0 };
	FILE* countryFilePointer = NULL;
	CountryPosition newCountryList = NULL;
	CountryPosition newCountryTree = NULL;
	CountryPosition newCountryHash = NULL;
	TownPosition newTownList = NULL;
	TownPosition newTownTree = NULL;
	TownPosition newTownHash = NULL;
	char townName[MAX_LENGTH] = { 0 };
	int townPopulation = 0;

	strcpy(countryLocation, countryFile);

	countryFilePointer = fopen(countryLocation, "r");
	if (!countryFilePointer) {
		printf("Can't open file!\n");
		return FILE_NOT_OPEN;
	}

	newCountryList = createNewCountry(countryName);
	newCountryTree = createNewCountry(countryName);
	newCountryHash = createNewCountry(countryName);

	while (!feof(countryFilePointer)) {
		fscanf(countryFilePointer, " %s %d", townName, &townPopulation);
		newTownList = createNewTown(townName, townPopulation);
		newTownTree = createNewTown(townName, townPopulation);
		newTownHash = createNewTown(townName, townPopulation);
		insertSortedNewTownList(&newCountryTree->townListHead, newTownList);
		newCountryList->townRootTree = insertNewTownTree(newCountryList->townRootTree, newTownTree);
		newCountryHash->townRootTree = insertNewTownTree(newCountryHash->townRootTree, newTownHash);
		newTownList = NULL;// provjeri treba li
	}
	countries[0] = newCountryList;
	countries[1] = newCountryTree;
	countries[2] = newCountryHash;

	fclose(countryFilePointer);

	return EXIT_SUCCESS;
}

CountryPosition createNewCountry(char* countryName) {
	CountryPosition country = NULL;
	country = (CountryPosition)malloc(sizeof(Country));
	if (!country) {
		printf("Can't allocate memory!\n");
		return FAILED_MEMORY_ALLOCATION;
	}


	strcpy(country->name, countryName);
	country->next = NULL;
	country->left = NULL;
	country->right = NULL;
	country->townRootTree = NULL;

	country->townListHead.population = 0;
	country->townListHead.next = NULL;
	country->townListHead.left = NULL;
	country->townListHead.right = NULL;

	return country;
}

TownPosition createNewTown(char* townName, int townPopulation) {
	TownPosition town = NULL;
	town = (TownPosition)malloc(sizeof(Town));
	if (!town) {
		printf("Can't allocate memory!\n");
		return FAILED_MEMORY_ALLOCATION;
	}

	strcpy(town->name, townName);
	town->population = townPopulation;
	town->next = NULL;
	town->left = NULL;
	town->right = NULL;

	return town;
}

int insertSortedNewTownList(TownPosition townHeadList, TownPosition newTown) {
	TownPosition townCurrent = townHeadList;
	while (townCurrent->next != NULL && townCurrent->next->population > newTown->population) {
		townCurrent = townCurrent->next;
	}

	insertTownAfter(townCurrent, newTown);

	return EXIT_SUCCESS;
}

int insertTownAfter(TownPosition townCurrent, TownPosition newTown) {
	newTown->next = townCurrent->next;
	townCurrent->next = newTown;

	return EXIT_SUCCESS;
}

TownPosition insertNewTownTree(TownPosition townRootTree, TownPosition newTown) {
	if (townRootTree == NULL)
		return newTown;

	if (newTown->population > townRootTree->population)//dodaj provjeru po imenima naknadno...
		townRootTree->left = insertNewTownTree(townRootTree->left, newTown);
	else if (newTown->population <= townRootTree->population)
		townRootTree->right = insertNewTownTree(townRootTree->right, newTown);

	return townRootTree;
}

int insertSortedNewCountryList(CountryPosition townHeadList, CountryPosition newCountry) {
	CountryPosition countryCurrent = townHeadList;
	while (countryCurrent->next != NULL && strcmp(countryCurrent->next->name, newCountry->name) < 0) {
		countryCurrent = countryCurrent->next;
	}

	insertCountryAfter(countryCurrent, newCountry);

	return EXIT_SUCCESS;
}

int insertCountryAfter(CountryPosition countryCurrent, CountryPosition newCountry) {
	newCountry->next = countryCurrent->next;
	countryCurrent->next = newCountry;

	return EXIT_SUCCESS;
}

CountryPosition insertNewCountryTree(CountryPosition countryRootTree, CountryPosition newCountry) {
	if (countryRootTree == NULL)
		return newCountry;

	if (strcmp(countryRootTree->name, newCountry->name) > 0)
		countryRootTree->left = insertNewCountryTree(countryRootTree->left, newCountry);
	else if (strcmp(countryRootTree->name, newCountry->name) <= 0)
		countryRootTree->right = insertNewCountryTree(countryRootTree->right, newCountry);

	return countryRootTree;
}

int printCountryList(CountryPosition countryHeadList) {
	CountryPosition currentCountry = countryHeadList->next;
	while (currentCountry != NULL) {
		printf("\n%s", currentCountry->name);
		printTownTree(currentCountry->townRootTree);
		currentCountry = currentCountry->next;
	}
}

int printCountryTree(CountryPosition countryRootTree) {
	if (countryRootTree) {
		printCountryTree(countryRootTree->left);
		printf("\n%s", countryRootTree->name);
		printTownList(&countryRootTree->townListHead);
		printCountryTree(countryRootTree->right);
	}
	return EXIT_SUCCESS;
}

int printTownList(TownPosition townHeadList) {
	TownPosition currentTown = townHeadList->next;
	while (currentTown != NULL) {
		printf("\n\t%s %d", currentTown->name, currentTown->population);
		currentTown = currentTown->next;
	}
}

int printTownTree(TownPosition townRootTree) {
	if (townRootTree) {
		printTownTree(townRootTree->left);
		printf("\n\t%s %d", townRootTree->name, townRootTree->population);
		printTownTree(townRootTree->right);
	}
	return EXIT_SUCCESS;
}

int findCountries(CountryPosition countryHeadList, CountryPosition countryRootTree, CountryPosition* countries) {
	CountryPosition countryCurrentList = countryHeadList->next;
	CountryPosition countryCurrentTree = countryRootTree;
	char countryName[MAX_LENGTH] = { 0 };
	printf("\n\nEnter country name: ");
	scanf(" %s", countryName);

	while (countryCurrentList != NULL && strcmp(countryCurrentList->name, countryName)) {
		countryCurrentList = countryCurrentList->next;
	}

	countryCurrentTree = searchCountryTree(countryRootTree, countryName);

	countries[0] = countryCurrentList;
	countries[1] = countryCurrentTree;

	return EXIT_SUCCESS;
}

CountryPosition searchCountryTree(CountryPosition countryRootTree, char* countryName) {
	if (countryRootTree == NULL || strcmp(countryRootTree->name, countryName) == 0)
		return countryRootTree;

	if (strcmp(countryRootTree->name, countryName) > 0)
		return searchCountryTree(countryRootTree->left, countryName);

	return searchCountryTree(countryRootTree->right, countryName);
}