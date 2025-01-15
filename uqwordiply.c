#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_LINE_LENGTH 52

/* is_all_numbers()
 * -------------------
 * Checks to see if the inputted string is all numbers.
 *
 * string: pointer to string (char*) that is being checked.
 *
 * Returns: an integer equal to 0 if the string pointed to by the argument is
 *     all numbers and 1 if the string pointed to by the argument contains
 *     a character that isn't a number.
 *
 * REF: The following code, specifically to determine if a character is a 
 * REF: digit, is inspired by the code at
 * REF: https://www.programiz.com/c-programming/library-functions/ctype.h/
 * REF: isdigt#:~:text=Function%20isdigit()%20takes%20a,It%20is%20defined%20in
 * REF: %20%3Cctype.
 */
int is_all_numbers(char* string) {
    int isValid = 0;
    for (int i = 0; i < strlen(string); i++) {
	if (isdigit(string[i]) == 0) {
	    return isValid;
	}
    }
    isValid = 1;
    return isValid;
}

/* valid_command_line_args()
 * ---------------------------
 * Function validates the arguments are in an acceptable format to start the
 *     game.
 *
 * argc: number of arguments in the array which is used to loop.
 * argv: array of the command line strings that we are verifying match the
 *     specified format.
 * 
 * Returns: an integer equal to 0 if the inputted array of strings are not
 *     valid. It is equal to 1 when the array of strings are valid and the
 *     --len argument was not specified. Lastly it equals 3 or 4 when the
 *     array of strings are valid and the --len argument was specifed so that
 *     it matches the number that was inputted to the array.
 *
 * REF: The following code, specifically converting a string to number, is
 * REF: inspired by the code at
 * REF: https://www.educative.io/answers/how-to-convert-a-string-to-an-integer
 * REF: -in-c
 */
int valid_command_line_args(int argc, char** argv) {
    int isValid = 1;
    int startOccurences = 0;
    int lenOccurences = 0;
    int dictionaryOccurences = 0;
    char* startArgument = "--start";
    char* lenArgument = "--len";
    char* dictionaryArgument = "--dictionary";
    // Ensures execution when only filename provided and each key has a
    // matching argument in the array.
    if (argc == 1) {
        return isValid;
    } else if (argc % 2 == 0) {
        isValid = 0;
        return isValid;
    }
    // Loops through array of arguments checking and counting which keys are 
    // there and if len is one of them, its argument is checked and returned 
    // if valid.
    for (int i = 1; i < argc; i += 2) {
	if (strcmp(argv[i], lenArgument) == 0) {
	    if (is_all_numbers(argv[i + 1]) == 0) {
		isValid = 0;
		break;
	    }
	    int lengthOfWord = atoi(argv[i + 1]);
	    lenOccurences++;
	    if (lengthOfWord == 3 || lengthOfWord == 4) {
		isValid = lengthOfWord;
	    } else {
		isValid = 0;
		break;
	    }
	} else if (strcmp(argv[i], startArgument) == 0) {
	    startOccurences++;
	} else if (strcmp(argv[i], dictionaryArgument) == 0) {
	    dictionaryOccurences++;
	} else {
	    isValid = 0;
	    break;
	}
    }
    // Ensures start and len keys aren't present together and each key only
    // exists once.
    if ((startOccurences > 0 && lenOccurences > 0) || startOccurences > 1 || 
	    lenOccurences > 1 || dictionaryOccurences > 1) {
        isValid = 0;
    }
    return isValid;
}

/* is_all_alphabet()
 * ------------------
 * Funciton checks that the inputted string is only characaters A-Z uppercase 
 *     or lowercase
 *
 * word: pointer to string (char*) that is being checked for all letters
 *
 * Returns: an integer equal to 0 if the string pointed to by word has
 *     characters other than letters and 1 if the string pointed to by word
 *     has only letters as characters
 */
int is_all_alphabet(char* word) {
    for (int i = 0; i < strlen(word); i++) {
	if (isalpha(word[i]) == 0) {
	    return 0;
	}
    }
    return 1;
}

