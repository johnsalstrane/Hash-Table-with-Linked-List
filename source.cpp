// This is to build and understand a hash table with linked lists

#include <stdio.h>
#include <string.h>

#define MAX_NAME 256
#define TABLE_SIZE 10


struct person
{
    char Name[MAX_NAME];
    int Age;
    struct person* next;
};

person* HashTable[TABLE_SIZE];

unsigned int Hash(char* Name)
{
    unsigned int HashValue;
    int length = strnlen(Name, MAX_NAME);
    for (int i = 0; i < length; i++)
    {
        HashValue += Name[i];
        HashValue = (HashValue * Name[i]) % TABLE_SIZE;
    }

    return HashValue;
}

void InitHashTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HashTable[i] = 0;
    }
}

void PrintHashTable()
{
    printf("Table Begin\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (HashTable[i] == NULL)
        {
            printf("\t%i\t----\n", i);
        }
        else
        {
            printf("\t%i\t", i);
            person* temp = HashTable[i];
            while (temp != NULL)
            {
                printf("%s - ", temp->Name);
                temp = temp->next;
            }
            printf("\n");
        }
    }
    printf("Table End\n\n");

}

bool HashTableInsert(person* Person)
{
    if (Person == NULL) return false;

    int index = Hash(Person->Name);

    Person->next = HashTable[index];

    HashTable[index] = Person;

    return true;
}

person* HashTableLookup(char* Name)
{
    int Index = Hash(Name);
    person* temp = HashTable[Index];

    while (temp != NULL &&
        strncmp(temp->Name, Name, MAX_NAME) != 0)
    {
        temp = temp->next;
    }
    return temp;
}

person* HashTableDelete(char* Name)
{
    int Index = Hash(Name);
    person* temp = HashTable[Index];
    person* previous = NULL;
    while (temp != NULL &&
        strncmp(temp->Name, Name, MAX_NAME) == 0)
    {
        previous = temp;
        temp = temp->next;
    }
    if (temp == NULL) return NULL;
    if (previous == NULL)
    {
        // deleting the head
        HashTable[Index] = temp->next;
    }
    return temp;
}

int main()
{
    InitHashTable();
    PrintHashTable();

    person John = { "John", 35 };
    person Suzie = { "Suzie", 27 };
    person Harvey = { "Harvey", 38 };
    person Decker = { "Decker", 45 };
    person Mark = { "Mark", 40 };
    person Al { "Al", 87 };
    person Steven = { "Steven", 20 };
    person BillyBobThorton = { "Billy Bob Thorton", 100 };
    person Cookie = { "Cookie", 37 };
    person SteveJobs = { "Steve Jobs", 48 };
    person Jane = { "Jane", 11 };


    HashTableInsert(&John);
    HashTableInsert(&Suzie);
    HashTableInsert(&Harvey);
    HashTableInsert(&Decker);
    HashTableInsert(&Al);
    HashTableInsert(&Steven);
    HashTableInsert(&BillyBobThorton);
    HashTableInsert(&Cookie);
    HashTableInsert(&SteveJobs);
    HashTableInsert(&Mark);
    HashTableInsert(&Jane);


    PrintHashTable();

    person* temp = HashTableLookup("John");
    if (temp == NULL) printf("Name not found\n");
    else printf("Found %s\n", temp->Name);

    temp = HashTableLookup("Jamie");
    if (temp == NULL) printf("Name not found\n");
    else printf("Found %s\n", temp->Name);

    HashTableDelete("John");

    temp = HashTableLookup("John");
    if (temp == NULL) printf("Name not found\n");
    else printf("Found %s\n", temp->Name);

    return(0);
}