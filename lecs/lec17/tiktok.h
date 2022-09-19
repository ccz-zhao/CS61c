#include <time.h>
#define Tik(x) long start_##x = clock();
#define Tok(x) printf(#x " Done computing in %.3f seconds.\n", (double)(clock()-start_##x) / CLOCKS_PER_SEC);