/* make_capital()
 * ---------------
 * Function takes two strings and capitalizes the first string into the
 *     second one
 *
 * word: pointer to string (char*) that is to be capitalized
 * capitalizedWord: pointer to string (char*) that will be used to store the
 *     capitalized version of word.
 *
 * Returns: the capitalized version of the argument word which gets stored in 
 *     the capitalizedWord parameter
 * REF: The following code, specifically passing parameter to be returned
 * REF: instead of returning a local variable, is inspired by the code at
 * REF: https://www.educative.io/answers/resolving-the-function-returns-address
 * REF: -of-local-variable-error
 */
char* make_capital(char* word, char* capitalizedWord) {
    for (int i = 0; i < strlen(word); i++) {
	capitalizedWord[i] = toupper(word[i]);
    }
    return capitalizedWord;
}

/* valid_starter_word_check()
 * ---------------------------
 * Function ensures the argument associated with the --start key in the array
 *     only consists of letters and is of length 3 or 4.
 *
 * argc: number of arguments in the array which is used to loop.
 * argv: array of strings that we are verifying have a --start key and 
 *     appropriate string associated with it.
 *
 * Returns: pointer to string which contains the starting word if it is valid,
 *     "NA" (not applicable) if there is no --start key and "NO" if the
 *     inputted starter word is not valid.
 */
char* valid_starter_word_check(int argc, char** argv) {
    char* startKeyword = "--start";
    char* starterWord = "NA";
    for (int i = 1; i < argc; i += 2) {
	// Ensures the --start keyword is in argv then makes sure the argument
	// associated with it is only letters and 3-4 characters long.
	if (strcmp(argv[i], startKeyword) == 0) {
	    if ((strlen(argv[i + 1]) == 3 || strlen(argv[i + 1]) == 4) && 
		    is_all_alphabet(argv[i + 1]) != 0) {
		starterWord = argv[i + 1];
	    } else { 
		starterWord = "NO";
	    }
	    break;
	}
    }
    return starterWord;
}

/* get_index_of_dictionary_file()
 * -------------------------------
 * Function finds the index of the argument associated with the --dictionary
 *     key in the given array
 *
 * 
 * argc: number of arguments in the array which is used to loop.
 * argv: array of strings that we are verifying have a --dictionary key and 
 *     getting its associated argument index.
 *
 * Returns: an integer that is the index of the array that the --dicionary
 *     argument is located. If there is no --dictionary key then -1 is
 *     returned instead.
 */
int get_index_of_dictionary_file(int argc, char** argv) {
    char* dictionaryKeyword = "--dictionary";
    for (int i = 1; i < argc; i += 2) {
	if (strcmp(argv[i], dictionaryKeyword) == 0) {
	    return i + 1;
	}
    }
    return -1;
}

/* print_welcome_message()
 * ------------------------
 * Function prints out the welcome message for the uqwordiply game.
 *
 * starterWord: pointer to string (char*) this is the starter word for the 
 *     game and will be used to give more details in the welcome message
 */
void print_welcome_message(const char* starterWord) {
    printf("Welcome to UQWordiply!\n");
    printf("The starter word is: %s\n", starterWord);
    printf("Enter words containing this word.\n");
}

/* trim_new_line()
 * ----------------
 * Function removes the new line character from a string
 *
 * word: pointer to string (char*) that will have the new line removed from it.
 *     Assumed that the new line is at the end of the string.
 *
 * Returns: a string that has the same value of word but without the new line
 *     character.
 *
 * REF: The following code is inspired by code at
 * REF: https://cboard.cprogramming.com/c-programming/70320-how-remove-newline
 * REF: -string.html
 */
char* trim_new_line(char* word) {
    // Sets pointer to where the new line character is and replaces it with
    // the null character which then terminates the string there.
    char* newLinePointer;
    if ((newLinePointer = strchr(word, '\n')) != NULL) {
	*newLinePointer = '\0';
    }
    return word;
}

/* make_dictionary_array()
 * -----------------------
 * Function checks, manipulates, then copies valid strings from an inputted 
 * file and dynamically allocates them to an array of strings.
 * 
 * dictionary: pointer to a file that holds the strings to be added to the
 *     array.
 * starterWord: pointer to string (char*) that holds the starter word of the
 *     game.
 * dictSize: pointer to an integer that will be set to the number of valid
 *     strings in the dictionary.
 *
 * Returns: an array of strings which hold all the strings from dictionary that
 *     contain only letters, and contain the starterWord.
 *
 * REF: The following block of code is inspired by my CSSE2310 EdPuzzle 2.1
 * REF: last question assignment and code at
 * REF: https://stackoverflow.com/questions/7652293/how-do-i-dynamically-
 * REF: allocate-an-array-of-strings-in-c
 */
