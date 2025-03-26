#include <stdio.h>
#include <cs50.h>

void draw(int h);

int main (void)
{
    int h = get_int("H? ");

    draw(h);
   // printf("Hello, world");
}

void draw(int h)
{
      if (h == 0)
      {
          return;
          //return; not "return0;" because this is in (draw function) that its output is (void)
          //return 0; in the (main function) because (main) output is (int) so there is must be a number output
      }

      draw(h - 1);

      for(int j = 0; j < h; j++)
      {
          printf("#");
      }
      printf("\n");

}