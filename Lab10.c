#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    int count;
    struct Trie* children[26];
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie* tmp = pTrie;

    for(int i = 0;i<strlen(word);i++)
    {
        int index = word[i]-'a';
        tmp->children[index] = (struct Trie*)malloc(sizeof(struct Trie));
        tmp = pTrie->children[index];
    }

    tmp->count+=1;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie* tmp = pTrie;

    for(int i = 0;i<strlen(word);i++)
    {
        int index = word[i]-'a';
        tmp = pTrie->children[index];
    }

    return tmp->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    struct Trie* tmp;
    tmp = pTrie;

    for(int i = 0; i < 26; i++)
    {
        tmp=tmp->children[i];
        if(tmp!=NULL)
        {
            for(int j = 0;j<26;j++)
            {
                free(tmp->children[i]->children[j]);
            }
        }
    }

    free(tmp);
    free(pTrie);
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* trie;
    trie = (struct Trie*)malloc(sizeof(struct Trie));

    for(int i = 0;i < 26;i++)
    {
        trie->children[i]=NULL;
        trie->count=0;
    }

    return trie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* file;
    file = fopen(filename,"r");

    if(file == NULL)
    {
        printf("Cannot open file\n");
        return 0;
    }

    int numWords = 0;
    fscanf(file, "%d",numWords);

    for(int i = 0; i < numWords;i++)
    {
        fscanf(file,"%s",pInWords[i]);
    }

    fclose(file);

    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}