char** make_dictionary_array(FILE* dictionary, const char* starterWord, 
	int* dictSize) {
    char** dictArray = NULL;
    char* word;
    char buffer[MAX_LINE_LENGTH];
    int index = 0;
    // Equivalent to while fgets doesn't return NULL which would be the end of
    // the file.
    while ((word = fgets(buffer, sizeof(buffer), dictionary))) {
	// Checks validity and changes each valid string so that it fits the 
	// format for the dictArray.
	word = trim_new_line(word);
	if (is_all_alphabet(word) != 0) {
            word = make_capital(word, word);
	    if (strstr(word, starterWord) != NULL) {
		// Copies current contents of dictArray into a new array with
		// increased memory space so that another string can be added.
		dictArray = realloc(dictArray, sizeof(char*) * (index + 1));
		dictArray[index] = NULL;
		dictArray[index] = malloc(strlen(word) + 1);
		strcpy(dictArray[index], word);
		index++;
	    }
	}
    }
    // The value of the dictSize is set to the index (size of dictionary) so
    // that the variable passed into the function at this parameter can be
    // used outside this function yet still have information from it without
    // it being returned.
    *dictSize = index;
    fclose(dictionary);
    return dictArray;
}

/* is_in_array()
 * --------------
 * Function checks to see if the inputted guess is in the array or not.
 *
 * guess: pointer to string (char*) that is the word we are looking for in the
 *     array.
 * array: array of strings which will be checked to see if it contains guess.
 * arrayLength: number of strings the array.
 *
 * Returns: an integer equal to 0 if the guess is not in the array and an
 *     an integer equal to 1 if the guess is in the array.
 */
int is_in_array(char* guess, char** array, int arrayLength) {
    int index = 0;
    int isValid = 1;
    // Covers special case when the array is empty and as there are no strings
    // in the array the guess can't be in it.
    if (arrayLength == 0) {
	isValid = 0;
	return isValid;
    } else {
        while (index < arrayLength) {
	    if (strcmp(guess, array[index]) == 0) {
	        return isValid;
	    }
	    index++;
        }
    }
    isValid = 0;
    return isValid;
}

/* is_valid_guess()
 * -----------------
 * Function checks to see if the inputted guess is valid. This test for
 * validity includes the string being all letters, it contains the starter 
 * word, its not the starter word, its in the dictionary and it not being
 * previously guessed.
 *
 * guess: pointer to string (char*) that holds the word being checked. Assumed
 *     that the string has no new line and is capitalized.
 * guessedWords: array of strings that holds the previous valid guesses.
 * starterWord: pointer to string (char*) that holds the starting word.
 * dictionary: array of strings that holds the entire list of acceptable 
 *     guesses.
 * numGuesses: integer that represents the number of valid guesses made by the 
 *     user.
 * dictSize: integer that represents the number of strings in the dictionary.
 *
 * Returns: an integer that is 1 if guess consists of all letters, it contains
 * the starter word, it's not the starter word, it's in the dictionary and it
 * hasn't previously been guessed. Otherwise guess is not valid and 0 is the
 * return value.
 */
int is_valid_guess(char* guess, char** guessedWords, const char* starterWord, 
	char** dictionary, int numGuesses, int dictSize) {
    int isValid = 0;
    if (is_all_alphabet(guess) == 0) {
	printf("Guesses must contain only letters - try again.\n");
    } else if (strstr(guess, starterWord) == NULL) {
	printf("Guesses must contain the starter word - try again.\n");
    } else if (strcmp(guess, starterWord) == 0) {
	printf("Guesses can't be the starter word - try again.\n");
    } else if (is_in_array(guess, dictionary, dictSize) == 0) {
	printf("Guess not found in dictionary - try again.\n");
    } else if ((guessedWords != NULL) && 
	    (is_in_array(guess, guessedWords, numGuesses - 1) == 1)) {
	printf("You've already guessed that word - try again.\n");
    } else {
	isValid = 1;
    }
    return isValid;
}

