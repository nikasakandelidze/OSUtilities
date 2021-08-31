#ifndef TOKENIZER_HEADER
#define TOKENIZER_H


typedef struct tokens {
    char **tokens;
    int alloc_len; //allocated length
    int log_len; //logical length
} tokens;

// Api detail: line shouldnt contain word bigger than 4096 bytes(characters)
struct tokens *tokenize(char *line);

size_t get_number_of_tokens(struct tokens *tokens);

char *get_nth_token(size_t n, struct tokens *tokens);

void destroy_tokens(struct tokens *tokens);

#endif
