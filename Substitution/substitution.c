#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
   //Validating the correctness of the key
   if(argc != 2)
   {
        printf("Usage: ./substitution key\n");
        return 1;
   }
   else if (strlen(argv[1]) != 26)
   {
        printf("Key must contain 26 characters.\n");
        return 1;
   }
   // validating if all the key is of unique letters
   for (int i = 0; i < strlen(argv[1]); i++)
   {
     for (int  j = i + 1; j < strlen(argv[1]); j++)
     {
          if (argv[1][i] == argv[1][j])
          {
               printf("Key must be unique\n");
               return 1;
          }
     }
   }

   // Make all letters of the key upper
   for(int i = 0; i < strlen(argv[1]); i++)
   {
     if (islower(argv[1][i]))
     {
          argv[1][i] = toupper(argv[1][i]);
     }
   }

   // store letters and validate if exist in alphabet
   char código [26];
   for(int i = 0; i < 26; i++)
   {
     if (argv[1][i] >= 65 && argv[1][i] <= 90)
     {
          código[i] = argv[1][i];
          for (int j = 0; j < i; j++)
          {
               if (código[i] == argv[1][j])
               {
                    printf("Usage: ./substitution key\n");
               }
          }
     }
   }

   //Making the substitution
   string word = get_string("plaintext: ");

   int size = strlen(word);
   char newWord[size + 1];

   for (int i = 0; i < size; i++)
   {
     if (isupper(word[i]))
     {
          newWord[i] = argv[1][word[i] - 'A'];
     }
     else if (islower(word[i]))
     {
          newWord[i] = argv[1][word[i] - 'a'];
          newWord[i] = tolower(newWord[i]);
     }
     else
     {
          newWord[i] = word[i];
     }
   }
   newWord[size] = '\0';

   //printing the substitution
   printf("ciphertext: %s\n", newWord);


   return 0;
}