/* prompt_guesses()
 * -----------------
 * Function continuously prompts the user for guesses and dynamically allocates
 * valid guesses from standard input to an array of strings until five guesses 
 * have been made or EOF is detected.
 *
 * starterWord: pointer to string (char*) that holds the starting word.
 * dict: array of strings that holds the entire list of acceptable guesses.
 * numGuessed: pointer to integer (int*) that will be set to the number of
 *     guesses made by the user.
 * dictSize: integer that represents the number of strings in the dictionary.
 *
 * Returns: an array of strings which contain the valid words guessed by the 
 *     user.
 * 
 * REF: The following block of code is inspired by my CSSE2310 EdPuzzle 2.1
 * REF: last question assignment and code at
 * REF: https://stackoverflow.com/questions/7652293/how-do-i-dynamically-
 * REF: allocate-an-array-of-strings-in-c
 */
char** prompt_guesses(const char* starterWord, char** dict, int* numGuessed, 
	int dictSize) {
    int numGuess = 1;
    char** guessedWords = NULL;
    // Continuously reads input by the user from standard input until five
    // guesses have been made or EOF is detected.
    while (numGuess <= 5) {
	char* guess;
	char buffer[MAX_LINE_LENGTH];
	printf("Enter guess %i:\n", numGuess); 
	guess = fgets(buffer, sizeof(buffer), stdin);
	if (guess == NULL) {
	    break;
	}
	// Formats the inputted guess so that it is easily comparable and
	// can be checked for validity.
	guess = trim_new_line(guess);
	guess = make_capital(guess, guess);
	// If the guess is valid then the guess is dynamically allocated and 
	// added to guessedWords array. 
        if (is_valid_guess(guess, guessedWords, starterWord, dict, 
                numGuess, dictSize) == 1) {
	    guessedWords = realloc(guessedWords, sizeof(char*) * numGuess);
	    guessedWords[numGuess - 1] = NULL;
	    guessedWords[numGuess - 1] = malloc(strlen(guess) + 1);
	    strcpy(guessedWords[numGuess - 1], guess);
	    numGuess++;
	}
    }
    // The value of the numGuessed is set to numGuess (minus 1 because the loop
    // adds one extra) so that the variable passed into the function at this 
    // parameter can be used outside this function yet still have information 
    // from it without it being returned.
    *numGuessed = numGuess - 1;
    return guessedWords;
}

/* free_array()
 * --------------
 * Function frees the memory allocated by an array of strings.
 *
 * array: array of strings (char**) that will be freed.
 * arrayLength: integer that holds the number of strings in array.
 */
void free_array(char** array, int arrayLength) {
    // First frees each string then frees the array itself so there are no
    // memory leaks.
    for (int i = 0; i < arrayLength; i++) {
	free(array[i]);
    }
    free(array);
}

/* longest_word()
 * ---------------
 * Function finds the longest string in the inputted array of strings.
 *
 * wordArray: array of strings (char**) that is searched through to find the
 *     longest string in it.
 * numWords: integer that represents the number of strings in wordArray.
 * numLongestWords: pointer to integer (int*) that will be set to the number of
 *     longest words there are.
 *
 * Returns: an array of strings (char**) that contain the longest strings found
 *     in wordArray. There are multiple strings when there are more than one
 *     string with the same length and that length is the longest in the array.
 * 
 * REF: The following block of code is inspired by my CSSE2310 EdPuzzle 2.1
 * REF: last question assignment and code at
 * REF: https://stackoverflow.com/questions/7652293/how-do-i-dynamically-
 * REF: allocate-an-array-of-strings-in-c
 */
