#ifndef PRELAMDA_LEX_H_H
#define PRELAMDA_LEX_H_H

typedef void (*lex_status_callback)(int line);

void
lex_init(FILE *file);
void
lex_init_with_callback(FILE *file, lex_status_callback callback);

void
lex_start_parse();

#endif //PRELAMDA_LEX_H_H
