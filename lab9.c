// Oma Persaud
// Lab 9
// July 28, 2023

#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
	struct RecordType*  next;
};

// Fill out this structure
struct HashType
{
	struct RecordType* ptr;
};

// Compute the hash function
int hash(int x, int tableSize)
{
	return x % tableSize;
}

// parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData)
{
	FILE *inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}

		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;

            fscanf(inFile, "%d %c %d\n", &pRecord->id, &pRecord->name, &pRecord->order);

            pRecord->next = NULL;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\n%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// Have to put in values and set up list
void insertRecord(struct HashType hashTable[], struct RecordType record, int tableSize)
{
    // hash function to get index
    int index = hash(record.id, tableSize);

    // if index is NULL
    if (hashTable[index].ptr == NULL)
    {
        // set equal to HashType pointer index
        hashTable[index].ptr = &record;
    }

    else

    {
        // go to end of the linkedlist 
        struct RecordType* curr = hashTable[index].ptr;

        while (curr -> next != NULL)
        {
            curr = curr -> next;
        }
        curr -> next = &record;
    }
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType hashTable[], int tableSize)
{
	for (int i = 0; i < tableSize; i++)

	{
		if (hashTable[i].ptr != NULL)
		{
		// if index is occupied with any records, print all	
		printf("Index %d -> ", i);

        struct RecordType* curr = hashTable[i].ptr;

        while (curr != NULL)
			{
			 printf("%d %c %d -> ", curr->id, curr->name, curr->order);
        
			curr = curr->next;
			}
		}
	}	
}	

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);

	// Your hash implementation

	// have to start has table
	int hashTableSize = 10;

	struct HashType* hashTable = (struct HashType*)calloc(hashTableSize, sizeof(struct HashType));

	// add values
	for (int i = 0; i < recordSz; ++i)
	{
		insertRecord(hashTable, *(pRecords + i), hashTableSize);
	}

	// display records
	displayRecordsInHash(hashTable, hashTableSize);

	// Free memory
	free(pRecords);
	free(hashTable);

	return 0;

}