char** longest_word(char** wordArray, int numWords, 
	int* numLongestWords) {
    int guessesIndex = 0;
    int longestWordsIndex = 0;
    int maxLength = 0;
    char* maxWord;
    int numMaxWords = 0;
    char** longestWords = NULL;
    while (guessesIndex < numWords) {
	// Compares length of current word in array with the max one so far in
	// the list that has been found. If the current string is longer then
	// that it becomes the new max. If is the same length then it is added
	// to the longestWords array
        if (strlen(wordArray[guessesIndex]) > maxLength) {
	    maxWord = wordArray[guessesIndex];
	    maxLength = strlen(maxWord);
	    // If there is a new longest word then the old pointer to the
	    // previous longest word is freed
	    if (guessesIndex != 0) {
	        free_array(longestWords, numMaxWords);
                longestWords = NULL;
	    }
	    numMaxWords = 1;
	    longestWordsIndex = 0;
	    // Dynamically recreates the array so that it matches the number
	    // of longest words found (only one when this section is run) and
	    // adds that word to this array.
	    longestWords = malloc(sizeof(char*));
	    longestWords[longestWordsIndex] = malloc(
		    strlen(wordArray[guessesIndex]) + 1);
	    strcpy(longestWords[longestWordsIndex], wordArray[guessesIndex]);
	    longestWordsIndex++;
	} else if (strlen(wordArray[guessesIndex]) == maxLength) {
	    // If the current word matches the length of the longest word then
	    // it is added to the array of longest words
	    numMaxWords++;
	    longestWords = realloc(longestWords, 
		    sizeof(char*) * numMaxWords);
	    longestWords[longestWordsIndex] = malloc(
		    strlen(wordArray[guessesIndex]) + 1);
	    strcpy(longestWords[longestWordsIndex], wordArray[guessesIndex]);
	    longestWordsIndex++;
	}
	guessesIndex++;
    }
    // The value of the numLongestWords is set to numMaxWords so that the 
    // variable passed into the function at this parameter can be used outside 
    // this function yet still have information from it
    *numLongestWords = numMaxWords;
    return longestWords;
}

/* num_letters()
 * --------------
 * Function that counts the number of letters in the inputted array of strings.
 *
 * arrayWords: array of strings (char**) that will be looped through to count
 *     the letters of.
 * numWords: integer that represents the number of strings in arrayWords.
 *
 * Returns: an integer that is the number of letters in arrayWords.
 */
int num_letters(char** arrayWords, int numWords) {
    int total = 0;
    for (int i = 0; i < numWords; i++) {
	int j = 0;
	while (arrayWords[i][j] != '\0') {
	    total++;
	    j++;
        }
    }
    return total;
}

/* print_results()
 * ----------------
 * Function prints the final details of the uqwordiply game once it finishes.
 * The prinout includes the total length of words found, the longest word(s)
 * found and the longest word(s) possible. Also frees the memory allocated to
 * the guessed words array of strings and dictionary array of strings.
 *
 * guessedWords: array of strings (char**) that holds the words guessed by
 *     the player throughout the game.
 * numGuesses: integer that holds the number of guesses made by the user
 *     throughout the game.
 * dictArray: array of strings (char**) that holds the list of all possible
 *     guesses that could be made with the starter word and dictionary file.
 * sizeDict: integer that holds the number of strings in dictArray.
 */
void print_results(char** guessedWords, int numGuesses, char** dictArray,
	int sizeDict) {
    int totalLength = num_letters(guessedWords, numGuesses);
    printf("\nTotal length of words found: %i\n", totalLength);
    int numLongestGuessWords;
    char** longestGuessWords = longest_word(guessedWords, numGuesses, 
	    &numLongestGuessWords);
    printf("Longest word(s) found:\n");
    for (int i = 0; i < numLongestGuessWords; i++) {
        printf("%s (%li)\n", longestGuessWords[i], 
		strlen(longestGuessWords[i]));
    }
    int numLongestDictWords;
    char** longestDictWords = longest_word(dictArray, sizeDict, 
	    &numLongestDictWords);
    printf("Longest word(s) possible:\n");
    for (int i = 0; i < numLongestDictWords; i++) {
	printf("%s (%li)\n", longestDictWords[i], strlen(longestDictWords[i]));
    }
    free_array(longestGuessWords, numLongestGuessWords);
    free_array(longestDictWords, numLongestDictWords);
}

/* free_mem()
 * -----------
 * Function frees the memory allocated throughout the program
 *
 * dictArray: array of strings (char**) that holds the list of all possible
 *     guesses that could be made with the starter word and dictionary file.
 * dictSize: integer that holds the number of strings in dictArray.
 * guessedWords: array of strings (char**) that holds the words guessed by the
 *     player throughout the game.
 * numGuesses: integer that holds the number of guesses made by the user
 *     throughout the game.
 */
