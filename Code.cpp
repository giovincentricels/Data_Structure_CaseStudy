#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct trie trie; 

struct trie{
	char word; 
	int valid; 
	char description[100]; 
	trie* edge[128]; 
}*root = NULL;


trie* Newnode(char w){
	trie* New = (trie*) malloc (sizeof(trie)); 
	New->word = w; 
	New->valid = 0; 
	New->description[0] = '\0'; 
	for(int i = 0; i < 128; i++){
		New->edge[i] = NULL;
	}
	return New;
}

void insert(trie* curr, char* w,char* desc){
	if(*w == '\0') {
        if (curr->valid) {
            strcpy(curr->description, desc);
            puts("");
            printf("Successfully updated a slang word.\n");
        } else {
            curr->valid = 1;
            strcpy(curr->description, desc);
            puts("");
            printf("Successfully released new slang word.\n");
        }
        return;
    }
    if(curr->edge[*w] == NULL) {
        curr->edge[*w] = Newnode(*w);
    }
    insert(curr->edge[*w], w+1, desc);
}

char* search(trie* curr, char* w) {
    if(curr == NULL) return NULL; 
    
    if(*w == '\0') {
        if(curr->valid) {
            return curr->description; 
        } else {
            return NULL; 
        }
    }
    
    if(curr->edge[*w] == NULL) return NULL; 
    
    return search(curr->edge[*w], w+1); 
}

int count; 

void findPrefix(trie* node, char* prefix, int depth) {
	if (node->valid) {
		count++;
        printf("%d. %s\n",count,prefix);
    }

    for (int i = 0; i < 128; i++) {
        if (node->edge[i] != NULL) {
            prefix[depth] = node->edge[i]->word; 
            prefix[depth + 1] = '\0'; 
            findPrefix(node->edge[i], prefix, depth + 1); 
        }
    }
}

int hashwords; 
int main(){
	int choose = 0;
	
	root = Newnode('\0');
	while(choose != 5){
		puts("---------------------------------");
		printf("Welcome to Boogle\n");
		puts("---------------------------------");
		puts("1. Release a new slang word");
		puts("2. Search a slang word");
		puts("3. View all slang words starting with a certain prefix word");
		puts("4. View all slang words");
		puts("5. Exit");
		printf("Choose menu: ");
		scanf("%d",&choose);
		getchar();
		system("cls"); 
		
		if(choose == 1){
			char slangword[50]; 
			char description[100]; 
			int cek = 1; 
			hashwords = 1;
			while(cek){
				printf("Input a new slang word [Must be more than 1 characters abd contains no space]: ");
				scanf("%[^\n]s",slangword);
				getchar();
				for(int i = 0; i < strlen(slangword); i++){
					if(slangword[i] == ' ' || strlen(slangword) == 1){
						cek = 1;
						break;
					}
					else{
						cek = 0;
					}
				}
			}
			cek = 1; 
			while(cek){
				printf("Input a new slang word description [Must be more than 2 words]: ");
				scanf("%[^\n]s",description);
				getchar();
				
				for(int i = 0; i < strlen(description); i++){
					if(description[i] == ' '){
						cek = 0; //memberhentikan perulangan 
					}
				}
			}
			insert(root, slangword, description);
			printf("Press enter to continue...");
			getchar();
			system("cls");
		}
		else if(choose == 2) {
            char searchWord[50];
            int x = 1; 
        	
        	while(x){
	            printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
	            scanf("%s", searchWord);
	            getchar();
	            for(int i = 0; i < strlen(searchWord); i++){
					if(searchWord[i] == ' ' || strlen(searchWord) == 1){
						x = 1; //syarat while
						break;
					}
					else{
						x = 0; //syarat while untuk berhenti
					}
				}
			}
			
			char* foundDesc = search(root, searchWord);
            if(foundDesc != NULL) { 
            	puts("");
                printf("Slang word : %s\n", searchWord);
                printf("Description : %s\n", foundDesc); 
                puts("");
            } else {
           		puts("");
                printf("There is no word \"%s\" in the dictionary.\n", searchWord);
            }
            printf("Press enter to continue...");
            getchar();
            system("cls");
    	}
    	else if(choose == 3) {
    		char prefix[50];
            printf("Input a prefix to be searched: ");
            scanf("%s", prefix);
            getchar();

            int n = strlen(prefix);
            int isLastIndex = 0; 
            trie* curr = root; 

            for (int i = 0; i < n && !isLastIndex; i++) {
                if (curr->edge[prefix[i]] == NULL) {
                    isLastIndex = 1;
                } else {
                    curr = curr->edge[prefix[i]];
                }
            }

            if (!isLastIndex) {
            	puts("");
                printf("Words starts with \"%s\":\n", prefix);
                count = 0;
                findPrefix(curr, prefix, n);
            	puts("");
            } else {
            	puts("");
                printf("There is no prefix \"%s\" in the dictionary.\n", prefix);
            }
            printf("Press enter to continue...");
            getchar();
            system("cls");
		}
		else if (choose == 4) {
		    count = 0;
		    char prefix1[50] = ""; 
		    if(!hashwords){ //
		    	printf("There is no slang word yet in the dictionary.");
			}
			else{
				printf("List of all slang words in the dictionary:\n");
		    	findPrefix(root, prefix1, 0); 
			}
			puts("");
		    printf("Press enter to continue...");
		    getchar();
		    system("cls");
		}
		else if (choose == 5){ //Exit case
			printf("Thank you... Have a nice day :)\n");
		}
		else{
			choose = 0;
		}
	}
	
	return 0;
}
