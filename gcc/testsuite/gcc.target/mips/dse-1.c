/* { dg-mips-options "-mgp64 -O" } */

#define TEST(ID, TYPE1, TYPE2)					\
  union {							\
    TYPE1 m1[sizeof (TYPE2) / sizeof (TYPE1)];			\
    TYPE2 m2;							\
  } u##ID;							\
								\
  /* The MIPS16 versions of the shifts we need are too		\
     expensive.  */						\
  TYPE1 __attribute__((nomips16))				\
  f##ID (TYPE2 x)						\
  {								\
    u##ID.m2 = x;						\
    return (u##ID.m1[0]						\
	    + u##ID.m1[sizeof (TYPE2) / sizeof (TYPE1) - 1]);	\
  }

TEST (1, unsigned int, unsigned long long);
TEST (2, int, long long);
TEST (3, unsigned short, unsigned long long);
TEST (4, short, long long);
TEST (5, unsigned char, unsigned long long);
TEST (6, signed char, long long);

TEST (7, unsigned short, unsigned int);
TEST (8, short, int);
TEST (9, unsigned char, unsigned int);
TEST (10, signed char, int);

/* DSE isn't yet read to consider stores of subregs, so the corresponding
   (char, short) tests won't pass.  */

/* { dg-final { scan-assembler-not "\tlh\t" } } */
/* { dg-final { scan-assembler-not "\tlw\t" } } */
/* { dg-final { scan-assembler-not "\tlb\t" } } */