void free_mem(char** dictArray, int dictSize, char** guessedWords, 
	int numGuesses) {
    free_array(dictArray, dictSize);
    free_array(guessedWords, numGuesses);
}

/* get_wordiply_starter_word()
 * ----------------------------
 * Rudimentary function to get a starter word for the game based on the
 * length provided to the function. This method was originally defined in a
 * given .h file but was developed here to enable the game to work.
 *
 * wordLen: integer that holds the size of the starting word to be used in
 *     the game.
 */
const char* get_wordiply_starter_word(int wordLen) {
    // Arrays of 3 and 4 letter combinations
    static const char* threeLetterCombos[] = {"ism", "ion", "cat", "tac", "arc", "ack", "ite", "ati", "len", "ish"};
    static const char* fourLetterCombos[] = {"ties", "rate", "tion", "ance", "pris", "ling", "nect", "ment", "fied", "prop"};

    // Gets sizes of the arrays
    size_t threeLen = sizeof(threeLetterCombos) / sizeof(threeLetterCombos[0]);
    size_t fourLen = sizeof(fourLetterCombos) / sizeof(fourLetterCombos[0]);

    // Seed the random number generator
    srand((unsigned int)time(NULL));

    // Pick a random string from the specified array based on the input
    if (wordLen == 3) {
        return threeLetterCombos[rand() % threeLen];
    } else if (wordLen == 4) {
        return fourLetterCombos[rand() % fourLen];
    }
}

/* main()
 * -------
 * Main entry point to the program that facilitates the game. First takes in
 * the command lines and ensures they're valid and what arguments they contain.
 * This can be partially known through commandLineOption return value and
 * starterWord. The dictionary to be used is then found and opened (if 
 * possible). Next an array is made of the appropriate dictionary contents
 * and the guessing prompts begin. Lastly the results of the game are printed
 * and the allocated memory is freed
 *
 * argc: integer that holds the number of command line arguments
 * argv: array of strings (char**) that holds the command line arguments as
 *     strings
 *
 * Returns: integer that represents the exit status of the program. Returns
 *     0 when it was a complete and successful run, 1 when there was an error
 *     in the command line arguments, 2 when the starter word is invalid, 3
 *     when the dictionary file can't be opened and 4 when the game ends with
 *     no valid guesses made.
 */
int main(int argc, char** argv) {
    int commandLineOption = valid_command_line_args(argc, argv);
    const char* starterWord;
    if (commandLineOption == 0) {
	fprintf(stderr, "Usage: uqwordiply [--start starter-word | "
		"--len length] [--dictionary filename]\n");
	return 1;
    } else if (commandLineOption == 3 || commandLineOption == 4) {
	starterWord = get_wordiply_starter_word(commandLineOption);
    } else {
	char* errorWord = "NO";
	char* naWord = "NA";
	char* checkWord = valid_starter_word_check(argc, argv);
	if (strcmp(checkWord, errorWord) == 0) {
	    fprintf(stderr, "uqwordiply: invalid starter word\n");
	    return 2;
        } else if (strcmp(checkWord, naWord) == 0) {
	    starterWord = get_wordiply_starter_word(0);
	} else {
	    starterWord = make_capital(checkWord, checkWord);
	}
    }
    int dictionaryIndex = get_index_of_dictionary_file(argc, argv);
    FILE* dictionary;
    if (dictionaryIndex == -1) {
	dictionary = fopen("./dictionary.txt", "r");
    } else {
	dictionary = fopen(argv[dictionaryIndex], "r");
	if (dictionary == 0) {
	    fprintf(stderr, 
		    "uqwordiply: dictionary file \"%s\" cannot be opened\n", 
		    argv[dictionaryIndex]);
	    return 3;
	}
    }
    print_welcome_message(starterWord);
    char** dictArray;
    int sizeDict, numGuesses;
    dictArray = make_dictionary_array(dictionary, starterWord, &sizeDict);
    char** guessedWords;
    guessedWords = prompt_guesses(starterWord, dictArray, &numGuesses, 
	    sizeDict);
    if (numGuesses == 0) {
	free_mem(dictArray, sizeDict, guessedWords, numGuesses);
	return 4;
    }
    print_results(guessedWords, numGuesses, dictArray, sizeDict);
    free_mem(dictArray, sizeDict, guessedWords, numGuesses);
    return 0;
}

